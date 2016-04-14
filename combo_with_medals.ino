//patricia torvalds and david betancourt 2016
// april 13 2016 most recent

//begin line following variables
#include <Servo.h>                           // Use the Servo library (included with Arduino IDE)
#include <SoftwareSerial.h>

//line following global variables
Servo servoL;                                // Define the left and right servos
Servo servoR;

int farLP = 2;
int centerLP = 5;
int centerRP = 6;
int farRP = 7;
int Left = 0;
int Right = 0;
int onRamp = 5;
int yesdetach = 0;

//xbee global variables
#define Rx 10 // DOUT to pin 10
#define Tx 11 // DIN to pin 11
#define LED4 38 // change to fit your own LED configuration
#define LED3 39
#define LED2 40
#define LED1 41

int led = 3; // this may vary based on your hardware configuration.
int button = 9; // this may vary based on your hardware configuration.


//Pin definitions
int xaccPin = 8;
int yaccPin = 49;
int heightValue = 0;

//Global height variables
long xacc = 0;
long yacc = 0;

//anthem stuff

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define melodyPin 43
//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

void setup() {
  Serial.begin(9600); // Sets the baud rate to 9600
  //  servoL.attach(13);                         // Attach servos to pins on Arduino
  //  servoR.attach(12);

  //define pinmodes xbee, button, led
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED1, OUTPUT);
  // 7 segment display
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(43, OUTPUT);//buzzer

  // accelerometer
  pinMode(xaccPin, INPUT);
  pinMode(yaccPin, INPUT);

  //clear the initial pin readouts
  digitalWrite(31, LOW);
  digitalWrite(32, LOW);
  digitalWrite(33, LOW);
  digitalWrite(34, LOW);
  digitalWrite(35, LOW);
  digitalWrite(36, LOW);
  digitalWrite(37, LOW);

  // xbee light show

  pinMode(LED4, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED1, OUTPUT);
}

//linefollowing
long RCTime(int sensorIn) {
  long duration = 0;
  pinMode(sensorIn, OUTPUT);     // Make pin OUTPUT
  digitalWrite(sensorIn, HIGH);  // Pin HIGH (discharge capacitor)
  delay(1);                      // Wait 1ms
  pinMode(sensorIn, INPUT);      // Make pin INPUT
  digitalWrite(sensorIn, LOW);   // Turn off internal pullups
  while (digitalRead(sensorIn)) { // Wait for pin to go LOW
    duration++;
  }
  return duration;
}

//line following calibration
int isHighfR(int rctime) {
  if (rctime < 30)
    return 0;
  else
    return 1;
}
int isHighCR(int rctime) {
  if (rctime < 20)
    return 0;
  else
    return 1;
}
int isHighCL(int rctime) {
  if (rctime < 20)
    return 0;
  else
    return 1;
}
int isHighfL(int rctime) {
  if (rctime < 20)
    return 0;
  else
    return 1;
}

// accelerometer stuff
long readAcceleration(int axe) {
  int count = 0;
  long accel = 0;
  int value = 0;

  value = digitalRead(axe);
  while (value == HIGH) { // Loop until pin reads a low
    value = digitalRead(axe);
  }

  while (value == LOW) { // Loop until pin reads a high
    value = digitalRead(axe);
  }

  while (value == HIGH) { // Loop until pin reads a low and count
    value = digitalRead(axe);
    count = count + 1;
  }
  accel = count;
  return accel;
}

//song singing
int song = 0;

void sing(int s) {
  // iterate over the notes of the melody:
  song = s;
  if (song == 2) {
    Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];

      buzz(melodyPin, underworld_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }

  } else {

    Serial.println(" 'Mario Theme'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];

      buzz(melodyPin, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }
  }
}

void buzz(int targetPin, long frequency, long length) {
  //digitalWrite(2, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  // 1 second's worth of microseconds, divided by the frequency, then split in half since
  // there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  // multiply frequency, which is really cycles per second, by the number of seconds to
  // get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  //digitalWrite(2, LOW);

}

