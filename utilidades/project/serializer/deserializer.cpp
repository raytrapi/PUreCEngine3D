#include "deserializer.h"

void Deserializer::deserialize_inter(unsigned char * p, int length){
   int posF = (((int)bytes->size()) - pos - length);
    if(bytes && posF >=0 && posF<bytes->size()){
        for(int i=0;i<length;i++){
            p[i]=bytes->operator[](i+pos);
        }
        //pos+=length;
    }
    pos += length;
}
void Deserializer::setBytes(std::vector<unsigned char>* bytes){
    pos=0;
    Deserializer::bytes=bytes;
}
int Deserializer::getPos() { return pos; }
void Deserializer::setPos(int pos) { Deserializer::pos = pos; }
void Deserializer::stackBytes(std::vector<unsigned char>* bytes) {
   bytesStack.push_back({ Deserializer::bytes, pos });
   setBytes(bytes);
};
void Deserializer::unstackBytes() {
   if (bytesStack.size() > 0) {
      std::tie(bytes, pos) = bytesStack[bytesStack.size() - 1];
      bytesStack.pop_back();
   }/**/
};
void Deserializer::extract(std::vector<unsigned char>*dataT, int length, bool freeze) {
   int i = 0;
   int j = pos;
   while (i < length && j < bytes->size()) {
      dataT->push_back(bytes->operator[](j));
      j++;
      i++;
   }
   if (!freeze) {
      pos += length;
   }
}
/*void Deserializer::deserialize(int * v){
    auto longitud=sizeof(*v);
    deserialize_inter((unsigned char*)v,longitud);
}
void Deserializer::deserialize(float * v){
    auto longitud=sizeof(*v);
    deserialize_inter((unsigned char*)v,longitud);
}
void Deserializer::deserialize(double * v){
    auto longitud=sizeof(*v);
    deserialize_inter((unsigned char*)v,longitud);
}
void Deserializer::deserialize(char * v){
    *v=bytes->operator[](pos++);
}/**/
void Deserializer::deserialize(char* * v){
    //En principio deberíamos tener la cadena con el hueco necesario
    auto longitud=getLengthString();
    if (*v == 0 && longitud>0) {
       *v = new char[longitud];
    }
    deserialize_inter((unsigned char*)(*v),longitud);
    
}
int Deserializer::getLengthString(){
    if(bytes){
        int resultado=0;
        int posActual=pos;
        while(bytes->size()>posActual && bytes->operator[](posActual)!='\0'){
            posActual++;
            resultado++;
        }
        if (resultado + 1 + pos > bytes->size()) {
           return 0;
        }
        return resultado+1;
    }
    return 0;
}
bool Deserializer::end() { return (bytes == 0 || pos >= bytes->size()); }
std::vector<unsigned char>* Deserializer::bytes=0;
std::vector< std::tuple<std::vector<unsigned char>*, int>> Deserializer::bytesStack;
int Deserializer::pos=0;