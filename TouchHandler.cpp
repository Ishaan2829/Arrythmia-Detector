// TouchHandler.cpp
// Touch input handling class implementation

#include "TouchHandler.h"

#define TOUCH_X_MIN 598
#define TOUCH_X_MAX 3699
#define TOUCH_Y_MIN 305
#define TOUCH_Y_MAX 3718
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define DEBOUNCE_TIME 100

TouchHandler::TouchHandler(XPT2046_Touchscreen* touchscreen, Adafruit_ILI9341* display) : 
  ts(touchscreen), 
  tft(display),
  lastTouchTime(0) {}

TouchPoint TouchHandler::getTouch() {
  TouchPoint point;
  point.touched = false;
  point.x = 0;
  point.y = 0;
  
  // Check for touch with debouncing
  if (ts->touched() && (millis() - lastTouchTime > DEBOUNCE_TIME)) {
    TS_Point p = ts->getPoint();
    
    // Debug output - raw touch values
    Serial.print("Raw touch: X=");
    Serial.print(p.x);
    Serial.print(", Y=");
    Serial.print(p.y);
    Serial.print(", Z=");
    Serial.println(p.z);
    
    
    int x = map(p.x, TOUCH_X_MAX, TOUCH_X_MIN, 0, SCREEN_WIDTH);
    int y = map(p.y, TOUCH_Y_MAX, TOUCH_Y_MIN, 0, SCREEN_HEIGHT);

    x = constrain(x, 0, SCREEN_WIDTH - 1);
    y = constrain(y, 0, SCREEN_HEIGHT - 1);

    Serial.print("Raw: X=");
    Serial.print(p.x);
    Serial.print(", Y=");
    Serial.print(p.y);
    Serial.print(" -> Mapped: X=");
    Serial.print(x);
    Serial.print(", Y=");
    Serial.println(y);

    point.x = x;
    point.y = y;
    point.touched = true;
    lastTouchTime = millis();
    
    // Debug output - mapped values
    Serial.print("Mapped to: X=");
    Serial.print(point.x);
    Serial.print(", Y=");
    Serial.print(point.y);
    
    // Calibrate if needed
    //calibratePoint(point.x, point.y);
    
    // Debug output - final calibrated values
    Serial.print(" -> Final: X=");
    Serial.print(point.x);
    Serial.print(", Y=");
    Serial.println(point.y);
    
    point.touched = true;
    lastTouchTime = millis();
  }
  
  return point;
}

bool TouchHandler::isButtonPressed(TouchPoint touch, int16_t bx, int16_t by, uint16_t bw, uint16_t bh) {
  if (!touch.touched) return false;
  
  // Add a small margin for easier button pressing
  int16_t margin = 5;
  
  bool pressed = (touch.x >= (bx - margin) && touch.x <= (bx + bw + margin) &&
                  touch.y >= (by - margin) && touch.y <= (by + bh + margin));
  
  if (pressed) {
    Serial.print("Button pressed at (");
    Serial.print(touch.x);
    Serial.print(", ");
    Serial.print(touch.y);
    Serial.print(") - Button area: (");
    Serial.print(bx);
    Serial.print(", ");
    Serial.print(by);
    Serial.print(", ");
    Serial.print(bw);
    Serial.print(", ");
    Serial.print(bh);
    Serial.println(")");
  }
  
  return pressed;
}

void TouchHandler::calibratePoint(int16_t &x, int16_t &y) {
  // Apply any necessary calibration adjustments
  // These values may need to be adjusted based on your specific display
  
  // Ensure values are within screen bounds
  if (x < 0) x = 0;
  if (x >= SCREEN_WIDTH) x = SCREEN_WIDTH - 1;
  if (y < 0) y = 0;
  if (y >= SCREEN_HEIGHT) y = SCREEN_HEIGHT - 1;
}

void TouchHandler::runCalibration(Adafruit_ILI9341* display) {
  Serial.println("=== Touch Calibration Mode ===");
  Serial.println("Touch the corners of the screen when prompted");
  Serial.println("Send any character via Serial to start...");
  
  // Wait for serial input
  while (!Serial.available()) {
    delay(100);
  }
  Serial.read(); // Clear the buffer
  
  display->fillScreen(ILI9341_BLACK);
  display->setTextColor(ILI9341_WHITE);
  display->setTextSize(2);
  
  // Calibration points (corners and center)
  struct CalPoint {
    int16_t x, y;
    const char* name;
  };
  
  CalPoint points[] = {
    {10, 10, "TOP-LEFT"},
    {SCREEN_WIDTH-10, 10, "TOP-RIGHT"},
    {SCREEN_WIDTH-10, SCREEN_HEIGHT-10, "BOTTOM-RIGHT"},
    {10, SCREEN_HEIGHT-10, "BOTTOM-LEFT"},
    {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, "CENTER"}
  };
  
  for (int i = 0; i < 5; i++) {
    display->fillScreen(ILI9341_BLACK);
    display->setCursor(20, 50);
    display->print("Touch:");
    display->setCursor(20, 80);
    display->print(points[i].name);
    
    // Draw crosshair
    display->drawLine(points[i].x-10, points[i].y, points[i].x+10, points[i].y, ILI9341_RED);
    display->drawLine(points[i].x, points[i].y-10, points[i].x, points[i].y+10, ILI9341_RED);
    display->fillCircle(points[i].x, points[i].y, 3, ILI9341_RED);
    
    // Wait for touch
    Serial.print("Touch ");
    Serial.print(points[i].name);
    Serial.println(" corner...");
    
    bool touched = false;
    while (!touched) {
      if (ts->touched()) {
        TS_Point p = ts->getPoint();
        Serial.print("Raw values - X: ");
        Serial.print(p.x);
        Serial.print(", Y: ");
        Serial.print(p.y);
        Serial.print(", Z: ");
        Serial.println(p.z);
        
        touched = true;
        delay(500); // Debounce
      }
      delay(50);
    }
  }
  
  display->fillScreen(ILI9341_BLACK);
  display->setCursor(20, 100);
  display->print("Calibration");
  display->setCursor(20, 130);
  display->print("Complete!");
  
  Serial.println("=== Calibration Complete ===");
  Serial.println("Update your Config.h with the raw values shown above");
  delay(2000);
}

void TouchHandler::printRawTouch() {
  if (ts->touched()) {
    TS_Point p = ts->getPoint();
    Serial.print("Raw Touch - X: ");
    Serial.print(p.x);
    Serial.print(", Y: ");
    Serial.print(p.y);
    Serial.print(", Pressure: ");
    Serial.println(p.z);
  }
}