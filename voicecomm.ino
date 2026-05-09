#include <SoftwareSerial.h>

// Motor Pins
const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 6;
const int IN4 = 7;
const int ENA = 10;
const int ENB = 11;

// SoftwareSerial for Bluetooth on A0 (RX) and A1 (TX)
SoftwareSerial BTSerial(A0, A1); // RX, TX

String command = "";

void setup() {
  // Motor pins as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Start hardware Serial for debug output
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for Serial Monitor to open
  }
  Serial.println("Serial monitor started. Waiting for Bluetooth commands...");

  // Start SoftwareSerial for Bluetooth communication
  BTSerial.begin(9600);
}

void loop() {
  if (BTSerial.available()) {
    command = BTSerial.readStringUntil('\n');
    command.trim();  // remove whitespace and newline

    Serial.print("Command received via Bluetooth: ");
    Serial.println(command);

    if (command == "forward") {
      moveForward();
      Serial.println("Moving forward");
    } else if (command == "backward") {
      moveBackward();
      Serial.println("Moving backward");
    } else if (command == "left") {
      turnLeft();
      Serial.println("Turning left");
    } else if (command == "right") {
      turnRight();
      Serial.println("Turning right");
    } else if (command == "stop") {
      stopMotors();
      Serial.println("Stopping motors");
    } else {
      Serial.println("Unknown command");
    }
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 110);
  analogWrite(ENB, 110);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 110);
  analogWrite(ENB, 110);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}