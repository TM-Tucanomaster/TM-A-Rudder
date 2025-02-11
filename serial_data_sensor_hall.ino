void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging
}

void loop() {
  // Read the values from the Hall sensors
  int hallValue1 = analogRead(A0);  // Read the value from the Hall sensor on pin A0
  int hallValue2 = analogRead(A1);  // Read the value from the Hall sensor on pin A1
  int hallValue3 = analogRead(A2);  // Read the value from the Hall sensor on pin A2

  // Print the values from the Hall sensors
  Serial.print("Hall 1 Value: ");
  Serial.println(hallValue1);
  Serial.print("Hall 2 Value: ");
  Serial.println(hallValue2);
  Serial.print("Hall 3 Value: ");
  Serial.println(hallValue3);

  delay(500);  // Delay to make it easier to read in the Serial Monitor
}
