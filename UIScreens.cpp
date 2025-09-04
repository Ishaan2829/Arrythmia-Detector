// UIScreens.cpp
#include "UIScreens.h"

UIScreens::UIScreens(Display* d, TouchHandler* t, HeartMonitor* h) {
  display = d;
  touchHandler = t;
  heartMonitor = h;
}

void UIScreens::showTitleScreen() {
  display->clear(ILI9341_BLACK);
  
  display->drawCenteredText(40, "Arrhythmia", ILI9341_CYAN, 3);
  display->drawCenteredText(80, "Detector", ILI9341_CYAN, 3);
  display->drawCenteredText(120, "by Suhana & Simran", ILI9341_WHITE, 1);
  
  int heart[7][8] = {
    {0,1,1,0,0,1,1,0},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,0},
    {0,0,1,1,1,1,0,0},
    {0,0,0,1,1,0,0,0}
  };
  
  int startX = 88; 
  int startY = 150; 
  int pixelSize = 6; 
  
  for(int row = 0; row < 7; row++) {
    for(int col = 0; col < 8; col++) {
      if(heart[row][col] == 1) {
        display->fillRect(startX + col * pixelSize, startY + row * pixelSize, 
                         pixelSize, pixelSize, ILI9341_CYAN);
      }
    }
  }
  
  display->drawButton(45, 220, 150, 40, "Continue", ILI9341_CYAN, ILI9341_BLACK);
}

void UIScreens::showMenuScreen() {
  display->clear(ILI9341_BLACK);
  
  // Title
  display->drawCenteredText(30, "Main Menu", ILI9341_CYAN, 2);
  
  // Menu buttons
  display->drawButton(60, 70, 200, 40, "Heart Rate Monitor", ILI9341_BLUE, ILI9341_WHITE);
  display->drawButton(60, 120, 200, 40, "Arrhythmia Detection", ILI9341_MAGENTA, ILI9341_WHITE);
  display->drawButton(60, 170, 200, 40, "About", ILI9341_YELLOW, ILI9341_BLACK);
  
  // Back button
  display->drawButton(120, 240, 80, 30, "Back", ILI9341_RED, ILI9341_WHITE);
  
  // Status indicator
  display->drawText(10, 280, "System Ready", ILI9341_GREEN, 1);
}

void UIScreens::showHeartRateScreen() {
  display->clear(ILI9341_BLACK);
  
  // Title
  display->drawCenteredText(10, "Heart Rate Monitor", ILI9341_CYAN, 2);
  
  // Current BPM display area
  display->drawRect(10, 35, 300, 30, ILI9341_WHITE);
  display->drawText(15, 45, "BPM: --", ILI9341_WHITE, 2);
  
  // Waveform area border
  display->drawRect(10, 70, 300, 120, ILI9341_WHITE);
  display->drawText(15, 75, "ECG Waveform", ILI9341_WHITE, 1);
  
  // Grid lines for waveform
  for (int i = 20; i < 300; i += 30) {
    display->drawLine(i, 85, i, 185, ILI9341_DARKGREY);
  }
  for (int i = 95; i < 185; i += 20) {
    display->drawLine(15, i, 305, i, ILI9341_DARKGREY);
  }
  
  // Status area
  display->drawText(10, 200, "Monitoring... 10s", ILI9341_YELLOW, 1);
  
  // Back button
  display->drawButton(120, 240, 80, 30, "Back", ILI9341_RED, ILI9341_WHITE);
}

void UIScreens::showArrhythmiaScreen() {
  display->clear(ILI9341_BLACK);
  
  // Title
  display->drawCenteredText(10, "Arrhythmia Detection", ILI9341_CYAN, 2);
  
  // Current BPM display area
  display->drawRect(10, 35, 300, 30, ILI9341_WHITE);
  display->drawText(15, 45, "BPM: --", ILI9341_WHITE, 2);
  
  // Classification area
  display->drawRect(10, 70, 300, 50, ILI9341_WHITE);
  display->drawText(15, 80, "Classification:", ILI9341_WHITE, 1);
  display->drawText(15, 95, "Analyzing...", ILI9341_YELLOW, 2);
  
  // Waveform area (smaller)
  display->drawRect(10, 125, 300, 80, ILI9341_WHITE);
  display->drawText(15, 130, "ECG Signal", ILI9341_WHITE, 1);
  
  // Status area
  display->drawText(10, 210, "Monitoring... 10s", ILI9341_YELLOW, 1);
  
  // Back button
  display->drawButton(120, 240, 80, 30, "Back", ILI9341_RED, ILI9341_WHITE);
}

void UIScreens::showAboutScreen() {
  display->clear(ILI9341_BLACK);
  
  // Title
  display->drawCenteredText(20, "About Arrhythmia", ILI9341_CYAN, 2);
  
  // Information text
  display->drawText(10, 50, "What is Arrhythmia?", ILI9341_WHITE, 1);
  display->drawText(10, 65, "An arrhythmia is an irregular", ILI9341_LIGHTGREY, 1);
  display->drawText(10, 78, "heartbeat. It can be too fast,", ILI9341_LIGHTGREY, 1);
  display->drawText(10, 91, "too slow, or irregular.", ILI9341_LIGHTGREY, 1);
  
  display->drawText(10, 110, "Classifications:", ILI9341_WHITE, 1);
  display->drawText(10, 125, "• Normal: 60-100 BPM", ILI9341_GREEN, 1);
  display->drawText(10, 140, "• Bradycardia: <60 BPM", ILI9341_YELLOW, 1);
  display->drawText(10, 155, "• Tachycardia: >100 BPM", ILI9341_ORANGE, 1);
  
  display->drawText(10, 175, "This device uses AD8232 sensor", ILI9341_LIGHTGREY, 1);
  display->drawText(10, 188, "to monitor heart electrical", ILI9341_LIGHTGREY, 1);
  display->drawText(10, 201, "activity and detect patterns.", ILI9341_LIGHTGREY, 1);
  
  // Back button
  display->drawButton(120, 240, 80, 30, "Back", ILI9341_RED, ILI9341_WHITE);
}

