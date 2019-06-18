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

uint32_t tickCountMs;
uint32_t motionRefCount = 0;
uint32_t nextMotionCount = 8000;
uint32_t motionRange = 350;

bool flipDir = false;
uint32_t flipRefCount = 0;
uint32_t nextFlipCount = 10000;

bool isIncreece = false;
void tick10ms() {

  if ((tickCountMs - motionRefCount) < motionRange) {
    if (flipDir) {
      rotateServo(nowAngle - 1);
    } else {
      rotateServo(nowAngle + 1);
    }
  } else if ((tickCountMs - motionRefCount) < (motionRange * 2)) {
    if (flipDir) {
      rotateServo(nowAngle + 1);
    } else {
      rotateServo(nowAngle - 1);
    }
  } else if ((tickCountMs - motionRefCount) >= nextMotionCount) {
    nextMotionCount = random(5000, 10000);
    motionRange = random(300, 1000);
    motionRefCount = tickCountMs;
  }

  if ((tickCountMs - flipRefCount) >= nextFlipCount) {
    rotateServo(flipDir ? 0 : 180);
    flipDir = !flipDir;
    nextFlipCount = random(10000, 20000);
    flipRefCount = tickCountMs;
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
