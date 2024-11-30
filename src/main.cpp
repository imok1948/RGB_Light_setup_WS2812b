#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#define PIN 2        // input pin Neopixel is attached to
#define NUMPIXELS 20 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayTime = 1;

int redColor = 211;
int greenColor = 3;
int blueColor = 252;

int i, j, k;

void setup()
{
  Serial.begin(9600);
  pixels.begin();
}

void loop()
{
  // Neopixel test all colors

  Serial.println("Up");
  for (i = 0; i < 256; i++)
  {
    Serial.println(i);
    pixels.setPixelColor(3, pixels.Color(i, 100, i));
    pixels.show();
    delay(delayTime);
  }


  delay(200);


  Serial.println("Down");
  for (i = 255; i >= 0; i--)
  {
    Serial.println(i);
    pixels.setPixelColor(3, pixels.Color(i, 100, i));
    pixels.show();
    delay(delayTime);
  }

  delay(700);
}
