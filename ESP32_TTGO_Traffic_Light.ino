// ========================================================================
// ESP32+TTGO Traffic Light
// ========================================================================


#include <TFT_eSPI.h>        // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();   // Invoke library


const int buttonPin0 = 0;
const int buttonPin1 = 35;

const int kCenterX = 67;

const int kTrafficLightY = 9;
const int kTrafficLightWidth = 80;
const int kTrafficLightHeight = 130;
const int kTrafficLightCornerRadius = 12;

const int kTrafficLightStopY = 24;
const int kTrafficLightStopRadius = 16;

const int kTrafficLightWarningY = 66;
const int kTrafficLightWarningRadius = 14;

const int kTrafficLightGoY = 104;
const int kTrafficLightGoRadius = 14;

const int kWalkWidth = 96;
const int kWalkY = 150;
const int kWalkHeight = 80;
const int kWalkCornerRadius = 12;

const int kStopDurationSeconds = 10;
const int kWarningDurationSeconds = 4;
const int kWalkDurationSeconds = 15;


bool buttonHeldDown0 = false;


void setup()
{
  pinMode (buttonPin0, INPUT);
  pinMode (buttonPin1, INPUT);
  
  // Initialize display, paint screen sky blue.
  tft.begin ();
  tft.fillScreen (TFT_SKYBLUE);

  // Initial draw of traffic light.
  drawTrafficLight (0);

  drawDontWalk();
}

void loop()
{
  long duration;
  long count;
  
  if ((digitalRead (buttonPin0) == LOW) || (digitalRead (buttonPin1) == LOW)) {
    buttonHeldDown0 = true;
  } else {
    buttonHeldDown0 = false;
  }

  // Stop.
  drawTrafficLight (0);
  drawDontWalk();
  sleep(kStopDurationSeconds);
  
  // Go.
  drawTrafficLight (2);
  duration = kWalkDurationSeconds - kWarningDurationSeconds;
  do {
    drawWalk(duration);
    sleep(1);
    duration = duration - 1;
  } while (duration > 0);

  // Warning.
  drawTrafficLight (1);
  drawDontWalk();
  duration = kWarningDurationSeconds;
  sleep (kWarningDurationSeconds);
}

void drawWalk (int count)
{
  tft.fillRoundRect (kCenterX - (kWalkWidth / 2), kWalkY, kWalkWidth , kWalkHeight, kWalkCornerRadius, TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("WALK", 34, 158, 2);
  if (count < 10) {
    tft.drawNumber(count, 58, 188, 2);
  }
}

void drawDontWalk ()
{
  tft.fillRoundRect (kCenterX - (kWalkWidth / 2), kWalkY, kWalkWidth , kWalkHeight, kWalkCornerRadius, TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.drawString("DONT", 36, 158, 2);
  tft.drawString("WALK", 34, 188, 2);
}
void drawTrafficLight (int state)
{
  tft.fillRoundRect (kCenterX - (kTrafficLightWidth / 2), kTrafficLightY, kTrafficLightWidth, kTrafficLightHeight, kTrafficLightCornerRadius, TFT_BLACK);

  switch (state) {
    case 0:
    drawStopLight(true);
    drawWarningLight(false);
    drawGoLight(false);
    break;
    
    case 1:
    drawStopLight(false);
    drawWarningLight(true);
    drawGoLight(false);
    break;
    
    case 2:
    drawStopLight(false);
    drawWarningLight(false);
    drawGoLight(true);
    break;
  }
}

void drawStopLight (bool isOn)
{
  if (isOn) {
    tft.fillCircle (kCenterX, kTrafficLightY + kTrafficLightStopY, kTrafficLightStopRadius, TFT_RED);
  } else  {
    tft.fillCircle (kCenterX, kTrafficLightY + kTrafficLightStopY, kTrafficLightStopRadius, 0x0861);
  }
}

void drawWarningLight (bool isOn)
{
  if (isOn) {
    tft.fillCircle (kCenterX, kTrafficLightY + kTrafficLightWarningY, kTrafficLightWarningRadius, TFT_GOLD);
  } else {
    tft.fillCircle (kCenterX, kTrafficLightY + kTrafficLightWarningY, kTrafficLightWarningRadius, 0x0861);
  }
}

void drawGoLight (bool isOn)
{
  if (isOn) {
    tft.fillCircle (kCenterX, kTrafficLightY + kTrafficLightGoY, kTrafficLightGoRadius, TFT_GREEN);
  } else {
    tft.fillCircle (kCenterX, kTrafficLightY + kTrafficLightGoY, kTrafficLightGoRadius, 0x0861);
  }
}
