#pragma once
#include <cmath>
#include <ctime>
#include <random>
#include "../utiles/utilidades.h"
class EXPORTAR_UTILIDADES Math {

public:
	static float* perlin2D(long int posX, long int posY, int width, int height, int octetos, int seed , float amplitude, float density=1.0f);
	static float interpolateBilinear(int x1, int y1, int x2, int y2, float v1, float v2, float v3, float v4, int tx, int ty);
	static float interpolateLinear(int x1, int y1, int x2, int y2);
	static float* generateRandomGradient();
	static float* perlin2D(long int posX, long int posY, int width, int height, int seed = -1, int widthGrid=100, int heightGrid=100, float density = 16.f, int octave=8, float persistence=1.f, float darkness=1.f);
	static float perlinNoise(float x, float y, float** gradients, int widthGrid, int heightGrid);
	static float lerp(float a, float b, float t);
	static float inverseLerp(float a, float b, float t);
	static float dotGridGradient(int ix, int iy, float x, float y, float** gradients, int widthGrid, int heightGrid);
};