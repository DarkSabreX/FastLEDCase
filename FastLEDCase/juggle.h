#define JUGGLE_H

void drawJuggle(CRGBSet strip, int pixelcount) {
	// eight colored dots, weaving in and out of sync with each other
	strip.fadeToBlackBy(20);
	byte dothue = 0;
	for (int i = 0; i < 8; i++) {
		strip[beatsin16(i + 7, 0, pixelcount)] |= CHSV(dothue, 200, 255);
		dothue += 32;
	}
}