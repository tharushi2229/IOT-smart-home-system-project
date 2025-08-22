#include <Servo.h> // Include the Servo library

// Pin Definitions
#define TRIG_PIN 2          // Ultrasonic sensor trigger pin
#define ECHO_PIN 4          // Ultrasonic sensor echo pin
#define ULTRASONIC_LED 7    // LED for ultrasonic sensor

#define PIR_SENSOR_PIN 8    // PIR sensor pin
#define PIR_LED_PIN 9       // LED for PIR sensor

#define GAS_SENSOR_PIN A0   // Gas sensor connected to analog pin A0
#define GAS_LED_NORMAL 11   // LED for gas detection (normal state)
#define GAS_LED_WARNING 12  // LED for gas detection (warning state)
#define PIEZO_PIN 6        // Piezo buzzer pin

#define LDR_SENSOR_PIN A1   // LDR sensor connected to analog pin A1
#define LDR_LED_PIN 10      // LED for LDR sensor

#define SERVO_PIN 5         // Servo motor control pin

// Variables for LDR Calibration
int ldrValue = 0;
int ldrMin = 1023;   // Minimum LDR value for calibration
int ldrMax = 0;      // Maximum LDR value for calibration

// Servo Motor
Servo gasServo; // Create a Servo object

void setup() {
  // Initialize Pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ULTRASONIC_LED, OUTPUT);

  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(PIR_LED_PIN, OUTPUT);

  pinMode(GAS_LED_NORMAL, OUTPUT);
  pinMode(GAS_LED_WARNING, OUTPUT);
  pinMode(PIEZO_PIN, OUTPUT);

  pinMode(LDR_LED_PIN, OUTPUT);

  // Attach Servo to Pin
  gasServo.attach(SERVO_PIN);

  // Move Servo to Default Position
  gasServo.write(0);

  // Calibrate LDR Sensor
  calibrateLDR();

  // Initialize Serial Communication
  Serial.begin(9600);
}

void loop() {
  // Sensor Functions
  handleUltrasonicSensor();
  handlePIRSensor();
  handleGasSensor();
  handleLDRSensor();

  // Short Delay for Stability
  delay(50);
}

// Function to Handle Ultrasonic Sensor
void handleUltrasonicSensor() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration / 29 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Turn LED on or off based on distance
  if (distance < 50) {
    digitalWrite(ULTRASONIC_LED, HIGH);
  } else {
    digitalWrite(ULTRASONIC_LED, LOW);
  }
}

// Function to Handle PIR Sensor
void handlePIRSensor() {
  int pirState = digitalRead(PIR_SENSOR_PIN);

  if (pirState == HIGH) {
    digitalWrite(PIR_LED_PIN, HIGH);
    Serial.println("Motion Detected!");
  } else {
    digitalWrite(PIR_LED_PIN, LOW);
  }
}

// Function to Handle Gas Sensor
void handleGasSensor() {
  int gasValue = analogRead(GAS_SENSOR_PIN);

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  if (gasValue > 200) {  // If gas concentration exceeds the threshold
    digitalWrite(GAS_LED_NORMAL, LOW);   // Turn off LED 1 (normal state)
    digitalWrite(GAS_LED_WARNING, HIGH); // Turn on LED 2 (warning)

    // Move Servo to Warning Position (e.g., 90°)
    gasServo.write(90);
    Serial.println("Gas Detected! Warning! Servo Moved to 90°");

    // Activate Piezo Buzzer
    tone(PIEZO_PIN, 1000); // 1000 Hz frequency
    Serial.println("Piezo Buzzer ON!");
  } else {
    digitalWrite(GAS_LED_NORMAL, HIGH);  // Turn on LED 1 (normal)
    digitalWrite(GAS_LED_WARNING, LOW);  // Turn off LED 2 (warning)

    // Move Servo to Safe Position (e.g., 0°)
    gasServo.write(0);
    Serial.println("Gas Levels Normal. Servo at 0°");

    // Deactivate Piezo Buzzer
    noTone(PIEZO_PIN);
    Serial.println("Piezo Buzzer OFF!");
  }
}

// Function to Handle LDR Sensor
void handleLDRSensor() {
  int rawLDRValue = analogRead(LDR_SENSOR_PIN);
  Serial.print("Raw LDR Value: ");
  Serial.println(rawLDRValue);

  // Map and constrain LDR value
  int mappedLDRValue = map(rawLDRValue, ldrMin, ldrMax, 0, 255);
  mappedLDRValue = constrain(mappedLDRValue, 0, 255);

  // Control LED brightness
  analogWrite(LDR_LED_PIN, mappedLDRValue);

  // Debug Output
  if (mappedLDRValue < 128) {
    Serial.println("Bright Light Detected! LED Dim.");
  } else {
    Serial.println("Low Light Detected! LED Bright.");
  }
}

// Function to Calibrate LDR Sensor
void calibrateLDR() {
  Serial.println("Calibrating LDR Sensor...");
  unsigned long startTime = millis();

  while (millis() - startTime < 5000) {  // Calibrate for 5 seconds
    int sensorValue = analogRead(LDR_SENSOR_PIN);

    // Update Min and Max
    if (sensorValue > ldrMax) {
      ldrMax = sensorValue;
    }
    if (sensorValue < ldrMin) {
      ldrMin = sensorValue;
    }
    delay(50);
  }

  Serial.println("LDR Calibration Complete.");
  Serial.print("LDR Min: ");
  Serial.println(ldrMin);
  Serial.print("LDR Max: ");
  Serial.println(ldrMax);
}
