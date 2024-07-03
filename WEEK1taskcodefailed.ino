#include <Servo.h>

// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3;

// Servo motor pin
const int servoPin = 9;

// LEDs pins
const int ledPin1 = 4;
const int ledPin2 = 5;
const int ledPin3 = 6;

// Constants for distance thresholds
const int farThreshold = 100;  // Greater than this, no LEDs are on
const int closeThreshold = 25; // Less than this, all LEDs are on

// Variables
int distance = 0;
Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  servo.attach(servoPin);
  servo.write(0); // Start servo at 0 degrees
}

void loop() {
  // Read distance from ultrasonic sensor
  distance = getDistance();

  // Adjust LEDs based on distance
  if (distance >= farThreshold) {
    turnOffAllLEDs();
  } else if (distance <= closeThreshold) {
    turnOnAllLEDs();
  } else {
    // Determine which LEDs to turn on based on checkpoints
    if (distance <= 75) {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
    } else if (distance <= 50) {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, LOW);
    } else {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
    }
  }

  // Adjust servo angle based on distance
  if (distance >= closeThreshold && distance <= farThreshold) {
    int angle = map(distance, closeThreshold, farThreshold, 0, 180);
    servo.write(angle);
    delay(100); // Delay for servo movement
  }

  delay(100); // Delay for stability
}

// Function to get distance from ultrasonic sensor
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2; // Calculate distance in cm
  return distance;
}

// Function to turn off all LEDs
void turnOffAllLEDs() {
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
}

// Function to turn on all LEDs
void turnOnAllLEDs() {
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
}

