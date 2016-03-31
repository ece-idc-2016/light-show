/*
 * Credits: Joyce Choi
 */

#include <SoftwareSerial.h>
#define Rx 10 // DOUT to pin 10
#define Tx 11 // DIN to pin 11
#define LED4 31 // change to fit your own LED configuration
#define LED3 33
#define LED2 35 
#define LED1 37 
int led=3; // this may vary based on your hardware configuration. 
int button=9; // this may vary based on your hardware configuration. 

SoftwareSerial Xbee (Rx, Tx);

void setup() {
  Serial.begin(9600); // Set to No line ending;
  Xbee.begin(9600); // type a char, then hit enter
  delay(500); // wait half a second 
  pinMode(led, OUTPUT); 
  pinMode(button, INPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED1, OUTPUT);
}
void loop() {
  int pushed = 0; // the button is *not* pushed by default
  pushed = digitalRead(button);
  if(pushed == HIGH) { // Is the button pushed?
    char outgoing = 'Q'; // sets outgoing character to s
    Xbee.print(outgoing);
    delay(500);
    
}
  if(Xbee.available()) { // Is data a vailable from XBee?
    char incoming = Xbee.read(); // Read character,
    Serial.println(incoming); // send to Serial Monitor
    if(incoming){
      digitalWrite(led, HIGH); // switches on the light if signal is received
      delay(500); // waits half a second
      digitalWrite(led,LOW); // turns off LED
    }
    if(incoming == 's') {
      digitalWrite(LED4, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, HIGH);
      delay(250);
      digitalWrite(LED1, LOW);
      delay(500);
      digitalWrite(LED2, LOW);
      delay(500);
      digitalWrite(LED3, LOW);
      delay(500);
      digitalWrite(LED4, LOW);
      delay(500);
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      delay(500);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      delay(500);
      digitalWrite(LED4, LOW);
      delay(500);
    }
}

  delay(50);
}
