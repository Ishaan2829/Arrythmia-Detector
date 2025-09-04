// HeartMonitor.h
// Heart rate monitoring class header

#ifndef HEART_MONITOR_H
#define HEART_MONITOR_H

#include <Arduino.h>
#include "Config.h"

class HeartMonitor {
private:
  int analogPin;
  float currentBPM;
  float averageBPM;
  int beatCount;
  unsigned long lastBeatTime;
  unsigned long firstBeatTime;
  
  // Peak detection variables
  int threshold;
  int lastValue;
  bool isPeak;
  int peakCount;
  
  // Moving average for smoothing
  static const int BUFFER_SIZE = 10;
  int valueBuffer[BUFFER_SIZE];
  int bufferIndex;
  
  // BPM calculation
  static const int BPM_BUFFER_SIZE = 10;
  float bpmBuffer[BPM_BUFFER_SIZE];
  int bpmIndex;
  
public:
  HeartMonitor(int pin);
  void begin();
  int readValue();
  void updateHeartRate(int value);
  float getCurrentBPM();
  float getAverageBPM();
  void reset();
  bool detectPeak(int value);
  int getSmoothedValue(int value);
  void calculateBPM();
};

#endif // HEART_MONITOR_H