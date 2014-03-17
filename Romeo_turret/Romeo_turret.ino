// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo hServo;  // create servo object to control a servo 
Servo vServo;  // a maximum of eight servo objects can be created 
Servo steeringServo; // steering wheel
Servo fireServo;
Servo motor;

#define BUFFER_LENGTH 64
char buffer[BUFFER_LENGTH];
int bufIndex=0;
 
int pos = 0;    // variable to store the servo position 
 char* buf=0;
void setup() 
{ 
  Serial.begin(9600);
  Serial1.begin(9600);
  hServo.attach(8);  // attaches the servo on pin 9 to the servo object 
  vServo.attach(9);
  steeringServo.attach(10);
  fireServo.attach(11);
  motor.attach(12);
  
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  setMotor(0);
  fireServo.write(85);
  motor.write(0);
}

#define C2I (int)(unsigned char)

int av=90;
int ah=90;

int fireState = 0;
int pumpState = 0;

int steeringZero = 90;

void loop() 
{
  while (Serial1.available()>0 && bufIndex<BUFFER_LENGTH) {
    buffer[bufIndex++] = Serial1.read();
  }
  
  int z = (int)'z';
  
  if (bufIndex>0 && buffer[bufIndex-1]==(char)254 || bufIndex == BUFFER_LENGTH) {
    fireState = 0;
    
    switch (buffer[0]) {
      case 'A':
        if (bufIndex == 6) {
          ah -= (C2I(buffer[1])-z)/4;
          av += (C2I(buffer[2])-z)/4;
          ah = ah>180? 180 : (ah<0 ? 0 : ah);
          av = av>180? 180 : (av<0 ? 0 : av);
          hServo.write(ah);
          vServo.write(av);
          int s = steeringZero - (C2I(buffer[3])-z)*3;
          s = s>180? 180 : (s<0 ? 0 : s);
          steeringServo.write(s);
          //setMotor((C2I(buffer[4])-z)*12);
          int m = C2I(buffer[4])-z;
          motor.write(m>0?m+54:0);
        }
        break;
      case 'F':
        if ((bufIndex == 3) && (buffer[1] == '1')) {
          fireState = 1;
        }
        break;
      case 'J':
        if (bufIndex == 3)
        switch (buffer[1]) {
          case 'L': steeringZero--; break;
          case 'R': steeringZero++; break;
        }
        break;
      case 'S':
        if (bufIndex == 3)
        switch (buffer[1]) {
          case '4': pumpState = 0; break;
          case '3': pumpState = 1; break;
          case '5': fireState = 1; break;
          case '2': fireState = 2; break;
        }
        break;
    }
    
    switch(fireState) {
      case 0: fireServo.write(85); break;
      case 1: fireServo.write(130); break;
      case 2: fireServo.write(40); break;
    }
    
    setPump(pumpState);
  
    buffer[bufIndex] = 0; // end character
    Serial.println(buffer);
    bufIndex = 0;
  }
}

int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control

void setMotor(int a) {
  /*a = a>255 ? 255 : (a<-255 ? -255 : a);
  if (a>0) {
    analogWrite (E1, a); //PWM Speed Control
    digitalWrite(M1, HIGH);
  } else {
    analogWrite (E1, -a); //PWM Speed Control
    digitalWrite(M1, LOW);
  }*/
}

void setPump(int a) {
  analogWrite (E2, a?255:0);
  digitalWrite(M2, HIGH);
}
