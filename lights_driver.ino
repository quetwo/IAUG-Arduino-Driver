/*
 *
 *   Copyright 2015 Michigan State University Board of Trustees
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 */

#include "Adafruit_WS2801.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#include <SoftwareSerial.h>

uint8_t dataPin  = 11;    // Green wire
uint8_t clockPin = 13;    // Blue wire

// Red wire goes to +5 regulated output
// Yellow wire goes to GND on regulated output
// Make sure to tie Arduino and regulated power together.

Adafruit_WS2801 strip = Adafruit_WS2801(20);

String inFromEdison;
int led,r,g,b = 0;

SoftwareSerial edison(6,7);

void setup() 
{
  Serial.begin(9600);
  edison.begin(9600);
  
  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();

  colorWipe(Color(255, 0, 0), 100);  // init all colors to make sure they are working
  colorWipe(Color(0, 255, 0), 100);
  colorWipe(Color(0, 0, 255), 100);
  
  colorWipe(0,75);   // clear all LEDs within 75ms
}


void loop() 
{
  if (edison.available())
  {
    led = edison.parseInt();
     
    r = edison.parseInt();
    g = edison.parseInt();
    b = edison.parseInt();
    
    edison.readStringUntil('\n');  // ignore up to newline.
    
    Serial.print("LED [");
    Serial.print(led, DEC);
    Serial.print("] ");
    
    Serial.print(r, DEC);
    Serial.print(",");
    
    Serial.print(g, DEC);
    Serial.print(",");
  
    Serial.print(b, DEC);
    Serial.println();
    
    if (led == -2)
    {
      strip.show(); 
    }
    
    if (led == -1)
    {
      colorSetAll(Color(r,g,b));
    }
    
    if (led >= 0)
    {
      strip.setPixelColor(led, Color(r,g,b));      
    }
  
  }
}

void colorWipe(uint32_t c, uint8_t wait) 
{
  int i;
  
  for (i=0; i < strip.numPixels(); i++) 
  {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void colorSetAll(uint32_t c) 
{
  int i;
  
  for (i=0; i < strip.numPixels(); i++) 
  {
      strip.setPixelColor(i, c);
  }
}

uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

