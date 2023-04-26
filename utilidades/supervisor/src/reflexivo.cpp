#include "reflexivo.h"
Parametro::Parametro(TIPO_PARAMETRO t, void*v, std::vector<std::string> partes){
    tipo=t;
    variable = v; 
    //Averigamos el típo
    if(t==TIPO_PARAMETRO::PROP){
        //Debemos buscar el primer ; o el primer =
        int i=0;
        while (i<partes.size() && partes[i]!=";" && partes[i]!="="){
            i++;
        }
        nombre=partes[i-1];
        std::string mag=join(partes,std::string(""),0,i-2);
        std::cout << "("<<i<<")" << "MAG: " << mag << std::endl;
        magnitud=buscarVector(magnitudes,mag);
    }
}
Parametro::Parametro(TIPO_PARAMETRO t, void* v, std::string n, int m) {
   tipo = t;
   magnitud = m;
   nombre = n;
   variable = v;
}
std::string Parametro::serializar(){
    std::string resultado="{";
    switch (tipo){
        case TIPO_PARAMETRO::FUNC:
            resultado+="TIPO_PARAMETRO::FUNC";      
        default:
            resultado+="TIPO_PARAMETRO::PROP";      
            break;
    }
    resultado += ",&" + nombre + "";
    resultado+=",\""+nombre+"\"";
    resultado+=","+std::to_string(magnitud);
    for(auto p:parametros){
        resultado+=p.serializar();
    }
    resultado+="}";
    return resultado;
};
std::string Parametro::join(std::vector<std::string> nombres, std::string pegamento, int ini, int fin){
    std::string resultado="";
    bool pegar=false;
    for(int i=ini;i<=fin;i++){
        if(i>=0 && i<nombres.size()){
            resultado+=(pegar?pegamento:"")+nombres[i];
            pegar=true;
        }
        
    }

    return resultado;
}
std::vector<std::string> Parametro::magnitudes={"int", "char", "float", "double", "int*", "float*", "double*", "char*", "int**", "float**", "double**", "char**"};