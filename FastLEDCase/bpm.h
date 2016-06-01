#define BPM_H

void drawRbowBpm(CRGBSet strip, int striplen, bool isLeft)
{
	// colored stripes pulsing at a defined Beats-Per-Minute (BPM)
	uint8_t BeatsPerMinute = 62;
	CRGBPalette16 palette = PartyColors_p;
	uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
	if (isLeft == 1) {
		for (int i = striplen - 1; i >= 0; i--) { //9948
			strip[i] = ColorFromPalette(palette, gHue - (i * 2), beat + gHue - (i * 10));
		}
	}
	else {
		for (int i = 0; i < striplen; i++) { //9948
			strip[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
		}
	}
	
}