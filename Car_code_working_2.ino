#include <ECE3.h>

uint16_t sensorValues[8];
int maxValues[8]={2500,2129,2500,2094,2500,2104,2500,2500};
int minValues[8]={710,549,640,549,617,553,687,757};
//int weight[8]= {8,12,14,15,-15,-14,-12,-8};
int weight[8]={15,14,12,8,-8,-12,-14,-15};
int wValue=0;
const int left_nslp_pin = 31;
const int left_dir_pin  = 29;
const int left_pwm_pin  = 40;
const int right_nslp_pin = 11;
const int right_dir_pin  = 30;
const int right_pwm_pin  = 39;
int leftspd;
int rightspd;
char new_duty_cycle[4];
int get_spd(int prev_spd);
int wValuep=0;
int count;
int count2;
bool state=false;


float K_p=.002;
float K_d=.002*6;

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

   digitalWrite(right_dir_pin, LOW);
   digitalWrite(left_dir_pin, LOW);
   analogWrite(right_pwm_pin, 50);
    analogWrite(left_pwm_pin, 50);
  delay(200);
   
}

void loop() {
  ECE3_read_IR(sensorValues);
   wValue=0;
   count=0;
for (unsigned char i = 0; i < 8; i++)
  {
    //Serial.print(sensorValues[i]);
    //Serial.print("    ");
    if(sensorValues[i]>2000){
      count+=1;
    }
    int value=((sensorValues[i]-minValues[i])*1000)/(maxValues[i]-minValues[i]);
    wValue= wValue+(value*weight[i]);
   //delay(100);
   //Serial.println();
   //Serial.print('\t'); 
   
  }
  //Serial.print(count);
 //Serial.println();
  //Serial.print(wValue/8);
  int basespeed=80-abs(wValue)/200;
 
  int correction= K_p * wValue; //+ K_d * (wValuep - wValue);
    leftspd = basespeed+correction;
    rightspd = basespeed-correction;

 
 //Serial.print(correction);
 //Serial.println();
  // delay(200);
  wValuep=wValue;

  
  if(count>=6){
    count2+=1;
  }else{
    count2=0;
  }
  if(count2>=7 and state==false){
    int encoder= getEncoderCount_right();
    while(getEncoderCount_right()-encoder < 360){
    digitalWrite(right_dir_pin, LOW);
    digitalWrite(left_dir_pin, HIGH);
    analogWrite(right_pwm_pin, 50);
    analogWrite(left_pwm_pin, 50);
    }
    analogWrite(right_pwm_pin, 0);
    analogWrite(left_pwm_pin, 0);
    digitalWrite(left_dir_pin, LOW);
    analogWrite(right_pwm_pin, 80);
    analogWrite(left_pwm_pin, 80);
    delay(100);
    state=true;
    count2=0;    
  }

  if(count2>=10 and state==true){
      analogWrite(right_pwm_pin, 0);
      analogWrite(left_pwm_pin, 0);
      delay(100000);
  }
  

  

  if( leftspd<0){
    digitalWrite(left_dir_pin,HIGH);
    analogWrite(left_pwm_pin, abs(leftspd));
     //Serial.print("Leftbackward   ");
    //delay(1000);
  }
   if( leftspd>=0){
    digitalWrite(left_dir_pin,LOW);
    analogWrite(left_pwm_pin, abs(leftspd));
     //Serial.print("Leftforward   ");
    //delay(1000);
  }
   if( rightspd<0){
    digitalWrite(right_dir_pin,HIGH);
    analogWrite(right_pwm_pin, abs(rightspd));
     //Serial.print("rightbackwards   ");
    //delay(1000);
  }
   if( rightspd>=0){
    digitalWrite(right_dir_pin,LOW);
    analogWrite(right_pwm_pin, abs(rightspd));
    //Serial.print("rightforward   ");
    //delay(1000);
  }
  //Serial.print(correction);
  //Serial.println();
  
}
