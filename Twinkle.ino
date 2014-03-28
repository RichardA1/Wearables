#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);

  int r = 10;
  int g = 100;
  int b = 255;
  int c;
long randNumber;

void setup() {
  Serial.begin(9600);
  Serial.println("Color View Test!");
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    uint32_t c = strip.Color(r, g, b); 
    strip.setPixelColor(i, c);
    strip.show();
    delay(100);
  }
}

  
  
void loop() {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    int color = strip.getPixelColor(i);  
    if (color > 0) {
    int red = (color & 0xFF0000) >> 16;
    int green = (color & 0x00FF00) >> 8;
    int blue = color & 0x0000FF;
    Serial.print("\n Color"); Serial.print(color);Serial.print("\n r"); Serial.print(red);Serial.print(" g"); Serial.print(green);Serial.print(" b"); Serial.print(blue);
    if (red > 0) { red = red - 5; }
    if (green > 0) { green = green - 5; }
    if (blue > 0) { blue = blue - 5; }
    uint32_t c = strip.Color(red, green, blue);
    
    strip.setPixelColor(i, c);
    strip.show();
    randNumber = 250;
    }
    randNumber = random(500);
    if (randNumber < 2) { 
    uint32_t c = strip.Color(10, 100, 255); 
    strip.setPixelColor(i, c);
    strip.show();
  }
    delay(5);
    
  }
  //delay(0);
}

// Fill the dots one after the other with a color
void colorWipe() {
  
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
