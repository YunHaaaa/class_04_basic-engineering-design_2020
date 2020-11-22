#include <Servo.h>

// Arduino pin assignment
#define PIN_LED 9
#define PIN_SERVO 10
#define PIN_IR A0

// configurable parameters
#define INTERVAL 50 // sampling interval (unit: ms)
#define _DIST_MIN 69 // minimum distance to be measured (unit: mm)
#define _DIST_MAX 321 // maximum distance to be measured (unit: mm)

float val, raw_val, prev_val, ema_val, a;
float raw_dist;

// servo한테 줄 duty값의 최대, 최소, 적용값
#define _DUTY_MIN 750 // servo full clockwise position (0 degree)
#define _DUTY_NEU 1520 + (-1.5) * raw_dist//neutral position (90 degree)
#define _DUTY_MAX 1950 // servo full counterclockwise position (180 degree)

Servo myservo;

void setup() {
// initialize GPIO pins
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED, 1);
// servo 연결
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  
// initialize
  raw_val = prev_val = 0.0;
  
// initialize serial port
  Serial.begin(57600);

// initialize last sampling time
//   last_sampling_time = 0;
}

// get a distance reading from the 적외선 센서
float ir_distance(void){ // return value unit: mm
  float volt = float(analogRead(PIN_IR));
  raw_val = ((6762.0/(volt-9.0))-4.0) * 10.0;
// ema 필터링
  a = 0.5;
  val = raw_val - 170.0;
  ema_val = a * raw_val + (1-a) * ema_val;
  return val;
}

void loop() {
// wait until next sampling time. 
// millis() returns the number of milliseconds since the program started. Will overflow after 50 days.
//  if(millis() < last_sampling_time + INTERVAL) return;
  
  float raw_dist = ir_distance();
  Serial.print("dist:");
  Serial.println(raw_dist);
  delay(60);

  // 범위 벗어난 값 처리
if(raw_val < 69.0) {
     myservo.writeMicroseconds(_DUTY_MIN);
  }
  else if(raw_val < 321.0){
     myservo.writeMicroseconds(_DUTY_NEU);
  }
  else {
    myservo.writeMicroseconds(_DUTY_MAX);
  }
   
// update last sampling time
//   last_sampling_time += INTERVAL;
}
