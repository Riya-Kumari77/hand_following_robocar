// =====================================================
// MOTOR DRIVER
// =====================================================

// Left Wheel
#define ENA 11
#define IN1 4
#define IN2 5

// Right Wheel
#define ENB 10
#define IN3 6
#define IN4 7

// =====================================================
// ULTRASONIC SENSOR
// =====================================================

#define TRIG 2
#define ECHO 3

// =====================================================
// IR SENSORS
// =====================================================

#define IR_LEFT 9
#define IR_RIGHT A0

// =====================================================
// SETTINGS
// =====================================================

const int MOTOR_SPEED = 255;

// Follow distance zone
const int FORWARD_DISTANCE  = 25;
const int BACKWARD_DISTANCE = 15;

// =====================================================
// FUNCTION DECLARATIONS
// =====================================================

int getDistance();
int getStableDistance();

void forward();
void backward();
void turnLeft();
void turnRight();
void stopRobot();

// =====================================================
// SETUP
// =====================================================

void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  Serial.begin(9600);
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  // -------------------------
  // Stable IR Reading
  // -------------------------

  int leftCount = 0;
  int rightCount = 0;

  for (int i = 0; i < 3; i++) {

    if (digitalRead(IR_LEFT) == LOW)
      leftCount++;

    if (digitalRead(IR_RIGHT) == LOW)
      rightCount++;

    delay(1);
  }

  int leftIR = (leftCount >= 2) ? LOW : HIGH;
  int rightIR = (rightCount >= 2) ? LOW : HIGH;

  // Distance only needed when hand is centered
  int distance = 250;

  if (leftIR == LOW && rightIR == LOW) {
    distance = getStableDistance();
  }

  Serial.print("Distance=");
  Serial.print(distance);

  Serial.print(" L=");
  Serial.print(leftIR);

  Serial.print(" R=");
  Serial.println(rightIR);

  // =================================================
  // HAND ON RIGHT SIDE
  // =================================================

  if (rightIR == LOW && leftIR == HIGH) {

    turnLeft();     // unchanged

  }

  // =================================================
  // HAND ON LEFT SIDE
  // =================================================

  else if (leftIR == LOW && rightIR == HIGH) {

    turnRight();    // unchanged

  }

  // =================================================
  // HAND IN CENTER
  // =================================================

  else if (leftIR == LOW && rightIR == LOW) {

    if (distance > FORWARD_DISTANCE) {

      forward();

    }
    else if (distance < BACKWARD_DISTANCE && distance > 2) {

      backward();

    }
    else {

      stopRobot();

    }
  }

  // =================================================
  // NO HAND
  // =================================================

  else {

    stopRobot();

  }
}

// =====================================================
// ULTRASONIC FUNCTIONS
// =====================================================

int getStableDistance() {

  int d1 = getDistance();
  int d2 = getDistance();
  int d3 = getDistance();

  return (d1 + d2 + d3) / 3;
}

int getDistance() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  // Faster timeout than before
  long duration = pulseIn(ECHO, HIGH, 10000);

  if (duration == 0)
    return 250;

  return duration * 0.034 / 2;
}

// =====================================================
// MOTOR FUNCTIONS
// =====================================================

void forward() {

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopRobot() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}