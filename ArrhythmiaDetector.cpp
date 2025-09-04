// ArrhythmiaDetector.cpp
// Arrhythmia detection and classification class implementation

#include "ArrhythmiaDetector.h"

ArrhythmiaDetector::ArrhythmiaDetector() : hrvIndex(0) {
  // Initialize HRV buffer
  for (int i = 0; i < HRV_BUFFER_SIZE; i++) {
    hrvBuffer[i] = 0;
  }
}

ArrhythmiaType ArrhythmiaDetector::classify(float bpm) {
  if (bpm < MIN_HEART_RATE || bpm > MAX_HEART_RATE) {
    return UNKNOWN;
  }
  
  if (bpm < BRADYCARDIA_THRESHOLD) {
    return BRADYCARDIA;
  } else if (bpm > TACHYCARDIA_THRESHOLD) {
    return TACHYCARDIA;
  } else {
    return NORMAL_SINUS;
  }
}

String ArrhythmiaDetector::getClassificationName(ArrhythmiaType type) {
  switch (type) {
    case NORMAL_SINUS:
      return "Normal Sinus Rhythm";
    case BRADYCARDIA:
      return "Bradycardia";
    case TACHYCARDIA:
      return "Tachycardia";
    case UNKNOWN:
    default:
      return "Unknown";
  }
}

uint16_t ArrhythmiaDetector::getClassificationColor(ArrhythmiaType type) {
  switch (type) {
    case NORMAL_SINUS:
      return ILI9341_GREEN;
    case BRADYCARDIA:
      return ILI9341_YELLOW;
    case TACHYCARDIA:
      return ILI9341_ORANGE;
    case UNKNOWN:
    default:
      return ILI9341_RED;
  }
}

String ArrhythmiaDetector::getDescription(ArrhythmiaType type) {
  switch (type) {
    case NORMAL_SINUS:
      return "Normal heart rhythm (60-100 BPM)";
    case BRADYCARDIA:
      return "Slow heart rate (<60 BPM)";
    case TACHYCARDIA:
      return "Fast heart rate (>100 BPM)";
    case UNKNOWN:
    default:
      return "Unable to classify rhythm";
  }
}

float ArrhythmiaDetector::calculateHRV(float* intervals, int count) {
  if (count < 2) return 0.0;
  
  float sum = 0.0;
  float sumSquares = 0.0;
  
  for (int i = 0; i < count; i++) {
    sum += intervals[i];
    sumSquares += intervals[i] * intervals[i];
  }
  
  float mean = sum / count;
  float variance = (sumSquares / count) - (mean * mean);
  
  return sqrt(variance);
}

bool ArrhythmiaDetector::isIrregular(float hrv) {
  // Simple threshold for irregularity detection
  return hrv > 50.0; // ms - adjust based on requirements
}