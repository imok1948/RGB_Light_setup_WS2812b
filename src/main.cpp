#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2        // input pin Neopixel is attached to
#define NUMPIXELS 67 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayTime = 20;                 // Delay between color updates
int red = 255, green = 0, blue = 0; // Start with pure red

void nextColor()
{
  // Move along the RGB color spectrum
  if (red == 255 && green < 255 && blue == 0)
  {
    green++; // Red to yellow
  }
  else if (green == 255 && red > 0 && blue == 0)
  {
    red--; // Yellow to green
  }
  else if (green == 255 && blue < 255 && red == 0)
  {
    blue++; // Green to cyan
  }
  else if (blue == 255 && green > 0 && red == 0)
  {
    green--; // Cyan to blue
  }
  else if (blue == 255 && red < 255 && green == 0)
  {
    red++; // Blue to magenta
  }
  else if (red == 255 && blue > 0 && green == 0)
  {
    blue--; // Magenta to red
  }
}

void setup()
{
  Serial.begin(9600);
  pixels.begin(); // Initialize the NeoPixel library
}

void loop()
{
  // Set all LEDs to the current color
  for (int pixel = 0; pixel < NUMPIXELS; pixel++)
  {
    pixels.setPixelColor(pixel, pixels.Color(red, green, blue));
  }

  // Show the updated colors
  pixels.show();

  // Print the current color to Serial for debugging
  Serial.print("Color: R=");
  Serial.print(red);
  Serial.print(", G=");
  Serial.print(green);
  Serial.print(", B=");
  Serial.println(blue);

  // Update color to the next one in the gradient
  nextColor();

  // Wait for a while to create the transition effect
  delay(delayTime);
}
