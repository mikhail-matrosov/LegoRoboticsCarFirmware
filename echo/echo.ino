/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */
 
 #define BAUDRATE 9600

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(BAUDRATE);
}

// the loop routine runs over and over again forever:
void loop() {
   Serial.println("Uno!");
   delay(500);
}



