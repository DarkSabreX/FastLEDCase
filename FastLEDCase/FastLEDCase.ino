/*
White Queen PC Case Lighting powered by FastLED.
By: Remy Z Romano
Date: May, 2016

Intro:

LED Lighting effects for my Resident Evil Themed Pc named "White Queen".
2 arrays pf APA102 led strips.
Outside strips are separated in 4 parts, corresponding to Top and Front left and right sides of the case.
Inside strips are separated into x strips in different zones.
Using CRGBSets to animate sections corresponding to their location in the case.
Serial data can be received to change variables such as the mode, color, and the palette

*/

/*------------------------------------------------------------------------------------------
--------------------------------------- Start of variables ---------------------------------
------------------------------------------------------------------------------------------*/
#include<FastLED.h>

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

//Fixed Definitions
//#define DATA_PIN           7
//#define CLK_PIN            14

//Exterior Strip Pins
#define EDATA_PIN           7
#define ECLK_PIN            14
//Interior Strip Pins
#define IDATA_PIN          11
#define ICLK_PIN           13

#define MHZRATE            DATA_RATE_MHZ(12)
#define COLOR_ORDER        BGR

#define FRAMES_PER_SECOND  100

//#define NUM_LEDS 268

#define ENUM_LEDS 300
#define INUM_LEDS 144


// Individual Strip definitions
// -Exterior Strips
// --Right
#define TR_START     0
#define TR_END       61
#define TR_LENGTH    62

#define FR_START     62
#define FR_END       132
#define FR_LENGTH    71
// --Left
#define FL_START     133
#define FL_END       203
#define FL_LENGTH    71

#define TL_START     206
#define TL_END       267
#define TL_LENGTH    62

//Whole Sides
#define ER_START     0
#define ER_END       133
#define ER_LENGTH    134

#define EL_START     268 
#define EL_END       134
#define EL_LENGTH    134

#define I_START      0
#define I_END        143
#define I_LENGTH     144

//----------------------- Palettes ---------------------------------------------------------
// Gradient palette "bhw1_14_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_14.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_14_gp) {
	0, 0, 0, 0,
		12, 1, 1, 3,
		53, 8, 1, 22,
		80, 4, 6, 89,
		119, 2, 25, 216,
		145, 7, 10, 99,
		186, 15, 2, 31,
		233, 2, 1, 5,
		255, 0, 0, 0
};
// -Inside Strips
// --Big Window Top

// --Lil Window Top

// --Big Window Bottom

//  --Lil Window Bottom

// Strip Groups
// -Outside Strips
// -Inside Strips
// --Big Window

// --Lil Window

//Global Vairables
CRGBPalette16 gPal;

bool gReverseDirection = true;
uint8_t max_bright = 50;
uint8_t gHue = 0;
uint8_t gSat = 255;
uint8_t gBrt = 128;

//CRGB LED Array
//CRGBArray<NUM_LEDS> leds;


CRGBArray<ENUM_LEDS> eleds;
CRGBArray<INUM_LEDS> ileds;


//Individual CRGBSets for each strip and strip group
CRGBSet topRight(eleds(TR_START, TR_END));
CRGBSet frontRight(eleds(FR_START, FR_END));
CRGBSet outsideRight(eleds(TR_START, FR_END));
//CRGBSet outsideRight(leds(OR_START, OR_END));

CRGBSet frontLeft(eleds(FL_START, FL_END));
/*
CRGBSet topLeft(leds(TL_START, TL_END));
CRGBSet frontLeft(leds(FL_START, FL_END));
CRGBSet outsideLeft(leds(OL_START, OL_END));
*/
CRGBSet inside(ileds(I_START, I_END));

//Set starting mode
int ledMode = 0;
int maxMode; 

// Serial definition
#define SERIAL_BAUDRATE 115200                                 // Or 115200.
#define SERIAL_TIMEOUT 8

byte inbyte;                                                  // Serial input byte
int thisarg;                                                  // Serial input argument
bool leftSide = 1;
bool rightSide = 0;
															  // Generic variables
