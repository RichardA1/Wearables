#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800);

  int rColor = 0;
  int gRead = 12;
  int bRead = 200;
  int c;
long randNumber;

void setup() {
  Serial.begin(9600);
  Serial.println("Color View Test!");
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    uint32_t c = strip.Color(rColor, gRead, bRead); 
    strip.setPixelColor(i, c);
    strip.show();
    delay(100);
  }
}

  
  
void loop() {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    int color = strip.getPixelColor(i); 
   Serial.print("\n Color"); Serial.print(color); 
    if (color != 0) {
    int red = (color & 0xFF0000) >> 16;
    int green = (color & 0x00FF00) >> 8;
    int blue = color & 0x0000FF;
    Serial.print("\n Color"); Serial.print(color);Serial.print("\n r"); Serial.print(red);Serial.print(" g"); Serial.print(green);Serial.print(" b"); Serial.print(blue);
    if (red > 0) { 
    red = red - 5; 
  }
    if (green > 0) { 
    green = green - 5; 
  }
    if (blue > 0) { 
    blue = blue - 5; 
  }
    uint32_t c = strip.Color(red, green, blue);
    
    strip.setPixelColor(i, c);
    strip.show();
    randNumber = 250;
    }
    randNumber = random(500);
    if (randNumber < 2) { 
    uint32_t c = strip.Color(rColor, gRead, bRead); 
    strip.setPixelColor(i, c);
    strip.show();
  }
    delay(1);
    
  }
  //delay(0);
}

