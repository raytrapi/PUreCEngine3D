#include "conDLLIMG.h"

std::tuple<float*, int, int, unsigned int, modules::graphics::TextureImg::FORMAT_COLOR> ResourcesDirect::loadImage(const char* file) {
	LOG_DBG("Cargamos la image %", file);
	FILE* fp = fopen(file, "rb");
	if (!fp) {
		return {};
	}

	png_const_bytep cabecera = new unsigned char(8);
		//unsigned int* buffer=new unsigned int[10000];
	int cargados = 8;
	fread((void*)cabecera, 1, cargados, fp);
	bool is_png = !png_sig_cmp(cabecera, 0, cargados);
	if (!is_png) {
		fclose(fp);
		return {};
	}


	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
													NULL, NULL, NULL);
	if (!png_ptr) return {};
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(fp);
		return {};
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		fclose(fp);
		return {};
	}

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);

	png_read_info(png_ptr, info_ptr);

	unsigned int ancho = png_get_image_width(png_ptr, info_ptr);
	unsigned int alto = png_get_image_height(png_ptr, info_ptr);
	unsigned int color_type = png_get_color_type(png_ptr, info_ptr);
	unsigned int canales=png_get_channels(png_ptr, info_ptr);
		/*
		1 - PNG_COLOR_TYPE_GRAY or PNG_COLOR_TYPE_PALETTE
		2 - PNG_COLOR_TYPE_GRAY_ALPHA
		3 - PNG_COLOR_TYPE_RGB
		4 - PNG_COLOR_TYPE_RGB_ALPHA or PNG_COLOR_TYPE_RGB+filler byte 
		5 - PNG_COLOR_MASK_PALETTE
		6 - PNG_COLOR_MASK_COLOR
		7 - PNG_COLOR_MASK_ALPHA
		PARA PNG
		0: Gray (1 channel)
		2: RGB  (3 channels)
		3: color palette (1 channel)
		4: Gray-alpha (2 channels)
		6: RGBA (4 channels)
		*/
	unsigned char bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	LOG_DBG("Colores % - %", canales, color_type);
	int number_of_passes = png_set_interlace_handling(png_ptr);
	png_read_update_info(png_ptr, info_ptr);


	if (setjmp(png_jmpbuf(png_ptr))) {
		fclose(fp);
		return {};
	}

	png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * alto);
	for (int y = 0; y < alto; y++) {
		size_t d = png_get_rowbytes(png_ptr, info_ptr);
		row_pointers[y] = (png_byte*)malloc(d);
	}

	png_read_image(png_ptr, row_pointers);

	float* raw = (float*)malloc(sizeof(float) * alto*ancho*4);
	int b = 0;
	for (int y = 0; y < alto; y++) {
		for (int x = 0; x < ancho; x++) {
			if ((x == 0 && y == 0) || (x==110 && y== 76)) {
				DBG("Color RGBA [%,%] %,%,%,%", x,y,
					(int)row_pointers[y][(x * 4) + 0], 
					(int)row_pointers[y][(x * 4) + 1], 
					(int)row_pointers[y][(x * 4) + 2], 
					(int)row_pointers[y][(x * 4) + 3]);
			}
			for (int j = 0; j < 4; j++) {
				raw[b+j] = (float)((float)row_pointers[alto - y - 1][(x*4)+j]/255.f); //
			}
			b += 4;
		}
		free(row_pointers[alto - y-1]);
	}
	free(row_pointers);
	fclose(fp);
	LOG_DBG("La imgaen es de %x%", ancho, alto);
	return { raw,ancho,alto,ancho * alto * 4,modules::graphics::TextureImg::RGBA };
}
/*std::vector<std::tuple<Key, std::function<void(Key)>, bool>> Input::controlTeclasPulsadas;
Input* Input::instancia;/**/
REGISTRAR_MODULO(ResourcesDirect);