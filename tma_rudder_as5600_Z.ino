#include <Joystick.h>
#include <Wire.h>
#include <AS5600.h>

// Joystick object definition
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_MULTI_AXIS, 3, 2,  // 3 axes (rudder, X, Y)
                   true, true, false, false, false, false,
                   true, false, false, false, true); // 'true' for Y rotation

AS5600 as5600;  // Object for the AS5600 sensor

const int button1Pin = 4;    // Pin for button 1 (e.g., digital pin 4)
const int button2Pin = 5;    // Pin for button 2 (e.g., digital pin 5)
const int hallSensor1Pin = A0;  // Pin for Hall sensor 1 (analog pin A0)
const int hallSensor2Pin = A1;  // Pin for Hall sensor 2 (analog pin A1)

// Minimum and maximum values obtained from the AS5600 sensor
const int minSensorValue = 2463;
const int maxSensorValue = 1594;

void setup() {
  Wire.begin();              // Initialize I2C communication
  as5600.begin();            // Initialize the AS5600 sensor
  
  pinMode(button1Pin, INPUT_PULLUP);  // Configure the pin for button 1
  pinMode(button2Pin, INPUT_PULLUP);  // Configure the pin for button 2
  
  Joystick.begin();          // Initialize the Joystick library
}

void loop() {
  // Read the value from the AS5600 sensor
  int valorAS5600 = as5600.readAngle();
  int mappedRudder = map(valorAS5600, minSensorValue, maxSensorValue, 0, 1023);
  Joystick.setRudder(mappedRudder);

  // Read values from the Hall sensors
  int hallValue1 = analogRead(hallSensor1Pin);  // Hall sensor 1 (A0)
  int hallValue2 = analogRead(hallSensor2Pin);  // Hall sensor 2 (A1)

  // Map Hall sensor values to joystick range
  int mappedHallValueX = map(hallValue1, 203, 470, 0, 1023);  // For X-axis
  int mappedHallValueY = map(hallValue2, 404, 506, 0, 1023);  // For Y-axis

  // Set the mapped Hall values
  Joystick.setXAxis(mappedHallValueX); // X-axis
  Joystick.setYAxis(mappedHallValueY); // Y-axis

  // Read the state of the buttons and update them on the joystick
  int buttonState1 = !digitalRead(button1Pin);  // Invert the value due to pull-up
  int buttonState2 = !digitalRead(button2Pin);  // Invert the value due to pull-up
  
  Joystick.setButton(0, buttonState1);  // Set the state of button 1
  Joystick.setButton(1, buttonState2);  // Set the state of button 2
  
  delay(10);  // Small delay to avoid excessive readings
}



