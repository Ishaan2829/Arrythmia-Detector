// Display.h
// Display management class header

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_ILI9341.h>
#include "Config.h"

class Display {
private:
  Adafruit_ILI9341* tft;
  
public:
  Display(Adafruit_ILI9341* display);
  void begin();
  void clear(uint16_t color = ILI9341_BLACK);
  void drawText(int16_t x, int16_t y, String text, uint16_t color, uint8_t size);
  void drawButton(int16_t x, int16_t y, uint16_t w, uint16_t h, String text, uint16_t bgColor, uint16_t textColor = ILI9341_WHITE);
  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  void drawRect(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color);
  void fillRect(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color);
  void drawCircle(int16_t x, int16_t y, int16_t r, uint16_t color);
  void fillCircle(int16_t x, int16_t y, int16_t r, uint16_t color);
  void drawWaveformPoint(int16_t x, int16_t y, uint16_t color);
  void drawTitle(String title, uint16_t color = ILI9341_WHITE);
  void drawCenteredText(int16_t y, String text, uint16_t color, uint8_t size);
  void fillScreen(uint16_t color);
};

#endif // DISPLAY_H