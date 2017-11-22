#include "FastLED.h"
#include "telecommande.h"
#include <IRremote.h>


#define NUM_LEDS     150
#define NB_ROWS       10
#define NB_COLUMNS    15

//Leds
CRGB leds[NUM_LEDS];
CRGB ledArray[NB_COLUMNS][NB_ROWS];

//Micro
int soundLevels[NB_COLUMNS];

const int sampleWindow = 35; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

//Ir remote
#define RECV_PIN 30
IRrecv irrecv(RECV_PIN);
decode_results ir_remote;




//led effect
 #define UPDATES_PER_SECOND 100
  
  CRGBPalette16 currentPalette;
  TBlendType    currentBlending;
  
  extern CRGBPalette16 myRedWhiteBluePalette;
  extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
 


void setup() 
{ 
    // Leds
    FastLED.addLeds<NEOPIXEL, 53>(leds, NUM_LEDS);
    FastLED.setBrightness(40);
    
    //Micro
    analogReference(INTERNAL2V56);
    
    Serial.begin(115200);
    
    // IR Remote
    irrecv.enableIRIn();
    
}

void loop() 
{ 
 
  
 /*irrecv.decode(&ir_remote);
  telecommande();
  irrecv.resume(); 
  delay(300);*/
  
  
  //Display_SoundLevel();
  Display_Effect1();
  
  /*
  FastLED.setCorrection( TypicalLEDStrip );
  Display_FullWhite();
  delay(3000);
  FastLED.setCorrection( UncorrectedColor );
  Display_FullWhite();
  delay(1000);*/

  
  /*
  
  Display_FrenchFlag();
  delay(3000);
  Display_USAFlag();
  delay(3000);
  
  //Display_Effect1();
  
   Display_DiceValue(1);
   delay(150);
   Display_DiceValue(2);
   delay(150);
   Display_DiceValue(3);
   delay(150);
   Display_DiceValue(4);
   delay(150);
   Display_DiceValue(5);
   delay(150);
   Display_DiceValue(6);
   delay(150);
   */
   
  
}
/*
void DrawCircle(int x0, int y0, int radius, CRGB color)
{
  int x = radius;
  int y = 0;
  int radiusError = 1-x;
   
  while(x >= y)
  {
    ledArray[x + x0][y + y0] = color;
    ledArray[y + x0][x + y0] = color;
    ledArray[-x + x0][y + y0] = color;
    ledArray[-y + x0,][x + y0] = color;
    ledArray[-x + x0][-y + y0] = color;
    ledArray[-y + x0][-x + y0] = color;
    ledArray[x + x0][-y + y0] = color;
    ledArray[y + x0][-x + y0] = color;

    y++;
    
    if (radiusError<0)
    {
      radiusError += 2 * y + 1;
    }
    else
    {
      x--;
      radiusError += 2 * (y - x) + 1;
    }
  }
}

*/
void Display_FrenchFlag()
{
  //Init Background
  for( int column = 0; column < 5; column++ )
  {
    for( int row = 0; row < NB_ROWS; row++ )
    {
      ledArray[column][row] = CRGB::Blue;
    }
  }
  for( int column = 5; column < 10; column++ )
  {
    for( int row = 0; row < NB_ROWS; row++ )
    {
      ledArray[column][row] = CRGB::White;
    }
  }
  for( int column = 10; column < NB_COLUMNS; column++ )
  {
    for( int row = 0; row < NB_ROWS; row++ )
    {
      ledArray[column][row] = CRGB::Red;
    }
  }
  
  RefreshLeds(); 
}


void Display_FullWhite()
{
  //Init Background
  for( int column = 0; column < NB_COLUMNS; column++ )
  {
    for( int row = 0; row < NB_ROWS; row++ )
    {
      ledArray[column][row] = CRGB::White;
    }
  }
  RefreshLeds(); 
}

