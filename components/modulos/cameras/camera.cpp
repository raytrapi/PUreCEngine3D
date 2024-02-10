#include "camera.h"
#include <constantes.h>
#include <entity.h>




void Camera::ponerOrto() {
	/*proyeccion[0] = 2.f / (derecha - izquierda);
	proyeccion[1] = proyeccion[2] = 0.f;
	proyeccion[3] = -((derecha+izquierda)/(derecha-izquierda));
	proyeccion[4] = 0.f;
	proyeccion[5] = 2.f / (arriba - abajo);
	proyeccion[6] =  0.f;
	proyeccion[7] = -((arriba + abajo) / (arriba - abajo));
	proyeccion[8] = proyeccion[9] = 0.f;
	proyeccion[10] = -2.f / (lejos - cerca);
	proyeccion[11] = -((lejos+cerca) / (lejos-cerca));
	proyeccion[12] = proyeccion[13] = proyeccion[14] = 0.f;
	proyeccion[15] = 1;/**/
	float ancho = derecha - izquierda;
	float alto = arriba - abajo;
	float profundidad = lejos - cerca;
	proyeccion[0] = 2.f / ancho;
	proyeccion[1] = proyeccion[2] = proyeccion[3] = 0.f;
	proyeccion[4] = 0.f;
	proyeccion[5] = 2.f / alto;
	proyeccion[6] = proyeccion[7] = 0.f;
	proyeccion[8] = proyeccion[9] = 0.f;
	proyeccion[10] = -2.f / profundidad;
	proyeccion[11] = 0.f;
	proyeccion[12] = -(derecha + izquierda) / ancho;
	proyeccion[13] = -(arriba + abajo) / alto;
	proyeccion[14] = -(lejos + cerca) / profundidad;
	proyeccion[15] = 1.f;/**/
}
/*void Camera::ponerOrto() {
	proyeccion[0] = 2.f / (derecha - izquierda);
	proyeccion[1] = proyeccion[2] = 0.f;
	proyeccion[3] = -((derecha + izquierda) / (derecha - izquierda));
	proyeccion[4] = 0.f;
	proyeccion[5] = 2.f / (arriba - abajo);
	proyeccion[6] = 0.f;
	proyeccion[7] = -((arriba + abajo) / (arriba - abajo));
	proyeccion[8] = proyeccion[9] = 0.f;
	proyeccion[10] = -2.f / (lejos - cerca);
	proyeccion[11] = -((lejos + cerca) / (lejos - cerca));
	proyeccion[12] = proyeccion[13] = proyeccion[14] = 0.f;
	proyeccion[15] = 1;

}/**/

