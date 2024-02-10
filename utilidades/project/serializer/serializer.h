#pragma once
#include <vector>
#include <iostream>
#include "../../utiles/utilidades.h"
class EXPORTAR_UTILIDADES Serializer{
    static void serialize_inter2(int longitud, std::vector<unsigned char> *bytes, unsigned char const *p);
    template<typename T>
    static int serialize_inter(T v,std::vector<unsigned char> *bytes);
    /*static int serialize_inter(float v, std::vector<unsigned char>* bytes);
    static int serialize_inter(double v,std::vector<unsigned char> *bytes);
    static int serialize_inter(char v,std::vector<unsigned char> *bytes);/**/
    //static int serialize_inter(void* v, std::vector<unsigned char>* bytes);
    static int serialize_inter(char * v,std::vector<unsigned char> *bytes);
    static int serialize_inter(const char * v,std::vector<unsigned char> *bytes);
    static int serialize_inter(std::vector<unsigned char>* v, std::vector<unsigned char>* bytes);
    //template<typename T>
    //static int serialize_inter(std::tuple<T,T,T> v, std::vector<unsigned char>* bytes);
    public:
    template<typename T>
    static int serialize(std::vector<unsigned char> *bytes, T t);
    template<typename T, typename... Args>
    static int serialize(std::vector<unsigned char> *bytes, T t, Args... args);
    template<unsigned int L,typename T>
    static int serialize(std::vector<unsigned char> *bytes, T* t);
    
};

template<typename T>
inline int Serializer::serialize(std::vector<unsigned char> *bytes,T t){
    int cuenta=serialize_inter(t, bytes);
    return cuenta;
}
template<typename T, typename... Args>
inline int Serializer::serialize(std::vector<unsigned char> *bytes,T t, Args... args){
    int cuenta=serialize_inter(t, bytes);
    cuenta+=serialize(bytes, args...);
    return cuenta;
}
template<unsigned int L, typename T>
int Serializer::serialize(std::vector<unsigned char> *bytes, T* t){
    int cuenta=0;
    for(int i=0;i<L;i++){
        cuenta+=serialize(bytes,t[i]);
    }
    return cuenta;
};
template<typename T>
inline int Serializer::serialize_inter(T v, std::vector<unsigned char>* bytes) {
   auto longitud = sizeof(v);
   unsigned char const* p = reinterpret_cast<unsigned char const*>(&v);
   serialize_inter2(longitud, bytes, p);
   return longitud;
}