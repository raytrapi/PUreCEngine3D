#pragma once
#include <vector>
#include <iostream>
#include "../../utiles/utilidades.h"
class EXPORTAR_UTILIDADES Deserializer{
    static std::vector<unsigned char>* bytes;
    static int pos;
    static std::vector< std::tuple<std::vector<unsigned char>*, int>> bytesStack;
    static void deserialize_inter(unsigned char * p, int length);
    public:
    static void setBytes(std::vector<unsigned char>* bytes);
    static void stackBytes(std::vector<unsigned char>* bytes);
    static void unstackBytes();
    static int getPos();
    static void setPos(int pos);
    //static void deserialize(int * v);
    //static void deserialize(float * v);
    //static void deserialize(double * v);
    //static void deserialize(char * v);
    static void deserialize(char* * v);
    template<typename T>
    static void deserialize(T* v);
    template<typename T, typename... Args>
    static void deserialize(T* v, Args... args);
    template<unsigned int L, typename T>
    static void deserialize(T**v);
    static int getLengthString();
    static bool end();
    static void extract(std::vector<unsigned char>*, int length,bool freeze = false);
};

template<unsigned int L, typename T>
inline void Deserializer::deserialize(T**v){
    //std::cout<<L<<std::endl;
    T* lista=*v;
    for(int i=0;i<L;i++){
        //std::cout<<i;
        //std::cout<<":  "<<lista[i];
        deserialize(lista+i);
        //std::cout<<" --  "<<lista[i];
        //std::cout<<std::endl;
    } 
}

template<typename T, typename... Args>
inline void Deserializer::deserialize(T* v, Args... args) {
   auto longitud = sizeof(*v);
   deserialize_inter((unsigned char*)v, longitud);
   deserialize(args...);
}


template<typename T>
inline void Deserializer::deserialize(T* v){
    auto longitud=sizeof(*v);
    deserialize_inter((unsigned char*)v,longitud);
}