void Camera::ponerPerspectiva() {
	if (!focal) {

		proyeccion[0] = 2.f  / (derecha - izquierda);
		proyeccion[1] = 0;
		proyeccion[2] = (derecha + izquierda) / (derecha - izquierda);
		proyeccion[3] = 0.f;
		proyeccion[4] = 0.f;
		proyeccion[5] = 2.f / (arriba - abajo);
		proyeccion[6] = (arriba + abajo) / (arriba - abajo);
		proyeccion[7] = proyeccion[8] = proyeccion[9] = 0.f;
		proyeccion[10] = -(lejos + cerca) / (lejos - cerca);
		proyeccion[11] = -2.f*lejos*cerca/(lejos-cerca);
		proyeccion[12] = proyeccion[13] = 0.f;
		proyeccion[14] = 1.f;
		proyeccion[15] = 0.f;
		/*proyeccion[0] = 2.f * cerca / (derecha - izquierda);
		proyeccion[1] = proyeccion[2] = proyeccion[3] = 0.f;
		proyeccion[4] = 2.f * cerca / (arriba - abajo);
		proyeccion[5] = proyeccion[6] = proyeccion[7] = 0.f;
		proyeccion[8] = (derecha + izquierda) / (derecha - izquierda);
		proyeccion[9] = (arriba + abajo) / (arriba - abajo);
		proyeccion[10] = -(lejos + cerca) / (lejos - cerca);
		proyeccion[11] = -1.f;
		proyeccion[12] = -2.f * (lejos * cerca) / (lejos - cerca);
		proyeccion[13] = proyeccion[14] = proyeccion[15] = 0.f;/**/
	} else {
		// = anguloFocal ;
		/*float aspectRatio = Screen::getWidth() / Screen::getHeight();
		float fovRad = 1.0f / tan(anguloFocal * 0.5f);

		proyeccion[0] = fovRad / aspectRatio;
		proyeccion[1] = 0.0f;
		proyeccion[2] = 0.0f;
		proyeccion[3] = 0.0f;

		proyeccion[4] = 0.0f;
		proyeccion[5] = fovRad;
		proyeccion[6] = 0.0f;
		proyeccion[7] = 0.0f;

		proyeccion[8] = 0.0f;
		proyeccion[9] = 0.0f;
		proyeccion[10] = (lejos + cerca) / (cerca - lejos);
		proyeccion[11] = -1.0f;

		proyeccion[12] = 0.0f;
		proyeccion[13] = 0.0f;
		proyeccion[14] = (2.0f * lejos * cerca) / (cerca - lejos);
		proyeccion[15] = 0.0f;/**/
		//float const a = 1.f / tanf(anguloFocal / 2.f);
		float const a = tanf(M_PI2 - anguloFocal * 0.5f);
		float w = (float)Screen::getWidth();
		float h = (float)Screen::getHeight();
		float const aspect_ratio = w / h;
		float const inversaRango = 1.0f / (cerca - lejos);
		//float const a = 1.f / tanf(anguloFocal / 2.f);
		//proyeccion[0] = a / ((derecha-izquierda) / (arriba- abajo));
		proyeccion[0] = a / aspect_ratio;
		proyeccion[1] = proyeccion[2] = proyeccion[3] = 0.f;
		proyeccion[4] = 0.f;
		proyeccion[5] = a;
		proyeccion[6] = proyeccion[7] = proyeccion[8] = proyeccion[9] = 0.f;
		proyeccion[10] = ((lejos + cerca) * inversaRango);
		proyeccion[11] = -1.f;
		
		proyeccion[12] = proyeccion[13] = 0.f;
		proyeccion[14] = cerca * lejos * inversaRango * 2;
		proyeccion[15] = 0.0f;/**/
		
		/*float sensor_width = 36.0; // En mm
		float fov = 60.0; // En grados
		float focal_length = sensor_width / (2 * tan(fov / 2));
		fov= 2.0f * atan(0.5f * (1.0f / focal_length));
		float f = 1.0f / tan(fov * 0.5f);
		float const a = 1.f / tanf(anguloFocal / 2.f);
		float const aspect_ratio = Screen::getWidth() / Screen::getHeight();
		proyeccion[0] = f/aspect_ratio;
		proyeccion[1] = proyeccion[2] = proyeccion[3] = 0.f;
		proyeccion[4] = 0.f;
		proyeccion[5] = f;
		proyeccion[6] = proyeccion[7] = proyeccion[8] = proyeccion[9] = 0.f;
		proyeccion[10] = ((lejos + cerca) / (lejos - cerca));
		proyeccion[11] = 2*(lejos+cerca)/(lejos-cerca);

		proyeccion[12] = proyeccion[13] = 0.f;
		proyeccion[14] = 1.f;
		proyeccion[15] = 0.f;/**/
		
		
		/*proyeccion[12] = proyeccion[13] = 0.f;
		proyeccion[14] = -((2.f * lejos * cerca) / (lejos - cerca));
		proyeccion[15] = 0.f;/**/
	}
}

