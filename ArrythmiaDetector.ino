// ArrhythmiaDetector.ino
// Main Arduino sketch file
// Arrhythmia Detection System using ESP32 + ILI9341 + AD8232
// By Suhana & Simran

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

// Include custom headers
#include "Config.h"
#include "Display.h"
#include "HeartMonitor.h"
#include "TouchHandler.h"
#include "UIScreens.h"
#include "ArrhythmiaDetector.h"

// Global objects
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen touchscreen(TOUCH_CS, TOUCH_IRQ);
Display display(&tft);
HeartMonitor heartMonitor(AD8232_OUTPUT);
TouchHandler touchHandler(&touchscreen, &tft);
UIScreens uiScreens(&display, &touchHandler, &heartMonitor);
ArrhythmiaDetector arrhythmiaDetector;

// Global state variables
ScreenState currentScreen = SCREEN_TITLE;
unsigned long lastUpdate = 0;
unsigned long monitoringStartTime = 0;
bool isMonitoring = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Arrhythmia Detector Starting...");
  
  // Initialize display
  tft.begin();
  tft.setRotation(0); // Portrait mode
  
  // Initialize touchscreen
  touchscreen.begin();
  touchscreen.setRotation(0);
  
  // Initialize heart monitor pins
  heartMonitor.begin();
  
  // Setup interrupt for heart rate detection
  pinMode(AD8232_LO_PLUS, INPUT);
  pinMode(AD8232_LO_MINUS, INPUT);
  
  // Check for calibration mode
  Serial.println("=== ARRHYTHMIA DETECTOR ===");
  Serial.println("Send 'C' within 5 seconds for touch calibration mode");
  Serial.println("Otherwise, normal operation will start...");
  
  unsigned long startTime = millis();
  bool calibrationMode = false;
  
  while (millis() - startTime < 5000) { // 5 second window
    if (Serial.available()) {
      char input = Serial.read();
      if (input == 'C' || input == 'c') {
        calibrationMode = true;
        break;
      }
    }
    delay(100);
  }
  
  if (calibrationMode) {
    Serial.println("Entering touch calibration mode...");
    touchHandler.runCalibration(&tft);
    // After calibration, continue with normal operation
  }
  
  // Show initial title screen
  uiScreens.showTitleScreen();
  
  Serial.println("Setup complete!");
  Serial.println("Touch coordinates will be printed to Serial for debugging");
}

void loop() {
  // Handle touch events
  TouchPoint touch = touchHandler.getTouch();
  
  if (touch.touched) {
    handleTouchEvent(touch);
  }
  
  // Update display based on current screen
  updateScreen();
  
  // Small delay to prevent overwhelming the processor
  delay(10);
}

void handleTouchEvent(TouchPoint touch) {
  switch (currentScreen) {
    case SCREEN_TITLE:
      if (touchHandler.isButtonPressed(touch, 85, 200, 150, 40)) { // Continue button
        currentScreen = SCREEN_MENU;
        uiScreens.showMenuScreen();
      }
      break;
      
    case SCREEN_MENU:
      if (touchHandler.isButtonPressed(touch, 60, 70, 200, 40)) { // Heart Rate Monitoring
        currentScreen = SCREEN_HEART_RATE;
        startMonitoring();
        uiScreens.showHeartRateScreen();
      }
      else if (touchHandler.isButtonPressed(touch, 60, 120, 200, 40)) { // Arrhythmia Detection
        currentScreen = SCREEN_ARRHYTHMIA;
        startMonitoring();
        uiScreens.showArrhythmiaScreen();
      }
      else if (touchHandler.isButtonPressed(touch, 60, 170, 200, 40)) { // About
        currentScreen = SCREEN_ABOUT;
        uiScreens.showAboutScreen();
      }
      else if (touchHandler.isButtonPressed(touch, 120, 240, 80, 30)) { // Back
        currentScreen = SCREEN_TITLE;
        uiScreens.showTitleScreen();
      }
      break;
      
    case SCREEN_HEART_RATE:
    case SCREEN_ARRHYTHMIA:
      if (touchHandler.isButtonPressed(touch, 120, 240, 80, 30)) { // Back
        stopMonitoring();
        currentScreen = SCREEN_MENU;
        uiScreens.showMenuScreen();
      }
      break;
      
    case SCREEN_ABOUT:
      if (touchHandler.isButtonPressed(touch, 120, 240, 80, 30)) { // Back
        currentScreen = SCREEN_MENU;
        uiScreens.showMenuScreen();
      }
      break;
  }
}

void updateScreen() {
  unsigned long currentTime = millis();
  
  if (currentScreen == SCREEN_HEART_RATE || currentScreen == SCREEN_ARRHYTHMIA) {
    if (isMonitoring) {
      // Update countdown
      int remainingTime = (MONITORING_DURATION - (currentTime - monitoringStartTime)) / 1000;
      if (remainingTime >= 0) {
        uiScreens.updateCountdown(remainingTime);
      }
      
      // Update waveform and heart rate
      if (currentTime - lastUpdate > 20) { // Update every 20ms for smooth waveform
        int heartValue = heartMonitor.readValue();
        
        // Check if leads are connected
        if (digitalRead(AD8232_LO_PLUS) == 1 || digitalRead(AD8232_LO_MINUS) == 1) {
          // Leads off detected
          uiScreens.showLeadsOffWarning();
        } else {
          // Clear any previous warning
          uiScreens.clearLeadsOffWarning();
          
          // Update heart rate calculation
          heartMonitor.updateHeartRate(heartValue);
          
          // Draw waveform
          uiScreens.updateWaveform(heartValue);
          
          // Display current BPM
          float currentBPM = heartMonitor.getCurrentBPM();
          uiScreens.updateBPMDisplay(currentBPM);
        }
        
        lastUpdate = currentTime;
      }
      
      // After 10 seconds, show analysis
      if (currentTime - monitoringStartTime >= MONITORING_DURATION) {
        stopMonitoring();
        showAnalysisResults();
      }
    }
  }
}

void startMonitoring() {
  isMonitoring = true;
  monitoringStartTime = millis();
  heartMonitor.reset();
  Serial.println("Started monitoring...");
}

void stopMonitoring() {
  isMonitoring = false;
  Serial.println("Stopped monitoring...");
}

void showAnalysisResults() {
  float avgBPM = heartMonitor.getAverageBPM();
  
  if (currentScreen == SCREEN_HEART_RATE) {
    // Show heart rate results using the new UI method
    uiScreens.showHeartRateResults(avgBPM);
  } 
  else if (currentScreen == SCREEN_ARRHYTHMIA) {
    // Show arrhythmia classification using the new UI method
    ArrhythmiaType type = arrhythmiaDetector.classify(avgBPM);
    String classification = arrhythmiaDetector.getClassificationName(type);
    uint16_t color = arrhythmiaDetector.getClassificationColor(type);
    String description = arrhythmiaDetector.getDescription(type);
    
    uiScreens.showArrhythmiaResults(classification, color, avgBPM, description);
  }
}