//dancing
void dance() {
  servoL.writeMicroseconds(1700);      // Steer robot to recenter it over the line
  servoR.writeMicroseconds(1700);
  delay(500);
  servoL.writeMicroseconds(1700);      // Steer robot to recenter it over the line
  servoR.writeMicroseconds(1300);
  delay(500);
  servoL.writeMicroseconds(1300);      // Steer robot to recenter it over the line
  servoR.writeMicroseconds(1700);
  delay(500);
  servoL.writeMicroseconds(1700);      // Steer robot to recenter it over the line
  servoR.writeMicroseconds(1700);
  delay(500);
  servoL.writeMicroseconds(1300);      // Steer robot to recenter it over the line
  servoR.writeMicroseconds(1300);
  delay(1000);
  servoL.writeMicroseconds(1700);      // Steer robot to recenter it over the line
  servoR.writeMicroseconds(1700);
  delay(500);                               // Delay for 50 milliseconds (1/20 second)

}

void loop() {
  //  delay(50);

  // HEIGHT SENSING
  // variables to read the pulse widths:
  int pulseX, pulseY;
  // variables to contain the resulting accelerations
  int accX, accY;

  // read pulse from x- and y-axes:
  pulseX = pulseIn(xaccPin, HIGH);
  pulseY = pulseIn(yaccPin, HIGH);
  // convert the pulse width into acceleration
  // accelerationX and accelerationY are in milli-g's:
  // earth's gravity is 1000 milli-g's, or 1g.
  accX = ((pulseX / 10) - 500) * 8;
  accY = ((pulseY / 10) - 500) * 8;
  //Grab the accelerometer readings:
  //xacc = readAcceleration(xaccPin); //reads and represents acceleration X
  //yacc = readAcceleration(yaccPin); //reads and represents acceleration Y

  //Print the output to the serial port:
  Serial.print("X:");
  Serial.print(accX);
  Serial.print(" Y:");
  Serial.print(accY);
  Serial.print("\n\r");


  //  delay(100);

  //begin xbee comm code

  //begin xbee loop code (button)
  //Change the status of the LEDs depending on which direction the board is facing
  while (onRamp == 5) {
    if (accX < -365) {
      digitalWrite(31, HIGH);
      digitalWrite(32, LOW);
      digitalWrite(33, HIGH);
      digitalWrite(34, HIGH);
      digitalWrite(35, LOW);
      digitalWrite(36, HIGH);
      digitalWrite(37, HIGH);
      heightValue = 2;
      onRamp = 1;
      Serial.println(onRamp);
      if (onRamp == 1) {
        servoL.attach(13);
        servoR.attach(12);
        servoL.writeMicroseconds(1300);
        servoR.writeMicroseconds(1700);
        delay(1500); //this may change
        servoL.writeMicroseconds(1700);         // Left wheel counterclockwise
        servoR.writeMicroseconds(1700);        // Right wheel clockwise
        delay(750); //this may change           // ...for x microseconds
        onRamp = 8;
        Serial.println(onRamp);
        while (onRamp == 8) {
          onRamp = 8;
          // line following:

          pinMode(farLP, OUTPUT);
          pinMode(centerLP, OUTPUT);
          pinMode(centerRP, OUTPUT);
          pinMode(farRP, OUTPUT);

          digitalWrite(farLP, HIGH);
          digitalWrite(centerLP, HIGH);
          digitalWrite(centerRP, HIGH);
          digitalWrite(farRP, HIGH);
          delayMicroseconds(230); // allow capcitor charge in QTI

          pinMode(farLP, INPUT);
          pinMode(centerLP, INPUT);
          pinMode(centerRP, INPUT);
          pinMode(farRP, INPUT);

          digitalWrite(farLP, LOW);
          digitalWrite(centerLP, LOW);
          digitalWrite(centerRP, LOW);
          digitalWrite(farRP, LOW);

          delayMicroseconds(230);

          int pin4 = isHighfR(RCTime(farRP));
          int pin1 = isHighCR(RCTime(centerRP));
          int pin2 = isHighCL(RCTime(centerLP));
          int pin3 = isHighfL(RCTime(farLP));
          //Serial.println(RCTime(centerLP));
          String s = String(pin4) + String(pin1) + String(pin2) + String(pin3);
          int pins = s.toInt();
          Serial.println(pins);

          // Determine how to steer based on state of the four QTI sensors
          int vL, vR;
          switch (pins)                              // Compare pins to known line following states
          {
            case 1000:
              vL = -200;                             // -100 to 100 indicate course correction values
              vR = 200;                              // -100: full reverse; 0=stopped; 100=full forward
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 1100:
              vL = -200;
              vR = 0;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 101:
              vL = -200;
              vR = -200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
            //      delay(50);
            //  break; //DID NOT DO THIS BEFORE
            case 1010:
              vL = 200;
              vR = 200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
            // break; //DID NOT DO THIS BEFORE
            case 100:
              vL = -200;
              vR = 200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 110:
              vL = 100;
              vR = 100;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 10:
              vL = 200;
              vR = 200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 11:
              vL = 0;
              vR = -200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 1:
              vL = 200;
              vR = -200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 1110:
              vL = -200;
              vR = 200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 111:
              vL = 200;
              vR = -200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 1111:
              servoL.detach();                        // Stop sending servo signals
              servoR.detach();
              yesdetach = 1;
              onRamp = 40;
              break;
            case 0000:
              vL = 0;
              vR = 0;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
          }
        }
      }
    }
    else if (accX < -190) {
      digitalWrite(31, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(33, LOW);
      digitalWrite(34, LOW);
      digitalWrite(35, LOW);
      digitalWrite(36, LOW);
      digitalWrite(37, LOW);
      heightValue = 1;
      onRamp = 1;
      if (onRamp == 1) {
        servoL.attach(13);
        servoR.attach(12);
        servoL.writeMicroseconds(1300);
        servoR.writeMicroseconds(1700);
        delay(1500); //this may change
        servoL.writeMicroseconds(1700);         // Left wheel counterclockwise
        servoR.writeMicroseconds(1700);        // Right wheel clockwise
        delay(750); //this may change           // ...for x microseconds
        onRamp = 8;
        Serial.println(onRamp);
        while (onRamp == 8) {
          onRamp = 8;
          // line following:

          pinMode(farLP, OUTPUT);
          pinMode(centerLP, OUTPUT);
          pinMode(centerRP, OUTPUT);
          pinMode(farRP, OUTPUT);

          digitalWrite(farLP, HIGH);
          digitalWrite(centerLP, HIGH);
          digitalWrite(centerRP, HIGH);
          digitalWrite(farRP, HIGH);
          delayMicroseconds(230); // allow capcitor charge in QTI

          pinMode(farLP, INPUT);
          pinMode(centerLP, INPUT);
          pinMode(centerRP, INPUT);
          pinMode(farRP, INPUT);

          digitalWrite(farLP, LOW);
          digitalWrite(centerLP, LOW);
          digitalWrite(centerRP, LOW);
          digitalWrite(farRP, LOW);

          delayMicroseconds(230);

          int pin4 = isHighfR(RCTime(farRP));
          int pin1 = isHighCR(RCTime(centerRP));
          int pin2 = isHighCL(RCTime(centerLP));
          int pin3 = isHighfL(RCTime(farLP));
          //Serial.println(RCTime(centerLP));
          String s = String(pin4) + String(pin1) + String(pin2) + String(pin3);
          int pins = s.toInt();
          Serial.println(pins);

          // Determine how to steer based on state of the four QTI sensors
          int vL, vR;
          switch (pins)                              // Compare pins to known line following states
          {
            case 1000:
              vL = -200;                             // -100 to 100 indicate course correction values
              vR = 200;                              // -100: full reverse; 0=stopped; 100=full forward
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 1100:
              vL = -200;
              vR = 0;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 101:
              vL = -200;
              vR = -200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
            //      delay(50);
            //  break; //DID NOT DO THIS BEFORE
            case 1010:
              vL = 200;
              vR = 200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
            // break; //DID NOT DO THIS BEFORE
            case 100:
              vL = -200;
              vR = 200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 110:
              vL = 100;
              vR = 100;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 10:
              vL = 200;
              vR = 200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 11:
              vL = 0;
              vR = -200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 1:
              vL = 200;
              vR = -200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 1110:
              vL = -200;
              vR = 200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 111:
              vL = 200;
              vR = -200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 1111:
              servoL.detach();                        // Stop sending servo signals
              servoR.detach();
              yesdetach = 1;
              onRamp = 40;
              break;
            case 0000:
              vL = 0;
              vR = 0;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
          }
        }
      }
    }
    else if (accX < 45) {
      digitalWrite(31, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(34, HIGH);
      digitalWrite(35, HIGH);
      digitalWrite(36, HIGH);
      digitalWrite(37, LOW);
      heightValue = 0;
      onRamp = 1;
      if (onRamp == 1) {
        servoL.attach(13);
        servoR.attach(12);
        servoL.writeMicroseconds(1300);
        servoR.writeMicroseconds(1700);
        delay(1500); //this may change
        servoL.writeMicroseconds(1700);         // Left wheel counterclockwise
        servoR.writeMicroseconds(1700);        // Right wheel clockwise
        delay(750); //this may change           // ...for x microseconds
        onRamp = 8;
        Serial.println(onRamp);
        while (onRamp == 8) {
          // line following:
          pinMode(farLP, OUTPUT);
          pinMode(centerLP, OUTPUT);
          pinMode(centerRP, OUTPUT);
          pinMode(farRP, OUTPUT);

          digitalWrite(farLP, HIGH);
          digitalWrite(centerLP, HIGH);
          digitalWrite(centerRP, HIGH);
          digitalWrite(farRP, HIGH);
          delayMicroseconds(230); // allow capcitor charge in QTI

          pinMode(farLP, INPUT);
          pinMode(centerLP, INPUT);
          pinMode(centerRP, INPUT);
          pinMode(farRP, INPUT);

          digitalWrite(farLP, LOW);
          digitalWrite(centerLP, LOW);
          digitalWrite(centerRP, LOW);
          digitalWrite(farRP, LOW);

          delayMicroseconds(230);

          int pin4 = isHighfR(RCTime(farRP));
          int pin1 = isHighCR(RCTime(centerRP));
          int pin2 = isHighCL(RCTime(centerLP));
          int pin3 = isHighfL(RCTime(farLP));
          //Serial.println(RCTime(centerLP));
          String s = String(pin4) + String(pin1) + String(pin2) + String(pin3);
          int pins = s.toInt();
          Serial.println(pins);

          // Determine how to steer based on state of the four QTI sensors
          int vL, vR;
          switch (pins)                              // Compare pins to known line following states
          {
            case 1000:
              vL = -200;                             // -100 to 100 indicate course correction values
              vR = 200;                              // -100: full reverse; 0=stopped; 100=full forward
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 1100:
              vL = -200;
              vR = 0;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 101:
              vL = -200;
              vR = -200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
            //      delay(50);
            //  break; //DID NOT DO THIS BEFORE
            case 1010:
              vL = 200;
              vR = 200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
            // break; //DID NOT DO THIS BEFORE
            case 100:
              vL = -200;
              vR = 200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 110:
              vL = 100;
              vR = 100;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 10:
              vL = 200;
              vR = 200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 11:
              vL = 0;
              vR = -200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 1:
              vL = 200;
              vR = -200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 1110:
              vL = -200;
              vR = 200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 111:
              vL = 200;
              vR = -200;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
            case 1111:
              servoL.detach();                        // Stop sending servo signals
              servoR.detach();
              yesdetach = 1;
              onRamp = 40;
              break;
            case 0000:
              vL = 0;
              vR = 0;
              servoL.writeMicroseconds(1500 + vL);      // Steer robot to recenter it over the line
              servoR.writeMicroseconds(1500 - vR);
              delay(50);
              break;
          }

        }
      }
    }
    if (yacc > 1200) {
      digitalWrite(5, HIGH);
    } else {
      digitalWrite(5, LOW);
    }
    Serial.println("yd" + yesdetach);
    if (yesdetach == 1) {
      SoftwareSerial Xbee (Rx, Tx);
      Xbee.begin(9600); // type a char, then hit enter
      //begin xbee comm code
      int pushed = 0; // the button is *not* pushed by default
      pushed = digitalRead(button);
      while (heightValue == 0) { // Is the button pushed?
        char outgoing = 'f'; // sets outgoing character to s
        Xbee.print(outgoing);
        delay(500);
        if (Xbee.available()) { // Is data a vailable from XBee?
          char incoming = Xbee.read(); // Read character,
          Serial.println(incoming); // send to Serial Monitor
          if (incoming == 0) {
            ServoL.attach(13);
            ServoR.attach(12);
            pinMode(farLP, OUTPUT);
            pinMode(centerLP, OUTPUT);
            pinMode(centerRP, OUTPUT);
            pinMode(farRP, OUTPUT);

            digitalWrite(farLP, HIGH);
            digitalWrite(centerLP, HIGH);
            digitalWrite(centerRP, HIGH);
            digitalWrite(farRP, HIGH);
            delayMicroseconds(230); // allow capcitor charge in QTI

            pinMode(farLP, INPUT);
            pinMode(centerLP, INPUT);
            pinMode(centerRP, INPUT);
            pinMode(farRP, INPUT);

            digitalWrite(farLP, LOW);
            digitalWrite(centerLP, LOW);
            digitalWrite(centerRP, LOW);
            digitalWrite(farRP, LOW);

            delayMicroseconds(230);
            dance();
            return;
          }
          else if (incoming == 1) {
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
          else if (incoming == 2) {
            sing(1);
            sing(1);
            sing(2);
          }
        }
        delay(50);

      }

      while (heightValue == 1) {
        char outgoing = 'e';
        Xbee.print(outgoing);
        delay(500);
        if (Xbee.available()) { // Is data a vailable from XBee?
          char incoming = Xbee.read(); // Read character,
          Serial.println(incoming); // send to Serial Monitor
          if (incoming == 0) {
            ServoL.attach(13);
            ServoR.attach(12);
            pinMode(farLP, OUTPUT);
            pinMode(centerLP, OUTPUT);
            pinMode(centerRP, OUTPUT);
            pinMode(farRP, OUTPUT);

            digitalWrite(farLP, HIGH);
            digitalWrite(centerLP, HIGH);
            digitalWrite(centerRP, HIGH);
            digitalWrite(farRP, HIGH);
            delayMicroseconds(230); // allow capcitor charge in QTI

            pinMode(farLP, INPUT);
            pinMode(centerLP, INPUT);
            pinMode(centerRP, INPUT);
            pinMode(farRP, INPUT);

            digitalWrite(farLP, LOW);
            digitalWrite(centerLP, LOW);
            digitalWrite(centerRP, LOW);
            digitalWrite(farRP, LOW);

            delayMicroseconds(230);
            dance();
            return;
          }
          else if (incoming == 1) {
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
          else if (incoming == 2) {
            sing(1);
            sing(1);
            sing(2);
          }

        }
        delay(50);      
      while (heightValue == 2) {
        char outgoing = 'd';
        Xbee.print(outgoing);
        delay(500);
        if (Xbee.available()) { // Is data a vailable from XBee?
          char incoming = Xbee.read(); // Read character,
          Serial.println(incoming); // send to Serial Monitor
          if (incoming == 0) {
            ServoL.attach(13);
            ServoR.attach(12);
            pinMode(farLP, OUTPUT);
            pinMode(centerLP, OUTPUT);
            pinMode(centerRP, OUTPUT);
            pinMode(farRP, OUTPUT);

            digitalWrite(farLP, HIGH);
            digitalWrite(centerLP, HIGH);
            digitalWrite(centerRP, HIGH);
            digitalWrite(farRP, HIGH);
            delayMicroseconds(230); // allow capcitor charge in QTI

            pinMode(farLP, INPUT);
            pinMode(centerLP, INPUT);
            pinMode(centerRP, INPUT);
            pinMode(farRP, INPUT);

            digitalWrite(farLP, LOW);
            digitalWrite(centerLP, LOW);
            digitalWrite(centerRP, LOW);
            digitalWrite(farRP, LOW);

            delayMicroseconds(230);
            dance();
            return;
          }
          else if (incoming == 1) {
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
          else if (incoming == 2) {
            sing(1);
            sing(1);
            sing(2);
          }

          delay(50);
        }

      }

    }
  }
}
