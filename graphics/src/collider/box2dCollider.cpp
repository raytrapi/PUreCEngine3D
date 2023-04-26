#include "box2dCollider.h"
#include "../renderable/line.h"
//namespace collider {
	
	Box2dCollider::Box2dCollider(Entity* entity, modules::graphics::Graphic* g, Component * p):Collider(entity,g,p) {
		borrarVertices();
		vertices = new float[12]{
			limites[0], limites[3], limites[5],
			limites[1], limites[3], limites[5],
			limites[1], limites[2], limites[5],
			limites[0], limites[2], limites[5]
		};
		verticesExpandidos = new float[12];
		for (int i = 0; i < 12; i++) {
			verticesExpandidos[i] = vertices[i];
		}/**/
		tipo = TYPE::BOX_2D;
		//if (graphic == NULL) {
		//	graphic = Module::get<modules::graphics::Graphic>();
		//}
		if (graphic != NULL) {
			showGizmo();
				
		}
	}
	void Box2dCollider::borrarVertices() {

		//for (int i = 0; i < 4; i++) {
			//delete vertices[i];
		//}
		if (vertices!=NULL) {
			delete[]vertices;
			vertices = NULL;
		}
		if (verticesExpandidos != NULL) {
			delete[]verticesExpandidos;
			verticesExpandidos = NULL;
		}/**/
	}

	void Box2dCollider::whenChargeEntity() {
		borrarVertices();
		vertices = new float[12]{
			0,0,0, //sup-izq (top-left)
			0,0,0, //sup-der (top-right)
			0,0,0, //inf-der (bottom-right)
			0,0,0  //inf-izq (bottom-left)
		};
		
		if (entidad) {
			renderable::Mesh* malla = entidad->getComponent<renderable::Mesh>();
			if (malla != NULL) {
				//Calculamos la caja
				int numeroVertices = malla->getVertexNumber();
				float* verticesObjeto = malla->getMesh();
				unsigned j = 0;
				for (int i = 0; i < numeroVertices; i++) {
					//Comprobamos si esta más a la izquierda que mis coordenadas
					if (verticesObjeto[j] < vertices[0]) {
						vertices[0] = verticesObjeto[j];
						vertices[9] = verticesObjeto[j];
					}
					if (verticesObjeto[j + 3] > vertices[3]) {
						vertices[3] = verticesObjeto[j];
						vertices[6] = verticesObjeto[j];
					}
					if (verticesObjeto[j + 1] > vertices[1]) {
						vertices[1] = verticesObjeto[j + 1];
						vertices[4] = verticesObjeto[j + 1];
					}
					if (verticesObjeto[j + 4] < vertices[7]) {
						vertices[7] = verticesObjeto[j + 4];
						vertices[10] = verticesObjeto[j + 4];
					}
					j += 3;
				}

			}
		}
		verticesExpandidos = new float[12];
		for (int i = 0; i < 12; i++){
			verticesExpandidos[i] = vertices[i];
		}/**/
		ancho = vertices[3] - vertices[0];
		alto = vertices[1] - vertices[7];
		ancho_2 = ancho / 2.f;
		alto_2 = alto / 2.f;

	}

	void Box2dCollider::recalcular() {
		Collider::recalcular();
		
		//float difX = cX - entidad->transform()->position()->x;
		//float difY = cY - entidad->transform()->position()->y;

		//DBG("recalculo Colider hijo Box2dCollider");
		//int j = 0;
		//for (int i = 0; i < 4; i++) {
		/*vertices[0] = cX - ancho_2;
		vertices[9] = vertices[0];
		vertices[1] = cY + alto_2;
		vertices[4] = vertices[1];
		vertices[3] = cX + ancho_2;
		vertices[6] = vertices[3];
		vertices[7] = cY - alto_2;
		vertices[10] = vertices[7];
		/**/
		//}
	}

	Box2dCollider::~Box2dCollider() {
		borrarVertices();
	}

	void Box2dCollider::setBox(float x, float y, float width, float height) {
		cX = x;
		cY = y;
		ancho = width;
		alto = height;
		ancho_2 = width / 2.f;
		alto_2 = height / 2.f;
		borrarVertices();
		vertices = new float[12]{
			x - ancho_2, y + alto_2, 0,
			x + ancho_2, y + alto_2, 0,
			x + ancho_2, y - alto_2, 0,
			x - ancho_2, y - alto_2, 0
		};
		verticesExpandidos = new float[12];
		for (int i = 0; i < 12; i++) {
			verticesExpandidos[i] = vertices[i];
		}/**/
		//Modificamos el gizmo y el gizmoExtendido //change the gizmo and the gizmoExtended
		renderable::Line* linea = (renderable::Line*)gizmo->getComponent<RenderableComponent>()->getRenderable();
		linea->setVertex(vertices, 4);
		linea = (renderable::Line*)gizmoExpandido->getComponent<RenderableComponent>()->getRenderable();
		linea->setVertex(verticesExpandidos, 4);
		changePhysics();
		//TODO: Mirar si esto lo podemos mejorar
		/*if (gizmo) {
			if (graphic->getGlobal()->showGizmoCollider) {
				renderable::Line* linea = (renderable::Line*)gizmo->getComponent<RenderableComponent>()->getRenderable();
				linea->setVertex(vertices, 4);
			}
			
		}else{
			if (graphic != NULL) {

				showGizmo();
				
			}
		}
		if (gizmoExpandido) {
			if (graphic->getGlobal()->showGizmoColliderExpand) {
				renderable::Line* linea = (renderable::Line*)gizmoExpandido->getComponent<RenderableComponent>()->getRenderable();
				linea->setVertex(verticesExpandidos, 4);

			}
		}/**/
	}

	void Box2dCollider::setBox(float width, float height) {
		borrarVertices();
		ancho = width;
		alto = height;
		ancho_2 = width / 2.f;
		alto_2 = height / 2.f;
		vertices = new float[12]{
			-ancho_2, +alto_2, 0,
			+ancho_2, +alto_2, 0,
			+ancho_2, -alto_2, 0,
			-ancho_2, -alto_2, 0
		};
		verticesExpandidos = new float[12];
		for (int i = 0; i < 12; i++) {
			verticesExpandidos[i] = vertices[i];
		}/**/
		changePhysics();
	}

	void Box2dCollider::setVertex(float* vec1, float* vec2, float* vec3, float* vec4) {
		borrarVertices();
		vertices = new float[12]{
			vec1[0], vec1[1], vec1[2],
			vec2[0],	vec2[1],	vec2[2],
			vec3[0],	vec3[1], vec3[2],
			vec4[0],	vec4[1], vec4[2]
		};
		verticesExpandidos = new float[12];
		for (int i = 0; i < 12; i++) {
			verticesExpandidos[i] = vertices[i];
		}/**/
		ancho = vertices[3] - vertices[0];
		alto = vertices[1] - vertices[7];
		ancho_2 = ancho / 2.f;
		alto_2 = alto / 2.f;
	}

	bool Box2dCollider::haveCollision(Collider* object) {
		float esquinas[12]{
			cX - ancho_2, cY + alto_2, 0.f,
			cX + ancho_2, cY + alto_2, 0.f,
			cX + ancho_2, cY - alto_2, 0.f,
			cX - ancho_2, cY - alto_2, 0.f
		};
		return haveCollision(object,(float*) &esquinas);
	}

	bool Box2dCollider::haveCollision(Collider* object, float* vertex) {
		if (object->getType() == TYPE::BOX_2D) {
			Box2dCollider* target = (Box2dCollider*)object;
			//DBG("V [%,%][%,%]", vertices[0], vertices[1], vertices[6], vertices[7]);
			//DBG("VT [%,%][%,%]", target->vertices[0], target->vertices[1], target->vertices[6], target->vertices[7]);
			
			if (
				target!=NULL && target->vertices!=NULL && 
				vertex[0] < target->vertices[6] &&
				vertex[3] > target->vertices[0] &&
				vertex[1] > target->vertices[7] &&
				vertex[7] < target->vertices[1]) {
				return true;
			}

		}
		return false;
	}

	
	std::vector<collider::Hit> Box2dCollider::getCollisions() {
		return getCollisions(cX, cY, cZ);
	}
	std::vector<collider::Hit> Box2dCollider::getCollisionsExpanding(float x, float y, float z) {
		cX = entidad->getTransform()->position()->x;
		cY = entidad->getTransform()->position()->y;
		cZ = entidad->getTransform()->position()->z;
		/*vertices[0] = ((cX < x) ? cX : x) - ancho_2;
		vertices[9] = vertices[0];
		vertices[3] = ((cX > x) ? cX : x) + ancho_2;
		vertices[6] = vertices[3];

		vertices[1] = ((cY > y) ? cY : y) + alto_2;
		vertices[4] = vertices[1];
		vertices[7] = ((cY < y) ? cY : y) - alto_2;
		vertices[10] = vertices[7];*/
		float xI = (x < cX ? x : cX);
		float xD = (x > cX ? x : cX);
		float yS = (y > cY ? y-cY : 0);
		float yI = (y < cY ? (cY-y) : 0);

		/*xI = 0;
		xD = 0;
		yS = 0;
		yI = 0;/**/
		if (vertices != NULL) {
			//verticesExpandidos[0] = xI + vertices[0];
			verticesExpandidos[1] = yS + vertices[1];
			//verticesExpandidos[3] = xD + vertices[3];
			verticesExpandidos[4] = yS + vertices[4];
			//verticesExpandidos[6] = xD + vertices[6];
			verticesExpandidos[7] = vertices[7]-yI;
			//verticesExpandidos[9] = xI + vertices[9];
			verticesExpandidos[10] = vertices[10]-yI;

			renderable::Line* linea = (renderable::Line*)gizmoExpandido->getComponent<RenderableComponent>()->getRenderable();
			linea->setVertex(verticesExpandidos, 4);
		}
		return obtenerObjetosColision();
	}
	std::vector<collider::Hit> Box2dCollider::getCollisions(float x, float y, float z) {
		/*float tX = cX;
		float tY = cY;
		float tZ = cZ;/**/

		verticesExpandidos[0] = x + vertices[0];
		verticesExpandidos[1] = y + vertices[1];
		verticesExpandidos[3] = x + vertices[3];
		verticesExpandidos[4] = y + vertices[4];
		verticesExpandidos[6] = x + vertices[6];
		verticesExpandidos[7] = y + vertices[7];
		verticesExpandidos[9] = x + vertices[9];
		verticesExpandidos[10] = y + vertices[10];
		return obtenerObjetosColision();
	}
	std::vector<collider::Hit> Box2dCollider::obtenerObjetosColision() {
		std::vector<collider::Hit> exitos;
		if (verticesExpandidos == NULL) {
			return exitos;
		}
		//cX = entidad->getTransform()->position()->x;
		//cY = entidad->getTransform()->position()->y;
		//cZ = entidad->getTransform()->position()->z;
		float xDif = (verticesExpandidos[3] - verticesExpandidos[0]) / 2.0f;
		float yDif = (verticesExpandidos[1] - verticesExpandidos[7])/2.0f;
		float verticesExpandidos2[12];
		verticesExpandidos2[0] = cX-xDif;
		verticesExpandidos2[1] = cY+yDif;
		verticesExpandidos2[2] = verticesExpandidos[2];
		
		verticesExpandidos2[3] = cX + xDif;
		verticesExpandidos2[4] = verticesExpandidos2[1];
		verticesExpandidos2[5] = verticesExpandidos[5];
		
		verticesExpandidos2[6] = verticesExpandidos2[0];
		verticesExpandidos2[7] = cY-yDif;
		verticesExpandidos2[8] = verticesExpandidos[8];
		
		verticesExpandidos2[9] = verticesExpandidos2[3];
		verticesExpandidos2[10] = verticesExpandidos2[7];
		verticesExpandidos2[11] = verticesExpandidos[110];
		
		
		//return exitos;
		/*if (graphic->getGlobal()->showGizmoColliderExpand) {
			if(gizmoExpandido==NULL){
				crearGizmoExpandido();
			}
			renderable::Line* lineas = gizmoExpandido->getComponent<renderable::Line>();
			if (lineas != NULL) {
				lineas->setVertex(verticesExpandidos, 4);

				gizmoExpandido->setUpdatingRender(true);

				////DBG("block 2");
			
			}
		}/**/
		for (auto it = Entity::entidades[Entity::defaultStack].begin(); it != Entity::entidades[Entity::defaultStack].end(); it++) {
			if ((*it)->isActive()) {
				std::vector<Collider*>* colisiones = (*it)->getComponents<Collider>();
				if (colisiones != NULL) {
					for (auto itC = colisiones->begin(); itC != colisiones->end(); itC++) {
						if ((*itC != this) && haveCollision((*itC), verticesExpandidos2)) {
							//TODO: Aquí suponemos que es un boxCollider
							collider::Hit exito = obtenerObjetoColisionCaja(this, (Box2dCollider*)(*itC), verticesExpandidos2);
							exitos.push_back(exito);
						}
						//DBG("block 5");
					}
				}
			}

		}/**/
		/*if (x != tX || y != tY || z != tZ) {
			cX = tX;
			cY = tY;
			cZ = tZ;
			recalcular();
		}/**/
		return exitos;
	}
	collider::Hit Box2dCollider::obtenerObjetoColisionCaja(Box2dCollider* principal, Box2dCollider* secundario, float* vertexMain) {
		collider::Hit exito;
		exito.object = secundario;
		exito.distance = std::numeric_limits<float>::infinity();
		unsigned j = 0; //Cuenta el vertice i
		unsigned k = 3; //Cuenta el siguiente vertice
		float distanciaX = principal->cX - secundario->cX;
		float distanciaY = principal->cY - secundario->cY;
		
		for (unsigned i = 0; i < 4 && exito.collision; i++) {
			auto [ejeX,ejeY]= getNormal2D(vertexMain[j], vertexMain[j+1],
				vertexMain[k], vertexMain[k+1]);
			j += 3;
			k += 3;
			if (k > 9) {
				k = 0;
			}
			auto [minA, maxA] = getMinMax2D(ejeX, ejeY, vertexMain, 4);
			auto [minB, maxB] = getMinMax2D(ejeX, ejeY, secundario->vertices, 4);
			float desplazamiento= dotProduct2D(ejeX, ejeY ,distanciaX,distanciaY);
			minA+=desplazamiento;
			maxA+=desplazamiento;/**/
			if ((minA < maxB) && (maxA < minB)) {
				exito.collision=false; //están separados.
				return exito;
			} 
			float distanciaMasCorta= std::numeric_limits<float>::infinity();
			if (maxA > minB) {
				distanciaMasCorta = maxA - minB;
			} else if (minA > maxB) {
				
				distanciaMasCorta = minA - maxB;
			} 
			std::tie(exito.isContained,exito.isContainer) = checkRangesForContainment(minA,maxA,minB,maxB);
			//float distanciaMin = -(maxBpoligonoBRango[1] - poligonoARango[0]);

			//let distanciaMinAbs=Math.abs(distanciaMin);
			if (distanciaMasCorta < exito.distance) {

				exito.distance = distanciaMasCorta;
				exito.vX = ejeX;
				exito.vY = ejeY;
				exito.vZ = 0.f;
			}
			
		}
		float distanciaYVertices = principal->vertices[1] - vertexMain[1] + principal->vertices[7] - vertexMain[7];
		//TODO: Corregir calculo de centro expandido cuando la caja esté rotada
		exito.sX = (exito.vX * exito.distance);
		exito.sY = (exito.vY * exito.distance)+distanciaYVertices;
	
		return exito;
	}
	void Box2dCollider::crearGizmo()	{
		graphic->setStackTemp(1);
		gizmo = graphic->drawLineLoop(vertices, 4, 0.f, 0.8f, 0.f, 0.8f, 1);
		//gizmo->setOnTop(true);
		gizmo->setParent(entidad);
		gizmo->setGraphic(graphic);
		gizmo->setActive(graphic->getGlobal()->showGizmoCollider);
	}
	void Box2dCollider::crearGizmoExpandido(){
		graphic->setStackTemp(1);
		gizmoExpandido = graphic->drawLineLoop(verticesExpandidos, 4, 1.f, 0.0f, 1.f, 0.8f, 1);
		//gizmo->setOnTop(true);
		gizmoExpandido->setParent(entidad);
		gizmoExpandido->setGraphic(graphic);
		gizmoExpandido->setActive(graphic->getGlobal()->showGizmoColliderExpand);
	}
	void Box2dCollider::showGizmo() {
		//if (show) {
			RenderableComponent* rend = entidad->getComponent<RenderableComponent>();
			renderable::Object* padre = rend->getRenderable();
			if (gizmo == NULL) {
				//DBG("Creamos el GIZMO");
				if (graphic) {
					crearGizmo();
					//gizmo->setParent()
				}
			}
			if (gizmoExpandido == NULL) {
				crearGizmoExpandido();
			}
		/* } else {
			if (gizmo != NULL) {
				DBG("Borramos el GIZMO");
				gizmo->removeParent();
				graphic->removeEntity(gizmo);
				gizmo = NULL;
				gizmoExpandido->removeParent();
				graphic->removeEntity(gizmoExpandido);
				gizmoExpandido = NULL;
			}
		}/**/
	}


	/**
	* Función para refrescar los collider //Funtion to refresh the collider
	*
	*/
	void Box2dCollider::refresh()	{
		//Cogeremos la lineas y las activaremos o desactivaremos en función de la variable global

		if (gizmo == NULL) {
			crearGizmo();
		}
		//Obtener una referencia al renderable de la entidad //Get a reference to the renderable of the entity
		RenderableComponent* rend = gizmo->getComponent<RenderableComponent>();
		bool show = graphic->getGlobal()->showGizmoCollider;
		gizmo->setUpdatingRender(true);
		gizmo->setActive(show);
		rend->setActive(show);
		if (gizmoExpandido == NULL) {
			//Creamos el gizmo Expandido
			crearGizmoExpandido();
		}
		//Obtener una referencia al renderable de la entidad //Get a reference to the renderable of the entity
		rend = gizmoExpandido->getComponent<RenderableComponent>();
		gizmoExpandido->setActive(graphic->getGlobal()->showGizmoColliderExpand);
		rend->setActive(graphic->getGlobal()->showGizmoColliderExpand);
		gizmoExpandido->setUpdatingRender(true);
		
	}

//}
