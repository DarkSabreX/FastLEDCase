#define CONFETTI_H

/*
RGBSet adapted Confetti routine
*/

void drawConfetti(CRGBSet strip, int pixelcount)
{
	// random colored speckles that blink in and fade smoothly

	strip.fadeToBlackBy(30);
	int pos = random16(pixelcount);
	strip[pos] += CHSV(gHue - 32 + random8(64), 200, 255);
}