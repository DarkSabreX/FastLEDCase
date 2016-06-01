#define LIGHTNING_H

void drawLightning(CRGBSet strip, int striplen) {

	FastLED.clear();

	static const uint8_t FLASHES = 8;
	static unsigned long flashNext;
	static uint8_t flashCounter = 0, flashMax = 0;
	static uint8_t ledlen, ledstart;
	static uint8_t flashchance = 10;

	// (re)init data
	if (flashCounter == flashMax) {
		ledlen = random8(3, striplen - 3); // length of flash, at least 3 LEDs
		ledstart = 1 + random8(striplen - ledlen); // start of flash
		flashNext = millis() + 1000 * random8(flashchance); // random start of flash sequence
		flashCounter = 0;
		flashMax = random8(3, FLASHES);
	}

	// show next flash, if it's time has come
	if (millis() >= flashNext) {
		uint8_t dimmer;

		if (flashCounter == 0) {
			// the brightness of the leader is scaled down by a factor of 5
			dimmer = 5;
		}
		else {
			// return strokes are brighter than the leader
			dimmer = random8(1, 3);
		}

		// Show a section of LED's
		fill_solid(strip + ledstart, ledlen, CHSV(255, 0, 255 / dimmer));

		// each flash only lasts 4-10 milliseconds
		FastLED.delay(random8(4, 10));

		// Clear the section of LED's
		fill_solid(strip + ledstart, ledlen, CRGB::Black);
		FastLED.show();

		flashNext = millis() + 50 + random8(100);
		if (flashCounter == 0) {
			flashNext += 150;
		}
		flashCounter++;
	}
}
