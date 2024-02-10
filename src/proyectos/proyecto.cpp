#include "proyecto.h"

std::vector<std::string> Proyecto::split(std::string cadena,char caracter) {
   std::vector<std::string> respuesta;

   int pos = cadena.find(caracter);
   if (pos == std::string::npos) {
      respuesta.push_back(cadena);
   } else {
      respuesta.push_back(cadena.substr(0, pos));
      respuesta.push_back(cadena.substr(pos+1));
   }
   return respuesta;
}

std::string Proyecto::trim(std::string cadena) {
   //TODO: Pendiente de hacer
   return cadena;
}

const char* Proyecto::generarProyecto(const char* proyecto, const char* ruta){
   if (FileControl::existsFolder(ruta)) {
      std::string carpeta = (std::string(ruta) + "/" + std::string(proyecto));
      if (!FileControl::createFolder(carpeta.c_str())) {
         //TODO: Controlar si la carpeta ya existe, en ese caso mostrar un mensaje más adecuado
         return "No se ha podido crear la carpeta";
      } else {
         //Empezamos la creación de estructura
         if (!FileControl::createFolder((carpeta + "/build").c_str())) {
            return "No se ha podido crear la carpeta de compilación";
         }
         if (!FileControl::createFolder((carpeta + "/src").c_str())) {
            return  "No se ha podido crear la carpeta de código";
         }

         //Cargamos el fichero de configuración
         parametros[std::string("NAME")] = std::string(proyecto);
         parametros[std::string("PATH")] = carpeta;
         parametros[std::string("PATHSRC")] = carpeta+"/src";
         parametros[std::string("PATHBUILD")] = std::string(carpeta + "/build/");
         //TODO: Lo de abajo hat que corregirlo para que tenga la carpeta de release
         std::string rutaBIN = (std::filesystem::current_path() / "../../../..").string();
         for (int i = 0; i < rutaBIN.size(); i++) {
            if (rutaBIN[i] == '\\') {
               rutaBIN[i] = '/';
            }
         }
         parametros[std::string("PATHMOTOR")] = rutaBIN;
         parametros[std::string("PATHMOTORLIB")] = std::string("/out/build/x64-Debug/lib/");
         parametros[std::string("PATHMOTORDLL")] = std::string("/out/build/x64-Debug/bin/modulos/");

         escribir(carpeta, "conf", "defproj");
         escribir(carpeta, "CMakeLists.txt","compiler");
         //Compilamos
         Compile::generateProject(carpeta.c_str(), Compile::NINJA);

      }
   } else {
      return "La carpeta no es correcta";
   }

   return NULL;
}
const char* Proyecto::escribir(std::string carpeta, const char* destino, const char* origen) {
   std::ifstream ficheroEntrada;
   std::ofstream ficheroSalida;
   ficheroEntrada.open(origen, std::ios::in);
   ficheroSalida.open((carpeta+"/"+destino).c_str(), std::ios::out);
   char caracter;
   char ultimoCaracter = '/0';
   std::string termino = "";
   bool conTermino = false;
   while (ficheroEntrada.get(caracter)) {
      //TODO: Añadir lógica para sustituir los %___% por el valor del mapa(diccionario)
      if (caracter == '%' && ultimoCaracter=='%') {
         caracter = '\0';
         if (!conTermino) {
            conTermino = true;
         } else {
            if (parametros.contains(termino)) {
               //Tenemos el termino así que lo escribimos
               ficheroSalida << parametros[termino];
            } else {
               ficheroSalida << "%%" << termino << "%%";
            }
            ultimoCaracter = '\0';
            conTermino = false;
            termino = "";
         }
      } else {
         if (caracter != '%'){
            if (ultimoCaracter == '%') {
               ficheroSalida << '%';
            }
            if (conTermino) {
               termino += caracter;
            } else {
               ficheroSalida << caracter;
            }
         }

      }
      ultimoCaracter = caracter;
   }

   ficheroEntrada.close();
   ficheroSalida.close();
   return NULL;
}
bool Proyecto::cargarProyecto(const char* ruta) {
   conf.clear();
   std::string ficheroConfiguracion = std::string(ruta) + "/conf";
   if (!std::filesystem::exists(ficheroConfiguracion)) {
      return false;
   }
   std::ifstream configuracion;
   configuracion.open(ficheroConfiguracion.c_str());
   if (!configuracion.is_open()) {
      return false;
   }
   std::string linea;
   while (std::getline(configuracion, linea)) {
      linea = trim(linea);
      std::vector<std::string> partes = split(linea, '=');
      if (partes.size() > 1) {
         conf[partes[0]] = partes[1];
      }
   }

   configuracion.close();
   
   return true;
}
const char* Proyecto::cogerRutaCodigoProyecto() {
   return conf.contains("pathSRC")?conf["pathSRC"].c_str():"";
}
const char* Proyecto::cogerNombreProyecto() {
   return conf.contains("name") ? conf["name"].c_str() : "";
}
bool Proyecto::estaCargado() {
   return !conf.empty();
}
void Proyecto::guardarEstado(Global* global){
   auto estadoActual = global->getDataState();
   estadoActual->clear();
   auto entidadesStack = Entity::getAllEntities();
   for (auto stack : *entidadesStack) {
      int i = 0;
      for (auto entidad : stack.second) {
         entidad->saveState(estadoActual, true, i++);
      }
   }
   {//Se puede borrar
      char* resultado = new char[estadoActual->size() + 1];
      for (int i = 0; i < estadoActual->size(); i++) {
         char c = estadoActual->operator[](i);
         resultado[i] = (c != '\0' ? c : '$');
      }
      resultado[estadoActual->size()] = '\0';
      DBG(resultado);
      delete[] resultado;
   }
}
void Proyecto::restaurarEstado(Global* global){
   auto estadoActual = global->getDataState();
   auto entidadesPila = Entity::getAllEntities();
   Deserializer::setBytes(estadoActual);
   while (!Deserializer::end()) {
      void* entidadSalvada = 0;
      int pos = -1;
      //int longitudEntidad = 0;
      //Deserializer::deserialize(&longitudEntidad);
      //std::vector<unsigned char> datosE;
      //Deserializer::extract(&datosE, longitudEntidad);
      //Deserializer::stackBytes(&datosE);
      {
         Deserializer::deserialize(&entidadSalvada);
         Deserializer::deserialize(&pos);
         bool existeEntidad = false;
         for (auto entidadPila : *entidadesPila) {
            for (auto entidad : entidadPila.second) {
               if (entidad == entidadSalvada) {
                  existeEntidad = true;
                  break;
               }
            }
            if (existeEntidad) {
               break;
            }
         }
         if (!existeEntidad) {
            entidadSalvada = new Entity(0, pos);
         }
         ((Entity*)entidadSalvada)->restoreState(NULL, true);
      }
      //Deserializer::unstackBytes();
   }
}
const char* Proyecto::cogerRutaCompilacionProyecto() {
   return conf.contains("pathBuild") ? conf["pathBuild"].c_str() : "";
}
std::map<std::string, std::string> Proyecto::parametros;

std::map<std::string, std::string> Proyecto::conf;