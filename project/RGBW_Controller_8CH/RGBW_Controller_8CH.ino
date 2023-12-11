#include <Wire.h>
#include <PCA9685.h>
#include <Thread.h>

PCA9685 pwm1;
PCA9685 pwm2;

Thread StatusRGB = Thread();

String newLed;

int n = 0;
int tickSpeed = 4;
int allUpTickCounter = 0;
int updateChannel = 0;

static const uint8_t StatusChannel[] = {8, 7, 6, 5, 4, 3, A3, A1};
int statusCounter = 0;

int StatusCh1[] = {0,0,0,0};
int StatusCh2[] = {0,0,0,0};
int StatusCh3[] = {0,0,0,0};
int StatusCh4[] = {0,0,0,0};
int StatusCh5[] = {0,0,0,0};
int StatusCh6[] = {0,0,0,0};
int StatusCh7[] = {0,0,0,0};
int StatusCh8[] = {0,0,0,0};

//Change 1 Ch    0-8       0-4096    0-4096    0-4096    0-4096
void tickRGB(int channel, int red, int green, int blue, int white) { 
    //channel range = 0-7 (1,2,3,7 on pwm1) (4,5,6,8 on pwm2)
    //color ranges = 0-4096
    
    if (channel == 1)
    {
      pwm1.setChannelPWM(3, blue);
      pwm1.setChannelPWM(2, white);
      pwm1.setChannelPWM(1, red);
      pwm1.setChannelPWM(0, green);
      
      StatusCh1[0] = blue;
      StatusCh1[1] = white;
      StatusCh1[2] = red;
      StatusCh1[3] = green;
    }
    if (channel == 2)
    {
      pwm1.setChannelPWM(7, blue);
      pwm1.setChannelPWM(6, white);
      pwm1.setChannelPWM(5, red);
      pwm1.setChannelPWM(4, green);
      
      StatusCh2[0] = blue;
      StatusCh2[1] = white;
      StatusCh2[2] = red;
      StatusCh2[3] = green;
    }
    if (channel == 3)
    {
      pwm1.setChannelPWM(11, blue);
      pwm1.setChannelPWM(10, white);
      pwm1.setChannelPWM(9, red);
      pwm1.setChannelPWM(8, green);

      StatusCh3[0] = blue;
      StatusCh3[1] = white;
      StatusCh3[2] = red;
      StatusCh3[3] = green;
    }
    if (channel == 4)
    {
      pwm2.setChannelPWM(0, blue);
      pwm2.setChannelPWM(1, white);
      pwm2.setChannelPWM(2, red);
      pwm2.setChannelPWM(3, green);
      
      StatusCh4[0] = blue;
      StatusCh4[1] = white;
      StatusCh4[2] = red;
      StatusCh4[3] = green;
    }
    if (channel == 5)
    {
      pwm2.setChannelPWM(4, blue);
      pwm2.setChannelPWM(5, white);
      pwm2.setChannelPWM(6, red);
      pwm2.setChannelPWM(7, green);
      
      StatusCh5[0] = blue;
      StatusCh5[1] = white;
      StatusCh5[2] = red;
      StatusCh5[3] = green;
    }
    if (channel == 6)
    {
      pwm2.setChannelPWM(8, blue);
      pwm2.setChannelPWM(9, white);
      pwm2.setChannelPWM(10, red);
      pwm2.setChannelPWM(11, green);
      
      StatusCh6[0] = blue;
      StatusCh6[1] = white;
      StatusCh6[2] = red;
      StatusCh6[3] = green;
    }
    if (channel == 7)
    {
      pwm1.setChannelPWM(15, blue);
      pwm1.setChannelPWM(14, white);
      pwm1.setChannelPWM(13, red);
      pwm1.setChannelPWM(12, green);
      
      StatusCh7[0] = blue;
      StatusCh7[1] = white;
      StatusCh7[2] = red;
      StatusCh7[3] = green;
    }
    if (channel == 8)
    {
      pwm2.setChannelPWM(12, blue);
      pwm2.setChannelPWM(13, white);
      pwm2.setChannelPWM(14, red);
      pwm2.setChannelPWM(15, green);
      
      StatusCh8[0] = blue;
      StatusCh8[1] = white;
      StatusCh8[2] = red;
      StatusCh8[3] = green;
    }
  }

