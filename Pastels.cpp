#include "Pastels.h"
#include <cstdlib>
#include <iostream>

//https://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
float hue2rgb(float p, float q, float t) {
 

    if (t < 0) t += 1;
    if (t > 1) t -= 1;
    if (t < 1.0 / 6.0) return p + (q - p) * 6 * t;
    if (t < 1.0 / 2.0) return q;
    if (t < 2.0 / 3.0) return p + (q - p) * (2 / 3 - t) * 6;
    return p;
}


SDL_Color generateRandomPastel() {
	float h =(rand() % 361) / 360.0;
	float s = (25 + rand() % 71) / 100.0;
	float l =( 85 + rand() % 11) / 100.0;

   
    float r, g, b;
    SDL_Color returnColor;

    if (s == 0) {
        r = g = b = 1;
    }
    else {
        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;
        r = hue2rgb(p, q, h + 1.0 / 3.0);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1.0 / 3.0);
    }

    returnColor.r = round(r * 255);
    returnColor.g = round(g * 255);
    returnColor.b = round(b * 255);

   
    returnColor.a = 255;
 /*   //stolen from here: https://www.codespeedy.com/hsv-to-rgb-in-cpp/
 *  float C = s * v;
    float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    float m = v - C;
    float r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    }
    else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    }
    else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    }
    else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    }
    else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    }
    else {
        r = C, g = 0, b = X;
    }
    int R = (r + m) * 255;
    int G = (g + m) * 255;
    int B = (b + m) * 255;

    SDL_Color returnColor;
    returnColor.r = R;
    returnColor.g = G;
    returnColor.b = B;
    returnColor.a = 255;*/
    return returnColor;

}