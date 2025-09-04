# Touch Calibration Troubleshooting Guide

## 🔧 How to Calibrate Your Touch Screen

### Step 1: Enter Calibration Mode
1. Upload the updated code to your ESP32
2. Open Serial Monitor (115200 baud)
3. Reset your ESP32
4. **Within 5 seconds**, type 'C' and press Enter
5. Follow the on-screen prompts

### Step 2: Record Calibration Values
Touch each corner when prompted and note the **raw values** printed in Serial Monitor:
- TOP-LEFT corner → note X and Y values
- TOP-RIGHT corner → note X and Y values  
- BOTTOM-RIGHT corner → note X and Y values
- BOTTOM-LEFT corner → note X and Y values
- CENTER → note X and Y values

### Step 3: Update Config.h
Use the corner values to update your Config.h:
```cpp
#define TOUCH_MIN_X [smallest X value from corners]
#define TOUCH_MAX_X [largest X value from corners] 
#define TOUCH_MIN_Y [smallest Y value from corners]
#define TOUCH_MAX_Y [largest Y value from corners]
```

## 🚨 Common Issues & Solutions

### Issue 1: Touch is Inverted/Mirrored
**Solution:** Swap min/max values in Config.h
```cpp
// If X is inverted:
#define TOUCH_MIN_X 3699  // Use your MAX value
#define TOUCH_MAX_X 598   // Use your MIN value

// If Y is inverted:
#define TOUCH_MIN_Y 3718  // Use your MAX value  
#define TOUCH_MAX_Y 305   // Use your MIN value
```

### Issue 2: X and Y are Swapped
**Solution:** Try different rotation settings
```cpp
// In setup(), try different combinations:
tft.setRotation(0);      // Try 0, 1, 2, or 3
touchscreen.setRotation(0); // Try 0, 1, 2, or 3
```

### Issue 3: Touch Offset (Close but not exact)
**Solution:** Fine-tune your calibration values by ±50-100

### Issue 4: No Touch Response
**Check:**
1. Wiring connections (especially CS and IRQ pins)
2. Power supply (3.3V stable)
3. SPI connections
4. Pin definitions in Config.h match your wiring

## 🔍 Debug Information
The updated code prints detailed debug info:
- Raw touch coordinates
- Mapped coordinates  
- Final calibrated coordinates
- Button press detection

Monitor Serial output while testing to see what's happening.

## 📋 Quick Test Values
If calibration doesn't work, try these common values in Config.h:

**Set 1:**
```cpp
#define TOUCH_MIN_X 200
#define TOUCH_MAX_X 3800
#define TOUCH_MIN_Y 240  
#define TOUCH_MAX_Y 3800
```

**Set 2:**
```cpp
#define TOUCH_MIN_X 320
#define TOUCH_MAX_X 3700
#define TOUCH_MIN_Y 400
#define TOUCH_MAX_Y 3600
```

**Set 3 (Your current):**
```cpp
#define TOUCH_MIN_X 598
#define TOUCH_MAX_X 3699
#define TOUCH_MIN_Y 305
#define TOUCH_MAX_Y 3718
```

## ⚡ Quick Fix
1. Upload the code
2. Send 'C' to enter calibration  
3. Touch corners and note raw values
4. Update Config.h with proper min/max
5. Re-upload and test

The touch should now work correctly!