//LEDs Up     0-4096         0-4096         0-4096       0-4096          0-4096               0-4096                   0-4096
void allUp(int initRed, int initGreen, int initBlue, int initWhite, int tickSpeed = 1, int minBrightness = 0, int maxBrightness = 4096) {

  float redMultiplier = float(initRed) / 4096;
  float greenMultiplier = float(initGreen) / 4096;
  float blueMultiplier = float(initBlue) / 4096;
  float whiteMultiplier = float(initWhite) / 4096;

  for(allUpTickCounter = minBrightness; allUpTickCounter <= maxBrightness; allUpTickCounter = allUpTickCounter + tickSpeed) {

    int red = int(allUpTickCounter * redMultiplier);
    int green = int(allUpTickCounter * greenMultiplier);
    int blue = int(allUpTickCounter * blueMultiplier);
    int white = int(allUpTickCounter * whiteMultiplier);
  
    uint16_t pwms1[16];
    pwms1[0] = green;
    pwms1[1] = red;
    pwms1[2] = white;
    pwms1[3] = blue;
    pwms1[4] = green;
    pwms1[5] = red;
    pwms1[6] = white;
    pwms1[7] = blue;
    pwms1[8] = green;
    pwms1[9] = red;
    pwms1[10] = white;
    pwms1[11] = blue;
    pwms1[12] = green;
    pwms1[13] = red;
    pwms1[14] = white;
    pwms1[15] = blue;

    uint16_t pwms2[16];
    pwms2[0] = blue;
    pwms2[1] = white;
    pwms2[2] = red;
    pwms2[3] = green;
    pwms2[4] = blue;
    pwms2[5] = white;
    pwms2[6] = red;
    pwms2[7] = green;
    pwms2[8] = blue;
    pwms2[9] = white;
    pwms2[10] = red;
    pwms2[11] = green;
    pwms2[12] = blue;
    pwms2[13] = white;
    pwms2[14] = red;
    pwms2[15] = green;

    pwm1.setChannelsPWM(0, 16, pwms1);
    pwm2.setChannelsPWM(0, 16, pwms2);

    for(statusCounter = 0; statusCounter < 8; statusCounter++) {
      analogWrite(9, ((red / 32) + (white / 32)));
      analogWrite(10, ((green / 32) + (white / 32)));
      analogWrite(11, ((blue / 32) + (white / 32)));
      digitalWrite(StatusChannel[statusCounter], HIGH);
    }
    if (allUpTickCounter == maxBrightness) {
      StatusCh1[0] = blue; StatusCh1[1] = white; StatusCh1[2] = red; StatusCh1[3] = green;
      StatusCh2[0] = blue; StatusCh2[1] = white; StatusCh2[2] = red; StatusCh2[3] = green;
      StatusCh3[0] = blue; StatusCh3[1] = white; StatusCh3[2] = red; StatusCh3[3] = green;
      StatusCh4[0] = blue; StatusCh4[1] = white; StatusCh4[2] = red; StatusCh4[3] = green;
      StatusCh5[0] = blue; StatusCh5[1] = white; StatusCh5[2] = red; StatusCh5[3] = green;
      StatusCh6[0] = blue; StatusCh6[1] = white; StatusCh6[2] = red; StatusCh6[3] = green;
      StatusCh7[0] = blue; StatusCh7[1] = white; StatusCh7[2] = red; StatusCh7[3] = green;
      StatusCh8[0] = blue; StatusCh8[1] = white; StatusCh8[2] = red; StatusCh8[3] = green;

      for(statusCounter = 0; statusCounter < 8; statusCounter++) {
        digitalWrite(StatusChannel[statusCounter], LOW);
      }
    }
  }
}
//LEDs Down    0-4096         0-4096         0-4096       0-4096          0-4096               0-4096                   0-4096
void allDown(int initRed, int initGreen, int initBlue, int initWhite, int tickSpeed = 1, int minBrightness = 0, int maxBrightness = 4096) {

  float redMultiplier = float(initRed) / 4096;
  float greenMultiplier = float(initGreen) / 4096;
  float blueMultiplier = float(initBlue) / 4096;
  float whiteMultiplier = float(initWhite) / 4096;

  for(allUpTickCounter = maxBrightness; allUpTickCounter >= minBrightness; allUpTickCounter = allUpTickCounter - tickSpeed) {

    int red = int(allUpTickCounter * redMultiplier);
    int green = int(allUpTickCounter * greenMultiplier);
    int blue = int(allUpTickCounter * blueMultiplier);
    int white = int(allUpTickCounter * whiteMultiplier);
  
    uint16_t pwms1[16];
    pwms1[0] = green;
    pwms1[1] = red;
    pwms1[2] = white;
    pwms1[3] = blue;
    pwms1[4] = green;
    pwms1[5] = red;
    pwms1[6] = white;
    pwms1[7] = blue;
    pwms1[8] = green;
    pwms1[9] = red;
    pwms1[10] = white;
    pwms1[11] = blue;
    pwms1[12] = green;
    pwms1[13] = red;
    pwms1[14] = white;
    pwms1[15] = blue;

    uint16_t pwms2[16];
    pwms2[0] = blue;
    pwms2[1] = white;
    pwms2[2] = red;
    pwms2[3] = green;
    pwms2[4] = blue;
    pwms2[5] = white;
    pwms2[6] = red;
    pwms2[7] = green;
    pwms2[8] = blue;
    pwms2[9] = white;
    pwms2[10] = red;
    pwms2[11] = green;
    pwms2[12] = blue;
    pwms2[13] = white;
    pwms2[14] = red;
    pwms2[15] = green;

    pwm1.setChannelsPWM(0, 16, pwms1);
    pwm2.setChannelsPWM(0, 16, pwms2);

    for(statusCounter = 0; statusCounter < 8; statusCounter++) {
      analogWrite(9, ((red / 32) + (white / 32)));
      analogWrite(10, ((green / 32) + (white / 32)));
      analogWrite(11, ((blue / 32) + (white / 32)));
      digitalWrite(StatusChannel[statusCounter], HIGH);
    }
    if (allUpTickCounter == minBrightness) {
      StatusCh1[0] = blue; StatusCh1[1] = white; StatusCh1[2] = red; StatusCh1[3] = green;
      StatusCh2[0] = blue; StatusCh2[1] = white; StatusCh2[2] = red; StatusCh2[3] = green;
      StatusCh3[0] = blue; StatusCh3[1] = white; StatusCh3[2] = red; StatusCh3[3] = green;
      StatusCh4[0] = blue; StatusCh4[1] = white; StatusCh4[2] = red; StatusCh4[3] = green;
      StatusCh5[0] = blue; StatusCh5[1] = white; StatusCh5[2] = red; StatusCh5[3] = green;
      StatusCh6[0] = blue; StatusCh6[1] = white; StatusCh6[2] = red; StatusCh6[3] = green;
      StatusCh7[0] = blue; StatusCh7[1] = white; StatusCh7[2] = red; StatusCh7[3] = green;
      StatusCh8[0] = blue; StatusCh8[1] = white; StatusCh8[2] = red; StatusCh8[3] = green;
      
      for(statusCounter = 0; statusCounter < 8; statusCounter++) {
        digitalWrite(StatusChannel[statusCounter], LOW);
      }
    }
  }
}