uint8_t thisdelay = 0;                                        // Standard delay
uint8_t thishue = 0;                                          // Standard hue
uint8_t thissat = 255;                                        // Standard saturation
int thisbright = 0;                                           // Standard brightness
uint8_t thisfade = 224;                                         // Standard fade rate
bool thisdir = 0;                                             // Standard direction


//Pattern Variables

//Confetti


//Patterns to include
#include "confetti.h"
#include "rainbow.h"
#include "juggle.h"
#include "rainbowchase.h"
#include "breath.h"
#include "addglitter.h"
#include "bpm.h"
#include "fire.h"
#include "lightning.h"

/*------------------------------------------------------------------------------------------
--------------------------------------- Start of code --------------------------------------
------------------------------------------------------------------------------------------*/
void setup() { 
	delay(3000); // 3 second delay for recovery
	Serial.begin(SERIAL_BAUDRATE);                              // SETUP HARDWARE SERIAL (USB)
	Serial.setTimeout(SERIAL_TIMEOUT);
	//FastLED.addLeds<APA102, DATA_PIN, CLK_PIN, COLOR_ORDER, MHZRATE>(leds, NUM_LEDS);
	
	FastLED.addLeds<APA102, EDATA_PIN, ECLK_PIN, COLOR_ORDER, MHZRATE>(eleds, ENUM_LEDS);
	FastLED.addLeds<APA102, IDATA_PIN, ICLK_PIN, COLOR_ORDER, MHZRATE>(ileds, INUM_LEDS);
	

	FastLED.setBrightness(max_bright);
	random16_set_seed(4832);                                    // Awesome randomizer
	random16_add_entropy(analogRead(2));
	//int ranstart = random16();

	Serial.println("---SETUP COMPLETE---");
	change_mode(ledMode, 1);                                    // Initialize the first sequence
}

void loop() {
	readkeyboard();
	change_mode(ledMode, 0);
	//drawConfetti(frontRight, FR_LENGTH);
	//drawRainbow();
	// send the 'leds' array out to the actual LED strip
	//FastLED.show();
	// insert a delay to keep the framerate modest
	//FastLED.delay(1000 / FRAMES_PER_SECOND);
	// do some periodic updates
	//EVERY_N_MILLISECONDS(10) { gHue--; } // slowly cycle the "base color" through the rainbow
}

//Modes

void change_mode(int newMode, int mc) {
	
	maxMode = 8;
	if (mc != 99999) {

		switch (newMode)
		{
	    //All off, No Animation    
		case  0: 
			//leds.fill_solid(CRGB(0, 0, 0));
			eleds.fill_solid(CRGB(0, 0, 0));
			ileds.fill_solid(CRGB(0, 0, 0));
			FastLED.show();
			break;
			/*drawConfetti(frontRight, FR_LENGTH); 
			drawJuggle(topRight, TR_LENGTH); 
			FastLED.show(); 
			FastLED.delay(1000 / FRAMES_PER_SECOND); 
			break; */
		//All on, no Animation
		case  1: 
			//leds.fill_solid(CRGB(255, 255, 255));
			eleds.fill_solid(CRGB(255, 255, 255));
			ileds.fill_solid(CRGB(255, 255, 255));
			FastLED.show(); 
			break; 
		//Fill All strips with a Rainbow, no Animation   
		case  2: 
			drawRainbow(); 
			FastLED.show(); 
			break;
		//Fill All Strips with a solid color
		case  3: 
			//leds.fill_solid(CHSV(gHue, gSat, gBrt));
			eleds.fill_solid(CHSV(gHue, gSat, gBrt));
			ileds.fill_solid(CHSV(gHue, gSat, gBrt));
			FastLED.show(); 
			break;
			//Animations
		//Fill All strips with an animated rainbow
		case  4: 
			drawRainbow(); 
			FastLED.show(); 
			EVERY_N_MILLISECONDS(10) { gHue--; };
			break;
		//Fill All Strips With Animated Rainbow and Add Glitter
		case  5: 
			drawRainbow(); 
			addGlitterAll(80); 
			FastLED.show(); 
			FastLED.delay(1000 / FRAMES_PER_SECOND); 
			EVERY_N_MILLISECONDS(10) { gHue--; };
			break;
		case  6: 
			drawRainbowChase(topRight, TR_LENGTH); 
			drawRbowBpm(frontRight, FR_LENGTH, rightSide);
			drawBreath(frontLeft);
			drawBreath(inside);
			FastLED.show(); 
			FastLED.delay(1000 / FRAMES_PER_SECOND); 
			break;
		case  7:
			random16_add_entropy(random());
			gPal = bhw1_14_gp;
			ifire();
			FastLED.show();
			FastLED.delay(1000 / FRAMES_PER_SECOND);
			break;
		case  8:
			drawLightning(topRight, TR_LENGTH);
			FastLED.show();
			FastLED.delay(1000 / FRAMES_PER_SECOND);
			break;
			//DEMO MODE
			//case 99: demo_modeA(); break;
		}
		ledMode = newMode;
	}
	
}