void Display_USAFlag()
{
  //Init Background
  for( int column = 0; column < NB_COLUMNS; column++ )
  {
    for( int row = 0; row < NB_ROWS; row++ )
    {
      if( (row % 2) == 0)
      {
        ledArray[column][row] = CRGB::Red;
      }
      else
      {
        ledArray[column][row] = CRGB::White;
      }
    }
  }
  
  for( int column = 0; column < 7; column++ )
  {
    for( int row = 5; row < NB_ROWS; row++ )
    {
      if( (column % 2) == 1)
      {
        if( (row % 2) == 0)
        {
          ledArray[column][row] = CRGB::Blue;
        }
        else
        {
          ledArray[column][row] = CRGB::White;
        }
      }
      else
      {
        if( (row % 2) == 1)
        {
          ledArray[column][row] = CRGB::Blue;
        }
        else
        {
          ledArray[column][row] = CRGB::White;
        }
      }
        
    }
  }
  
  RefreshLeds(); 
}



void Display_Effect1()
{
  
    currentPalette = RainbowColors_p;
  currentBlending = BLEND;

  while(1)
  {
    ChangePalettePeriodically();
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
  
    FillLEDsFromPaletteColors( startIndex);
  
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    
  }
  
}






void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;
  
  for( int i = 0; i < NUM_LEDS; i++) 
  {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;
  
  if( lastSecond != secondHand) {
    lastSecond = secondHand;
    if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = BLEND; }
    if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
    if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = BLEND; }
    if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = BLEND; }
    if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = BLEND; }
    if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
    if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = BLEND; }
    if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = BLEND; }
    if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = BLEND; }
    if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
    if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = BLEND; }
  }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
  for( int i = 0; i < 16; i++) {
    currentPalette[i] = CHSV( random8(), 255, random8());
  }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;
  
  currentPalette = CRGBPalette16( 
    green,  green,  black,  black,
    purple, purple, black,  black,
    green,  green,  black,  black,
    purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more 
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Gray, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};











void Display_DiceValue(int value)
{
  
  //Init Background
  for( int column = 0; column < 2; column++ )
  {
    for( int row = 0; row < NB_ROWS; row++ )
    {
      ledArray[column][row] = CRGB::Black;
    }
  }
  for( int column = 2; column < 12; column++ )
  {
    for( int row = 0; row < NB_ROWS; row++ )
    {
      ledArray[column][row] = CRGB::White;
    }
  }
  for( int column = 12; column < NB_COLUMNS; column++ )
  {
    for( int row = 0; row < NB_ROWS; row++ )
    {
      ledArray[column][row] = CRGB::Black;
    }
  }
  
  
  // Up left
  if((value == 4) || (value == 5) || (value == 6) )
  {
    ledArray[3][8] = CRGB::Red;
    ledArray[3][7] = CRGB::Red; 
    ledArray[4][8] = CRGB::Red; 
    ledArray[4][7] = CRGB::Red; 
  }
  
  // Middle left
  if( value == 6 )
  {
    ledArray[3][5] = CRGB::Red;
    ledArray[3][4] = CRGB::Red; 
    ledArray[4][5] = CRGB::Red; 
    ledArray[4][4] = CRGB::Red; 
  }
  
  // Down left
  if( (value == 2) || (value == 3) || (value == 4) || (value == 5) || (value == 6) )
  {
    ledArray[3][2] = CRGB::Red;
    ledArray[3][1] = CRGB::Red; 
    ledArray[4][2] = CRGB::Red; 
    ledArray[4][1] = CRGB::Red; 
  }
  
  // Center
  if( (value == 1) || (value == 3) || (value == 5) )
  {
    ledArray[6][5] = CRGB::Red;
    ledArray[6][4] = CRGB::Red; 
    ledArray[7][5] = CRGB::Red; 
    ledArray[7][4] = CRGB::Red; 
  }
  
  // Up Right
  if( (value == 2) || (value == 3) || (value == 4) || (value == 5) || (value == 6) )
  {
    ledArray[9][8] = CRGB::Red;
    ledArray[9][7] = CRGB::Red; 
    ledArray[10][8] = CRGB::Red;
    ledArray[10][7] = CRGB::Red; 
  }
  
  // Middle Right
  if( value == 6 )
  {
    ledArray[9][5] = CRGB::Red;
    ledArray[9][4] = CRGB::Red; 
    ledArray[10][5] = CRGB::Red;
    ledArray[10][4] = CRGB::Red; 
  }
  
  // Bottom Right
  if( (value == 4) || (value == 5) || (value == 6) )
  {
    ledArray[9][2] = CRGB::Red;
    ledArray[9][1] = CRGB::Red; 
    ledArray[10][2] = CRGB::Red;
    ledArray[10][1] = CRGB::Red; 
  }
  
    RefreshLeds(); 
  
}


