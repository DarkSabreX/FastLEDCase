#define BREATH_H

//Rainbow Breathing
void drawBreath(CRGBSet strip) {
	float breath = (exp(sin(millis() / 1000.0*PI)) - 0.36787944)*108.0;
	strip.fill_rainbow(gHue);
	strip.fadeToBlackBy(breath);
}