void drawRedStripes(CRGBSet strip, int striplen) {
	// running red stripes 
	for (uint16_t i = 0; i < striplen; i++) {
		uint8_t red = (millis() / 3) + (i * 5);
		if (red > 128) red = 0;
		strip[i] = CRGB(red, 0,0);
		
	}
}


//----------------- Hardware Support Functions ---------------------------------------------

void readkeyboard() {                                         // PROCESS HARDWARE SERIAL COMMANDS AND ARGS
while (Serial.available() > 0) {

inbyte = Serial.read();                                   // READ SINGLE BYTE COMMAND
Serial.print("Serial read is: ");
Serial.println(inbyte);
switch(inbyte) {

case 59: break;                                         // BREAK IF INBYTE = ';'

case 98:                                                // "b" - SET MAX BRIGHTNESS to #
max_bright = Serial.parseInt();
FastLED.setBrightness(max_bright);
break;

case 99:                                                // "c" - CLEAR STRIP
eleds.fill_solid(CRGB(0,0,0));
ileds.fill_solid(CRGB(0, 0, 0));
break;

case 100:                                               // "d" - SET DELAY VAR to #
thisarg = Serial.parseInt();
thisdelay = thisarg;
break;

case 101:                                               // "e1 or e2" - DECREASE OR INCREASE delay by 1
thisarg = Serial.parseInt();
if (thisarg == 1) thisdelay--; else thisdelay++;
if (thisdelay < 0 ) thisdelay = 0;
break;

case 104:                                               // "h" - SET HUE VAR to #
thisarg = Serial.parseInt();
gHue = thisarg;
break;

case 109:                                               // "m" - SET MODE to #
thisarg = Serial.parseInt();
change_mode(thisarg, 1);
break;

case 110:                                               // "n0 or n1" - DIRECTION is 0 or 1
thisarg = Serial.parseInt();
if (thisarg <=1 && thisarg >=0 ) thisdir = thisarg;
break;

case 111:                                               // "o1 or o2" - DECREASE OR INCREASE MODE by 1
thisarg = Serial.parseInt();
if (thisarg == 1) ledMode--;
if (thisarg == 2) ledMode++;
if (ledMode < 0) ledMode = 0;
change_mode(ledMode, 1);
break;


case 114:                                               // "r1 or r2" - DECREASE OR INCREASE BRIGHTNESS by / or * 2
thisarg = Serial.parseInt();
if (thisarg == 1) max_bright=max_bright/2; else max_bright=max_bright*2;
max_bright = constrain(max_bright, 1, 255);
FastLED.setBrightness(max_bright);
show_at_max_brightness_for_power();
break;

case 116:                                               // "t" - SET SATURATION VAR to #
thisarg = Serial.parseInt();
gSat = thisarg;
break;

case 117:                                               // "u1 or u2" - DECREASE OR INCREASE HUE by 8
thisarg = Serial.parseInt();                          // Only works in some CHSV modes
if (thisarg == 1) thishue=thishue-8; else thishue=thishue+8;
//show_at_max_brightness_for_power();
break;

case 122:                                               // "z" - COMMAND TO 'SHOW' LEDS
show_at_max_brightness_for_power();
break;
} // switch inbyte
} // while Serial.available
} 


/*const TProgmemRGBGradientPalettePtr gGradientPalettes[] = {

}*/



