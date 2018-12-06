
/************************************************************************
 * Mario Star
 * toggle power to cycle in leds modes
 */

#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>

/* 
 Adafruit Neopixels definition
 */
#define LEDPIN 9
#define NBLEDS 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NBLEDS, LEDPIN, NEO_GRB + NEO_KHZ800);

#define CYCLETIME 60000
#define NBSCENE 6
int addr = 0;
int val = 0 ;
int playMode = 0;

void setup() {
  Serial.begin(9600);
  val = EEPROM.read(addr);
  playMode = val % NBSCENE ;
  val++;
  if(val >= 255)
    val = 0;
  EEPROM.write(addr, val);
  Serial.println(playMode);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(64);

  switch (playMode)
  {
    case 0 :
    Blink();
    break;
    case 1 :
    Pulse();
    break;
    case 2:
    AlwaysOn();
    break;
    case 3:
    Star();
    break;
    case 4:
    Yellow();
    break;
        case 5:
    Cycle();
    break;
    }

}

void loop() {


}

void Cycle()
{
  
  unsigned long oldTime;
  unsigned long actualTime;
    
  long multiplier = 0;
  long increment = 1;
  
    for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, 255,0,0);
    strip.show();
    delay ( 1000 );
while (true)
{
    for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, 255,180,128);
    strip.show();

    delay(CYCLETIME);

    // pulse
      multiplier = 0;
      increment = 1; 
      oldTime = millis();
          actualTime  = millis();
      Serial.println("pulse");
    while ((actualTime-oldTime) < CYCLETIME)
  {
    for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, (int)(255*multiplier/1000), 255*multiplier/1000,0);
    strip.show();

    delay(10);
    multiplier += increment;
    
    if(multiplier >= 1000 )
    increment = -1;
    if (multiplier <= 0 )
    increment = 1;
      actualTime = millis();
    }

  // blink
    oldTime = millis();
    actualTime  = millis();
    Serial.println("blink");
    while ((actualTime-oldTime) < CYCLETIME)
  {
    for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, 255, 180, 128);
    strip.show();

    delay(1000);
    for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, 0, 0, 0);
        strip.show();
        delay(1000);
      actualTime = millis();
    }

    //Star !!!!!!
          oldTime = millis();
              actualTime  = millis();
                Serial.println("star");
    while ((actualTime-oldTime) < CYCLETIME)
    {
        for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, random(0,15)*16, random(0,15)*16, random(0,15)*16);
    strip.show();
    delay (150);
    actualTime = millis();
    }

  }

} 

void AlwaysOn()
{
      for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, 0,255,0);
    strip.show();
    delay ( 1000 );
    
    for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, 255,180,128);
    strip.show();
  
  }

void Yellow()
{
   for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, 255,255,0);
    strip.show();  
  }
  
void Pulse()
{
    for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, 0,0,255);
    strip.show();
    delay ( 1000 );
    
  long multiplier = 0;
  long increment = 1;
  
    while (true)
  {
    
    for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, (int)(255*multiplier/1000), 255*multiplier/1000, 0);
    strip.show();

    delay(10);
    multiplier += increment;
    
    if(multiplier >= 1000 )
    increment = -1;
    if (multiplier <= 0 )
    increment = 1;
    }
  }


void Star()
{
      for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, 255,255,0);
    strip.show();
    delay ( 1000 );
  while (true)
  {
        for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, random(0,15)*16, random(0,15)*16, random(0,15)*16);
    strip.show();
    delay (150);
    }
  
  }

void Blink()
{
        for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, 0,255,255);
    strip.show();
    delay ( 1000 );
  while (true)
  {
    for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, 255, 180, 128);
    strip.show();

    delay(1000);
    for (int i =0 ; i < NBLEDS ; i++)
    strip.setPixelColor(i, 0, 0, 0);
        strip.show();
        delay(1000);
    }
}
