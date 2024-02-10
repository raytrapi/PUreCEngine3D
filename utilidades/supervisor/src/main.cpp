#include <iostream>
#include "procesar.h"
using namespace std;

int main(int n, char** ps){
    bool vervose=true;
    if(vervose){
        cout<<"Revisando cabeceras"<<endl;
    }
    if(n>2){
        //Cogemos el directorio
        Procesar::procesarCarpeta(ps[1], ps[2]);
    }else{
        cout<<"Sin datos "<<n<<endl;
    }

    return 0;
}