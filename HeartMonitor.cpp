// HeartMonitor.cpp
// Heart rate monitoring class implementation

#include "HeartMonitor.h"

HeartMonitor::HeartMonitor(int pin) : 
  analogPin(pin), 
  currentBPM(0), 
  averageBPM(0), 
  beatCount(0),
  lastBeatTime(0),
  firstBeatTime(0),
  threshold(2048), // Mid-range for 12-bit ADC
  lastValue(0),
  isPeak(false),
  peakCount(0),
  bufferIndex(0),
  bpmIndex(0) {
  
  // Initialize buffers
  for (int i = 0; i < BUFFER_SIZE; i++) {
    valueBuffer[i] = 0;
  }
  for (int i = 0; i < BPM_BUFFER_SIZE; i++) {
    bpmBuffer[i] = 0;
  }
}

void HeartMonitor::begin() {
  pinMode(analogPin, INPUT);
  // Configure ADC for 12-bit resolution on ESP32
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
}

int HeartMonitor::readValue() {
  int rawValue = analogRead(analogPin);
  return getSmoothedValue(rawValue);
}

int HeartMonitor::getSmoothedValue(int value) {
  // Add to circular buffer
  valueBuffer[bufferIndex] = value;
  bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;
  
  // Calculate moving average
  long sum = 0;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    sum += valueBuffer[i];
  }
  
  return sum / BUFFER_SIZE;
}

bool HeartMonitor::detectPeak(int value) {
  bool peak = false;
  
  // Simple peak detection algorithm
  // Detect when signal crosses threshold going up
  if (value > threshold && lastValue <= threshold && !isPeak) {
    peak = true;
    isPeak = true;
  } else if (value < threshold - 100) { // Hysteresis to avoid noise
    isPeak = false;
  }
  
  lastValue = value;
  return peak;
}

void HeartMonitor::updateHeartRate(int value) {
  if (detectPeak(value)) {
    unsigned long currentTime = millis();
    
    if (lastBeatTime > 0) {
      // Calculate time between beats
      unsigned long beatInterval = currentTime - lastBeatTime;
      
      // Filter out unrealistic intervals (30-200 BPM range)
      if (beatInterval > 300 && beatInterval < 2000) {
        // Calculate instantaneous BPM
        float instantBPM = 60000.0 / beatInterval;
        
        // Add to BPM buffer for averaging
        bpmBuffer[bpmIndex] = instantBPM;
        bpmIndex = (bpmIndex + 1) % BPM_BUFFER_SIZE;
        
        // Calculate current BPM as average of recent measurements
        calculateBPM();
        
        beatCount++;
      }
    } else {
      // First beat detected
      firstBeatTime = currentTime;
    }
    
    lastBeatTime = currentTime;
    peakCount++;
  }
  
  // Update threshold dynamically (adaptive threshold)
  if (peakCount % 10 == 0 && peakCount > 0) {
    // Adjust threshold based on signal amplitude
    threshold = (threshold * 9 + value) / 10;
  }
}

void HeartMonitor::calculateBPM() {
  float sum = 0;
  int validCount = 0;
  
  for (int i = 0; i < BPM_BUFFER_SIZE; i++) {
    if (bpmBuffer[i] > 0) {
      sum += bpmBuffer[i];
      validCount++;
    }
  }
  
  if (validCount > 0) {
    currentBPM = sum / validCount;
    
    // Calculate overall average
    if (beatCount > 0 && lastBeatTime > firstBeatTime) {
      unsigned long totalTime = lastBeatTime - firstBeatTime;
      averageBPM = (beatCount * 60000.0) / totalTime;
    }
  }
}

float HeartMonitor::getCurrentBPM() {
  return currentBPM;
}

float HeartMonitor::getAverageBPM() {
  // Return current BPM if average not yet calculated
  return (averageBPM > 0) ? averageBPM : currentBPM;
}

void HeartMonitor::reset() {
  currentBPM = 0;
  averageBPM = 0;
  beatCount = 0;
  lastBeatTime = 0;
  firstBeatTime = 0;
  peakCount = 0;
  isPeak = false;
  
  // Clear buffers
  for (int i = 0; i < BPM_BUFFER_SIZE; i++) {
    bpmBuffer[i] = 0;
  }
  bpmIndex = 0;
}