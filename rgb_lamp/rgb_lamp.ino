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

  while(!Serial.available()){}
  char dir = Serial.read();
  // if its c, clear the LEDs. well make it blue...
  if(dir == 'c'){
    analogWrite(REDPin, 0);
    analogWrite(GREENPin, 0);
    analogWrite(BLUEPin, 120);
  }
  else if(dir == 'n'){
    while(!Serial.available()){}
    int count = (int)(char)Serial.read();
    int pow = map(count, 0, 10, 0, 255);
    analogWrite(REDPin, pow);
    analogWrite(GREENPin, 0);
    analogWrite(BLUEPin, 0);
  }
  //int del = 15;
  //int r, g, b;
  //r = g = b = 0;
  //while( r < 255 ){
    //while( g < 255 ){
        //g += increment;
        //analogWrite(GREENPin, g);
        //delay(del);
      //while( b < 255 ){
        //b += increment;
        //analogWrite(BLUEPin, b);
        //delay(del);
      //}
    //}
    //analogWrite(REDPin, r);
    //r += increment;
    //delay(del);
  //}
  //delay(1000);
}

