// UIScreens.h
// User Interface Screens management class header

#ifndef UISCREENS_H
#define UISCREENS_H

#include <Arduino.h>
#include "Display.h"
#include "TouchHandler.h"
#include "HeartMonitor.h"

class UIScreens {
  private:
    Display* display;
    TouchHandler* touchHandler;
    HeartMonitor* heartMonitor;

  public:
    UIScreens(Display* d, TouchHandler* t, HeartMonitor* h);

    // Screen display methods
    void showTitleScreen();
    void showMenuScreen();
    void showHeartRateScreen();
    void showArrhythmiaScreen();
    void showAboutScreen();

    // Dynamic content update methods
    void updateWaveform(int value);
    void updateBPMDisplay(float bpm);
    void updateCountdown(int seconds);
    void showLeadsOffWarning();
    void clearLeadsOffWarning();
    
    // Result display methods
    void showHeartRateResults(float avgBPM);
    void showArrhythmiaResults(String classification, uint16_t color, float bpm, String description);
};

#endif // UISCREENS_H
