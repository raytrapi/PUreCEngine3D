#include "serializer.h"

void Serializer::serialize_inter2(int longitud, std::vector<unsigned char> *bytes, unsigned char const *p){
    //std::cout<<bytes->size()<<std::endl;
    for(int i=0;i<longitud; i++){
        bytes->push_back(p[i]);
    }
    //std::cout<<bytes->size()<<std::endl;
    //std::cout<<"..."<<longitud<<std::endl;
}

/*int Serializer::serialize_inter(float v, std::vector<unsigned char> *bytes){
    auto longitud=sizeof(v);
    unsigned char const * p=reinterpret_cast<unsigned char const *>(&v);
    serialize_inter2(longitud,bytes,p);
    return longitud;
};

int Serializer::serialize_inter(double v,std::vector<unsigned char> *bytes){
    auto longitud=sizeof(v);
    unsigned char const * p=reinterpret_cast<unsigned char const *>(&v);
    serialize_inter2(longitud,bytes,p);
    return longitud;
}
int Serializer::serialize_inter(char v,std::vector<unsigned char> *bytes){
    auto longitud=sizeof(v);
    bytes->push_back(v);
    return longitud;
}/**/
int Serializer::serialize_inter(char * v,std::vector<unsigned char> *bytes){
    return serialize_inter((const char*)v,bytes);
}
int Serializer::serialize_inter(const char * v,std::vector<unsigned char> *bytes){
    auto longitud=strlen(v);
    serialize_inter2(longitud,bytes,(unsigned char *)v);
    bytes->push_back('\0');
    return longitud+1;
}
int Serializer::serialize_inter(std::vector<unsigned char>* v, std::vector<unsigned char>* bytes) {
   int longitud=serialize_inter((int)(v->size()), bytes)+ v->size();
   for (int i = 0; i < v->size(); i++) { 
      bytes->push_back(v->operator[](i));
   }
   return longitud;
}