void Camera::ponerVista2() {
	/* Obtenida de aquí https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function
	 Matrix44f lookAt(const Vec3f& from, const Vec3f& to, const Vec3f& tmp = Vec3f(0, 1, 0)){ 
		 Vec3f forward = normalize(from - to); 
		 Vec3f right = crossProduct(normalize(tmp), forward); 
		 Vec3f up = crossProduct(forward, right); 
 
		 Matrix44f camToWorld; 
 
		 camToWorld[0][0] = right.x; 
		 camToWorld[0][1] = right.y; 
		 camToWorld[0][2] = right.z; 
		 camToWorld[1][0] = up.x; 
		 camToWorld[1][1] = up.y; 
		 camToWorld[1][2] = up.z; 
		 camToWorld[2][0] = forward.x; 
		 camToWorld[2][1] = forward.y; 
		 camToWorld[2][2] = forward.z; 
 
		 camToWorld[3][0] = from.x; 
		 camToWorld[3][1] = from.y; 
		 camToWorld[3][2] = from.z; 
 
		 return camToWorld; 
	}
	*/
	
	//TODO: crear método par calcular la dimensión y la normal
	//float f_t[3] = { eye[0] - target[0], eye[1] - target[1], eye[2] - target[2] };
	float f_t[3] = { target[0] - eye[0], target[1] - eye[1], target[2] - eye[2] };

	//OJO puede ser todo 0;
	distanciaObjetivo= sqrtf(f_t[0] * f_t[0] + f_t[1] * f_t[1] + f_t[2] * f_t[2]);
	//float normalDistancia = 1.f / distanciaObjetivo;
	//float f_dimension =  sqrtf(f_t[0]* f_t[0] + f_t[1]* f_t[1]  + f_t[2]*f_t[2]);
	//FORWARD
	float axiZ[3] = { f_t[0] / distanciaObjetivo, f_t[1] / distanciaObjetivo, f_t[2] / distanciaObjetivo };

	//float s_t[3] = { f[1] * up[2] - f[2] * up[1], f[2] * up[0] - f[0] * up[2], f[0] * up[1] - f[1] * up[0] };
	//Producto en cuz de axiZ y Up
	/*float s_t[3] = {
		axiZ[1] * up[2] - axiZ[2] * up[1],
		axiZ[2] * up[0] - axiZ[0] * up[2],
		axiZ[0] * up[1] - axiZ[1] * up[0]
	};/**/
	//Producto en cuz de Up y axiZ
	float s_t[3] = {
		up[1] * axiZ[2] - up[2] * axiZ[1],
		up[2] * axiZ[0] - up[0] * axiZ[2],
		up[0] * axiZ[1] - up[1] * axiZ[0]
	};/**/
	float s_hipo = sqrtf(s_t[0]* s_t[0] + s_t[1]* s_t[1] + s_t[2]* s_t[2]);
	float s_dimension = (s_hipo != 0) ? s_hipo : 1;
	//OJO puede ser todo 0;
	//RIGHT
	float axiX[3] = { s_t[0] / s_dimension, s_t[1] / s_dimension, s_t[2] / s_dimension }; 

	//float t[3] = { s[1] * f[2] - s[2] * f[1], s[2] * f[0] - s[0] * f[2], s[0] * f[1] - s[1] * f[0] };
	//Multiplicamos X y Z
	/*float axiY[3] = {
		axiX[1] * axiZ[2] - axiX[2] * axiZ[1],
		axiX[2] * axiZ[0] - axiX[0] * axiZ[2],
		axiX[0] * axiZ[1] - axiX[1] * axiZ[0]
	};/**/
	//Multiplicamos Z y X
	//UP
	float axiY[3] = {
		axiZ[1] * axiX[2] - axiZ[2] * axiX[1],
		axiZ[2] * axiX[0] - axiZ[0] * axiX[2],
		axiZ[0] * axiX[1] - axiZ[1] * axiX[0]
	};/**/


	//look_at
	vista[0] = axiX[0];
	vista[1] = axiY[0];
	vista[2] = -axiZ[0];
	vista[3] = 0.f;
	vista[4] = axiX[1];
	vista[5] = axiY[1];
	vista[6] = -axiZ[1];
	vista[7] = 0.f;
	vista[8] = axiX[2];
	vista[9] = axiY[2];
	vista[10] = -axiZ[2];
	vista[11] = 0.f;
	vista[12] = (axiX[0] * -eye[0]) + (axiY[0] * -eye[1]) + (axiZ[0] * -eye[2]);
	vista[13] = (axiX[1] * -eye[0]) + (axiY[1] * -eye[1]) + (axiZ[1] * -eye[2]);
	vista[14] = (axiX[2] * -eye[0]) + (axiY[2] * -eye[1]) + (axiZ[2] * -eye[2]);
	vista[15] = 1.f;/**/
	/*vista[0] = axiX[0];
	vista[1] = axiY[0];
	vista[2] = axiZ[0];
	vista[3] = 0.f;
	vista[4] = axiX[1];
	vista[5] = axiY[1];
	vista[6] = axiZ[1];
	vista[7] = 0.f;
	vista[8] = axiX[2];
	vista[9] = axiY[2];
	vista[10] = axiZ[2];
	vista[11] = 0.f;
	vista[12] = (axiX[0] * -eye[0]) + (axiY[0] * -eye[1]) + (axiZ[0] * -eye[2]);
	vista[13] = (axiX[1] * -eye[0]) + (axiY[1] * -eye[1]) + (axiZ[1] * -eye[2]);
	vista[14] = (axiX[2] * -eye[0]) + (axiY[2] * -eye[1]) + (axiZ[2] * -eye[2]); 
	vista[15] = 1.f;/**/

	
}
void Camera::ponerVista() {

	/*
	//TODO: crear método par calcular la dimensión y la normal
	float f_t[3] = { eye[0] - target[0], eye[1] - target[1], eye[2] - target[2] };
	//float f_t[3] = { target[0] - eye[0], target[1] - eye[1], target[2] - eye[2] };

	//OJO puede ser todo 0;
	float f_dimension = sqrtf(f_t[0] * f_t[0] + f_t[1] * f_t[1] + f_t[2] * f_t[2]);
	float axiZ[3] = { f_t[0] / f_dimension, f_t[1] / f_dimension, f_t[2] / f_dimension };

	//float s_t[3] = { f[1] * up[2] - f[2] * up[1], f[2] * up[0] - f[0] * up[2], f[0] * up[1] - f[1] * up[0] };
	///float s_t[3] = {
		axiZ[1] * up[2] - axiZ[2] * up[1],
		axiZ[2] * up[0] - axiZ[0] * up[2],
		axiZ[0] * up[1] - axiZ[1] * up[0]
	};/*
	float s_t[3] = {
		up[1] * axiZ[2] - up[2] * axiZ[1],
		up[2] * axiZ[0] - up[0] * axiZ[2],
		up[0] * axiZ[1] - up[1] * axiZ[0]
	};/*
	float s_hipo = sqrtf(s_t[0] * s_t[0] + s_t[1] * s_t[1] + s_t[2] * s_t[2]);
	float s_dimension = (s_hipo != 0) ? s_hipo : 1;
	//OJO puede ser todo 0;
	float axiX[3] = { s_t[0] / s_dimension, s_t[1] / s_dimension, s_t[2] / s_dimension };

	//float t[3] = { s[1] * f[2] - s[2] * f[1], s[2] * f[0] - s[0] * f[2], s[0] * f[1] - s[1] * f[0] };
	/*float axiY[3] = {
		axiX[1] * axiZ[2] - axiX[2] * axiZ[1],
		axiX[2] * axiZ[0] - axiX[0] * axiZ[2],
		axiX[0] * axiZ[1] - axiX[1] * axiZ[0]
	};/*
	float axiY[3] = {
		axiZ[1] * axiX[2] - axiZ[2] * axiX[1],
		axiZ[2] * axiX[0] - axiZ[0] * axiX[2],
		axiZ[0] * axiX[1] - axiZ[1] * axiX[0]
	};/*


	//look_at
	vista[0] = axiX[0];
	vista[1] = axiY[0];
	vista[2] = axiZ[0];
	vista[3] = 0.f;
	vista[4] = axiX[1];
	vista[5] = axiY[1];
	vista[6] = axiZ[1];
	vista[7] = 0.f;
	vista[8] = axiX[2];
	vista[9] = axiY[2];
	vista[10] = axiZ[2];
	vista[11] = 0.f;
	vista[12] = (axiX[0] * -eye[0]) + (axiX[1] * -eye[1]) + (axiX[2] * -eye[2]); //MAL
	vista[13] = (axiY[0] * -eye[0]) + (axiY[1] * -eye[1]) + (axiY[2] * -eye[2]); //MAL
	vista[14] = (axiZ[0] * -eye[0]) + (axiZ[1] * -eye[1]) + (axiZ[2] * -eye[2]); //MAL
	vista[15] = 1;/**/
	/*float dirX = eye[0] - target[0];//target[0] - eye[0];//eye[0] - target[0];
	float dirY = eye[1] - target[1];//target[1] - eye[1];//eye[1] - target[1];
	float dirZ = eye[2] - target[2];//target[2] - eye[2];//eye[2] - target[2];/**/
	float dirX = target[0] - eye[0];//eye[0] - target[0];
	float dirY = target[1] - eye[1];//eye[1] - target[1];
	float dirZ = target[2] - eye[2];//eye[2] - target[2];
	// Normaliza los vectores de dirección hacia adelante. Frente
	float dirLength = std::sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
	if (dirLength > 0.00001f) {
		dirX /= dirLength;
		dirY /= dirLength;
		dirZ /= dirLength;
	} else {
		dirX = 0;
		dirY = 0;
		dirZ = 0;
	}

	//Dirección hacia la derecha
	// Calcula el vector lateral
	float sideX = up[1] * dirZ - up[2] * dirY;
	float sideY = up[2] * dirX - up[0] * dirZ;
	float sideZ = up[0] * dirY - up[1] * dirX;

	// Normaliza el vector lateral
	float sideLength = std::sqrt(sideX * sideX + sideY * sideY + sideZ * sideZ);
	if (sideLength > 0.00001f) {
		sideX /= sideLength;
		sideY /= sideLength;
		sideZ /= sideLength;
	} else {
		sideX = 0;
		sideY = 0;
		sideZ = 0;
	}

	// Calcula el vector lateral
	/*float upX = dirY * sideZ - dirZ * sideY;
	float upY = dirZ * sideX - dirX * sideZ;
	float upZ = dirX * sideY - dirY * sideX;
	float upLength = std::sqrt(upX * upX + upY * upY + upZ * upZ);
	if (upLength > 0.00001f) {
		upX /= upLength;
		upY /= upLength;
		upZ /= upLength;
	} else {
		upX = 0;
		upY = 0;
		upZ = 0;
	}/**/
	//Normalizar el UP
	float upLength = std::sqrt(up[0] * up[0] + up[1]* up[1] + up[2] * up[2]);
	if (upLength > 0.00001f) {
		up[0] /= upLength;
		up[1] /= upLength;
		up[2] /= upLength;
	} else {
		up[0] = 0;
		up[1] = 0;
		up[2] = 0;
	}
	// Construye la matriz de vista
	/*vista[0] = sideX;
	vista[1] = sideY;
	vista[2] = sideZ;
	vista[3] = 0.0f;

	vista[4] = up[0];
	vista[5] = up[1];
	vista[6] = up[2];
	vista[7] = 0.0f;

	vista[8] = dirX;
	vista[9] = dirY;
	vista[10] = dirZ;
	vista[11] = 0.0f;

	vista[12] = eye[0];
	vista[13] = eye[1];
	vista[14] = eye[2];
	vista[15] = 1.0f;*/
	vista[0] = sideX;
	vista[1] = up[0];
	vista[2] = -dirX;
	vista[3] = 0.0f;

	vista[4] = sideY;
	vista[5] = up[1];
	vista[6] = -dirY;
	vista[7] = 0.0f;

	vista[8] = sideZ;
	vista[9] = up[2];
	vista[10] = -dirZ;
	vista[11] = 0.0f;

	vista[12] = -eye[0];//;-(sideX * eye[0] + sideY * eye[1] + sideZ * eye[2]);
	vista[13] = -eye[1];// -(up[0] * eye[0] + up[1] * eye[1] + up[2] * eye[2]);
	vista[14] = eye[2];// (dirX * eye[0] + dirY * eye[1] + dirZ * eye[2]);
	vista[15] = 1.0f;/**/
	/*vista[0] = sideX;
	vista[1] = up[0];
	vista[2] = dirX;
	vista[3] = (sideX * eye[0] + sideY * eye[1] + sideZ * eye[2]);

	vista[4] = sideY;
	vista[5] = up[1];
	vista[6] = dirY;
	vista[7] = (up[0] * eye[0] + up[1] * eye[1] + up[2] * eye[2]);

	vista[8] = sideZ;
	vista[9] = up[2];
	vista[10] = dirZ;
	vista[11] = (dirX * eye[0] + dirY * eye[1] + dirZ * eye[2]);

	vista[12] = 0;
	vista[13] = 0;
	vista[14] = 0;
	vista[15] = 1.0f;/**/

	//Calculamos la inversa
	Transform::inverseMatrix(vista, inverseVista);

	/*float r[16];
	Transform::multMatrix(vista, 4, 4, inverseVista, 4, 4, r);

	DBG("Fin");/**/

}
void Camera::ponerVistaGuizmo() {
	
	//look_at
	/*float dirX = eye[0] - target[0];//target[0] - eye[0];//eye[0] - target[0];
	float dirY = eye[1] - target[1];//target[1] - eye[1];//eye[1] - target[1];
	float dirZ = eye[2] - target[2];//target[2] - eye[2];//eye[2] - target[2];/**/
	float dirX = target[0] - eye[0];//eye[0] - target[0];
	float dirY = target[1] - eye[1];//eye[1] - target[1];
	float dirZ = target[2] - eye[2];//eye[2] - target[2];*/
	// Normaliza los vectores de dirección hacia adelante. Frente
	float dirLength = std::sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
	if (dirLength > 0.00001f) {
		dirX /= dirLength;
		dirY /= dirLength;
		dirZ /= dirLength;
	} else {
		dirX = 0;
		dirY = 0;
		dirZ = 0;
	}

	//Dirección hacia la derecha
	// Calcula el vector lateral
	float sideX = up[1] * dirZ - up[2] * dirY;
	float sideY = up[2] * dirX - up[0] * dirZ;
	float sideZ = up[0] * dirY - up[1] * dirX;

	// Normaliza el vector lateral
	float sideLength = std::sqrt(sideX * sideX + sideY * sideY + sideZ * sideZ);
	if (sideLength > 0.00001f) {
		sideX /= sideLength;
		sideY /= sideLength;
		sideZ /= sideLength;
	} else {
		sideX = 0;
		sideY = 0;
		sideZ = 0;
	}

	//Normalizar el UP
	float upLength = std::sqrt(up[0] * up[0] + up[1] * up[1] + up[2] * up[2]);
	if (upLength > 0.00001f) {
		up[0] /= upLength;
		up[1] /= upLength;
		up[2] /= upLength;
	} else {
		up[0] = 0;
		up[1] = 0;
		up[2] = 0;
	}
	// Construye la matriz de vista
	vistaGuizmo[0] = sideX;
	vistaGuizmo[1] = up[0];
	vistaGuizmo[2] = -dirX;
	vistaGuizmo[3] = 0.0f;
	
	vistaGuizmo[4] = sideY;
	vistaGuizmo[5] = up[1];
	vistaGuizmo[6] = -dirY;
	vistaGuizmo[7] = 0.0f;
	
	vistaGuizmo[8] = sideZ;
	vistaGuizmo[9] = up[2];
	vistaGuizmo[10] = -dirZ;
	vistaGuizmo[11] = 0.0f;
	
	vistaGuizmo[12] = -eye[0];//;-(sideX * eye[0] + sideY * eye[1] + sideZ * eye[2]);
	vistaGuizmo[13] = -eye[1];// -(up[0] * eye[0] + up[1] * eye[1] + up[2] * eye[2]);
	vistaGuizmo[14] =  eye[2];// (dirX * eye[0] + dirY * eye[1] + dirZ * eye[2]);
	vistaGuizmo[15] = 1.0f;/**/
}
void Camera::actualizarProyeccion() {
	if (ortogonal) {
		//Modificamos la tabla a modo ortogonal
		ponerOrto();
	} else {
		ponerPerspectiva();
	}
	if (activa) {
		if (graphic == NULL) {
			graphic=Module::get<modules::graphics::Graphic>();
		}
		if (graphic != NULL) {
			graphic->updateEntities();
		}
		/*modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (g) {
			g->changeCamera(this);
		}/**/

	}
}
void Camera::recalcularObjetivo() {
	//return;
	if (mirandoPuntoFijo) {
		//Ahora calculamos los angulos
		auto [xR, yR, zR] = transformada->getRotation();
		auto [xC, yC, zC] = transformada->getPosition();
		auto [fx, fy, fz, upx, upy, upz] = Transform::calculateForwardVector2(xR, yR, zR, 0, 0, 1.0, 0, 1.0, 0);
		auto xD = target[0] - xC;
		auto yD = target[1] - yC;
		auto zD = target[2] - zC;
		//Normalizo
		float length = sqrtf(xD * xD + yD * yD + zD * zD);
		if (length != 0.0f) {
			xD /= length;
			yD /= length;
			zD /= length;
		}
		float rightX, rightY, rightZ; //Vector derecho
		rightX = up[1] * zD - up[2] * yD;
		rightY = up[2] * xD - up[0] * zD;
		rightZ = up[0] * yD - up[1] * xD;
		length = sqrtf(rightX * rightX + rightY * rightY + rightZ * rightZ);
		if (length != 0.0f) {
			rightX /= length;
			rightY /= length;
			rightZ /= length;
		}
		float upX, upY, upZ; //Vector UP Corregido
		up[0] = zD * rightY - yD * rightZ;
		up[1] = xD * rightZ - zD * rightX;
		up[2] = yD * rightX - xD * rightY;


		float azimuth = atan2f(rightX, rightZ);
		float pitch = atan2f(-yD, sqrtf(xD * xD + zD * zD));
		float roll = atan2f(up[0], up[1]);

		transformada->setRotation(pitch,0,0);// pitch, azimuth, roll);
	}
}


