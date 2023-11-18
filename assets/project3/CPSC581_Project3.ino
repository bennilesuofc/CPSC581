#include <Servo.h>

const int inputLedPin=13;
const int waitLedPin=9;
const int sensorPin= 12;
const int analogPin = A0;
bool inputState =0;
int sensorValue = 0;
int outputValue = 0;
bool hasInput = 0;

unsigned long prevMillis = 0;
unsigned long currMillis = 0;
const int interval = 3000;

Servo servo1;

void setup(){
  pinMode(inputLedPin, OUTPUT);
  pinMode(waitLedPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  servo1.attach(7);
  servo1.write(90);
  Serial.begin (9600);
}
  
void loop (){

  //check if currently receiving input
  //if so, wait three seconds and check again a few times
  //if no input send a signal

  inputState = digitalRead(sensorPin);

  currMillis = millis();
  // when the sensor detects a signal above the threshold value, LED flashes
  //sensor writes LOW when receiving signal
  if (inputState==LOW) {
    hasInput = 1;
    prevMillis = currMillis;
    digitalWrite(inputLedPin, HIGH);
    //Serial.println("input start");
   
  }
  else if(hasInput){
    if(currMillis - prevMillis >=interval){//amount of time has passed since recieving input
      hasInput = 0;
      digitalWrite(inputLedPin, LOW);
      digitalWrite(waitLedPin, HIGH);

      //read delay from potentiometer
      sensorValue = analogRead(analogPin);
      outputValue = map(sensorValue, 0, 1023, 0, 5000);
      Serial.print("sensor = " );
      Serial.print(sensorValue);
      Serial.print("\t output = ");
      Serial.println(outputValue);
      
      Serial.println("waiting for delay...");
      delay(outputValue);
      Serial.println("delay passed- firing servo");
     
      servo1.write(110);//drum hit 1
      delay(150);
      servo1.write(90);//move back
      delay(150);
      servo1.write(110);//drum hit 2
      delay(250);
      servo1.write(90);//move back
      delay(400);
      servo1.write(80);//cymbal hit
      delay(250);
      servo1.write(90);//reset position
      delay(1500);//wait so sound sensor isn't triggered by sound from drums or servos
      digitalWrite(waitLedPin, LOW);
      Serial.println("ba dum tish");
    }
  }
  else {
    digitalWrite(inputLedPin, LOW);
  }
  delay(200);//wait a little for analog stuff to settle
}