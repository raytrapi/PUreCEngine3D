#pragma once
#include "../imgui_impl_opengl3.h"
#include "../imgui_impl_glfw.h"
#include "../imgui_controles.h"
#include <vector>
#include <tuple>
#include <string>
#include <global.h>
#include <wchar.h>
#include <genericFile.h>
#include "../../utilidades/files/filesControl.h"

//extern struct DragFile;
namespace UI {
	namespace Components {

		
		struct File {
			std::string name;
			std::string path;
			TYPE_FILE type;
			unsigned int idImagen;
		};

		class FileNavigator {
			enum Acciones {
				NONE,
				DEL,
				NEW_FOLDER,
				NEW_LEVEL,
				NEW_MATERIAL
			};
			static const float anchoFichero;
			static int idDirectorio;
			static std::expected<treeDirectory, int> directorioActual;
			static treeDirectory* directorios;
			static std::vector<File> files;
			static bool recargar;
			static void nodoDirectorio(treeDirectory nodo);
			static void nodoFicheros();
			static void newFolderModal();
		
			static int marcado;
			static ImVec2 posicionI;
			static ImVec2 posicionF;
			static DragFile ficheroMovido;

			static void createFolder(char* path);
			static void createMaterial(char* path);
			static void createLevel(char* path);
			static std::expected<treeDirectory, int>getDirectory(treeDirectory node);
		public:
			static void view();
		};
	}
}