Camera::~Camera() {
	DBG("Borro cámara");
	if (transformada) {
		delete transformada;
	}
}

Transform* Camera::transform() {
	if (entidad) {
		return entidad->getTransform();
	} else {
		return transformada;
	}
	//return transformada;
	return NULL;
}

bool Camera::isActive() {
	return activa;
}

void Camera::setActive(bool active) {
	activa = active;
	if (active) {
		if (graphic == NULL) {
			graphic = Module::get<modules::graphics::Graphic>();
		}
		
		if (graphic != NULL) {
			graphic->changeCamera(this);
		}
	}
}

bool Camera::isOrtho() {
	return ortogonal;
}

void Camera::setOrto(bool ortho) {
	ortogonal = ortho;
	actualizarProyeccion();
}

void Camera::setSize(float x, float y, float width, float height) {
	izquierda = x;
	derecha = width;
	arriba = height;
	abajo = y;
	if (activa) {
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (g) {
			g->resizeCamera();
		}/**/
		actualizarProyeccion();
	}
}

void Camera::setDistance(float _near, float _far) {
	cerca = _near;
	lejos = _far;
	actualizarProyeccion();
	conCambio = true;

}

void Camera::setFocalAngle(float angle) {
	anguloFocal = angle;
	actualizarProyeccion();
}

