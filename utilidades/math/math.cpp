#include "math.h"

float* Math::perlin2D(long int posX, long int posY, int width, int height, int octetos, int seed, float amplitude, float density) {
	std::srand(seed >= 0 ? seed : std::time(nullptr));// std::time(nullptr));
	//DBG("aleatorio %", std::rand());
	if (width <= 0 || height <= 0) {
		return 0;
	}
	int size = width * height;

	float* mapa = new float[size];
	
	for (int i = 0; i < size; i++) {
		mapa[i] = 0.0f;
	}
	int numPuntosOctetosAncho = powf(2, octetos)+1;
	float cuadrantesAncho = (width*density) / (numPuntosOctetosAncho-1);
	
	float a_ = amplitude / 2.f;
	auto numPuntosOctetos = numPuntosOctetosAncho* numPuntosOctetosAncho;
	float* mapaOctetos = new float[numPuntosOctetos];
	for (int i = 0; i<numPuntosOctetos; i++) {
		mapaOctetos[i] = ((float)std::rand() / (float)RAND_MAX)*amplitude-a_;
	}
	
	for (int y = 0; y < height; y ++) {
		for (int x = 0; x < width; x ++) {
			int xR = x + posX;
			int yR = y + posX;
			//TODO: Realmente se calcularía una vez fuera y cuando lleguemos a sobrepasar
			int cuadranteAncho = (xR / cuadrantesAncho);
			int cuadranteAlto = (yR / cuadrantesAncho);
			int x1 = cuadranteAncho ;
			int y1 = cuadranteAlto;
			int x2 = (cuadranteAncho+1);
			int y2 = (cuadranteAlto+1);
			float v1 = mapaOctetos[x1 % numPuntosOctetosAncho + (y1 % numPuntosOctetosAncho) * numPuntosOctetosAncho];
			float v2 = mapaOctetos[x2 % numPuntosOctetosAncho + (y1 % numPuntosOctetosAncho) * numPuntosOctetosAncho];
			float v3 = mapaOctetos[x1 % numPuntosOctetosAncho + (y2 % numPuntosOctetosAncho) * numPuntosOctetosAncho];
			float v4 = mapaOctetos[x2 % numPuntosOctetosAncho + (y2 % numPuntosOctetosAncho) * numPuntosOctetosAncho];
			mapa[y * width + x] = interpolateBilinear(x1* cuadrantesAncho, y1* cuadrantesAncho, x2* cuadrantesAncho, y2* cuadrantesAncho, v1, v2, v3, v4, x, y);
		}
	}
	delete[]mapaOctetos;
	float amplitude_ = amplitude / 2.0f;
	for (int i = 0; i < size; i++) {
		mapa[i] = (mapa[i] + amplitude_) / amplitude;

	}

	return mapa;
}
/*float* Math::perlin2D(long int posX, long int posY, int width, int height, int octetos, int seed, float amplitude) {
	std::srand(seed>=0? seed:std::time(nullptr));// std::time(nullptr));
	//DBG("aleatorio %", std::rand());
	if (width <= 0 || height <= 0) {
		return 0;
	}
	int size = width * height;

	float* mapa = 0;
	float* valores = new float[size];
	for (int i = 0; i < size; i++) {
		valores[i] = 0.0f;
	}
	
	//float amplitud_ = amplitude2 / 2.f;

	for (int octeto = 0; octeto < octetos; octeto++) {
		float frecuencia = powf(2, octeto);
		float amplitude2 = amplitude/frecuencia;
		float amplitud_ = amplitude2 / 2.f;
		int step_length = floor((float)width / frecuencia);
		if (step_length <= 0) {
			step_length = 1;
		}

		for (int y = 0; y <= height; y += step_length) {
			for (int x = 0; x <= width; x += step_length) {
				int posX = x < width ? x : width - 1;
				int posY = y < height ? y : height - 1;
				float a1 = (float)std::rand();
				valores[posY * width + posX] = amplitud_ - ((a1 / (float)RAND_MAX) * amplitude2);
				//Interpolation between nodes
				if (y >= step_length && x >= step_length) {
					int y1 = y - (step_length);
					int y2 = y;
					int x1 = x - (step_length);
					int x2 = x;
					if (x1 >= width) {
						x1 = width - 1;
					}
					if (x2 >= width) {
						x2 = width - 1;
					}
					if (y1 >= height) {
						y1 = height - 1;
					}
					if (y2 >= height) {
						y2 = height - 1;
					}
					float v1 = valores[x1 + y1 * width];
					float v2 = valores[x2 + y1 * width];
					float v3 = valores[x1 + y2 * width];
					float v4 = valores[x2 + y2 * width];
					for (int a = y - (step_length); a < y; a++) {
						for (int b = x - (step_length); b < x; b++) {
							valores[a * width + b] = interpolateBilinear(x1, y1, x2, y2, v1, v2, v3, v4, b, a);
						}
					}
				}

			}
		}
		if (mapa == 0) {
			mapa = new float[size];
			for (int i = 0; i < size; i++) {
				mapa[i] = valores[i];
			}
		} else {
			for (int i = 0; i < size; i++) {
				mapa[i] += valores[i];

			}
		}
	}
	delete[] valores;
	float amplitude_ = amplitude / 2.0f;
	for (int i = 0; i < size; i++) {
		mapa[i] = (mapa[i]+amplitude_)/amplitude;

	}

	return mapa;
}/**/

