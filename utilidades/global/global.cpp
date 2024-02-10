#include "global.h"
#include "../../components/src/entity.h"

//EXPORTAR_UTILIDADES StateCompile Global::compileState = StateCompile::NOTHING;
int Global::loadProject(const char* path, bool create) {
   auto p = ProjectFile::load(path, create);
   if (p.has_value()) {
      this->proyecto = (*p);
      //this->executing = StateExecuting::RELOAD_PROJECT;
      this->executing = StateExecuting::STOP;
      auto root = std::filesystem::path(path).parent_path();
      this->rootProject = root.string();
      loadConfig();
      char* ruta = strdup((root / "content").string().c_str());
      cargarCarpetas(ruta);
      delete[] ruta;
      return 0;
   }
    
   return p.error();
   
}/**/ 
treeDirectory* Global::getDirectory(bool refresh) {
   if (refresh) {
      cargarCarpetas((rootProject+"/content").c_str());
   }
   return directorioCarpetas;
} 
//Global::Global(Entity * entitie) {
Global::Global() {
   if (instancia == 0) {
      instancia = this;
   }
   //entidad = entitie;
};
Global::~Global() {
   if (directorioCarpetas) {
      delete directorioCarpetas;
   }

}
/*Entity* Global::createEntity() {
   if (entidad) {
      return entidad->create();
   }
   return 0;
}/**/
int Global::cargarCarpetas(const char* ruta, treeDirectory*padre, int id, std::string rutaPadre) {
   if (!padre) {
      if (directorioCarpetas) {
         delete directorioCarpetas;
      }
      directorioCarpetas = new treeDirectory();
      padre = directorioCarpetas;
      id = 0;
   }


   std::filesystem::path carpetaPadre(ruta);
   padre->value.name = carpetaPadre.stem().string();
   padre->value.path = rutaPadre;
   padre->value.id = id;
   //padre->value.type = FILE_FOLDER;
   for (auto& fichero : std::filesystem::directory_iterator(carpetaPadre)) {
      if (fichero.is_directory()) {
         id++;
         
         padre->childrens.push_back(treeDirectory());
         id=cargarCarpetas(fichero.path().string().c_str(), &padre->childrens[padre->childrens.size() - 1], id, rutaPadre +"/"+ padre->value.name);
      }
   }
   return id;
}
std::string Global::getPathRoot() {
   return rootProject;
}
void Global::setPathRoot(const char* path) {
    rootProject = std::string(path);
}

std::expected<LevelFile, Error> Global::newLevel(std::string path) {
   auto level =LevelFile::create(path.c_str());
   if (level.has_value()) {
      //actualLevel = level;
   }
   return level;
}
void Global::loadLevel(const char* filePath) {

   

   auto [l,version] = LevelFile::load(filePath);
   versionNivel = version;
   if (l) {
      if (actualLevel) {
         delete actualLevel;
      }
      actualLevel = l;
      saveConfig();
      //if (version == 0) {
         if (funcionLoadLevel) {
            funcionLoadLevel(version);
         }
      //}
   }/**/
}
void Global::onLoadLevel(std::function<void(unsigned int)> f) {
   funcionLoadLevel = f; 
}
LevelFile* Global::getLevelFile() { 
   return actualLevel; 
}

const char* Global::getExt() {
   return ext;
};
void Global::loadConfig() {
   //Guardamos la configuración actual
   if (std::filesystem::exists((rootProject + "/project.cfg").c_str())) {
      std::ifstream fs((rootProject + "/project.cfg").c_str(), std::ios::binary);
      if (fs.peek() != std::ifstream::traits_type::eof()) {
         unsigned int longitud = 0;
         fs.read((char*)&longitud, sizeof(unsigned int));
         char* datos = new char[longitud];
         fs.read(datos, longitud);
         if (strcmp(datos, UID_CONFIG) != 0) {
            fs.close();
            return;
         }
         delete[] datos;
         fs.read((char*)&longitud, sizeof(unsigned int));
         datos = new char[longitud];
         fs.read(datos, longitud);
         unsigned int version = 0;
         std::tie(actualLevel,version) = LevelFile::load(datos);
         if (instancia) {
            if (instancia->funcionLoadLevel) {
               instancia->funcionLoadLevel(version);
            }
         }
         delete[] datos;
         fs.close();
      }
   }

}
void Global::saveConfig() {
   //Guardamos la configuración actual
   std::ofstream fs((rootProject+"/project.cfg").c_str(), std::ios::binary);
   unsigned int longitud = strlen(UID_CONFIG) + 1;
   fs.write((char*)&longitud, sizeof(unsigned int));
   fs.write(UID_CONFIG, longitud);
   if (actualLevel) {
      std::string rutaNivel = std::string(actualLevel->getRoot()) + "/" + actualLevel->getName();
      longitud = rutaNivel.size() + 1;
      fs.write((char*)&longitud, sizeof(unsigned int));
      fs.write(rutaNivel.c_str(), longitud);
   }
   fs.close();
}
Global* Global::getInstance() {
   return instancia;
}

/*void Global::saveState() {
   estadoActual.clear();
   auto entidadesStack = Entity::getAllEntities();
   for (auto stack : *entidadesStack) {
      for (auto entidad : stack.second) {
         entidad->saveState(&estadoActual);
      }
   }
   std::string resultado="";
   for (auto c : estadoActual) {
      resultado += c;
   }
   DBG(resultado);
   //estadoActual.
}/**/



treeDirectory* Global::directorioCarpetas = 0;
std::string Global::rootProject = "";
LevelFile* Global::actualLevel = 0;//std::unexpected(Error(0,"Sin definir"));
const char* Global::ext=".pc3d";
Global* Global::instancia = 0;
