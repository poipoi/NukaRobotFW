#include <MsTimer2.h>
#include <Servo.h>

float nowAngle = 0;
Servo nukaservo;

void rotateServo(float angle) {
  if (angle < 0.0) angle = 0.0;
  if (angle > 180.0) angle = 180.0;

  nowAngle = angle;
//  Serial.println(angle);
  nukaservo.writeMicroseconds(1800.0 * angle / 180.0 + 500); // サーボを動かすコード
}

#define MOTION_MODE_FAST  (0)
#define MOTION_MODE_SLOW  (1)

uint16_t motionMode = MOTION_MODE_SLOW;
uint32_t tickCountMs;
uint32_t nextMotionCount = 8000;
bool isIncreece = false;
uint32_t flipCount = 1000;
void tick10ms() {

  if (motionMode == MOTION_MODE_FAST) {
    if ((tickCountMs % nextMotionCount) == 0) {
      // piku moving
      rotateServo(random(5, 20));
    }
  
    if ((tickCountMs % nextMotionCount) == 100) {
      rotateServo(0);
      nextMotionCount = random(10, 30) * 1000;
      motionMode = random(0, 2);
      flipCount = random(500, 1500);
    }
  } else {
    if ((tickCountMs % nextMotionCount) < 1000) {
      int randVal = random(0, flipCount);
      float newAngle = nowAngle + randVal * 1.0 / 1000.0;
      rotateServo(newAngle);
    } else if ((tickCountMs % nextMotionCount) < 2000) {
      int randVal = random(0, 1000);
      float newAngle = nowAngle + -randVal * 1.0 / 1000.0;
      rotateServo(newAngle);
    } else if ((tickCountMs % nextMotionCount) == 2000) {
      nextMotionCount = random(10, 30) * 1000;
      motionMode = random(0, 2);
      flipCount = random(500, 1500);
    }
  }
  
  tickCountMs += 10;
}

void setup() {
//  Serial.begin(9600);
//  pinMode(2, OUTPUT);
  nukaservo.attach(3); //pwm pin attach
  MsTimer2::set(10, tick10ms); //set timer ms
  MsTimer2::start();

  rotateServo(0);
}

void loop() {
  
}
