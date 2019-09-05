#ifndef __MY_GYRO_H__
  #define __MY_GYRO_H__
// MPU-6050 Accelerometer + Gyro
// -----------------------------
//
// By arduino.cc user "Krodal".
// June 2012
// Open Source / Public Domain
//
// Using Arduino 1.0.1
// It will not work with an older version,
// since Wire.endTransmission() uses a parameter
// to hold or release the I2C bus.
//
// Documentation:
// - The InvenSense documents:
//   - "MPU-6000 and MPU-6050 Product Specification",
//     PS-MPU-6000A.pdf
//   - "MPU-6000 and MPU-6050 Register Map and Descriptions",
//     RM-MPU-6000A.pdf or RS-MPU-6000A.pdf
//   - "MPU-6000/MPU-6050 9-Axis Evaluation Board User Guide"
//     AN-MPU-6000EVB.pdf
//
// The accuracy is 16-bits.
//
// Temperature sensor from -40 to +85 degrees Celsius
//   340 per degrees, -512 at 35 degrees.
//
// At power-up, all registers are zero, except these two:
//      Register 0x6B (PWR_MGMT_2) = 0x40  (I read zero).
//      Register 0x75 (WHO_AM_I)   = 0x68.
//
#include <Wire.h>
#include "Arduino.h"
#include "MPU_GYRO_DEFINES.h"
// Declaring an union for the registers and the axis values.
// The byte order does not match the byte order of
// the compiler and AVR chip.
// The AVR chip (on the Arduino board) has the Low Byte
// at the lower address.
// But the MPU-6050 has a different order: High Byte at
// lower address, so that has to be corrected.
// The register part "reg" is only used internally,
// and are swapped in code.
typedef union accel_t_gyro_union
{
  struct
  {
    uint8_t x_accel_h;
    uint8_t x_accel_l;
    uint8_t y_accel_h;
    uint8_t y_accel_l;
    uint8_t z_accel_h;
    uint8_t z_accel_l;
    uint8_t t_h;
    uint8_t t_l;
    uint8_t x_gyro_h;
    uint8_t x_gyro_l;
    uint8_t y_gyro_h;
    uint8_t y_gyro_l;
    uint8_t z_gyro_h;
    uint8_t z_gyro_l;
  } reg;
  struct
  {
    int x_accel;
    int y_accel;
    int z_accel;
    int temperature;
    int x_gyro;
    int y_gyro;
    int z_gyro;
  } value;
};

#define RADIANS_TO_DEGREES 180/3.14159
#define FS_SEL 131

class KGyro {
  private:
    uint8_t i2cAddress;
    // Use the following global variables and access functions to help store the overall
    // rotation angle of the sensor
    unsigned long last_read_time;
    float         last_x_angle;  // These are the filtered angles
    float         last_y_angle;
    float         last_z_angle;
    float         last_gyro_x_angle;  // Store the gyro angles to compare drift
    float         last_gyro_y_angle;
    float         last_gyro_z_angle;

    //  Use the following global variables and access functions
    //  to calibrate the acceleration sensor
    float    base_x_accel;
    float    base_y_accel;
    float    base_z_accel;
    float    base_x_gyro;
    float    base_y_gyro;
    float    base_z_gyro;

    float unfiltered_gyro_angle_x;
    float unfiltered_gyro_angle_y;
    float unfiltered_gyro_angle_z;

    float angle_x;
    float angle_y;
    float angle_z;

    inline unsigned long get_last_time() {return last_read_time;}
    inline float get_last_x_angle() {return last_x_angle;}
    inline float get_last_y_angle() {return last_y_angle;}
    inline float get_last_z_angle() {return last_z_angle;}
    inline float get_last_gyro_x_angle() {return last_gyro_x_angle;}
    inline float get_last_gyro_y_angle() {return last_gyro_y_angle;}
    inline float get_last_gyro_z_angle() {return last_gyro_z_angle;}

