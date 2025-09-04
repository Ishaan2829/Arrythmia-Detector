// Config.h
// Configuration file for pin definitions and constants

#ifndef CONFIG_H
#define CONFIG_H

// Display pins for ILI9341 (ESP32 connections)
#define TFT_CS    15     // Chip select
#define TFT_DC    2     // Data/Command
#define TFT_RST   4    // Reset
#define TFT_MISO  19    // MISO
#define TFT_MOSI  23    // MOSI
#define TFT_CLK   18    // Clock

// Touch screen pins (XPT2046)
#define TOUCH_CS   5   // Touch chip select
#define TOUCH_IRQ  27   // Touch interrupt

// AD8232 Heart Rate Monitor pins
#define AD8232_OUTPUT    34   // Analog output from AD8232 (ADC pin)
#define AD8232_LO_PLUS   25   // Leads-off detection +
#define AD8232_LO_MINUS  26   // Leads-off detection -

// Screen dimensions
#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

// Heart rate monitoring parameters
#define MONITORING_DURATION 10000  // 10 seconds in milliseconds
#define SAMPLE_RATE 50             // Hz
#define MIN_HEART_RATE 40          // BPM
#define MAX_HEART_RATE 200         // BPM

// Arrhythmia thresholds
#define BRADYCARDIA_THRESHOLD 60   // BPM
#define TACHYCARDIA_THRESHOLD 100  // BPM

// Waveform display parameters
#define WAVEFORM_HEIGHT 80
#define WAVEFORM_Y_OFFSET 80
#define WAVEFORM_SCALE 0.05

// Screen states
enum ScreenState {
  SCREEN_TITLE,
  SCREEN_MENU,
  SCREEN_HEART_RATE,
  SCREEN_ARRHYTHMIA,
  SCREEN_ABOUT
};

// Touch calibration values (adjust based on your display)
#define TOUCH_MIN_X 598
#define TOUCH_MAX_X 3699
#define TOUCH_MIN_Y 305
#define TOUCH_MAX_Y 3718

#endif // CONFIG_H