float Math::interpolateBilinear(int x1, int y1, int x2, int y2, float v1, float v2, float v3, float v4, int tx, int ty){
	float area_v1 = (float)abs((tx - x1) * (ty - y1)) * v4;
	float area_v2 = (float)abs((tx - x2) * (ty - y1)) * v3;
	float area_v3 = (float)abs((tx - x1) * (ty - y2)) * v2;
	float area_v4 = (float)abs((tx - x2) * (ty - y2)) * v1;
	float area_total = (x2 - x1) * (y2 - y1);
	float sum = (area_v1 + area_v2 + area_v3 + area_v4);
	if (area_total != 0 && sum != 0) {
		return sum / area_total;
	} else {
		return 0;
	}
}

float Math::interpolateLinear(int x1, int y1, int x2, int y2){
	return ((x2 - x1) * (y2 - y1) / (x2 - x1)) + y1;
}


//**********//
//*PERLIN 2*//

float* Math::generateRandomGradient() {
	

	float* gradient = new float[2]; // Vector de gradiente de dos elementos (x, y)
	gradient[0] = ((float)std::rand() / (float)RAND_MAX) * 2.0f - 1.0f; // Valores entre -1 y 1
	gradient[1] = ((float)std::rand() / (float)RAND_MAX) * 2.0f - 1.0f;

	// Normalizar el vector
	float length = std::sqrt(gradient[0] * gradient[0] + gradient[1] * gradient[1]);
	gradient[0] /= length;
	gradient[1] /= length;

	return gradient;
}
float* Math::perlin2D(long int posX, long int posY, int width, int height, int seed, int gridW, int gridH, float density, int octave, float persistence, float darkness) {
	std::srand(seed >= 0 ? seed : std::time(nullptr));// std::time(nullptr));
	if (gridW <= 0) {
		gridW = 1;
	}
	if (gridH <= 0) {
		gridH = 1;
	}
	gridW = width;
	gridH = height;
	if (octave <= 0) {
		octave = 1;
	}
	int gridL = gridW * gridH;
	float** grid = new float* [gridL];
	int posG = 0;
	for (int posG = 0; posG < gridL; posG++) {
		grid[posG] = generateRandomGradient();
	}
	int size = width * height;
	float* map = new float[size];
	int posM = 0;
	float ruidoMaximo= std::numeric_limits<float>::min();
	float ruidoMinimo = std::numeric_limits<float>::max();
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float amplitud = 1.0f;
			float frecuencia = 1.0f;
			float noise = 0;
			for (int o = 0; o < octave; o++) {
				float xMuestra = (float)(x + posX) / (density)*frecuencia;
				float yMuestra = (float)(y + posY) / (density)*frecuencia;
				noise+= (perlinNoise(xMuestra, yMuestra,  grid, gridW, gridH) )* amplitud;//*2.f-1.f
				amplitud *= persistence;
				frecuencia *= darkness;
				if (frecuencia == 0) {
					break;
				}
			}
			if (noise > ruidoMaximo) {
				ruidoMaximo = noise;
			} else if (noise < ruidoMinimo) {
				ruidoMinimo = noise;
			}
			map[posM++] =noise;
		}
	}
	for (int i = 0; i < size; i++) {
		map[i] = inverseLerp(ruidoMinimo, ruidoMaximo, map[i]);
	}

	for (int posG = 0; posG < gridL; posG++) {
		delete[] grid[posG];
	}
	delete[] grid;
	return map;
}

float Math::perlinNoise(float x, float y, float** gradients, int widthGrid, int heightGrid) {
	// Determina la celda de la rejilla que rodea a (x, y)
	int x0 = (int)floor(x);
	int x1 = x0 + 1;
	int y0 = (int)floor(y);
	int y1 = y0 + 1;

	// Calcula las diferencias entre (x, y) y los vértices de la celda
	float sx = x - (float)(x0);
	float sy = y - (float)(y0);

	// Interpola los resultados de las funciones de punto de producto en las esquinas de la celda
	float n0 = dotGridGradient(x0, y0, x, y, gradients, widthGrid, heightGrid);
	float n1 = dotGridGradient(x1, y0, x, y, gradients, widthGrid, heightGrid);
	float ix0 = lerp(n0, n1, sx);

	n0 = dotGridGradient(x0, y1, x, y, gradients, widthGrid, heightGrid);
	n1 = dotGridGradient(x1, y1, x, y, gradients, widthGrid, heightGrid);
	float ix1 = lerp(n0, n1, sx);

	// Interpola entre ix0 e ix1 a lo largo del eje y
	return lerp(ix0, ix1, sy);// +1.0f) / 2.0f;
}
// Función de interpolación lineal
float Math::lerp(float a, float b, float t) {
	return a + t * (b - a);
}
float Math::inverseLerp(float a, float b, float t) {
	if (a == b) {
		// En caso de que a y b sean iguales, devuelve 0.0 para evitar la división por cero.
		return 0.0f;
	} else {
		return (t - a) / (b - a);
	}
}
// Función para calcular el producto punto entre un gradiente y un vector
float Math::dotGridGradient(int ix, int iy, float x, float y, float** gradients, int widthGrid, int heightGrid) {
	// Calcula el vector desde el punto de la rejilla hasta (x, y)
	ix = ix % widthGrid;
	iy = iy % heightGrid;
	float dx = x - (float)(ix);
	float dy = y - (float)(iy);

	
	// Obtener el vector de gradiente en la posición de la rejilla
	auto gradient = gradients[ix + iy * widthGrid];

	// Calcular el producto punto entre el gradiente y el vector (dx, dy)
	return (dx * gradient[0] + dy * gradient[1]);

}