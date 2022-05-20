#include "noise.h"
#include <ctime>

double Perlin::noise(int x, int y) {
    int n = x + y * 57;
    n = (n << 13) ^ n;
    // return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) /
    //                   1073741824.0);
    return (1.0 - ((n * (n * n * time(0) + 789221) + 1376312589) & 0x7fffffff) /
                      1073742024.0);
}

double Perlin::smoothedNoise(int x, int y) {
    double corners = (noise(x - 1, y - 1) + noise(x + 1, y - 1) +
                      noise(x - 1, y + 1) + noise(x + 1, y + 1)) /
                     16;
    double sides = (noise(x - 1, y) + noise(x + 1, y) + noise(x, y - 1) +
                    noise(x, y + 1)) /
                   8;
    double center = noise(x, y) / 4;
    return corners + sides + center;
}
double Perlin::cosineInterpolate(double a, double b, double x) {
    double ft = x * 3.1415927;
    double f = (1 - cos(ft)) * 0.5;
    return a * (1 - f) + b * f;
}
double Perlin::linearInterpolate(double a, double b, double x) {
    return a * (1 - x) + b * x;
}

double Perlin::interpolatedNoise(double x, double y) {
    int integer_X = int(x);
    double fractional_X = x - integer_X;
    int integer_Y = int(y);
    double fractional_Y = y - integer_Y;
    double v1 = smoothedNoise(integer_X, integer_Y);
    double v2 = smoothedNoise(integer_X + 1, integer_Y);
    double v3 = smoothedNoise(integer_X, integer_Y + 1);
    double v4 = smoothedNoise(integer_X + 1, integer_Y + 1);
    double i1 = cosineInterpolate(v1, v2, fractional_X);
    double i2 = cosineInterpolate(v3, v4, fractional_X);
    return cosineInterpolate(i1, i2, fractional_Y);
}

double Perlin::perlinNoise(double x, double y) {
    x /= scale;
    y /= scale;
    double noise = 0;
    double p = persistence;
    int n = num_octaves;
    for (int i = 0; i < n; i++) {
        double frequency = pow(2, i);
        double amplitude = pow(p, i);
        noise =
            noise + interpolatedNoise(x * frequency, y * frequency) * amplitude;
    }

    return noise;
}

// deprecated
Image Perlin::generateImage(int width, int height) {
    Color* pixels = new Color[width * height];
    Perlin perlin;
    for (int i = 0; i < width * height; i++) {
        double p =
            perlin.perlinNoise(double(i / width), double(i % width)) + 0.25;
        // printf("%lf ", p);
        if (p >= 1)
            pixels[i] = WHITE;
        else if (p <= 0)
            pixels[i] = BLACK;
        else
            pixels[i] = {(unsigned char)(p * 255), (unsigned char)(p * 255),
                         (unsigned char)(p * 255), 255};
        // printf("%d ", pixels[i].r);
    }

    Image image = {.data = pixels,
                   .width = width,
                   .height = height,
                   .mipmaps = 1,
                   .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};

    return image;
}