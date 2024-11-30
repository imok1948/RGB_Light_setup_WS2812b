#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2        // Input pin NeoPixel is attached to
#define NUMPIXELS 68 // Number of NeoPixels in the strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Fire colors
const int fireColors[][3] = {
    {255, 40, 0},  // Fire red
    {255, 40, 0},  // Fire red
    {255, 40, 0},  // Fire red
    {255, 40, 0},  // Fire red
    {255, 40, 0},  // Fire red
    {255, 40, 0},  // Fire red
    {255, 40, 0},  // Fire red
    {255, 40, 0},  // Fire red
    {255, 40, 0},  // Fire red
    {255, 40, 0},  // Fire red
    {255, 40, 0},  // Fire red
    {255, 40, 0},  // Fire red
    {193, 39, 0},  // Fire red
    {253, 54, 0},  // Bright orange
    {254, 154, 0}, // Yellow-orange
    {245, 100, 0}  // Light yellow
};
const int fireColorCount = sizeof(fireColors) / sizeof(fireColors[0]);

// Struct to manage individual pixel behavior
struct PixelState
{
  unsigned long nextBlinkTime; // Timestamp for the next blink action
  int rand1;                   // Random duration before blinking starts
  int rand2;                   // Random number of blinks
  int currentBlink;            // Tracks the current blink count
  bool isBlinking;             // Whether the pixel is currently blinking
  int currentColor[3];         // RGB values of the current color
};

// Array to hold the state of each pixel
PixelState pixelStates[NUMPIXELS];

void setup()
{
  Serial.begin(9600);
  pixels.begin();             // Initialize NeoPixel library
  randomSeed(analogRead(A0)); // Seed random number generator for randomness

  // Initialize each pixel state
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixelStates[i].rand1 = random(100, 300);                       // Random delay before blinking starts
    pixelStates[i].rand2 = random(1, 11);                           // Random number of blinks
    pixelStates[i].nextBlinkTime = millis() + pixelStates[i].rand1; // Initial timestamp
    pixelStates[i].currentBlink = 0;
    pixelStates[i].isBlinking = false;

    // Set a random initial color from fireColors
    int randomColorIndex = random(0, fireColorCount);
    pixelStates[i].currentColor[0] = fireColors[randomColorIndex][0];
    pixelStates[i].currentColor[1] = fireColors[randomColorIndex][1];
    pixelStates[i].currentColor[2] = fireColors[randomColorIndex][2];

    // Initialize all pixels with their initial color
    pixels.setPixelColor(i, pixels.Color(
                                pixelStates[i].currentColor[0],
                                pixelStates[i].currentColor[1],
                                pixelStates[i].currentColor[2]));
  }
  pixels.show();
}

void loop()
{
  unsigned long currentTime = millis();

  // Process each pixel individually
  for (int i = 0; i < NUMPIXELS; i++)
  {
    PixelState &state = pixelStates[i];

    // Check if the pixel is ready to start blinking
    if (currentTime >= state.nextBlinkTime)
    {
      if (!state.isBlinking)
      {
        // Start blinking
        state.isBlinking = true;
        state.currentBlink = 0;
      }

      // Blink logic
      if (state.currentBlink < state.rand2)
      {
        int delayTime = random(300, 1000); // Random delay between 5 and 300 ms
        if ((state.currentBlink % 2) == 0)
        {
          // Turn off the pixel
          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        }
        else
        {
          // Turn on the pixel with its current color
          pixels.setPixelColor(i, pixels.Color(
                                      state.currentColor[0],
                                      state.currentColor[1],
                                      state.currentColor[2]));
        }
        pixels.show();
        state.currentBlink++;
        state.nextBlinkTime = currentTime + delayTime; // Schedule the next blink
      }
      else
      {
        // Reset the pixel to glow continuously after blinking
        pixels.setPixelColor(i, pixels.Color(
                                    state.currentColor[0],
                                    state.currentColor[1],
                                    state.currentColor[2]));
        pixels.show();

        // Change to a new random fire color
        int randomColorIndex = random(0, fireColorCount);
        state.currentColor[0] = fireColors[randomColorIndex][0];
        state.currentColor[1] = fireColors[randomColorIndex][1];
        state.currentColor[2] = fireColors[randomColorIndex][2];

        // Prepare for the next random blinking sequence
        state.rand1 = random(500, 2001); // Random delay before next blink sequence
        state.rand2 = random(1, 11);     // Random number of blinks
        state.isBlinking = false;
        state.nextBlinkTime = currentTime + state.rand1;
      }
    }
  }
}
