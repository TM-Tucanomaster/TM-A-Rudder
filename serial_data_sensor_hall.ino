void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging
}

void loop() {
  // Read the values from the Hall sensors
  int rudderValue = analogRead(A0);  // Read the value from the rudder Hall sensor
  int leftBrakeValue = analogRead(A1);  // Read the value from the left brake Hall sensor
  int rightBrakeValue = analogRead(A2);  // Read the value from the right brake Hall sensor

  // Print the values from the Hall sensors
  Serial.print("Rudder Value: ");
  Serial.println(rudderValue);
  Serial.print("Left Brake Value: ");
  Serial.println(leftBrakeValue);
  Serial.print("Right Brake Value: ");
  Serial.println(rightBrakeValue);

  delay(500);  // Delay to make it easier to read in the Serial Monitor
}