void statusLed() {

  if (updateChannel == 1) {
    digitalWrite(StatusChannel[7], LOW);
    analogWrite(9, ((StatusCh1[2] / 32) + (StatusCh1[1] / 33)));
    analogWrite(10, ((StatusCh1[3] / 32) + (StatusCh1[1] / 33)));
    analogWrite(11, ((StatusCh1[0] / 32) + (StatusCh1[1] / 33)));
    digitalWrite(StatusChannel[0], HIGH);
  }

  if (updateChannel == 2) {
    digitalWrite(StatusChannel[0], LOW);
    analogWrite(9, ((StatusCh2[2] / 32) + (StatusCh2[1] / 33)));
    analogWrite(10, ((StatusCh2[3] / 32) + (StatusCh2[1] / 33)));
    analogWrite(11, ((StatusCh2[0] / 32) + (StatusCh2[1] / 33)));
    digitalWrite(StatusChannel[1], HIGH);
  }

  if (updateChannel == 3) {
    digitalWrite(StatusChannel[1], LOW);
    analogWrite(9, ((StatusCh3[2] / 32) + (StatusCh3[1] / 33)));
    analogWrite(10, ((StatusCh3[3] / 32) + (StatusCh3[1] / 33)));
    analogWrite(11, ((StatusCh3[0] / 32) + (StatusCh3[1] / 33)));
    digitalWrite(StatusChannel[2], HIGH);
  }

  if (updateChannel == 4) {
    digitalWrite(StatusChannel[2], LOW);
    analogWrite(9, ((StatusCh4[2] / 32) + (StatusCh4[1] / 33)));
    analogWrite(10, ((StatusCh4[3] / 32) + (StatusCh4[1] / 33)));
    analogWrite(11, ((StatusCh4[0] / 32) + (StatusCh4[1] / 33)));
    digitalWrite(StatusChannel[3], HIGH);
  }

  if (updateChannel == 5) {
    digitalWrite(StatusChannel[3], LOW);
    analogWrite(9, ((StatusCh5[2] / 32) + (StatusCh5[1] / 33)));
    analogWrite(10, ((StatusCh5[3] / 32) + (StatusCh5[1] / 33)));
    analogWrite(11, ((StatusCh5[0] / 32) + (StatusCh5[1] / 33)));
    digitalWrite(StatusChannel[4], HIGH);
  }

  if (updateChannel == 6) {
    digitalWrite(StatusChannel[4], LOW);
    analogWrite(9, ((StatusCh6[2] / 32) + (StatusCh6[1] / 33)));
    analogWrite(10, ((StatusCh6[3] / 32) + (StatusCh6[1] / 33)));
    analogWrite(11, ((StatusCh6[0] / 32) + (StatusCh6[1] / 33)));
    digitalWrite(StatusChannel[5], HIGH);
  }
  
  if (updateChannel == 7) {
    digitalWrite(StatusChannel[5], LOW);
    analogWrite(9, ((StatusCh7[2] / 32) + (StatusCh7[1] / 33)));
    analogWrite(10, ((StatusCh7[3] / 32) + (StatusCh7[1] / 33)));
    analogWrite(11, ((StatusCh7[0] / 32) + (StatusCh7[1] / 33)));
    digitalWrite(StatusChannel[6], HIGH);
  }

  if (updateChannel == 8) {
    digitalWrite(StatusChannel[6], LOW);
    analogWrite(9, ((StatusCh8[2] / 32) + (StatusCh8[1] / 33)));
    analogWrite(10, ((StatusCh8[3] / 32) + (StatusCh8[1] / 33)));
    analogWrite(11, ((StatusCh8[0] / 32) + (StatusCh8[1] / 33)));
    digitalWrite(StatusChannel[7], HIGH);
  }
  
  if(StatusRGB.shouldRun()) {
    StatusRGB.run();
  }
}

