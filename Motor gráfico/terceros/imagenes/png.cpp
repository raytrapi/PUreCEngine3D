#include "png.h"

namespace imagenes {
	Imagen* PNG::cargar(const char* nombreFichero) {
		FILE* fp = fopen(nombreFichero, "rb");
		if (!fp) {
			return NULL;
		}

		png_const_bytep cabecera = new unsigned char(8);
		//unsigned int* buffer=new unsigned int[10000];
		int cargados = 8;
		fread((void*)cabecera, 1, cargados, fp);
		bool is_png = !png_sig_cmp(cabecera, 0, cargados);
		if (!is_png) {
			fclose(fp);
			return NULL;
		}


		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
													 NULL, NULL, NULL);
		if (!png_ptr) return NULL;
		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr) {
			png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
			fclose(fp);
			return NULL;
		}

		if (setjmp(png_jmpbuf(png_ptr))) {
			fclose(fp);
			return NULL;
		}

		png_init_io(png_ptr, fp);
		png_set_sig_bytes(png_ptr, 8);

		png_read_info(png_ptr, info_ptr);

		unsigned int ancho = png_get_image_width(png_ptr, info_ptr);
		unsigned int alto = png_get_image_height(png_ptr, info_ptr);
		unsigned char color_type = png_get_color_type(png_ptr, info_ptr);
		unsigned char bit_depth = png_get_bit_depth(png_ptr, info_ptr);

		int number_of_passes = png_set_interlace_handling(png_ptr);
		png_read_update_info(png_ptr, info_ptr);


		if (setjmp(png_jmpbuf(png_ptr))) {
			fclose(fp);
			return NULL;
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
				for (int j = 0; j < 4; j++) {
					raw[b+j] = (float)(row_pointers[alto-y-1][(x*4)+j]/255);
				}
				b += 4;
			}
			free(row_pointers[alto - y-1]);
		}
		free(row_pointers);
		Imagen* imagen = new Imagen(); 
		imagen->ponerAncho(ancho);
		imagen->ponerAlto(alto);
		imagen->setDatos(raw);

		fclose(fp);
		return imagen;
	}

};
 