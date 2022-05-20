#ifndef NOISE_H
#define NOISE_H

#include <cmath>
#include "raylib.h"

class Perlin{
public:
    float persistence;
    int Number_Of_Octaves;
    Perlin(){
        persistence = 2.00;
        Number_Of_Octaves = 3;
    }
    double Noise(int x, int y);
    double SmoothedNoise(int x, int y);
    double Cosine_Interpolate(double a, double b, double x);
    double Linear_Interpolate(double a, double b, double x);
    double InterpolatedNoise(float x, float y);
    double PerlinNoise(float x, float y);
    static Image generateImage(int width, int height);
};

#endif // NOISE_H