// Display.cpp
// Display management class implementation

#include "Display.h"

Display::Display(Adafruit_ILI9341* display) : tft(display) {}

void Display::begin() {
  tft->begin();
  tft->setRotation(1);
  clear();
}

void Display::clear(uint16_t color) {
  tft->fillScreen(color);
}

void Display::drawText(int16_t x, int16_t y, String text, uint16_t color, uint8_t size) {
  tft->setCursor(x, y);
  tft->setTextColor(color);
  tft->setTextSize(size);
  tft->print(text);
}

void Display::drawButton(int16_t x, int16_t y, uint16_t w, uint16_t h, String text, uint16_t bgColor, uint16_t textColor) {
  // Draw button background
  fillRect(x, y, w, h, bgColor);
  
  // Draw button border
  drawRect(x, y, w, h, ILI9341_WHITE);
  
  // Calculate text position for centering
  int16_t textWidth = text.length() * 6; // Approximate width per character
  int16_t textX = x + (w - textWidth * 2) / 2;
  int16_t textY = y + (h - 16) / 2; // 16 is approximate height for size 2 text
  
  // Draw button text
  drawText(textX, textY, text, textColor, 2);
}

void Display::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  tft->drawLine(x0, y0, x1, y1, color);
}

void Display::drawRect(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color) {
  tft->drawRect(x, y, w, h, color);
}

void Display::fillRect(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color) {
  tft->fillRect(x, y, w, h, color);
}

void Display::drawCircle(int16_t x, int16_t y, int16_t r, uint16_t color) {
  tft->drawCircle(x, y, r, color);
}

void Display::fillCircle(int16_t x, int16_t y, int16_t r, uint16_t color) {
  tft->fillCircle(x, y, r, color);
}

void Display::drawWaveformPoint(int16_t x, int16_t y, uint16_t color) {
  tft->drawPixel(x, y, color);
  // Draw a slightly thicker line for better visibility
  tft->drawPixel(x, y+1, color);
}

void Display::drawTitle(String title, uint16_t color) {
  drawCenteredText(20, title, color, 3);
}

void Display::drawCenteredText(int16_t y, String text, uint16_t color, uint8_t size) {
  int16_t textWidth = text.length() * 6 * size;
  int16_t x = (SCREEN_WIDTH - textWidth) / 2;
  drawText(x, y, text, color, size);
}

void Display::fillScreen(uint16_t color) {
  tft->fillScreen(color);
}