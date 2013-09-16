int REDPin = 6;    // RED pin of the LED to PWM pin 4
int GREENPin = 5;  // GREEN pin of the LED to PWM pin 5
int BLUEPin = 3;   // BLUE pin of the LED to PWM pin 6
int increment = 5;  // brightness increment

int ser_buf = 0;
boolean has_unread = false;
int del = 20;
int min_pow = 100;

void setup()
{
  pinMode(REDPin, OUTPUT);
  pinMode(GREENPin, OUTPUT);
  pinMode(BLUEPin, OUTPUT);
  Serial.begin(9600);
  while( Serial.available() == 0 ){}
  Serial.read();
  Serial.print("hey");
}

void clearMessages(){
  has_unread = false;
  analogWrite(REDPin, 0);
  analogWrite(GREENPin, 0);
  analogWrite(BLUEPin, min_pow);
}

void setMessages(int count){
  has_unread = true;
  //int pow = map(count, 0, 10, 0, 255);
  analogWrite(REDPin, min_pow);
  analogWrite(GREENPin, 0);
  analogWrite(BLUEPin, 0);
}

void doAnimation(){
  int pow = min_pow;
  int g = 0;
  while( pow < 255 ){
    if( has_unread ) {
      analogWrite(REDPin, pow);
      analogWrite(BLUEPin, 0);
    }
    else {
      analogWrite(REDPin, 0);
      analogWrite(BLUEPin, pow);
    }
    analogWrite(GREENPin, 0);
    pow += increment;
    delay(del);
  }
  while( g < 255 ){
    analogWrite(GREENPin, g);
    g += increment;
    delay(del);
  }
  while( g > 0 ){
    analogWrite(GREENPin, g);
    g -= increment;
    delay(del);
  }
  while( pow > min_pow ){
    if( has_unread ) {
      analogWrite(REDPin, pow);
      analogWrite(BLUEPin, 0);
    }
    else {
      analogWrite(REDPin, 0);
      analogWrite(BLUEPin, pow);
    }
    analogWrite(GREENPin, 0);
    pow -= increment;
    delay(del);
  }
}

void loop()
{
  while( (ser_buf = Serial.available()) == 0 ){
    doAnimation();
  }
  char dir = Serial.read();
  // if its c, clear the LEDs. well make it blue...
  if(dir == 'c'){
    clearMessages();
  }
  else if(dir == 'n'){
    delay(2);
    while(!Serial.available()){}
    int count = (int)(char)Serial.read();
    setMessages(count);
  }
}

