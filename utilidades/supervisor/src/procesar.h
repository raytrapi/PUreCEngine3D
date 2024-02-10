#pragma once 
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include "reflexivo.h"
using namespace std;
namespace fs = filesystem;



class Procesar{
        static std::string reemplazar(const char, const char,std::string);
        static std::tuple<bool, std::string, std::string, bool> procesarCabecera(string origen, string destino);
        static string trim(string);
        template <class T>
        static bool enVector(vector<T>, T);
        static vector<string> strip(string, vector<char>, vector<char> eliminar={' ', '\t'});
    public:
        static void procesarCarpeta(const char *ficheroSalida, const char * ruta);
        PUBLIC()
        int parametro;
};
template <class T>
inline bool Procesar::enVector(vector<T> elementos, T elemento){
    for(auto el:elementos){
        if(el==elemento){
            return true;
        }
    }
    return false;
}