void statusLedHelper() {
  updateChannel ++;
  
  if(updateChannel == 9) {
    updateChannel = 1;
  }
}

void doSerialUpdate() {
  //Check for incoming serial data
  while (Serial.available()) {
    delayMicroseconds(100); 
    char incomingChar = Serial.read();
    newLed += incomingChar;
  }
  
  //Example incoming string: t14096123404931472
  //Example blown up: t 1 4096 1234 0493 1472
  if(newLed.indexOf("t") > -1) { 
    tickRGB((newLed.substring(1,2)).toInt(), (newLed.substring(2,6)).toInt(), (newLed.substring(6,10)).toInt(), (newLed.substring(10,14)).toInt(), (newLed.substring(14,18)).toInt());
    updateChannel = 0;
    newLed = "";
  }
  
  //Example incoming string: u4096409640964096000100004096
  //Example blown up: u 4096 4096 4096 4096 0001 0000 4096
  else if(newLed.indexOf("u") > -1) { 
    allUp((newLed.substring(1,5)).toInt(), (newLed.substring(5,9)).toInt(), (newLed.substring(9,13)).toInt(), (newLed.substring(13,17)).toInt(), (newLed.substring(17,21)).toInt(), (newLed.substring(21,25)).toInt(), (newLed.substring(25,29)).toInt());
    updateChannel = 0;
    newLed = "";
  }
    
  //Example incoming string: d4096409640964096000100004096
  //Example blown up: d 4096 4096 4096 4096 0001 0000 4096
  else if(newLed.indexOf("d") > -1) { 
    allDown((newLed.substring(1,5)).toInt(), (newLed.substring(5,9)).toInt(), (newLed.substring(9,13)).toInt(), (newLed.substring(13,17)).toInt(), (newLed.substring(17,21)).toInt(), (newLed.substring(21,25)).toInt(), (newLed.substring(25,29)).toInt());
    updateChannel = 0;
    newLed = "";
  }
}

void otherCrap() {
  
}

void setup() {
  
    Serial.begin(250000);

    Wire.begin();                       // Wire must be started first
    Wire.setClock(400000);              // Supported baud rates are 100kHz, 400kHz, and 1000kHz

    pwm1.resetDevices();       // Software resets all PCA9685 devices on Wire line

    pwm1.init(B000000);        // Address pins A5-A0 set to B000000
    pwm1.setPWMFrequency(1500); // Default is 200Hz, supports 24Hz to 1526Hz

    pwm2.init(B000001);        // Address pins A5-A0 set to B000000
    pwm2.setPWMFrequency(1500); // Default is 200Hz, supports 24Hz to 1526Hz

    pinMode(A1, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);

    pinMode(13, INPUT_PULLUP);
    pinMode(A0, INPUT_PULLUP);

    pinMode(A6, INPUT);
    pinMode(A7, INPUT);

    StatusRGB.onRun(statusLedHelper);
    StatusRGB.setInterval(333);

    tickRGB(1, 4096, 0, 0, 0);
//    tickRGB(2, 4096, 4096, 0, 0);
//    tickRGB(3, 0, 4096, 0, 0);
//    tickRGB(4, 0, 4096, 4096, 0);
//    tickRGB(5, 0, 0, 4096, 0);
//    tickRGB(6, 4096, 0, 4096, 0);
//    tickRGB(7, 0, 0, 0, 4096);
//    tickRGB(8, 4096, 0, 0, 0);

//    allDown(4096,4096,4096,4096);
    
//    allUp(4096,4096,4096,4096);
   
}

void loop() {
  //See if anything is coming in on the serial port
  doSerialUpdate();
  
  //take care of RGB Status lights
  statusLed();
}
