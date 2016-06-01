#define ADDGLITTER_H

void addGlitterAll(fract8 chanceOfGlitter)
{
	if (random8() < chanceOfGlitter) {
		eleds[random16(ENUM_LEDS)] += CRGB::White;
		ileds[random16(INUM_LEDS)] += CRGB::White;
	}
}

void addGlitter(fract8 chanceOfGlitter, CRGBSet strip, int striplen)
{
	if (random8() < chanceOfGlitter) {
		strip[random16(striplen)] += CRGB::White;
	}
}