//#define DEGUB_MODE

inline void print(char* s) {
  #ifdef DEGUB_MODE
    Serial.print(s);
  #endif
}
inline void println(char* s) {
  #ifdef DEGUB_MODE
    Serial.println(s);
  #endif
}
inline void print(__FlashStringHelper* s) {
  #ifdef DEGUB_MODE
    Serial.print(s);
  #endif
}
inline void print(float f, int k) {
  #ifdef DEGUB_MODE
    Serial.print(f, k);
  #endif
}
