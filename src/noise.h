#ifndef NOISE_H
#define NOISE_H
#include <cmath>
class Perlin{
public:
    float persistence;
    int Number_Of_Octaves;
    Perlin(){
        persistence = 0.50;
        Number_Of_Octaves = 4;
    }
    double Noise(int x, int y);
    double SmoothedNoise(int x, int y);
    double Cosine_Interpolate(double a, double b, double x);
    double Linear_Interpolate(double a, double b, double x);
    double InterpolatedNoise(float x, float y);
    double PerlinNoise(float x, float y);
};
#endif // NOISE_H