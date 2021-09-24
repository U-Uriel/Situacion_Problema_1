#include<vector>
#include"Registro.hpp"
#include"ordenamiento_generico/Ordenamiento.hpp"
#pragma once
using std::vector;
using std::string;


class VectorRegistros{
    protected:
        vector<Registro> vec_registros;

        /* Regresa un vector sin elementos repetidos. */
        vector<int> repeted(vector<int> &puertosDestino);

    public:
        //Constructores
        VectorRegistros(){}
        VectorRegistros(vector<Registro> vec_registros) : 
        vec_registros(vec_registros){}
        
        //Getter
        /* Regresa el vector de registros.*/
        vector<Registro> registros(){ return vec_registros; }

        //Metodos
        /* Regresa el numero de registros realizados. */
        int cantidadRegistros();

        /* Regresa el numero de registros hechos en una fecha dada.
        Se pasa un objeto de fecha o el numero de dia que se desea. */
        int buscarPorDia(Fecha fechaBuscar);
        /* Regresa el numero de registros hechos en una fecha dada.
        Se pasa un objeto de fecha o el numero de dia que se desea. */
        int buscarPorDia(int dia_buscar);

        /* Regresa un objeto fecha de un dia dado. */
        Fecha fechaDeDia(int dia_buscar);

        /* Regresa verdadero si el nombre se encuentra en el vector de registros. */
        bool buscarNombre(string nombre);

        /* Buscar correo. */
        bool buscarCorreo(string correo);
        
        /* Regresa un vector de los puertos destino debajo de un valor dado. */
        vector<int> buscarPuertosBajo(int mayorPuerto);

        /* Regresa la red interna de la compañia. */
        string desifrarRedInterna();

        //Sobrecarga de operadores
        Registro& operator[](int i);
};

int VectorRegistros::cantidadRegistros(){
    return this->vec_registros.size();
}

int VectorRegistros::buscarPorDia(Fecha fechaBuscar){
    int dias_contados = 0, i = 0;

    //Ordenar el vector para la comparacion
    vector<Registro> vec_ordenado = Ordenamiento<Registro>::insercion(vec_registros, Registro::comparaFecha_asc);

    while(fechaBuscar <= vec_ordenado[i].getFecha() ){
        if( fechaBuscar == vec_ordenado[i].getFecha() ){
            dias_contados++;
        }
        i++;
    }
    return dias_contados;
}

int VectorRegistros::buscarPorDia(int dia_buscar){
    int dias_contados = 0, num_dia_actual = 0;
    Fecha dia_actual, dia_siguiente;

    //Ordenar el vector para la comparacion
    vector<Registro> vec_ordenado = Ordenamiento<Registro>::insercion(vec_registros, Registro::comparaFecha_asc);
    
    for (int i = 0; i < vec_ordenado.size(); i++){
        dia_actual = vec_ordenado[i].getFecha();
        dia_siguiente = vec_ordenado[i+1].getFecha();

        if( dia_buscar-1 == num_dia_actual){
            dias_contados++;
        }

        if( dia_siguiente > dia_actual){
            num_dia_actual++;
        }
    }

    return dias_contados;
}

Fecha VectorRegistros::fechaDeDia(int dia_buscar){
    int num_dia = 1;
    Fecha dia_actual, dia_siguiente;

    //Ordenar el vector para la comparacion
    vector<Registro> vec_ordenado = Ordenamiento<Registro>::insercion(vec_registros, Registro::comparaFecha_asc);
    
    for (int i = 0; i < vec_ordenado.size(); i++){
        dia_actual = vec_ordenado[i].getFecha();
        dia_siguiente = vec_ordenado[i+1].getFecha();

        if( dia_buscar == num_dia){
            return dia_actual;
        }

        if( dia_siguiente > dia_actual){
            num_dia++;
        }
    }

    return Fecha(0,0,0);
}

bool VectorRegistros::buscarNombre(string nombre){
    bool encontrado = false;

    for (int i = 0; i < vec_registros.size(); i++){
        if( this->vec_registros[i].getNombreOrigen().substr(0, nombre.length()) == nombre){
            encontrado = true;
            break;
        }
    }
    return encontrado;   
}

bool VectorRegistros::buscarCorreo(string correo){
    bool encontrado = false;

    for (int i = 0; i < vec_registros.size(); i++){
        if( this->vec_registros[i].getNombreDestino().substr(0, correo.length()) == correo){
            encontrado = true;
            break;
        }
    }
    return encontrado;   
}

vector<int> VectorRegistros::repeted(vector<int> &puertosDestino){
    sort( puertosDestino.begin(), puertosDestino.end() );
    puertosDestino.erase( unique( puertosDestino.begin(), puertosDestino.end() ), puertosDestino.end() );
    return puertosDestino;
}

vector<int> VectorRegistros::buscarPuertosBajo(int mayorPuerto){

    string pDestino;
    int puertoDestino;

    vector<int> puertosDestino;

    for (int i = 0; i < vec_registros.size(); i++){
        pDestino = vec_registros[i].getPuertoDestino();
        puertoDestino = atoi(pDestino.c_str());

        if((puertoDestino < mayorPuerto) && (puertoDestino!= 0)){
            puertosDestino.push_back(puertoDestino);
        }
    }
    return repeted(puertosDestino);
}

string VectorRegistros::desifrarRedInterna(){
    string ip_Actual;

    for (int i = 0; i < this->vec_registros.size(); i++){
        if(vec_registros[i].getIpOrigen().substr(0,3) == "172" ||
           vec_registros[i].getIpOrigen().substr(0,3) == "192" ||
           vec_registros[i].getIpOrigen().substr(0,2) == "10"){

           ip_Actual = vec_registros[i].getIpOrigen();
           break;
        }
    }

    if ( ip_Actual[ip_Actual.size()-4] == '.' ){         //Si las ultimas son 3 cifras
        return ip_Actual.substr(0,ip_Actual.size()-3) + "xxx";

    } else if ( ip_Actual[ip_Actual.size()-3] == '.' ){  //Si las ultimas son 2 cifras
        return ip_Actual.substr(0,ip_Actual.size()-2) + "xxx";
        
    } else if ( ip_Actual[ip_Actual.size()-2] == '.' ){  //Si las ultimas es 1 cifra
        return ip_Actual.substr(0,ip_Actual.size()-1) + "xxx";

    } else {
        return " ";
    }
}

Registro& VectorRegistros::operator[](int index){
    return this->vec_registros[index];
}