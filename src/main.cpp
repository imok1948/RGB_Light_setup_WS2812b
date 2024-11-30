#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2        // Input pin NeoPixel is attached to
#define NUMPIXELS 68 // Number of NeoPixels in the strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayTime = 20; // Delay between shifts

// Struct to store RGB color
struct Color
{
  int red;
  int green;
  int blue;
};

// Array to hold colors for each pixel
Color pixelColors[NUMPIXELS];

// Current RGB values for generating the next color
int red = 255, green = 0, blue = 0;

void nextColor()
{
  // Generate the next color in the RGB spectrum
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

void shiftColors()
{
  // Shift all colors to the next pixel
  for (int i = NUMPIXELS - 1; i > 0; i--)
  {
    pixelColors[i] = pixelColors[i - 1];
  }

  // Generate a new color for the first pixel
  pixelColors[0] = {red, green, blue};
  nextColor();
}

void setup()
{
  Serial.begin(9600);
  pixels.begin(); // Initialize NeoPixel library

  // Initialize the color array with a gradient
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixelColors[i] = {red, green, blue};
    nextColor();
  }
}

void loop()
{
  // Shift colors to the next pixel
  shiftColors();

  // Update the LED strip with new colors
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(pixelColors[i].red, pixelColors[i].green, pixelColors[i].blue));
  }
  pixels.show(); // Display updated colors

  // Wait before shifting again
  delay(delayTime);
}
