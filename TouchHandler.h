// TouchHandler.h
// Touch input handling class header

#ifndef TOUCH_HANDLER_H
#define TOUCH_HANDLER_H

#include <XPT2046_Touchscreen.h>
#include <Adafruit_ILI9341.h>
#include "Config.h"

struct TouchPoint {
  int16_t x;
  int16_t y;
  bool touched;
};

class TouchHandler {
private:
  XPT2046_Touchscreen* ts;
  Adafruit_ILI9341* tft;
  unsigned long lastTouchTime;
  static const unsigned long DEBOUNCE_TIME = 200; // ms
  
public:
  TouchHandler(XPT2046_Touchscreen* touchscreen, Adafruit_ILI9341* display);
  TouchPoint getTouch();
  bool isButtonPressed(TouchPoint touch, int16_t bx, int16_t by, uint16_t bw, uint16_t bh);
  void calibratePoint(int16_t &x, int16_t &y);
  void runCalibration(Adafruit_ILI9341* display); // New calibration method
  void printRawTouch(); // For debugging
};

#endif // TOUCH_HANDLER_H
