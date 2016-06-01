#define RAINBOW_H

void drawRainbow()
{
	// FastLED's built-in rainbow generator

	//fill_rainbow( leds             , NUM_LEDS,   gHue, 17);
	eleds.fill_rainbow(gHue);
	ileds.fill_rainbow(gHue);
}