#include "entity.h"
#include "light.h"




LightComponent::LightComponent(Entity* entity, modules::graphics::Graphic* g, Component* p) {
	this->entidad = entity;
	graphic = g;
	padre = p;
	//fisicas = g->getPhysics();
	//cargarEntidad();
	this->entidad->setRenderUpdatable();
	updateGizmo();

	g->getFrameBuffer(&profundidadFBO);
	g->generateTexture2DWithFBO(&profundidadTextura2D, anchoTextura2D, altoTextura2D,profundidadFBO, g->TEXT_DEPTH_COMPONENT, g->FB_FRAMEBUFFER);
	g->getFrameBuffer(&profundidadFBO_DBG);
	g->generateTexture2DWithFBO(&profundidadTextura2D_DBG, anchoTextura2D, altoTextura2D, profundidadFBO_DBG, g->TEXT_RGBA, g->FB_RENDERBUFFER);
}

void LightComponent::updateGizmo() {
	auto [px, py, pz] = entidad->transform()->getPosition();

	auto camara = graphic->getActiveCamera();
	if (camara) {
		auto [pcx, pcy, pcz] = camara->getPosition();
	   

		auto dir_x = px - pcx;
		auto dir_y = py - pcy;
		auto dir_z = pz - pcz;
		auto length = sqrtf(dir_x * dir_x + dir_y * dir_y + dir_z * dir_z);
		if (length > 0) {
			dir_x /= length;
			dir_y /= length;
			dir_z /= length;
		}
		auto ry = atan2f(dir_x, dir_z);
		auto h = sqrtf(dir_x * dir_x + dir_z * dir_z);
		auto rx = atan2f(dir_y, h);
		auto rz = 0;

		auto distance = sqrtf((px - pcx) * (px - pcx) + (py - pcy) * (py - pcy) + (pz - pcz) * (pz - pcz));
		float s = 1.0f;
		if (distance > 0) {
			s /= distance;
		}
		auto sx = s;
		auto sy = s; 
		auto sz = s;
		rx = ry = rz = 0;
		sx = sy = sz = 1.0f;
		Transform::calculateMatrix(matrizGizmo, px, py, pz, rx, ry, rz, sx, sy, sz);
		entidad->setUpdatingRender(true);
	}
}
void LightComponent::transformChanged() {
	calcularVistaProyeccion();
	graphic->refresh();
	graphic->renderShadowMap(this,profundidadFBO, profundidadTextura2D, anchoTextura2D, altoTextura2D, graphic->SM_DIRECTIONAL);
	
	
	//TODO: Esto sería solo en modo edición
	updateGizmo();

}
void LightComponent::calcularVistaProyeccion() {

	//Ortonormal
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
	proyeccion[15] = 1.f;

	//Vista
	std::tie(this->eye[0], this->eye[1], this->eye[2]) = entidad->transform()->getPosition();
	auto [rx, ry, rz] = entidad->transformada->getRotation();
	//auto [fx, fy, fz, upX, upY, upZ] = Transform::calculateForwardVector2(rx, ry, rz, 0.0f, -1.0, 0.0f, 0.0f, 0.0f, 1.0f);
	auto [fx, fy, fz, upX, upY, upZ] = Transform::calculateForwardVector2(rx, ry, rz, 0.0f, 0.0, 1.0f, 0.0f, 1.0f, 0.0f);
	
	this->target[0] = fx*distanciaObjetivo;
	this->target[1] = fy * distanciaObjetivo;
	this->target[2] = fz * distanciaObjetivo;
	this->up[0] = upX;
	this->up[1] = upY;
	this->up[2] = upZ;

	float dX = target[0] - eye[0];// eye[0] - target[0];
	float dY = target[1] - eye[1];//eye[1] -target[1];
	float dZ = target[2] - eye[2];//eye[2] -target[2];
	distanciaObjetivo = sqrtf(dX * dX + dY * dY + dZ * dZ);


	float dirX = target[0] - eye[0];
	float dirY = target[1] - eye[1];
	float dirZ = target[2] - eye[2];

	// Normaliza los vectores de dirección y up
	float dirLength = std::sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
	dirX /= dirLength;
	dirY /= dirLength;
	dirZ /= dirLength;

	/*float upLength = std::sqrt(up[0] * up[0] + up[1] * up[1] + up[2] * up[2]);
	float upX = up[0] / upLength;
	float upY = up[1] / upLength;
	float upZ = up[2] / upLength;
	*/

	// Calcula el vector lateral
	float sideX = upY * dirZ - upZ * dirY;
	float sideY = upZ * dirX - upX * dirZ;
	float sideZ = upX * dirY - upY * dirX;

	// Normaliza el vector lateral
	float sideLength = std::sqrt(sideX * sideX + sideY * sideY + sideZ * sideZ);
	sideX /= sideLength;
	sideY /= sideLength;
	sideZ /= sideLength;

	// Calcula el vector up corregido
	float upSideX = dirY * sideZ - dirZ * sideY;
	float upSideY = dirZ * sideX - dirX * sideZ;
	float upSideZ = dirX * sideY - dirY * sideX;

	// Construye la matriz de vista
	vista[0] = sideX;
	vista[1] = upSideX;
	vista[2] = -dirX;
	vista[3] = 0.0f;

	vista[4] = sideY;
	vista[5] = upSideY;
	vista[6] = -dirY;
	vista[7] = 0.0f;

	vista[8] = sideZ;
	vista[9] = upSideZ;
	vista[10] = -dirZ;
	vista[11] = 0.0f;

	vista[12] = -(sideX * eye[0] + sideY * eye[1] + sideZ * eye[2]);
	vista[13] = -(upSideX * eye[0] + upSideY * eye[1] + upSideZ * eye[2]);
	vista[14] = dirX * eye[0] + dirY * eye[1] + dirZ * eye[2];
	vista[15] = 1.0f;


	Transform::multMatrix(proyeccion, 4, 4, vista, 4, 4, vista_proyeccion);
}
const float* LightComponent::getViewMatrix(int view) {
	return vista;
}
const float* LightComponent::getViewProjectMatrix(int view) {
	return vista_proyeccion;
}
const float* LightComponent::getProjectMatrix() {
	return proyeccion;
}


std::string LightComponent::serializar() {
	std::string objetoSerializado = "";
	std::string resultado = GenericFile::serializate("componente", "{\r\n" + GenericFile::serializate("tipo", TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_LUZ) + "}\r\n", false, false);
	return resultado;

};
int LightComponent::saveState_interno(std::vector<unsigned char>* data, bool withID) {
	int longitud = Serializer::serialize(data, (int)TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_LUZ);
	return longitud;
};
void LightComponent::restoreState_interno(std::vector<unsigned char>* data, bool withID, int pos) {
};