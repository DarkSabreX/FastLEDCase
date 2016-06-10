#define ONESINE_H

void one_sine(CRGBSet strip, int striplen) {                                                             // This is the heart of this program. Sure is short.
	onesinephase += onesinespeed;                                                     // You can change direction and speed individually.
	onesinehue = onesinehue + onesinerot;                                                // Hue rotation is fun for thiswave.
	for (int k = 0; k<striplen - 1; k++) {                                          // For each of the LED's in the strand, set a brightness based on a wave as follows:
		int onesinebright = qsubd(cubicwave8((k*onesinefreq) + onesinephase), onesinecutoff);    // qsub sets a minimum value called thiscutoff. If < thiscutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
		strip[k] = CHSV(bgclr, 255, bgbright);                                        // First set a background colour, but fully saturated.
		strip[k] += CHSV(onesinehue, onesinesat, onesinebright);                             // Then assign a hue to any that are bright enough.
	}
	bgclr++;                                                                    // You can change the background colour or remove this and leave it fixed.
} // one_sine()

void one_sine_pal(CRGBSet strip,int striplen, uint8_t colorIndex) {                                                         // This is the heart of this program. Sure is short.
	onesinephase += onesinespeed;                                                     // You can change direction and speed individually.
	for (int k = 0; k<striplen; k++) {                                          // For each of the LED's in the strand, set a brightness based on a wave as follows:
		int thisbright = qsuba(cubicwave8((k*onesinefreq) + onesinephase), onesinecutoff);    // qsub sets a minimum value called thiscutoff. If < thiscutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
		strip[k] = CHSV(bgclr, 255, bgbright);                                     // First set a background colour, but fully saturated.
		strip[k] += ColorFromPalette(currentPalette, colorIndex, thisbright, currentBlending);
		colorIndex += onesinerot;
	}
	bgclr += bgclrinc;                                                                    // You can change the background colour or remove this and leave it fixed.
} // one_sine_pal()

void SetupRandomColorPalette() {
	for (int i = 0; i < 16; i++) targetPalette[i] = CHSV(random8(), 255, 255);
} // SetupRandomColorPalette()

void ChangeMe() {
	uint8_t secondHand = (millis() / 1000) % 60;                // Increase this if you want a longer demo.
	static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.  
	if (lastSecond != secondHand) {
		lastSecond = secondHand;
		switch (secondHand) {
		case  0: break;
		case  5: targetPalette = RainbowColors_p; bgclr = 0; bgbright = 32; bgclrinc = 1; onesinerot = 1; onesinedelay = 10; onesinespeed = -4; onesinefreq = 16; onesinecutoff = 128; currentBlending = NOBLEND; break;
		case 10: targetPalette = ForestColors_p; onesinespeed = 12; onesinerot = 0; onesinespeed = 12; onesinedelay = 10; onesinecutoff = 128; onesinefreq = 64; bgclr = 50; bgbright = 15; break;
		case 15: SetupRandomColorPalette(); onesinespeed = 16; break;
		case 20: onesinespeed = 4; break; onesinefreq = 16; bgclr = 50; break;
		case 25: onesinecutoff = 96; bgclr = 20; bgbright = 20; break;
		case 30: onesinecutoff = 96; onesinerot = 1; break;
		case 35: targetPalette = OceanColors_p; break;
		case 40: onesinecutoff = 128; wavebright = 64; break;
		case 45: onesinespeed = 3; break;
		case 50: targetPalette = PartyColors_p; break;
		case 55: break;
		case 60: break;
		}
	}
} // ChangeMe()


  // RainbowColors_p, RainbowStripeColors_p, OceanColors_p, CloudColors_p, ForestColors_p, and PartyColors_p.

