#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2        // input pin NeoPixel is attached to
#define NUMPIXELS 67 // number of NeoPixels in the strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayTime = 50; // Delay between rotation steps

// Array to store the colors for each pixel
struct Color
{
  int red;
  int green;
  int blue;
};

Color pixelColors[NUMPIXELS];

// Initial color
int red = 255, green = 0, blue = 0;

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

void rotateColors()
{
  // Store the last color
  Color lastColor = pixelColors[NUMPIXELS - 1];

  // Shift all colors to the right
  for (int i = NUMPIXELS - 1; i > 0; i--)
  {
    pixelColors[i] = pixelColors[i - 1];
  }

  // Set the first pixel to the last color
  pixelColors[0] = lastColor;
}

void setup()
{
  Serial.begin(9600);
  pixels.begin(); // Initialize the NeoPixel library

  // Initialize the color array with a gradient
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixelColors[i] = {red, green, blue};
    nextColor();
  }
}

void loop()
{
  // Rotate the colors
  rotateColors();

  // Set the updated colors on the strip
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(pixelColors[i].red, pixelColors[i].green, pixelColors[i].blue));
  }

  // Show the updated strip
  pixels.show();

  // Wait before the next rotation
  delay(delayTime);
}
