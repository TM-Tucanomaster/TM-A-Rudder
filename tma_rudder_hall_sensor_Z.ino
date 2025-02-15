#include <Joystick.h>

// Defining Hall sensor pins
const int rudderPin = A0;    // Pin for the rudder Hall sensor
const int leftBrakePin = A1; // Pin for the left brake Hall sensor
const int rightBrakePin = A2; // Pin for the right brake Hall sensor

// Rudder limits (values read by the Hall sensor)
const int rudderMin = 150; // Minimum rudder value
const int rudderMax = 850; // Maximum rudder value

// Brake limits (values read by the Hall sensor)
const int leftBrakeMin = 200; // Minimum left brake value
const int leftBrakeMax = 900; // Maximum left brake value
const int rightBrakeMin = 200; // Minimum right brake value
const int rightBrakeMax = 900; // Maximum right brake value

// Creating a Joystick object with X and Y enabled but fixed at the center
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK, 
                   0, 0,  // No buttons and hat switches
                   true,  // X-axis enabled (but fixed at center)
                   true,  // Y-axis enabled (also fixed at center)
                   false, // Z-axis disabled
                   true,  // Rx enabled (Left Brake)
                   true,  // Ry enabled (Right Brake)
                   true,  // Rz enabled (Rudder)
                   false, false, false); // No rudder, throttle, or extra accelerators

void setup() {
  // Initialize the Joystick
  Joystick.begin();

  // Configure the Joystick axes
  Joystick.setXAxisRange(0, 1023);  // X enabled but fixed at 512 (center)
  Joystick.setYAxisRange(0, 1023);  // Y enabled but fixed at 512 (center)
  Joystick.setRxAxisRange(0, 1023); // Rx (Left Brake)
  Joystick.setRyAxisRange(0, 1023); // Ry (Right Brake)
  Joystick.setRzAxisRange(0, 1023); // Rz (Rudder)
}

void loop() {
  // Read values from Hall sensors
  int rudderValue = analogRead(rudderPin);
  int leftBrakeValue = analogRead(leftBrakePin);
  int rightBrakeValue = analogRead(rightBrakePin);

  // Map values to the 0-1023 range
  rudderValue = map(rudderValue, rudderMin, rudderMax, 0, 1023);
  leftBrakeValue = map(leftBrakeValue, leftBrakeMin, leftBrakeMax, 0, 1023);
  rightBrakeValue = map(rightBrakeValue, rightBrakeMin, rightBrakeMax, 0, 1023);

  // Ensure values stay within the 0-1023 range
  rudderValue = constrain(rudderValue, 0, 1023);
  leftBrakeValue = constrain(leftBrakeValue, 0, 1023);
  rightBrakeValue = constrain(rightBrakeValue, 0, 1023);

  // Keep X and Y axes always centered at 512
  Joystick.setXAxis(512);
  Joystick.setYAxis(512);

  // Send mapped values to the Joystick axes
  Joystick.setRzAxis(rudderValue);
  Joystick.setRxAxis(leftBrakeValue);
  Joystick.setRyAxis(rightBrakeValue);

  // Small delay for stability
  delay(10);
}

