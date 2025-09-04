// ArrhythmiaDetector.h
// Arrhythmia detection and classification class header

#ifndef ARRHYTHMIA_DETECTOR_H
#define ARRHYTHMIA_DETECTOR_H

#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "Config.h"

enum ArrhythmiaType {
  NORMAL_SINUS,
  BRADYCARDIA,
  TACHYCARDIA,
  UNKNOWN
};

class ArrhythmiaDetector {
private:
  // Heart rate variability analysis
  static const int HRV_BUFFER_SIZE = 20;
  float hrvBuffer[HRV_BUFFER_SIZE];
  int hrvIndex;
  
public:
  ArrhythmiaDetector();
  ArrhythmiaType classify(float bpm);
  String getClassificationName(ArrhythmiaType type);
  uint16_t getClassificationColor(ArrhythmiaType type);
  String getDescription(ArrhythmiaType type);
  float calculateHRV(float* intervals, int count);
  bool isIrregular(float hrv);
};

#endif // ARRHYTHMIA_DETECTOR_H