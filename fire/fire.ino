#include<FastLED.h>
#define NUM_LEDS 134
#define DATA_PIN 7
#define CLK_PIN 14
#define MHZRATE DATA_RATE_MHZ(12)

#define BRIGHTNESS         50
#define MAX_BRIGHTNESS     128
#define FRAMES_PER_SECOND  100

// Individual Strips
// -Outside Strips
// --Right
#define TR_START 0
#define TR_END 61
#define TR_LENGTH 62

#define FR_START 62
#define FR_END 134
#define FR_LENGTH 72
// --Left
#define TL_START 0
#define TL_END 61
#define TL_LENGTH 62

#define FL_START 62
#define FL_END 134
#define FL_LENGTH 72
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

uint8_t gHue = 0; // rotating "base color" used by both patterns

CRGBArray<NUM_LEDS> leds;

CRGBSet topRight(leds(TR_START, TR_END));
CRGBSet frontRight(leds(FR_START, FR_END));
CRGBSet outsideRight(leds(TR_START, FR_END));

//fire settings
CRGBPalette16 gPal;

void setup() {
	delay(3000); // 3 second delay for recovery
	FastLED.addLeds<APA102, DATA_PIN, CLK_PIN, BGR, MHZRATE>(leds, NUM_LEDS);
	FastLED.setBrightness(BRIGHTNESS);
	// This first palette is the basic 'black body radiation' colors,
	// which run from black to red to bright yellow to white.
	//gPal = HeatColors_p;

	// These are other ways to set up the color palette for the 'fire'.
	// First, a gradient from black to red to yellow to white -- similar to HeatColors_p
	//   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);

	// Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
	   gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);

	// Third, here's a simpler, three-step gradient, from black to red to white
	//   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);
}

void loop()
{
	// Add entropy to random number generator; we use a lot of it.
	random16_add_entropy(random());

	// Fourth, the most sophisticated: this one sets up a new palette every
	// time through the loop, based on a hue that changes every time.
	// The palette is a gradient from black, to a dark color based on the hue,
	// to a light color based on the hue, to white.
	//
	//   static uint8_t hue = 0;
	//   hue++;
	//   CRGB darkcolor  = CHSV(hue,255,192); // pure hue, three-quarters brightness
	//   CRGB lightcolor = CHSV(hue,128,255); // half 'whitened', full brightness
	//   gPal = CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);


	Fire2012WithPalette(topRight, TR_LENGTH, true); // run simulation frame, using palette colors

	FastLED.show(); // display this frame
	FastLED.delay(1000 / FRAMES_PER_SECOND);
}


// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
//// 
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation, 
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking. 
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100 
#define COOLING  75

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120


void Fire2012WithPalette(CRGBSet strip, int striplen, bool stripup)
{
	// Array of temperature readings at each simulation cell


	static byte heat[TR_LENGTH];
	bool gReverseDirection = stripup;
	// Step 1.  Cool down every cell a little
	for (int i = 0; i < striplen; i++) {
		heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / striplen) + 2));
	}

	// Step 2.  Heat from each cell drifts 'up' and diffuses a little
	for (int k = striplen - 1; k >= 2; k--) {
		heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
	}

	// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
	if (random8() < SPARKING) {
		int y = random8(7);
		heat[y] = qadd8(heat[y], random8(160, 255));
	}

	// Step 4.  Map from heat cells to LED colors
	for (int j = 0; j < striplen; j++) {
		// Scale the heat value from 0-255 down to 0-240
		// for best results with color palettes.
		byte colorindex = scale8(heat[j], 240);
		CRGB color = ColorFromPalette(gPal, colorindex);
		int pixelnumber;
		if (gReverseDirection) {
			pixelnumber = (striplen - 1) - j;
		}
		else {
			pixelnumber = j;
		}
		strip[pixelnumber] = color;
	}
}
