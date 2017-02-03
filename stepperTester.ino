/* Copyright 2017 mirage335

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
  
  modified 8 Sep 2016
  by Colby Newman
*/

/* Read Quadrature Encoder
  * Connect Encoder to Pins encoder0PinA, encoder0PinB, and +5V.
  *
  * Sketch by max wolf / www.meso.net
  * v. 0.1 - very basic functions - mw 20061220
  *
  */

//https://www.youtube.com/watch?v=v4BbSzJ-hz4

//http://www.instructables.com/id/Drive-a-Stepper-Motor-with-an-Arduino-and-a-A4988-/?ALLSTEPS
// Run a A4998 Stepstick from an Arduino UNO.
// Paul Hurley Aug 2015

//https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay

 int val; 
 int encoder0PinA = 12;
 int encoder0PinB = 11;
 int encoder0Pos = 0;
 int encoder0PinALast = LOW;
 int n = LOW;
 
 int encoder0Ground = 8;
 int encoder0Power = 9;
 int encoder0Button = 10;

 int stepper0Enable = 4;
 int stepper0Step = 3;
 int stepper0Dir = 2;

 bool steper0On = true;

 unsigned long interval = 1000;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

   pinMode (encoder0PinA,INPUT);
   pinMode (encoder0PinB,INPUT);

   pinMode (encoder0Button,INPUT);
   
   pinMode(encoder0Power, OUTPUT);
   digitalWrite (encoder0Power, HIGH);
   pinMode(encoder0Ground, OUTPUT);
   digitalWrite (encoder0Ground, LOW);
   
   pinMode(stepper0Enable, OUTPUT);
   pinMode(stepper0Step, OUTPUT);
   pinMode(stepper0Dir, OUTPUT);
   digitalWrite(stepper0Enable, LOW);
   
   
   encoder0PinALast = digitalRead(encoder0PinA);
   
   
   Serial.begin (9600);
}

void step() {
  digitalWrite(stepper0Step,HIGH); // Output high
  //delay(1); // Wait
  digitalWrite(stepper0Step,LOW); // Output low

  steper0On = true;
}

// the loop function runs over and over again forever
void loop() {
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(1000);                       // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  //delay(1000);                       // wait for a second

   static unsigned long currentMillis = millis();
   static unsigned long previousMillis = millis();

   n = digitalRead(encoder0PinA);
   if ((encoder0PinALast == LOW) && (n == HIGH)) {
     if (digitalRead(encoder0PinB) == LOW) {
       encoder0Pos--;
       digitalWrite(stepper0Dir, LOW);
       digitalWrite(stepper0Enable,LOW);
       step();
     } else {
       encoder0Pos++;
       digitalWrite(stepper0Dir, HIGH);
       digitalWrite(stepper0Enable,LOW);
       step();
     }
     interval = 10000;
     previousMillis = currentMillis;
     Serial.println (encoder0Pos);
   } 
   encoder0PinALast = n;

   int buttonState = 0;
   buttonState += digitalRead(encoder0Button);
   delay(1);
   buttonState += digitalRead(encoder0Button);
   buttonState *= 0.5;
   
   digitalWrite(LED_BUILTIN, buttonState);

   if (buttonState == 0) {
      digitalWrite(stepper0Enable,LOW);
      digitalWrite(stepper0Dir,HIGH); // Set Dir high
      
      
      Serial.println("Bunch of steps.");
      for(int i = 0; i < 100; i++)
      {
        step();
        delay(1); // Wait
      }

      previousMillis = currentMillis;
      interval = 1000;
   }

   currentMillis = millis();
   if ((currentMillis - previousMillis >= interval) && (steper0On)) {
      digitalWrite(stepper0Enable,HIGH);
      steper0On=false;
   }
   


  
}




