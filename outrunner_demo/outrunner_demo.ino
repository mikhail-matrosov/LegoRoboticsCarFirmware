
#include <Servo.h> 

Servo s;

int speed = 50;

// the setup routine runs once when you press reset:
void setup() {                
  s.attach(3);
  Serial.begin(9600);
  
  s.write(speed);
  Serial.println(speed);
}

// the loop routine runs over and over again forever:
void loop() {
  if (Serial.available()>0){
    switch(Serial.read()) {
      case 'a':
        speed++; break;
      case 'z':
        speed--; break;
      case '0':
        speed=0; break;
      case '1':
        speed=44; break;
    }
    s.write(speed);
    Serial.println(speed);
  }
}
