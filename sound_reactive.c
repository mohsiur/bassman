/*
Sound Reactive LED's using Adafruit NeoPixels and FLORA board

 Hardware requirements:
 - Adafruit Electret Microphone Amplifier
 - Adafruit NeoPixel Digital LED strip
 - Battery for portable use.
 
 Software requirements:
 - Adafruit NeoPixel library
 
 Connections:
 - 3.3V to mic amp +
 - GND to mic amp -
 - Analog pin to microphone output 
 - Digital pin to LED data input
 */

#include <Adafruit_NeoPixel.h>
#include <math.h>

#define N_PIXELS  80  // Number of pixels
#define MIC_PIN   A9  // Analog pin for Microphone
#define LED_PIN    6  // LED pin
#define SAMPLE_SIZE   16  // Sample SIZE for average level
#define PEAK_HANG 16 //Pause time before peak dot falls
#define PEAK_FALL 4 //Rate of falling peak dot
#define INPUT_FLOOR 22 //Lowest range of analogRead input
#define INPUT_CEILING 250 //Max range of analogRead input, the lower the value the more sensitive (1023 = max)


/* Variables */

byte peak = 24;      // Peak level of column; used for falling dots
unsigned int sample;

byte dotCount = 0;  //Frame counter for peak dot
byte dotHangCount = 0; //Frame counter for holding peak dot

//Initializing Strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  strip.begin();
  strip.setBrightness(10); //Set Brightness
  strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
  unsigned long startTime= millis();  // Start of sample SIZE
  float peakLvl = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1023;
  unsigned int c, y;


  // collect data for length of sample size (in ms)
  while (millis() - startTime < SAMPLE_SIZE)
  {
    sample = analogRead(MIC_PIN);
    if (sample < 1024)  // Exclude high readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // Find Max Level
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // Find Min Level
      }
    }
  }
  peakLvl = signalMax - signalMin;  // max - min = peak-peak amplitude
  
  //Fill the strip with rainbow gradient
  for (int i=0;i<=strip.numPixels()-1;i++){
    strip.setPixelColor(i,Wheel(map(i,0,strip.numPixels()-1,60,150)));
  }


  //Scale the input logarithmically instead of linearly
  c = fscale(INPUT_FLOOR, INPUT_CEILING, strip.numPixels(), 0, peakLvl, 2);
  
  if(c < peak) {
    peak = c;            // Keep dot on top
    dotHangCount = 0;    // make the dot hang before falling
  }
  if (c <= strip.numPixels()) { // Fill partial column with off pixels
    drawLine(strip.numPixels(), strip.numPixels()-c, strip.Color(0, 0, 0));
  }

  // Set the peak dot to match the rainbow gradient
  y = strip.numPixels() - peak;
  
  strip.setPixelColor(y-1,Wheel(map(y,0,strip.numPixels()-1,30,150)));

  strip.show();

  // Frame based peak dot animation
  if(dotHangCount > PEAK_HANG) { 
    if(++dotCount >= PEAK_FALL) {
      peak++;
      dotCount = 0;
    }
  } 
  else {
    dotHangCount++; 
  }
}

//Used to draw a line between two points of a given color
void drawLine(uint8_t from, uint8_t to, uint32_t c) {
  uint8_t fromTemp;
  if (from > to) {
    fromTemp = from;
    from = to;
    to = fromTemp;
  }
  for(int i=from; i<=to; i++){
    strip.setPixelColor(i, c);
  }
}


float fscale( float originalMin, float originalMax, float newBegin, float
newEnd, float inputValue, float curve){

  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;

  if (curve > 10) curve = 10;
  if (curve < -10) curve = -10;

  curve = (curve * -.1) ; // invert and scale
  curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

  // Check for out of range inputValues
  if (inputValue < originalMin) {
    inputValue = originalMin;
  }
  if (inputValue > originalMax) {
    inputValue = originalMax;
  }

  // Zero Refference the values
  OriginalRange = originalMax - originalMin;

  if (newEnd > newBegin){ 
    NewRange = newEnd - newBegin;
  }
  else
  {
    NewRange = newBegin - newEnd; 
    invFlag = 1;
  }

  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal  =  zeroRefCurVal / OriginalRange;   // normalize to 0 - 1 

  // Check for originalMin > originalMax 
  if (originalMin > originalMax ) {
    return 0;
  }

  if (invFlag == 0){
    rangedValue =  (pow(normalizedCurVal, curve) * NewRange) + newBegin;

  }
  else     // invert the ranges
  {   
    rangedValue =  newBegin - (pow(normalizedCurVal, curve) * NewRange); 
  }

  return rangedValue;
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}