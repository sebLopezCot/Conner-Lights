#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_PIXELS 30

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup(){
   strip.begin();
   strip.setBrightness(64);
   strip.show(); // Initialize all pixels to 'off'
}

void loop() {
    
  for(int i=0; i < 30; i++){
    randomColor();
  }
  for(int i=0; i < 4; i++){
    chase(strip.Color(255, 0, 0));
  }
  for(int i=0; i < 15; i++){
    alternate(strip.Color(0,0,255), 0);
  }
  for(int i=0; i < 2; i++){
    build(strip.Color(0,255,0));
  }
  for(int i=0; i < 4; i++){
    glowAndDim(strip.Color(255,215,0));
  }
  strip.setBrightness(64);
  strip.show();
  for(int i=0; i < 2; i++){
    pingPong(strip.Color(221,160,221));
  }
  for(int i=0; i < 100; i++){
    randomIndex(strip.Color(255,102,6));
  }
  threeTrain(strip.Color(0,0,255), 40);
  for(int i=0; i < 1; i++){
    build(strip.Color(0,0,255));
  }
//  setAll(0);
//  while(true){
//    delay(100);
//  }
}
 
static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(25);
  }
}

static void build(uint32_t c){
  setAll(0);
  
  for(int i=0; i < strip.numPixels()/2; i++){
    strip.setPixelColor(i, c);
    strip.setPixelColor(strip.numPixels()-1-i, c);
    strip.show();
    delay(150);
  }
}

static void alternate(uint32_t c1, uint32_t c2){
  // Shift evens
  for(int i=0; i < strip.numPixels(); i++){
    if((i+1) % 2 == 0){
       strip.setPixelColor(i, c1);
    } else {
       strip.setPixelColor(i, c2);
    }
    
    strip.show();
  }
  
  delay(100);
  
  // Shift odds
  for(int i=0; i < strip.numPixels(); i++){
    if((i+1) % 2 == 1){
       strip.setPixelColor(i, c1);
    } else {
       strip.setPixelColor(i, c2);
    }
    
    strip.show();
  }
  
  delay(100);
}

static void setAll(uint32_t c){
  for(int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, c);
    strip.show();
  }
}

static void glowAndDim(uint32_t c){
  setAll(c);
  
  int brightness = 10;
  while(brightness <= 150){
    strip.setBrightness(brightness);
    strip.show();
    brightness += 5;
    delay(20);
  }
  
  while(brightness >= 10){
    strip.setBrightness(brightness);
    brightness -= 5;
    strip.show();
    delay(20);
  }
}

static void pingPong(uint32_t c){
  setAll(0);
  
  for(int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, c);
    strip.show();
    delay(25);
  }
  
  for(int i=strip.numPixels()-1; i >= 0; i--){
    strip.setPixelColor(i, 0);
    strip.show();
    delay(25);
  }
}

static void randomColor(){
  // Shift evens
  for(int i=0; i < strip.numPixels(); i++){
    if((i+1) % 2 == 0){
       int r = random(0, 255);
       int g = random(0, 255);
       int b = random(0, 255);
      
       strip.setPixelColor(i, strip.Color(r,g,b));
       strip.show();
    }
  }
  
  delay(100);
  
  // Shift odds
  for(int i=0; i < strip.numPixels(); i++){
    if((i+1) % 2 == 1){
       int r = random(0, 255);
       int g = random(0, 255);
       int b = random(0, 255);
      
       strip.setPixelColor(i, strip.Color(r,g,b));
       strip.show();
    }
  }
  
  delay(100);
}

static void randomIndex(uint32_t c){
  setAll(0);
  for(int i=0; i < random(3, strip.numPixels()); i++){
    strip.setPixelColor(random(0, strip.numPixels()-1), c);
  }
  strip.show();
  delay(100);
}

static void threeTrain(uint32_t c, int times){
  int pos[] = {6, 14, 22};
  
  for(int count=0; count < times; count++){
    
      for(int trains=0; trains < sizeof(pos)-1; trains++){
        
        if((pos[trains] >= 0) && (pos[trains] < strip.numPixels())){
          strip.setPixelColor(pos[trains]  , c); // Draw new pixel
        }  
        
        if(((pos[trains]-3) >= 0)){
          strip.setPixelColor(pos[trains]-3, 0); // Erase pixel a few steps back
        } else {
          strip.setPixelColor(strip.numPixels()-3+pos[trains], 0);
        }
        
        if(pos[trains] >= strip.numPixels()){
          pos[trains] = 0;
        } else {
          pos[trains]++;
        }
    }
    
    strip.show();
    delay(150);
  }
}

