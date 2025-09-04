// Config_Calibration_Examples.h
// Alternative calibration values to try if your current ones don't work
// Copy the values that work best to your main Config.h file

#ifndef CONFIG_CALIBRATION_EXAMPLES_H
#define CONFIG_CALIBRATION_EXAMPLES_H

// ====== EXAMPLE CALIBRATION SET 1 ======
// Try these if your current values don't work
// Uncomment and replace in Config.h if these work better

/*
#define TOUCH_MIN_X 200
#define TOUCH_MAX_X 3800
#define TOUCH_MIN_Y 240
#define TOUCH_MAX_Y 3800
*/

// ====== EXAMPLE CALIBRATION SET 2 ======
// Common values for many ILI9341 displays

/*
#define TOUCH_MIN_X 320
#define TOUCH_MAX_X 3700
#define TOUCH_MIN_Y 400
#define TOUCH_MAX_Y 3600
*/

// ====== EXAMPLE CALIBRATION SET 3 ======
// Try these if the above don't work

/*
#define TOUCH_MIN_X 598
#define TOUCH_MAX_X 3699
#define TOUCH_MIN_Y 305
#define TOUCH_MAX_Y 3718
*/

// ====== INVERTED COORDINATES ======
// If your touch seems mirrored, try swapping min/max values

/*
#define TOUCH_MIN_X 3699
#define TOUCH_MAX_X 598
#define TOUCH_MIN_Y 3718
#define TOUCH_MAX_Y 305
*/

// ====== TROUBLESHOOTING NOTES ======
/*
ROTATION SETTINGS:
- If touch doesn't match display, try different rotation values
- Display rotation: tft.setRotation(0-3)
- Touch rotation: touchscreen.setRotation(0-3)

COMMON ISSUES:
1. Touch coordinates are inverted (swap min/max)
2. X and Y are swapped (use different rotation)
3. Touch offset (adjust min/max values)
4. Poor sensitivity (check wiring and power)

CALIBRATION PROCESS:
1. Upload code with calibration mode
2. Send 'C' in Serial Monitor within 5 seconds
3. Touch each corner when prompted
4. Note the raw values printed in Serial
5. Update Config.h with new min/max values
6. Test and repeat if needed
*/

// In setup(), try:
// tft.setRotation(1);           // Try 0, 1, 2, or 3
// touchscreen.setRotation(1);   // Try 0, 1, 2, or 3

#endif // CONFIG_CALIBRATION_EXAMPLES_H
