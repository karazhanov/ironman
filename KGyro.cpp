#include "KGyro.h"

KGyro::KGyro(uint8_t i2cAddress = MPU6050_I2C_ADDRESS) {
  this->i2cAddress = i2cAddress;
}

void KGyro::init() {
  // Initialize the 'Wire' class for the  I2C-bus.
  Wire.begin();
  int error;
  uint8_t c;
  // default at power-up:
  //    Gyro at 250 degrees second
  //    Acceleration at 2g
  //    Clock source at internal 8MHz
  //    The device is in sleep mode.
  error = MPU6050_read (MPU6050_WHO_AM_I, &c, 1);
  #ifdef DEGUB_MODE
    Serial.print(F("WHO_AM_I : "));
    Serial.print(c,HEX);
    Serial.print(F(", error = "));
    Serial.println(error,DEC);
  #endif
  // According to the datasheet, the 'sleep' bit
  // should read a '1'. But I read a '0'.
  // That bit has to be cleared, since the sensor
  // is in sleep mode at power-up. Even if the
  // bit reads '0'.
  error = MPU6050_read (MPU6050_PWR_MGMT_2, &c, 1);
  #ifdef DEGUB_MODE
    Serial.print(F("PWR_MGMT_2 : "));
    Serial.print(c,HEX);
    Serial.print(F(", error = "));
    Serial.println(error,DEC);
  #endif
  // Clear the 'sleep' bit to start the sensor.
  MPU6050_write_reg (MPU6050_PWR_MGMT_1, 0);
  //Initialize the angles
  calibrate_sensors();
  set_last_read_angle_data(millis(), 0, 0, 0, 0, 0, 0);
}

void KGyro::checkState() {
  int error;
  double dT;
  accel_t_gyro_union accel_t_gyro;
  // Read the raw values.
  error = read_gyro_accel_vals((uint8_t*) &accel_t_gyro);
  // Get the time of reading for rotation computations
  unsigned long t_now = millis();
  // Convert gyro values to degrees/sec
  float gyro_x = (accel_t_gyro.value.x_gyro - base_x_gyro)/FS_SEL;
  float gyro_y = (accel_t_gyro.value.y_gyro - base_y_gyro)/FS_SEL;
  float gyro_z = (accel_t_gyro.value.z_gyro - base_z_gyro)/FS_SEL;
  // Get raw acceleration values
  //float G_CONVERT = 16384;
  float accel_x = accel_t_gyro.value.x_accel;
  float accel_y = accel_t_gyro.value.y_accel;
  float accel_z = accel_t_gyro.value.z_accel;
  // Get angle values from accelerometer
    //  float accel_vector_length = sqrt(pow(accel_x,2) + pow(accel_y,2) + pow(accel_z,2));
  float accel_angle_y = atan(-1*accel_x/sqrt(pow(accel_y,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;
  float accel_angle_x = atan(accel_y/sqrt(pow(accel_x,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;
  float accel_angle_z = 0;
  // Compute the (filtered) gyro angles
  float dt =(t_now - get_last_time())/1000.0;
  float gyro_angle_x = gyro_x*dt + get_last_x_angle();
  float gyro_angle_y = gyro_y*dt + get_last_y_angle();
  float gyro_angle_z = gyro_z*dt + get_last_z_angle();
  // Compute the drifting gyro angles
  unfiltered_gyro_angle_x = gyro_x*dt + get_last_gyro_x_angle();
  unfiltered_gyro_angle_y = gyro_y*dt + get_last_gyro_y_angle();
  unfiltered_gyro_angle_z = gyro_z*dt + get_last_gyro_z_angle();
  // Apply the complementary filter to figure out the change in angle - choice of alpha is
  // estimated now.  Alpha depends on the sampling rate...
  float alpha = 0.95;
  float angle_x = alpha*gyro_angle_x + (1.0 - alpha)*accel_angle_x;
  float angle_y = alpha*gyro_angle_y + (1.0 - alpha)*accel_angle_y;
  float angle_z = gyro_angle_z;  //Accelerometer doesn't give z-angle
  // Update the saved data with the latest values
  set_last_read_angle_data(t_now, angle_x, angle_y, angle_z, unfiltered_gyro_angle_x, unfiltered_gyro_angle_y, unfiltered_gyro_angle_z);
}

float KGyro::getX() {
  return unfiltered_gyro_angle_x;
}

float KGyro::getY() {
  return unfiltered_gyro_angle_y;
}

float KGyro::getZ() {
  return unfiltered_gyro_angle_z;
}
