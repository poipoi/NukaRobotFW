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
uint32_t nextReverseCount = 800;
bool isIncreece = false;
void tick10ms() {
  if ((tickCountMs % nextReverseCount) == 0) {
      isIncreece = !isIncreece;
      nextReverseCount = random(60, 100) * 10;
  }
  
  int randVal = random(0, 1000);
  float newAngle = nowAngle + (isIncreece ? 1 : -1) * randVal * 0.2 / 1000.0;
  rotateServo(newAngle);
  
  tickCountMs += 10;
}

void setup() {
//  Serial.begin(9600);
//  pinMode(2, OUTPUT);
  nukaservo.attach(3); //pwm pin attach
  MsTimer2::set(10, tick10ms); //set timer ms
  MsTimer2::start();

}

void loop() {
  
}