    void set_last_read_angle_data(unsigned long time, float x, float y, float z, float x_gyro, float y_gyro, float z_gyro) {
      last_read_time = time;
      last_x_angle = x;
      last_y_angle = y;
      last_z_angle = z;
      last_gyro_x_angle = x_gyro;
      last_gyro_y_angle = y_gyro;
      last_gyro_z_angle = z_gyro;
    }
    int read_gyro_accel_vals(uint8_t* accel_t_gyro_ptr) {
      // Read the raw values.
      // Read 14 bytes at once,
      // containing acceleration, temperature and gyro.
      // With the default settings of the MPU-6050,
      // there is no filter enabled, and the values
      // are not very stable.  Returns the error value
      accel_t_gyro_union* accel_t_gyro = (accel_t_gyro_union *) accel_t_gyro_ptr;
      int error = MPU6050_read (MPU6050_ACCEL_XOUT_H, (uint8_t *) accel_t_gyro, sizeof(*accel_t_gyro));
      // Swap all high and low bytes.
      // After this, the registers values are swapped,
      // so the structure name like x_accel_l does no
      // longer contain the lower byte.
      uint8_t swap;
      #define SWAP(x,y) swap = x; x = y; y = swap
      SWAP ((*accel_t_gyro).reg.x_accel_h, (*accel_t_gyro).reg.x_accel_l);
      SWAP ((*accel_t_gyro).reg.y_accel_h, (*accel_t_gyro).reg.y_accel_l);
      SWAP ((*accel_t_gyro).reg.z_accel_h, (*accel_t_gyro).reg.z_accel_l);
      SWAP ((*accel_t_gyro).reg.t_h, (*accel_t_gyro).reg.t_l);
      SWAP ((*accel_t_gyro).reg.x_gyro_h, (*accel_t_gyro).reg.x_gyro_l);
      SWAP ((*accel_t_gyro).reg.y_gyro_h, (*accel_t_gyro).reg.y_gyro_l);
      SWAP ((*accel_t_gyro).reg.z_gyro_h, (*accel_t_gyro).reg.z_gyro_l);
      return error;
    }
    // The sensor should be motionless on a horizontal surface
    //  while calibration is happening
    void calibrate_sensors() {
      int                   num_readings = 10;
      float                 x_accel = 0;
      float                 y_accel = 0;
      float                 z_accel = 0;
      float                 x_gyro = 0;
      float                 y_gyro = 0;
      float                 z_gyro = 0;
      accel_t_gyro_union    accel_t_gyro;
      #ifdef DEGUB_MODE
        Serial.println("Starting Calibration");
      #endif
      // Discard the first set of values read from the IMU
      read_gyro_accel_vals((uint8_t *) &accel_t_gyro);
      // Read and average the raw values from the IMU
      for (int i = 0; i < num_readings; i++) {
        read_gyro_accel_vals((uint8_t *) &accel_t_gyro);
        x_accel += accel_t_gyro.value.x_accel;
        y_accel += accel_t_gyro.value.y_accel;
        z_accel += accel_t_gyro.value.z_accel;
        x_gyro += accel_t_gyro.value.x_gyro;
        y_gyro += accel_t_gyro.value.y_gyro;
        z_gyro += accel_t_gyro.value.z_gyro;
        delay(100);
      }
      x_accel /= num_readings;
      y_accel /= num_readings;
      z_accel /= num_readings;
      x_gyro /= num_readings;
      y_gyro /= num_readings;
      z_gyro /= num_readings;
      // Store the raw calibration values globally
      base_x_accel = x_accel;
      base_y_accel = y_accel;
      base_z_accel = z_accel;
      base_x_gyro = x_gyro;
      base_y_gyro = y_gyro;
      base_z_gyro = z_gyro;
      #ifdef DEGUB_MODE
        Serial.println("Finishing Calibration");
      #endif
    }
    // --------------------------------------------------------
    // MPU6050_read
    // This is a common function to read multiple bytes
    // from an I2C device.
    // It uses the boolean parameter for Wire.endTransMission()
    // to be able to hold or release the I2C-bus.
    // This is implemented in Arduino 1.0.1.
    // Only this function is used to read.
    // There is no function for a single byte.
    //
    int MPU6050_read(int start, uint8_t *buffer, int size) {
      int i, n, error;
      Wire.beginTransmission(i2cAddress);
      n = Wire.write(start);
      if (n != 1)
        return (-10);
      n = Wire.endTransmission(false);    // hold the I2C-bus
      if (n != 0)
        return (n);
      // Third parameter is true: relase I2C-bus after data is read.
      Wire.requestFrom(i2cAddress, size, true);
      i = 0;
      while(Wire.available() && i<size) {
        buffer[i++]=Wire.read();
      }
      if ( i != size)
        return (-11);
      return (0);  // return : no error
    }
    // --------------------------------------------------------
    // MPU6050_write
    //
    // This is a common function to write multiple bytes to an I2C device.
    //
    // If only a single register is written,
    // use the function MPU_6050_write_reg().
    //
    // Parameters:
    //   start : Start address, use a define for the register
    //   pData : A pointer to the data to write.
    //   size  : The number of bytes to write.
    //
    // If only a single register is written, a pointer
    // to the data has to be used, and the size is
    // a single byte:
    //   int data = 0;        // the data to write
    //   MPU6050_write (MPU6050_PWR_MGMT_1, &c, 1);
    //
    int MPU6050_write(int start, const uint8_t *pData, int size) {
      int n, error;
      Wire.beginTransmission(i2cAddress);
      n = Wire.write(start);        // write the start address
      if (n != 1)
        return (-20);
      n = Wire.write(pData, size);  // write data bytes
      if (n != size)
        return (-21);
      error = Wire.endTransmission(true); // release the I2C-bus
      if (error != 0)
        return (error);
      return (0);         // return : no error
    }
    // --------------------------------------------------------
    // MPU6050_write_reg
    // An extra function to write a single register.
    // It is just a wrapper around the MPU_6050_write()
    // function, and it is only a convenient function
    // to make it easier to write a single register.
    //
    int MPU6050_write_reg(int reg, uint8_t data) {
      int error;
      error = MPU6050_write(reg, &data, 1);
      return (error);
    }
  public:
    KGyro(uint8_t i2cAddress = MPU6050_I2C_ADDRESS);
    void init();
    void checkState();
    float getX();
    float getY();
    float getZ();
};

#endif
