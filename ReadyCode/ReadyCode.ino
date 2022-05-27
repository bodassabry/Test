//Commenting for a test.

#include <AFMotor.h>  
int trigPinM = A2;
int echoPinM = A3; 
int trigPinR = A0;
int echoPinR = A1; 

int trigPinL = A4;
int echoPinL = A5;

AF_DCMotor motorR (1); 
AF_DCMotor motorL (2);
AF_DCMotor motorR1 (3);
AF_DCMotor motorL1 (4);
long detection(int trigPin,int echoPin);
long duration, distance;
long dmiddle;
long dright;
long dleft;
int dis = 20;
int range = 2;
int range2 = 12;
int vel = 200;
void setup() {
  ////////////////////////// MIDDLE///////////////////////////////////
  pinMode(trigPinM, OUTPUT);         // set trig pin as output
  pinMode(echoPinM, INPUT);          //set echo pin as input to capture reflected waves
   ///////////////////////////////////////RIGHT///////////////////////////////////////
    pinMode(trigPinR, OUTPUT);         // set trig pin as output
  pinMode(echoPinR, INPUT);          //set echo pin as input to capture reflected waves
  ///////////////////////////////////////LEFT//////////////////////////////////////////////
    pinMode(trigPinL, OUTPUT);         // set trig pin as output
  pinMode(echoPinL, INPUT);          //set echo pin as input to capture reflected waves
Serial.begin(9600);
  Serial.setTimeout(5);

}

void loop() {
   ////////////////////////// MIDDLE///////////////////////////////////
    dmiddle=detection(trigPinM,echoPinM);
  Serial.print("Distancem: ");
  Serial.println(dmiddle);
    ///////////////////////////////////////RIGHT///////////////////////////////////////
  dright=detection(trigPinR,echoPinR);
  Serial.print("Distancer: ");
  Serial.println(dright);
  ///////////////////////////////////////LEFT//////////////////////////////////////////////
  dleft=detection(trigPinL,echoPinL);
   Serial.print("Distancel: ");
  Serial.println(dleft);

  
  if(dmiddle>dis){
    if(dright<range2){
      Serial.print("Move Left!!");
      moveLeft();
    }
    else if(dleft<range2){
      Serial.print("Move Right!!");
      moveRight();
    }
    else if(dleft>=range2 && dright>=range2){
      moveForward();
    }
    
  }
  else if(dmiddle<dis&&dright>dleft+range){
    moveRight();
  }
  else if (dmiddle<dis&&dleft>dright+range){
    moveLeft();
  }

/*moveForward();
delay(3000);
moveRight();
delay(3000);
moveLeft();
delay(3000);*/

/*if(dright<=6&&dleft<=6&&dmiddle>5){
  moveForward();
}
else if(dright>6&&dleft<=6&&dmiddle>5){
  moveRight();
}
else if(dleft>6&&dright<=6&&dmiddle>5){
  moveLeft();
}
else{
  moveForward();
}*/


}
////////////////////////////////////////////////////////////////////////////////////////////////////
long detection(int trigPin,int echoPin){
digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  distance = duration*0.034/2;   // convert to distance
 // Serial.print("Distance: ");
//Serial.println(distance);
//  delay(1000);
return distance;
}
void moveForward() {

  motorR.setSpeed(vel);
  motorL.setSpeed (vel);
  motorR.run(FORWARD);
  motorL.run(FORWARD);
  motorL1.setSpeed(vel);
  motorR1.setSpeed (vel);
  motorL1.run(FORWARD);
  motorR1.run(FORWARD);

}
void moveBackward(){
  motorR.setSpeed(100);
  motorL.setSpeed (100);
  motorR.run(BACKWARD);
  motorL.run(BACKWARD);
  motorL1.setSpeed(100);
  motorR1.setSpeed (100);
  motorL1.run(BACKWARD);
  motorR1.run(BACKWARD);  
  
}
void moveRight(){
  motorR.setSpeed(vel);
  motorL.setSpeed (vel);
  motorR.run(BACKWARD);
  motorL.run(FORWARD);
  motorL1.setSpeed(vel);
  motorR1.setSpeed (vel);
  motorL1.run(FORWARD);
  motorR1.run(BACKWARD);
  
}
void moveLeft(){
 motorR.setSpeed(vel);
  motorL.setSpeed (vel);
  motorR.run(FORWARD);
  motorL.run(BACKWARD);
  motorL1.setSpeed(vel);
  motorR1.setSpeed (vel);
  motorL1.run(BACKWARD);
  motorR1.run(FORWARD);
}
