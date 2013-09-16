int REDPin = 6;    // RED pin of the LED to PWM pin 4
int GREENPin = 5;  // GREEN pin of the LED to PWM pin 5
int BLUEPin = 3;   // BLUE pin of the LED to PWM pin 6
int brightness = 0; // LED brightness
int increment = 5;  // brightness increment

void setup()
{
  pinMode(REDPin, OUTPUT);
  pinMode(GREENPin, OUTPUT);
  pinMode(BLUEPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{

  int del = 15;
  brightness = constrain(brightness, 0, 255);
  brightness = 0;
  while( brightness < 255 ){
    analogWrite(REDPin, brightness);
    analogWrite(GREENPin, brightness);
    analogWrite(BLUEPin, brightness);
    brightness += increment;
    delay(del);
  }
  while( brightness >= 0 ){
    analogWrite(REDPin, brightness);
    analogWrite(GREENPin, brightness);
    analogWrite(BLUEPin, brightness);
    brightness -= increment;
    delay(del);
  }
  delay(1000);
  brightness = 0;
  while( brightness < 255 ){
    analogWrite(REDPin, brightness);
    analogWrite(GREENPin, 0);
    analogWrite(BLUEPin, 0);
    brightness += increment;
    delay(del);
  }
  while( brightness >= 0 ){
    analogWrite(REDPin, brightness);
    analogWrite(GREENPin, 0);
    analogWrite(BLUEPin, 0);
    brightness -= increment;
    delay(del);
  }
  delay(1000);
  brightness = 0;
  while( brightness < 255 ){
    analogWrite(REDPin, 0);
    analogWrite(GREENPin, 0);
    analogWrite(BLUEPin, brightness);
    brightness += increment;
    delay(del);
  }
  while( brightness >=0 ){
    analogWrite(REDPin, 0);
    analogWrite(GREENPin, 0);
    analogWrite(BLUEPin, brightness);
    brightness -= increment;
    delay(del);
  }
  delay(1000);
  brightness = 0;
  while( brightness < 255 ){
    analogWrite(REDPin, 0);
    analogWrite(GREENPin, brightness);
    analogWrite(BLUEPin, 0);
    brightness += increment;
    delay(del);
  }
  while( brightness >= 0 ){
    analogWrite(REDPin, 0);
    analogWrite(GREENPin, brightness);
    analogWrite(BLUEPin, 0);
    brightness -= increment;
    delay(del);
  }
  delay(1000);
}