void Display_SoundLevel()
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for x mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(A1);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 5);  // convert to volts
   
   ArrayRotate(&soundLevels[0], NB_COLUMNS);
   soundLevels[0] = (volts/10 -2);
   
  for(int column = 0; column < NB_COLUMNS; column++)
  {
    Column_DisplaySound(soundLevels[NB_COLUMNS-1-column], column);
  }

  RefreshLeds(); 
  
}


void Column_DisplaySound( int soundLevel, int column)  //0 to 9
{
    
  //Limit values    
  if(soundLevel > (NB_ROWS-1))
  {
    soundLevel = NB_ROWS-1;
  }
  else if(soundLevel  < 0)
  {
    soundLevel = 0;
  }
    
  //Affect values
  for(int row = 0; row < soundLevel; row++)
  {
    if(row < (NB_ROWS*0.5) )
    {
      ledArray[column][row] = CRGB::Green;
    }
    else if(row < (NB_ROWS*0.8) )
    {
      ledArray[column][row] = CRGB::Orange;
    }
    else
    {
      ledArray[column][row] = CRGB::Red;
    }
  }
  
  //Display in black remaining values
  for(int row = soundLevel; row < NB_ROWS; row++)
  {
      ledArray[column][row] = CRGB::Black;
  }
  
}


void RefreshLeds()
{
  for(int column = 0; column< NB_COLUMNS; column++)
  {
    for(int row = 0; row< NB_ROWS; row++)
    {
      if( (column % 2) == 0 )
      {
        leds[row + column*NB_ROWS] = ledArray[NB_COLUMNS-1-column][row]; 
      }
      else
      {
        leds[row + column*NB_ROWS] = ledArray[NB_COLUMNS-1-column][NB_ROWS-1-row]; 
      }
     }
   }
   
   FastLED.show(); 
}


void ArrayRotate(int *array, int nbElements)
{
  for(int i = (nbElements - 2); i >= 0; i--)
  {
    array[i+1] = array[i];
  } 
}


int telecommande(){

  if(ir_remote.value == 16738455)
  {
    Serial.println("1");
    return 1;
  }
  else if(ir_remote.value == 16750695)
  {
    Serial.println("2");
    return 2;
  }
  else if(ir_remote.value == 16756815){
    Serial.println("3");
    return 3;
  }
  else if(ir_remote.value == 16724175){
    Serial.println("4");
    return 4;
  }
  else if(ir_remote.value == 16718055){
    Serial.println("5");
    return 5;
  }
  else if(ir_remote.value == 16743045){
    Serial.println("6");
    return 6;
  }
  else if(ir_remote.value == 16716015){
    Serial.println("7");
    return 7;
  }

  else if(ir_remote.value == 16726215){
    Serial.println("8");
    return 8;
  }
  else if(ir_remote.value == 16734885)
  {
    Serial.println("9");
    return 9;
  }

  else if(ir_remote.value == 16730805){
    Serial.println("0");
    return 0;
  }
  else if(ir_remote.value == 16736925){
    Serial.println("haut");
    return 88;
  }
  else if(ir_remote.value == 16754775){
    Serial.println("bas");
    return 22;
  }
  else if(ir_remote.value == 16720605){
    Serial.println("gauche");
    return 44;
  }
  else if(ir_remote.value == 16761405){
    Serial.println("droite");
    return 66;
  }
  else if(ir_remote.value == 16712445){
    Serial.println("ok");
    return 55;
  }
  else if(ir_remote.value == 16728765){
    Serial.println("*");
    return 11;
  }
  else if(ir_remote.value == 16732845){
    Serial.println("#");
    return 33;
  }
  else if (ir_remote.value==4294967295)
  {
    Serial.println("V"); // V = 10= validation ( relachement du bouton )
    return 10;
  }
  else
  {
    Serial.println(ir_remote.value);
    return false;
  } 

}
