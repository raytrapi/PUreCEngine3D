#pragma once
#include <string>
#include <vector>

#include <iostream>

#define PUBLIC();
enum TIPO_PARAMETRO{
    PROP,
    FUNC
};


struct Parametro{
        TIPO_PARAMETRO tipo;
        int magnitud;
        std::string nombre;
        std::vector<Parametro> parametros;
        void* variable;
        Parametro(TIPO_PARAMETRO t, void* v, std::vector<std::string> partes);
        Parametro(TIPO_PARAMETRO t, void* v, std::string nombre,int m);
        std::string serializar();
        template <class T>
        static int buscarVector(std::vector<T>, T);
        template <class T>
        static int buscarVector(std::vector<T>, std::vector <T>);
    private:
        static std::vector<std::string> magnitudes;
        static std::string join(std::vector<std::string>, std::string, int, int);
};
template <class T>
inline int Parametro::buscarVector(std::vector<T>datos, T dato){
    int i=0;
    for(auto d:datos){
        if(d==dato){
            return i;
        }
        i++;
    }
    return -1;
};
template <class T>
inline int Parametro::buscarVector(std::vector<T>datosA, std::vector <T> datosB) {
   for (auto dato : datosB) {
      int pos = buscarVector(datosA, dato);
      if (pos != -1) {
         return pos;
      }
   }
   return -1;
};