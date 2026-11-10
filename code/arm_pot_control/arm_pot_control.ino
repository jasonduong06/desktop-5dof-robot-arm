// 5DOF arm: manual control with 5 potentiometers
// Board: Arduino Nano. Servos on a separate 5V supply (grounds connected to the Nano).
//
// Joints: J1 base, J2 shoulder, J3 elbow, J4 wrist, J5 gripper
// Pots (wiper to analog pin, outer pins to 5V and GND): A0..A4
//
// Tune the values in the "SETTINGS" block for your own arm before powering the servos
// under load. The angle limits below are placeholders: find each joint's real safe
// range by hand-testing, then update MIN_ANGLE / MAX_ANGLE.

#include <Servo.h>

// ----------------------------- SETTINGS -----------------------------
const uint8_t NUM_JOINTS = 5;

const uint8_t SERVO_PINS[NUM_JOINTS] = {3, 5, 6, 9, 10};
const uint8_t POT_PINS[NUM_JOINTS]   = {A0, A1, A2, A3, A4};

//                                       J1   J2   J3   J4   J5
const int MIN_ANGLE[NUM_JOINTS]      = {  0,  20,  20,   0,  10};
const int MAX_ANGLE[NUM_JOINTS]      = {180, 160, 160, 180,  90};
const int HOME_ANGLE[NUM_JOINTS]     = { 90,  90,  90,  90,  50};  // must be within limits
const bool REVERSE[NUM_JOINTS]       = {false, false, false, false, false};  // flip a pot's direction

const float POT_SMOOTHING   = 0.15;   // 0..1, lower = smoother but slower to respond
const float DEADBAND_DEG    = 1.5;    // ignore target changes smaller than this (stops jitter)
const float MAX_STEP_DEG    = 1.0;    // max degrees a joint moves per update (speed limit)
const unsigned long UPDATE_MS = 15;   // update interval; 1 deg / 15 ms = about 66 deg/s
const unsigned long ATTACH_DELAY_MS = 400;  // stagger servo start-up to limit current spikes

const bool DEBUG_SERIAL = false;      // set true to print joint angles at 115200 baud
// --------------------------------------------------------------------

Servo servos[NUM_JOINTS];
float potFiltered[NUM_JOINTS];
float targetAngle[NUM_JOINTS];
float currentAngle[NUM_JOINTS];
int lastWritten[NUM_JOINTS];
unsigned long lastUpdate = 0;
unsigned long lastPrint = 0;

float potToAngle(int joint, float potValue) {
  float t = potValue / 1023.0;
  if (REVERSE[joint]) t = 1.0 - t;
  float angle = MIN_ANGLE[joint] + t * (MAX_ANGLE[joint] - MIN_ANGLE[joint]);
  return constrain(angle, MIN_ANGLE[joint], MAX_ANGLE[joint]);
}

void setup() {
  if (DEBUG_SERIAL) Serial.begin(115200);

  // Start every joint at its home angle, one at a time, so the servos
  // do not all draw start-up current together.
  for (uint8_t i = 0; i < NUM_JOINTS; i++) {
    currentAngle[i] = HOME_ANGLE[i];
    targetAngle[i]  = HOME_ANGLE[i];
    lastWritten[i]  = HOME_ANGLE[i];
    servos[i].write(HOME_ANGLE[i]);
    servos[i].attach(SERVO_PINS[i]);
    delay(ATTACH_DELAY_MS);
  }

  // Seed the filters with the current pot positions so there is no
  // slow "catch-up" at start. The arm then ramps gently toward the pots.
  for (uint8_t i = 0; i < NUM_JOINTS; i++) {
    potFiltered[i] = analogRead(POT_PINS[i]);
    targetAngle[i] = potToAngle(i, potFiltered[i]);
  }
}

void loop() {
  unsigned long now = millis();
  if (now - lastUpdate < UPDATE_MS) return;
  lastUpdate = now;

  for (uint8_t i = 0; i < NUM_JOINTS; i++) {
    // 1) read and smooth the pot
    int raw = analogRead(POT_PINS[i]);
    potFiltered[i] += POT_SMOOTHING * (raw - potFiltered[i]);

    // 2) convert to a target angle, only update if it moved enough
    float newTarget = potToAngle(i, potFiltered[i]);
    if (fabs(newTarget - targetAngle[i]) > DEADBAND_DEG) {
      targetAngle[i] = newTarget;
    }

    // 3) move toward the target at a limited speed
    float diff = targetAngle[i] - currentAngle[i];
    if (fabs(diff) <= MAX_STEP_DEG) {
      currentAngle[i] = targetAngle[i];
    } else {
      currentAngle[i] += (diff > 0) ? MAX_STEP_DEG : -MAX_STEP_DEG;
    }

    // 4) write only when the integer angle changes
    int out = (int)(currentAngle[i] + 0.5);
    if (out != lastWritten[i]) {
      servos[i].write(out);
      lastWritten[i] = out;
    }
  }

  if (DEBUG_SERIAL && now - lastPrint > 200) {
    lastPrint = now;
    for (uint8_t i = 0; i < NUM_JOINTS; i++) {
      Serial.print(lastWritten[i]);
      Serial.print(i < NUM_JOINTS - 1 ? "\t" : "\n");
    }
  }
}
