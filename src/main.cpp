#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2        // Input pin NeoPixel is attached to
#define NUMPIXELS 68 // Number of NeoPixels in the strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int delayTime = 10; // Delay between blinks in milliseconds

// Constant color to glow
const int red = 255;
const int green = 40;
const int blue = 0;

void setStripColor(int r, int g, int b)
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}

void blinkStrip(int times)
{
  for (int i = 0; i < times; i++)
  {
    setStripColor(0, 0, 0); // Turn off the strip
    delay(delayTime);

    setStripColor(red, green, blue); // Turn on the strip
    delay(delayTime);
  }
}

void setup()
{
  Serial.begin(9600);
  pixels.begin(); // Initialize NeoPixel library
  randomSeed(analogRead(A0)); // Seed random number generator
}

void loop()
{
  // Keep the strip glowing with the fixed color
  setStripColor(red, green, blue);

  // Generate random values
  int rand1 = random(500, 2001); // Random duration in milliseconds (500 to 2000)
  int rand2 = random(1, 11);     // Random number of blinks (1 to 10)

  // Wait for a random duration
  delay(rand1);

  // Blink the strip random times
  blinkStrip(rand2);
}
