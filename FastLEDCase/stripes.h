#define STRIPES_H

void drawStripes(CRGBSet strip) 
{
	for (int i = 0; i < NUM_LEDS - 1; i++) 
	{ 
		strip(i, i + 1) = CRGB::Red; 
		FastLED.delay(33); 
		strip(i, i + 1) = CRGB::Black; 
	}
}