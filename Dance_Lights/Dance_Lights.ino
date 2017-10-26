// Basic demo for tap/doubletap readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <LEDiva_NeoPixel.h>
#include <avr/power.h>

// Used for hardware & software SPI
#define LIS3DH_CS 8

Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);

#define PIN 17

int LEDs = 10;

LEDiva_NeoPixel strip = LEDiva_NeoPixel(LEDs, PIN, NEO_GRB + NEO_KHZ800);

int R;
int G;
int B;
int Twinkle;
int FadeR;
int FadeG;
int FadeB;
int Lux = 135;
int wait = 10;
int shade;

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

// Adjust this number for the sensitivity of the 'click' force
// this strongly depend on the range! for 16G, try 5-10
// for 8G, try 10-20. for 4G try 20-40. for 2G try 40-80
#define CLICKTHRESHHOLD 80

void setup(void) {
#ifndef ESP8266
//  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif

  Serial.begin(9600);
    Serial.println("Adafruit LIS3DH Tap Test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");

  // 0 = turn off click detection & interrupt
  // 1 = single click only interrupt output
  // 2 = double click only interrupt output, detect single click
  // Adjust threshhold, higher numbers are less sensitive
  lis.setClick(2, CLICKTHRESHHOLD);
  delay(100);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'

    R = 255;
    G = 0;
    B = 255;
    strip.setBrightness(Lux);
}


void loop() {
  uint8_t click = lis.getClick();
  Twinkle = 30;
  //if (click == 0) return;
  //if (! (click & 0x30)) return;
  Serial.print("Click detected (0x"); Serial.print(click, HEX); Serial.print("): ");
  if (click & 0x10) {
    Serial.print(" single click");
     Twinkle = 2000;
  }
  if (click & 0x20) {
    Serial.print(" double click");
    Twinkle = 3000;
  }
  lis.read();
  sensors_event_t event; 
  lis.getEvent(&event);
  shade = map(event.acceleration.x,-10,10,100,255);
  Wheel(shade);
  Serial.print("\t\tX: "); Serial.print(shade);
  Serial.print(", R");Serial.print(R);
  Serial.print(", G");Serial.print(G);
  Serial.print(", B");Serial.print(B);
  Serial.println();
  
      for(uint16_t i=0; i<LEDs; i++) {
        if (random(3000) < Twinkle) {
          FadeR = R;
          FadeG = G;
          FadeB = B;
        } else {
          delay(10); 
          FadeR = strip.getR(i)-(R/60);
            if(FadeR < 0) {
            FadeR = 0;
          }
          FadeG = strip.getG(i)-(G/60);
            if(FadeG < 0) {
            FadeG = 0;
          }
          FadeB = strip.getB(i)-(B/60);
            if(FadeB < 0) {
            FadeB = 0;
          }
  Serial.print(", FadeR");Serial.print(FadeR);
  Serial.print(", FadeG");Serial.print(FadeG);
  Serial.print(", FadeB");Serial.print(FadeB);
  Serial.println();
        }
        strip.setPixelColor(i, FadeR, FadeG, FadeB);
      }
        strip.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
void Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    //return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    R = 255 - WheelPos * 3;
    G = 0;
    B = WheelPos * 3;
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    //return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    R = 0;
    G = WheelPos * 3;
    B = 255 - WheelPos * 3;
  } else {
  WheelPos -= 170;
 // return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    R = WheelPos * 3;
    G = 255 - WheelPos * 3;
    B = 0;
  }
}
