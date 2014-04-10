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

  // Starting values of each color befor they fade.
  int rBase = 150;
  int gBase = 200;
  int bBase = 30;
  // Initiolizing the memory for each of the 20 LEDs
  int rMemo[] = {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0};
  int gMemo[] = {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0};
  int bMemo[] = {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0};
  // Initiolizing the temporary RGB values
  int red = 0;
  int green = 0;
  int blue = 0;
  
  // How quickly the pixles fade (rBace/fade)
  int fade = 30;
  int thisFade = 0;
  
long randNumber;

void setup() {
  Serial.begin(9600);
  Serial.println("Color View Test!");
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  delay(1000);
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    rMemo[i] = rBase;
    gMemo[i] = gBase;
    bMemo[i] = bBase;
    Serial.print("\nSTART--- r"); Serial.print(i); Serial.print("="); Serial.print(rMemo[i]);Serial.print(" g"); Serial.print(i); Serial.print("="); Serial.print(gMemo[i]);Serial.print(" b"); Serial.print(i); Serial.print("="); Serial.print(bMemo[i]);
    uint32_t c = strip.Color(rMemo[i], gMemo[i], bMemo[i]); 
    strip.setPixelColor(i, c);
    strip.show();
    delay(10);
  }
} 
  
void loop() {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    //Load the last RGB values for this pixle 
    red = rMemo[i];
    green = gMemo[i];
    blue = bMemo[i];
// Make the fade adjustment for each color of this pixle
    if (red > 0) { 
      thisFade = rBase / fade;
      if (thisFade == 0) {thisFade = 1;}
      red = red - thisFade;
      if (red < 0) {red = 0;}
      rMemo[i] = red;
    }
    if (green > 0) {
      thisFade = gBase / fade;
      if (thisFade == 0) {thisFade = 1;}
      green = green - thisFade;
      if (green < 0) {green = 0;}
      gMemo[i] = green;
     }
    if (blue > 0) {
      thisFade = bBase / fade;
      if (thisFade == 0) {thisFade = 1;}
      blue = blue - thisFade; 
      if (blue < 0) {blue = 0;}
      bMemo[i] = blue;
      }
      Serial.print("\n pixle["); Serial.print(i);Serial.print("]"); Serial.print("= r"); Serial.print(red);Serial.print(", g"); Serial.print(green);Serial.print(", b"); Serial.print(blue);
    uint32_t c = strip.Color(red, green, blue);
    
    strip.setPixelColor(i, c);
    strip.show();
    randNumber = 250;
    //}
    randNumber = random(500);
    if (randNumber < 2) { 
    Serial.print("\n pixle["); Serial.print(i);Serial.print("]"); Serial.print("= r"); Serial.print(rBase);Serial.print(", g"); Serial.print(gBase);Serial.print(", b"); Serial.print(bBase); Serial.print(" ---- BLINK");
    uint32_t c = strip.Color(rBase, gBase, bBase); 
    rMemo[i] = rBase;
    gMemo[i] = gBase;
    bMemo[i] = bBase;
    strip.setPixelColor(i, c);
    strip.show();
  }
    delay(1);
    
  }
  //delay(0);
}