void Camera::setFocal(float focal) {
	this->focal = focal;
}

//void Camera::setLookAt(float eye[3], float target[3], float up[3]) {
void Camera::setLookAt(float eyeX, float eyeY, float eyeZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ){
	this->eye[0] = eyeX;
	this->eye[1] = eyeY;
	this->eye[2] = eyeZ;
	this->target[0] = targetX;
	this->target[1] = targetY;
	this->target[2] = targetZ;
	this->up[0] = upX;
	this->up[1] = upY;
	this->up[2] = upZ; 

	float dX = target[0] - eye[0];// eye[0] - target[0];
	float dY = target[1] - eye[1];//eye[1] -target[1];
	float dZ = target[2] - eye[2];//eye[2] -target[2];
	distanciaObjetivo = sqrtf(dX * dX + dY * dY + dZ * dZ);
	

	ponerVista();
	conCambio = true;
	/*if (activa) {
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (g) {
			g->changeCamera(this);
		}
	}/**/
}

const float* Camera::getViewMatrix() {
	return vista;
}
float* Camera::getViewMatrixGuizmo() {
	ponerVistaGuizmo();
	return vistaGuizmo;
};
const float* Camera::getInverseViewMatrix() {
	return inverseVista;
}
const float* Camera::getProjectionMatrix() {
	return proyeccion;
}

