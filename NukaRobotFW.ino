#include <MsTimer2.h>
#include <Servo.h>

float nowAngle = 0;
Servo nukaservo;

void rotateServo(float angle) {
  if (angle < 0.0) angle = 0.0;
  if (angle > 180.0) angle = 180.0;

  nowAngle = angle;
//  Serial.println(angle);
  nukaservo.write(angle); // サーボを動かすコード
}

uint32_t tickCountMs;
uint32_t nextReverseCount = 800;
bool isIncreece = false;
float newAngle;
void tick10ms() {
  if ((tickCountMs % nextReverseCount) == 0) {
      isIncreece = !isIncreece;
      nextReverseCount = random(60, 100) * 10;
      rotateServo(newAngle);
  }
  
  //int randVal = random(-1000, 1000);
  //float newAngle = (isIncreece ? 1 : -1) * randVal * 0.2 / 1000.0;
  int randVal = random(-180, 180);
  newAngle = (isIncreece ? 1 : -1) * randVal;
  //rotateServo(newAngle);
  
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
