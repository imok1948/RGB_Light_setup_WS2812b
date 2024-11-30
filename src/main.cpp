#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2        // input pin Neopixel is attached to
#define NUMPIXELS 68 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayTime = 1; // Delay between color changes

void setup()
{
  Serial.begin(9600);
  pixels.begin(); // Initialize the NeoPixel library
  randomSeed(analogRead(0)); // Seed the random number generator using an analog pin
}

void loop()
{
  Serial.println("Assigning Random Colors to LEDs");

  // Generate a unique random color
  int red = random(0, 256);
  int green = random(0, 256);
  int blue = random(0, 256);

  // Print the selected color to Serial
  Serial.print("Random Color: R=");
  Serial.print(red);
  Serial.print(", G=");
  Serial.print(green);
  Serial.print(", B=");
  Serial.println(blue);

  // Set all LEDs to the same random color
  for (int pixel = 0; pixel < NUMPIXELS; pixel++)
  {
    pixels.setPixelColor(pixel, pixels.Color(red, green, blue));
  }

  // Show the updated colors
  pixels.show();

  // Delay for effect
  delay(1000);
}