float Camera::getWidth() {
	return derecha-izquierda;
}

float Camera::getHeight() {
	return abajo-arriba;
}
float Camera::getLeft() {
	return izquierda;
}
float Camera::getRight() {
	return derecha;
}
float Camera::getTop() {
	return arriba;
}
float Camera::getBottom() {
	return abajo;
}

const float Camera::getFocalAngle() {
	return anguloFocal;
}

void Camera::setPosX(float v) {
	eye[0] = v;
	conCambio = true;
};
void Camera::setPosEyeX(float v) {
	target[0] = v;
	conCambio = true;
};
float Camera::getPosX() {
	return eye[0];
};
float Camera::getPosEyeX() {
	return target[0];
};
void Camera::setPosY(float v) {
	eye[1] = v;
	conCambio = true;
};
void Camera::setPosEyeY(float v) {
	target[1] = v;
	conCambio = true;
};
float Camera::getPosY() {
	return eye[1];
};
float Camera::getPosEyeY() {
	return target[1];
};
void Camera::setPosZ(float v) {
	eye[2] = v;
	conCambio = true;
};
void Camera::setPosEyeZ(float v) {
	eye[2] = v;
	conCambio = true;
};
float Camera::getPosZ() {
	return eye[2];
};
float Camera::getPosEyeZ() {
	return target[2];
}

