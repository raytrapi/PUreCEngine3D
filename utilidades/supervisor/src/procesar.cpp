#include "procesar.h"

void Procesar::procesarCarpeta(const char* ficheroSalida, const char *ruta){
    //Buscamos carpetas
    fs::path rutaP(ruta);
    std::string cinta = "";
    std::string rutaCinta="";
    std::vector<std::string> clases;
    //cout<<endl<<ruta<<endl;
    if(fs::exists(rutaP)){ //fs::current_path() / ruta
       ofstream salida;
       salida.open(ficheroSalida);
        //Buscamos los ficheros de cabecera
        for(auto fichero : fs::recursive_directory_iterator(rutaP)){
            if(!fichero.is_directory() && fichero.path().extension()==".h"){
                string nombreFicheroTemp=fichero.path().generic_string();
                nombreFicheroTemp=reemplazar('/','_',nombreFicheroTemp.substr(rutaP.generic_string().length()+1));
                auto resultado=procesarCabecera(fichero.path().generic_string(),nombreFicheroTemp);
                if (std::get<0>(resultado)) {
                   clases.push_back(std::get<1>(resultado));
                   //cout<<fichero.path().stem()<<" --- "<<fichero.path().filename()<<" --- "<<fichero.path().extension()<<" --- "<<nombreFicheroTemp<<endl;
                   ifstream fTemp(nombreFicheroTemp);
                   if (fTemp.is_open()) {
                      string linea;
                      while (getline(fTemp, linea)) {
                         salida << linea << endl;
                      }
                      fTemp.close();
                      std::filesystem::remove(nombreFicheroTemp);
                   }
                } else if (std::get<3>(resultado)) {
                   cinta = std::get<1>(resultado);
                   rutaCinta = std::get<2>(resultado);
                }
            }
        }
        if (clases.size() > 0) {
           //std::ofstream out(ficheroSalida, ios_base::app);
           
           //Carga los codigos base
           salida << "#ifdef _WIN32" << endl;
           salida << "extern \"C\" __declspec(dllexport) void listCodeBases(std::vector<std::string>*); " << endl;
           salida << "#endif"<< endl;
           salida << "extern \"C\" void listCodeBases(std::vector<std::string>* clases){"<<endl;
           int i = 0;
           for (auto c : clases) {
              salida << "clases->push_back(\""<<c<<"\");" << std::endl;
           }

           salida << "}"<<endl;/**/


           //Cargamos la creación de instancias de codigos base
           salida << "#include <"<<rutaCinta<<">" << endl;
           salida << "CodeBase* "<<cinta<<"::createCodeBase(const char* base) {" << endl;
           for (auto c : clases) {
              salida << "if (strcmp(base, \"" << c << "\")==0){" << endl;
              salida << "return new "<<c<<"();" << endl;
              salida << "}" << endl;
              
           }
           salida << "return NULL;" << endl;
           salida << "}" << endl;

           /*
           out << "#ifdef _WIN32" << endl;
           out << "extern \"C\" __declspec(dllexport) std::tuple<int, const char**>* listCodeBases(); " << endl;
           out << "#endif"<< endl;
           out << "extern \"C\" std::tuple<int, const char**>* listCodeBases(){"<<endl;

           out << "const char ** clases=new const char*["<<clases.size()<<"];" << endl;
           int i = 0;
           for (auto c : clases) {
              out << "clases["<<(i++)<<"]=\""<<c<<"\";" << std::endl;
           }



           out << "return new std::tuple<int, const char**> {"<<clases.size()<<",clases};"<< endl;
           out << "}"<<endl;/**/
           /**/
           
           //std::cout << "Clases disponibles" << std::endl;
           
        }
        //cout<<"Existe"<<endl;
        salida.close();
    }

}

std::tuple<bool, std::string, std::string, bool> Procesar::procesarCabecera(string origen, string destino){
    //cout<<"Abrimos "<<origen<<endl;
    
    ifstream fichero(origen);
    std::string linea;
    bool esPublico=false;
    bool cogerPublic=false;
    bool esEditable = false;
    bool esTape = false;
    vector<tuple<string,vector<string>>> parametros;
    string clase="";
    while (getline(fichero, linea)){
        linea=trim(linea);
        if(linea.length()>0){
            vector<string> palabras=strip(linea,{' ','{','(',')','}',':',';','=','*','[',']'});
            if(cogerPublic && esPublico){
                string tipo="PROPO";
                if(enVector(palabras,{'('})){
                    tipo="FUNC";
                }
                parametros.push_back({tipo,palabras});
                cogerPublic=false;
            }else{
                if(palabras[0]=="class"){
                    //cout<<"CLASE: "<<palabras[1]<<endl;
                   //Buscamos el : o el {
                   int pos = Parametro::buscarVector(palabras, { string(":"),string("{")});

                    clase=palabras[pos-1];
                }else if (palabras[0]=="PUBLIC"){
                    cogerPublic=true;
                }else if(palabras[0]=="public"){
                    esPublico=true;
                }else if(palabras[0]=="protected"){
                    esPublico=false;
                }else if(palabras[0]=="private"){
                    esPublico=false;
                } else if (palabras[0] == "EDITABLE") {
                   esEditable = true;
                } else if (palabras[0] == "TAPE") {
                   esTape = true;
                }
            }
        }
    }

    //Creamos el fichero
    if(clase.length()>0 && esEditable){

        std::ofstream out(destino);
        out<<"#include \""<< origen <<"\""<<endl;
        //out<<"#include <reflesivo.h>"<<endl;
        out << "void "<<clase<<"::loadParameters() {" << endl;
        //out << "std::cout<<\"Cargamos propiedades ...\"<<std::endl;" << endl;
        for(auto p:parametros){
           cout <<"P: "  << std::get<0>(p) << endl;
            TIPO_PARAMETRO t=TIPO_PARAMETRO::PROP;
            std::string tipo(std::get<0>(p));
            if(tipo=="FUNC"){
                t=TIPO_PARAMETRO::FUNC;
            }
            out<<"\taddParameter("<<(Parametro{t,NULL,std::get<1>(p)}).serializar()<<");"<<endl;
        }
        out << "}" << endl;
        out.close();
    }
    cout<<clase<<endl;
    for(auto par:parametros){
        cout<<get<0>(par)<<": ";
        for(auto t:get<1>(par)){
            cout<<t<<"  ";
        }
        cout<<endl;
    }
    return { esEditable,clase, origen, esTape };
}
vector<string> Procesar::strip(string texto, vector<char> separadores, vector<char> eliminar){
    vector<string> palabras;
    string palabra;
    for(char c:texto){
        if(!enVector(separadores,c)){
            palabra+=c;
        }else{
            
            if(palabra.length()>0){
                palabras.push_back(palabra);
                palabra="";
            }
            if(!enVector(eliminar,c)){
                palabra+=c;
                palabras.push_back(palabra);
                palabra="";
            }
        }
    }
    if(palabra.length()>0){
        palabras.push_back(palabra);
    }
    
   
    return palabras;
}
string Procesar::trim(string texto){

    int i1=0;
    while (i1<texto.length() && (texto[i1]==' ' || texto[i1]=='\t')){
        i1++;
    }
    int i2=texto.length();
    while (i2>0 && (texto[i2]==' ' || texto[i2]=='\t')){
        i2--;
    }
    return texto.substr(i1,i2);
}
std::string Procesar::reemplazar(const char a, const char b,std::string cadena){
    for (int i=0;i<cadena.length();i++){
        if(cadena[i]==a){
            cadena[i]=b;
        }
    }
    return cadena;
};