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

int     Ipos = TR_LENGTH / 2; // position of the "integer-based bar"
int     Idelta = 1; // how many pixels to move the Integer Bar
uint8_t Ihue = 20; // color for Integer Bar

int     F16pos = 0; // position of the "fraction-based bar"
int     F16delta = 1; // how many 16ths of a pixel to move the Fractional Bar
uint8_t Fhue = 20; // color for Fractional Bar

int Width = 4; // width of each light bar, in whole pixels

int InterframeDelay = 40; //ms

void setup() {
	delay(3000); // 3 second delay for recovery
	FastLED.addLeds<APA102, DATA_PIN, CLK_PIN, BGR, MHZRATE>(leds, NUM_LEDS);
	FastLED.setBrightness(BRIGHTNESS);
}

void drawIntegerBar(CRGBSet strip, int striplen, int intpos, int width, uint8_t hue)
{
	int i = intpos; // start drawing at "I"
	for (int n = 0; n < width; n++) {
		strip[i] += CHSV(hue, 255, 255);
		i++;
		if (i == striplen) i = 0; // wrap around
	}
}

void drawFractionalBar(CRGBSet strip, int striplen, int pos16, int width, uint8_t hue)
{
	int i = pos16 / 16; // convert from pos to raw pixel number
	uint8_t frac = pos16 & 0x0F;
	uint8_t firstpixelbrightness = 255 - (frac * 16);
	uint8_t lastpixelbrightness = 255 - firstpixelbrightness;
	uint8_t bright;
	for (int n = 0; n <= width; n++) {
		if (n == 0) {
			// first pixel in the bar
			bright = firstpixelbrightness;
		}
		else if (n == width) {
			// last pixel in the bar
			bright = lastpixelbrightness;
		}
		else {
			// middle pixels
			bright = 255;
		}

		strip[i] += CHSV(hue, 255, bright);
		i++;
		if (i == striplen) i = 0; // wrap around
	}
}

void mode2() {
	// Update the "Fraction Bar" by 1/16th pixel every time
	F16pos += F16delta;

	// wrap around at end
	// remember that F16pos contains position in "16ths of a pixel"
	// so the 'end of the strip' is (NUM_LEDS * 16)
	if (F16pos >= (TR_LENGTH * 16)) {
		F16pos -= (TR_LENGTH * 16);
	}
	static byte countdown = 0;
	if (countdown == 0) {
		countdown = 16; // reset countdown

						// advance Integer Bar one full pixel now
		Ipos += 1;
		// wrap around at end
		if (Ipos >= TR_LENGTH) {
			Ipos -= TR_LENGTH;
		}
	}
	// countdown is decremented every time through the loop
	countdown -= 1;

	// Draw everything:
	// clear the pixel buffer
	memset8(topRight, 0, TR_LENGTH * sizeof(CRGB));
	// draw the Integer Bar, length=4px, hue=180
	drawIntegerBar(topRight, TR_LENGTH, Ipos, Width, Ihue);
	// draw the Fractional Bar, length=4px, hue=180
	drawFractionalBar(topRight, TR_LENGTH, F16pos, Width, Fhue);

	FastLED.show();
	delay(InterframeDelay);
}

void loop()
{
	mode2();
}