std::tuple<float, float, float> Camera::getPositionTarget() {
	return {target[0], target[1], target[2]};
}
void Camera::setPositionTarget(float x, float y, float z) {
	target[0] = x;
	target[1] = y;
	target[2] = z;
	
	//auto pitch = -asin(up[0] * dx + up[1] * dy + up[2] * dz)//atan2f(zD, sqrtf(xD * xD + yD * yD));
	//auto yaw = atan2f(yD, xD);

	//refresh(2);
	//recalcularObjetivo()
}
std::tuple<float, float> Camera::getNormalizeScreenExtra(double x, double y) {
	if (graphic == NULL) {
		graphic = Module::get<modules::graphics::Graphic>();
	}
	if (graphic != NULL) {
		auto [w, h] = graphic->getScreenSize();
		return { (((float)x / (float)w) * 2.0f) - 1.f,(((float)y / (float)h) * 2.0f) - 1.f };
	} else {
		return { 0,0 };
	}

};
std::tuple<float, float> Camera::getNormalizeScreen(double x, double y) {
	if (graphic == NULL) {
		graphic = Module::get<modules::graphics::Graphic>();
	}
	if (graphic != NULL) {
		auto [w,h]=graphic->getScreenSize();
		return {(float)x/(float)w,(float)y / (float)h};
	} else {
		return { 0,0 };
	}
	
};

float Camera::getRotX() {
	return anguloCamara[0];
};
float Camera::getRotY() {
	return anguloCamara[1];
};
float Camera::getRotZ() {
	return anguloCamara[2];
};
void Camera::setRotate(float x, float y, float z) {
	anguloCamara[0] = x;
	anguloCamara[1] = y;
	anguloCamara[2] = z;
	//target[0] = distanciaObjetivo * sinf(y);
	//target[2] = distanciaObjetivo * cosf(y);
	conCambio = true;
};
void Camera::refresh(int modo) {

	if ((modo & 1)>0) {
		ponerVista();
	}
	if ((modo & 2)>0) {
		if (ortogonal) {
			//Modificamos la tabla a modo ortogonal
			ponerOrto();
		} else {
			ponerPerspectiva();
		}
	}
	
	/*if (activa) {
		if (graphic == NULL) {
			graphic = Module::get<modules::graphics::Graphic>();
		}
		if (graphic != NULL) {
			graphic->updateEntities();
		}

	}/**/
}

bool Camera::isChange(bool reset) {
	if (conCambio) {
		if (reset) {
			conCambio = false;
		}
		return true;
	}
	return false;
}
void Camera::transformChanged() {
	//DBG((char*)u8"He cambiado la posición, escala o rotación de la cámara");
	//TODO: Gestionar mivimiento y rotación de la cámara
	
	Transform* transf;
	if (entidad) {
		transf = entidad->transformada;
	} else {
		transf = transformada;
	}

	std::tie(eye[0], eye[1], eye[2]) = transf->getPosition();

	auto [rx, ry, rz] = transf->getRotation();
	

	auto [fx, fy, fz, upx,upy,upz] = Transform::calculateForwardVector2(rx, ry, rz, 0,0,1.0, 0, 1.0, 0);
	if(!mirandoPuntoFijo){
		target[0] = fx * distanciaObjetivo;
		target[1] = fy * distanciaObjetivo;
		target[2] = fz * distanciaObjetivo;
	}
	up[0] = upx;
	up[1] = upy;
	up[2] = upz;/**/
	/*
	float dX = target[0] - eye[0];// eye[0] - target[0];
	float dY = target[1] - eye[1];//eye[1] -target[1];
	float dZ = target[2] - eye[2];//eye[2] -target[2];
	distanciaObjetivo = sqrtf(dX * dX + dY * dY + dZ * dZ);
	/**/
	refresh(3);
	conCambio = true;
	graphic->updateEntities(0,graphic->ALL);
	//Gestionamos los GIZMO
	//Luces
	auto luces = Entity::getAllGlobalComponents<LightComponent>();
	for (auto luz:luces) {
		luz->updateGizmo();
	}

}


