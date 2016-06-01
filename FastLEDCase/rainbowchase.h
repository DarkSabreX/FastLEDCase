#define RAINBOWCHASE_H

void drawRainbowChase(CRGBSet strip, int pixelcount) {
	fadeToBlackBy(strip, pixelcount, 40);
	int pos = beatsin16(13, 0, pixelcount - 1);
	static int prevpos = 0;
	if (pos < prevpos) {
		fill_solid(strip + pos, (prevpos - pos) + 1, CHSV(gHue, 220, 255));
	}
	else {
		fill_solid(strip + prevpos, (pos - prevpos) + 1, CHSV(gHue, 220, 255));
	}
	prevpos = pos;
	EVERY_N_MILLISECONDS(10) { gHue--; }
}

void drawRainbowChaseMirror(CRGBSet strip, int pixelcount) {
	fadeToBlackBy(strip, pixelcount, 40);
	int pos = beatsin16(13, 0, pixelcount / 2);
	static int prevpos = 0;
	if (pos < prevpos) {
		fill_solid(strip + pos, (prevpos - pos) + 1, CHSV(gHue, 220, 255));
	}
	else {
		fill_solid(strip + prevpos, (pos - prevpos) + 1, CHSV(gHue, 220, 255));
	}
	prevpos = pos;
	strip(pixelcount / 2, pixelcount) = strip(pixelcount / 2, 0);
	EVERY_N_MILLISECONDS(10) { gHue--; }
}