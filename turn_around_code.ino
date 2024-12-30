#include <ECE3.h>

const int left_nslp_pin = 31;
const int left_dir_pin  = 29;
const int left_pwm_pin  = 40;
const int right_nslp_pin = 11;
const int right_dir_pin  = 30;
const int right_pwm_pin  = 39;


int average() // average pulse count
{
    int getL = getEncoderCount_left();
    int getR = getEncoderCount_right();
    // Serial.print(getL); Serial.print("\t"); Serial.println(getR);
    return ((getL + getR) / 2);
}



void setup() {
  pinMode(left_nslp_pin,OUTPUT);
   pinMode(left_dir_pin,OUTPUT);
   pinMode(left_pwm_pin,OUTPUT);

   digitalWrite(left_dir_pin,LOW);
  digitalWrite(left_nslp_pin,HIGH);

   pinMode(right_nslp_pin,OUTPUT);
   pinMode(right_dir_pin,OUTPUT);
   pinMode(right_pwm_pin,OUTPUT);

   digitalWrite(right_dir_pin,LOW);
   digitalWrite(right_nslp_pin,HIGH);

   ECE3_Init();
   Serial.begin(9600); // set the data rate in bits per second for serial data transmission
   delay(2000);

}

void loop() {
  delay(2000);
  digitalWrite(right_dir_pin, LOW);
  digitalWrite(left_dir_pin, HIGH);
  analogWrite(right_pwm_pin, 100);
  analogWrite(left_pwm_pin, 100);
  delay(560);
  analogWrite(right_pwm_pin, 0);
  analogWrite(left_pwm_pin, 0);
  delay(2000);
  
}
