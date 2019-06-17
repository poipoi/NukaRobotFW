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

uint32_t tickCountMs;
float movingRatio = 2.0;
uint32_t pikuCycleCount = 8000;
uint32_t flipCycleCount = 30000;

uint32_t flipRefCount = 0;
uint32_t pikuRefCount = 0;
uint32_t pikuRange = 150;

bool isFlip = true;
void tick10ms() {
  if ((tickCountMs - pikuRefCount) < pikuRange) {
    rotateServo(nowAngle + (movingRatio * (isFlip ? 1 : -1)));
  } else if ((tickCountMs - pikuRefCount) < (pikuRange + random(50, 200))) {
    rotateServo(nowAngle - (movingRatio * (isFlip ? 1 : -1)));
  } else if ((tickCountMs - pikuRefCount) >= pikuCycleCount) {
    pikuCycleCount = random(1000, 10000);
    pikuRefCount = tickCountMs;
    pikuRange = random(50, 200);
  }

  if ((tickCountMs - flipRefCount) >= flipCycleCount) {
    isFlip = !isFlip;
    rotateServo(isFlip ? 0 : 180);
    flipCycleCount = random(20000, 40000);
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
