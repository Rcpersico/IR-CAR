#include <ECE3.h>

uint16_t sensorValues[8];
int maxValues[8]={2500,2129, 2500,2250,2500,2104,2500,2500};
int minValues[8]={750,549,640,529,617,525,650,757};
int values[8];
int error=0;
int dcontrol=1;
int pcontrol=1;


void setup()
{
  ECE3_Init();
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(2000);
}


void loop(){
  ECE3_read_IR(sensorValues);
  for(int i=0; i<8; i++){
    values[i]=(((sensorValues[i]-minValues[i])*1000)/(maxValues[i]-minValues[i]));
    if(i=0){
       error= error+ values[i]*15;
    }
    if(i=1){
       error= error+ values[i]*14;
    }
    if(i=2){
       error= error+ values[i]*12;
    }
    if(i=3){
       error= error+ values[i]*8;
    }
    if(i=4){
       error= error+ values[i]*-8;
    }
    if(i=5) {
      error= error+ values[i]*-12;
    }
    if(i=6) {
      error= error+ values[i]*-14;
    }
    if(i=7) {
      error= error+ values[i]*-15;
    }
    
   
   
  }
  Serial.print(error/8);
  Serial.println();
  
  
 }

  
