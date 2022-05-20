#ifndef NOISE_H
#define NOISE_H

#include <cmath>
#include "raylib.h"

class Perlin {
   public:
    double persistence;
    int num_octaves;
    Perlin() {
        persistence = 2.00;
        num_octaves = 3;
    }
    double noise(int x, int y);
    double smoothedNoise(int x, int y);
    double cosineInterpolate(double a, double b, double x);
    double linearInterpolate(double a, double b, double x);
    double interpolatedNoise(double x, double y);
    double perlinNoise(double x, double y);
    static Image generateImage(int width, int height);
};

#endif  // NOISE_H