void UIScreens::updateWaveform(int value) {
  static int x = 15;
  static int lastY = 135;
  static unsigned long lastClear = 0;
  
  // Map ADC value to display coordinates
  int y = map(value, 0, 4095, 180, 90); // Inverted Y for better visualization
  
  // Constrain to waveform area
  y = constrain(y, 90, 180);
  
  // Clear the waveform area every few seconds to prevent clutter
  if (millis() - lastClear > 3000) {
    display->fillRect(15, 85, 295, 95, ILI9341_BLACK);
    // Redraw grid
    for (int i = 20; i < 300; i += 30) {
      display->drawLine(i, 85, i, 185, ILI9341_DARKGREY);
    }
    for (int i = 95; i < 185; i += 20) {
      display->drawLine(15, i, 305, i, ILI9341_DARKGREY);
    }
    x = 15;
    lastClear = millis();
  }
  
  // Draw the waveform line
  if (x > 15) {
    display->drawLine(x-1, lastY, x, y, ILI9341_GREEN);
  }
  
  x++;
  if (x >= 305) {
    x = 15;
    // Clear for next cycle
    display->fillRect(15, 85, 295, 95, ILI9341_BLACK);
    // Redraw grid
    for (int i = 20; i < 300; i += 30) {
      display->drawLine(i, 85, i, 185, ILI9341_DARKGREY);
    }
    for (int i = 95; i < 185; i += 20) {
      display->drawLine(15, i, 305, i, ILI9341_DARKGREY);
    }
  }
  
  lastY = y;
}

void UIScreens::updateBPMDisplay(float bpm) {
  // Clear the BPM display area
  display->fillRect(15, 40, 200, 20, ILI9341_BLACK);
  
  // Display current BPM
  if (bpm > 0) {
    display->drawText(15, 45, "BPM: " + String((int)bpm), ILI9341_WHITE, 2);
  } else {
    display->drawText(15, 45, "BPM: --", ILI9341_WHITE, 2);
  }
}

void UIScreens::updateCountdown(int seconds) {
  // Clear the status area
  display->fillRect(10, 210, 200, 15, ILI9341_BLACK);
  
  // Display countdown
  if (seconds > 0) {
    display->drawText(10, 210, "Monitoring... " + String(seconds) + "s", ILI9341_YELLOW, 1);
  } else {
    display->drawText(10, 210, "Analysis complete", ILI9341_GREEN, 1);
  }
}

void UIScreens::showLeadsOffWarning() {
  // Display warning message
  display->fillRect(10, 85, 300, 30, ILI9341_RED);
  display->drawText(60, 95, "LEADS OFF!", ILI9341_WHITE, 2);
  display->drawText(30, 110, "Check sensor connections", ILI9341_WHITE, 1);
}

void UIScreens::clearLeadsOffWarning() {
  // Clear the warning area and redraw the waveform area
  display->fillRect(10, 85, 300, 95, ILI9341_BLACK);
  
  // Redraw grid
  for (int i = 20; i < 300; i += 30) {
    display->drawLine(i, 85, i, 185, ILI9341_DARKGREY);
  }
  for (int i = 95; i < 185; i += 20) {
    display->drawLine(15, i, 305, i, ILI9341_DARKGREY);
  }
}

void UIScreens::showHeartRateResults(float avgBPM) {
  // Clear the analysis area
  display->fillRect(0, 70, 320, 120, ILI9341_BLACK);
  
  // Display results
  display->drawCenteredText(80, "Analysis Complete", ILI9341_CYAN, 2);
  display->drawCenteredText(110, "Average Heart Rate", ILI9341_WHITE, 1);
  display->drawCenteredText(130, String((int)avgBPM) + " BPM", ILI9341_GREEN, 3);
  
  // Classification based on BPM
  String status;
  uint16_t color;
  if (avgBPM < 60) {
    status = "Bradycardia";
    color = ILI9341_YELLOW;
  } else if (avgBPM > 100) {
    status = "Tachycardia";
    color = ILI9341_ORANGE;
  } else {
    status = "Normal";
    color = ILI9341_GREEN;
  }
  
  display->drawCenteredText(160, status, color, 2);
}

void UIScreens::showArrhythmiaResults(String classification, uint16_t color, float bpm, String description) {
  // Clear the analysis area
  display->fillRect(0, 70, 320, 120, ILI9341_BLACK);
  
  // Display classification results
  display->drawCenteredText(80, "Classification:", ILI9341_CYAN, 1);
  display->drawCenteredText(100, classification, color, 2);
  display->drawCenteredText(125, String((int)bpm) + " BPM", ILI9341_WHITE, 2);
  
  // Display description (wrapped text)
  display->drawText(10, 150, description.substring(0, 30), ILI9341_LIGHTGREY, 1);
  if (description.length() > 30) {
    display->drawText(10, 165, description.substring(30), ILI9341_LIGHTGREY, 1);
  }
}
