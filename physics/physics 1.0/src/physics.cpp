#include "physics.h"
#include "../../utilidades/timer/timer.h"
#include <math.h>
#include "../../components/modulos/collider/collider.h"
#include <physics/rigidBodyComponent.h>

void Physics10::update(){
	//Obtenemos todos los componentes RigidBody //Get all RigidBody components
	std::vector<physics::RigidBodyComponent*> cuerpos = entidades->getAllComponents<physics::RigidBodyComponent>();
	//int estaticos = 0;
	//int dinamicos = 0;
	for (auto cuerpo : cuerpos) {
		if (cuerpo->hasGravity()){
			//dinamicos++;
			//Obtenemos la entidad
			Entity* entidad=cuerpo->getEntity();
			//Obtenemos la posicion de la entidad
			Transform * transform=entidad->transform();
			//DBG("X: %, Y: %, Z: %",transform->position()->x, transform->position()->y, transform->position()->z);
			//Obtenemos la velocidad del cuerpo //Get the body speed
			
			auto [velocidadX, velocidadY, velocidadZ] = cuerpo->getVelocity();

			//Calculamos la normal //Calculated	the normal
			auto [normalX, normalY, normalZ] = getNormal(velocidadX, velocidadY, velocidadZ);
			//Invertimos la dirección // Invert the direction
			normalX = -normalX;
			normalY = -normalY;
			normalZ = -normalZ;

			//Obtenemos la magnitud del vector velocidad //Get the magnitude of the velocity vector
			float magnitud = getMagnitude(velocidadX,velocidadY,velocidadZ);
			//Calculamos la Frizción //Calculate the friction
			float friccionMagnitud = magnitud * magnitud * densidad;
			float friccionX = friccionMagnitud *normalX;
			float friccionY = friccionMagnitud * normalY;
			float friccionZ = friccionMagnitud * normalZ;
			//Calculamos la aceleración //Calculate the acceleration
			
			velocidadX += friccionX;
			velocidadY += friccionY;
			velocidadZ += friccionZ;/**/
			


			//global->deltaTime = Time::deltaTime();
			velocidadY += gravedad * Time::deltaTime();
			/*if (std::abs(velocidadY) > 5) {
				velocidadY = 5.0f;
			}/**/

			cuerpo->setVelocity(velocidadX, velocidadY, velocidadZ);
			auto [x, y, z] = transform->getPosition();
			x+=velocidadX * Time::deltaTime();
			y+=velocidadY * Time::deltaTime();
			z+=velocidadZ * Time::deltaTime();
			//Obtenemos el componente colisión //Get the collider component
			Collider* colision = entidad->getComponent<Collider>();
			if (colision != NULL) {
				//Comprobamos si golpeamos con algún objeto //Check if we hit something
				std::vector<collider::Hit> colisiones = colision->getCollisionsExpanding(x, y, z);
				if (colisiones.size() > 0) {
					velocidadY = 0;
					cuerpo->setVelocity(velocidadX, 0, velocidadZ);
					for (auto exito : colisiones) {
						y = std::get<1>(transform->getPosition()) - exito.sY;
					}
				}


				/*if (colision->hit(transform->position()->x, transform->position()->y, transform->position()->z)) {
					//Si golpeamos con algún objeto, obtenemos la posición del objeto //If we hit something, get the position of the object
					auto [x, y, z] = colision->getHitPosition();
					//DBG("X: %, Y: %, Z: %", x, y, z);
					//Calculamos la distancia entre la posición del cuerpo y la posición del objeto //Calculate the distance between the body position and the object position
					float distancia = sqrt(pow(x - transform->position()->x, 2) + pow(y - transform->position()->y, 2) + pow(z - transform->position()->z, 2));
					//DBG("Distancia: %", distancia);
					//Calculamos la velocidad del cuerpo //Calculate the body speed
					float velocidad = sqrt(pow(velocidadX, 2) + pow(velocidadY, 2) + pow(velocidadZ, 2));
					//DBG("Velocidad: %", velocidad);
					//Calculamos la velocidad del objeto //Calculate the object speed
					float velocidadObjeto = sqrt(pow(colision->getVelocityX(), 2) + pow(colision->getVelocityY(), 2) + pow(colision->getVelocityZ(), 2));
					//DBG("Velocidad objeto: %", velocidadObjeto);
					//Calculamos la velocidad de la colisión //Calculate the collision speed
					float velocidadColision = sqrt(pow(velocidadObjeto - velocidad,/**/
			}

			transform->setPosition(x, y, z);

			//Aplicamos resistencias
			if (std::abs(velocidadY) < std::abs(gravedad)) {
				velocidadY = gravedad;
			}
		} else {
			//estaticos++;
			
		}
	}
	//DBG("Actualizo físicas con % cuerpos [% estaticos, % dinamicos]",cuerpos.size(),estaticos,dinamicos);
}


REGISTRAR_MODULO(Physics10);