bool modules::graphics::Graphic::isChangeCamera(Camera* camera, bool reset) {
	if (camera != NULL) {
		return camera->isChange(reset);
	}
	return false;
}


bool Camera::interfazImGUI_C(ImGuiContext* imgui) {
	ImGui::SetCurrentContext(imgui);
	ImGui::TableNextColumn();
	ImGui::Text(U8(FOV));
	ImGui::TableNextColumn();
	bool cambioCamara = false;
	
	float angulo = anguloFocal * M_RAD_GRAD;
	if (ImGui::DragFloat("##fovCamara", &angulo,0.5f,10.0f,180.0f)) {
		anguloFocal=(angulo*M_GRAD_RAD);
		cambioCamara = true;
	}
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	ImGui::Text(U8(Cerca));
	ImGui::TableNextColumn();
	if (ImGui::DragFloat("##cercaCamara", &(this->cerca), 0.1f)) {
		cambioCamara = true;
	}
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	ImGui::Text(U8(Lejos));
	ImGui::TableNextColumn();
	if (ImGui::DragFloat("##lejosCamara", &(this->lejos), 0.1f)) {
		cambioCamara = true;
	}
	ImGui::TableNextRow();
	ImGui::TableNextColumn();

	ImGui::Text(U8(Posición));
	ImGui::TableNextColumn();
	float camaraPos[3];
	std::tie(camaraPos[0], camaraPos[1], camaraPos[2]) = transform()->getPosition();
	if (ImGui::DragFloatN_Colored("##posCamara", camaraPos, 3,0.01F)) {
		transform()->setPosition(camaraPos[0], camaraPos[1], camaraPos[2]);
		recalcularObjetivo();
		cambioCamara = true;
	}
	
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	ImGui::Text(U8(Punto Fijo));
	ImGui::TableNextColumn();
	ImGui::Checkbox("##puntoFijo", &(this->mirandoPuntoFijo));
	
	
	if (this->mirandoPuntoFijo) {
		ImGui::BeginDisabled();
	}
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	ImGui::Text(U8(Rotación));
	ImGui::TableNextColumn();
	float camaraRot[3];
	std::tie(camaraRot[0], camaraRot[1], camaraRot[2]) = transform()->getRotation();
	camaraRot[0] *= M_RAD_GRAD;
	camaraRot[1] *= M_RAD_GRAD;
	camaraRot[2] *= M_RAD_GRAD;
	if (ImGui::DragFloatN_Colored("##rotCamara", camaraRot, 3,0.5f)) {
		transform()->setRotation(camaraRot[0] * M_GRAD_RAD, camaraRot[1] * M_GRAD_RAD, camaraRot[2] * M_GRAD_RAD);
		cambioCamara = true;
	}
	if (cambioCamara) {
		transformChanged();
	}
	if (this->mirandoPuntoFijo) {
		ImGui::EndDisabled();
	}


	if (!this->mirandoPuntoFijo) {
		ImGui::BeginDisabled();
	}
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(U8(Punto vista));
		ImGui::TableNextColumn();
		float camaraTarget[3];
		std::tie(camaraTarget[0], camaraTarget[1], camaraTarget[2]) = getPositionTarget();
		if (ImGui::DragFloatN_Colored("##targetCamara", camaraTarget, 3)) {
			setPositionTarget(camaraTarget[0], camaraTarget[1], camaraTarget[2]);
			recalcularObjetivo();
			cambioCamara = true;
		}
	}
	if (!this->mirandoPuntoFijo) {
		ImGui::EndDisabled();
	} else {
		ImGui::BeginDisabled();
	}
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(U8(Distancia));
		ImGui::TableNextColumn();
		ImGui::DragFloat("##distancia", &(this->distanciaObjetivo), 0.5f, 0.1f, 500.0f);
	}
	if (this->mirandoPuntoFijo) {
		ImGui::EndDisabled();
	}
	if (cambioCamara) {
		transformChanged();
	}
	return true;
}
int Camera::saveState_interno(std::vector<unsigned char>* data, bool withID) {
	int longitud = Serializer::serialize(data, (int)TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_CAMERA);
	return longitud;
};
void Camera::restoreState_interno(std::vector<unsigned char>* data, bool withID, int pos) {
	transformada->restoreState(data, withID, pos);
};
void Camera::move(float incX, float incY, float incZ, float complete) {


	auto [rXC, rYC, rZC] = transformada->getPosition();
	rYC -= incY;
	rXC -= incX;
	transformada->setPosition(rXC, rYC, rZC);
	if (complete) {
		target[0] += incX;
		target[1] += incY;
		target[2] += incZ;
	}
	transformChanged();
}