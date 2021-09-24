//
//    El programa contiene un sistema procesamiento de datos capaz 
//    de analizar mas archivos .csv con la misma estructura.
//
//    Creado el 18 de septiembre de 2021 por:
//    Uriel A. Aguilar Martinez           |   A01781698
//    Maria de los Ángeles Garay Pizano   |   A01025416
//  
//    Parte de este codigo fue obtenido de:
//    https://github.com/vcubells/tc1031/blob/master/Retos/procesar_csv/procesar_csv/main.cpp
//


#include"allINCLUDES.hpp"
#include<string>
using namespace std;
using std::stoi; using std::cin;
using std::endl; using std::cout;

/* Lee un archivo csv y lo almacena en un vector de objetos Registro. */
std::vector<Registro> read_csv_persona(std::string filename){
    /* Crear un vector de vector de strings */
    std::vector<Registro> lineas;

    /* Crear un input filestream para leer el archivo CSV */
    std::ifstream file(filename);

    /* Verificar si no hubo error al abrir el archivo */
    if(!file.is_open()) throw std::runtime_error("No se puede abrir el archivo");

    /* Definir variable que almacena cada línea */
    std::string linea;
    
    /* Leer datos línea a línea */
    while(std::getline(file, linea))
    {
        /* Crear un steam de la línea */
        std::stringstream ss(linea);
    
        /* Variables que almacenan cada campo leído */
        std::string fecha, hora,
                    ip_origen, puerto_origen_s, nombre_origen,
                    ip_destino, puerto_destino_s, nombre_destino,
                    dia, mes, año;
        //int dia_i, mes_i, año_i;
        
        /* Iterar sobre la línea para extraer cada campo */
        getline(ss, dia, '-');
        getline(ss, mes, '-');
        getline(ss, año, ',');

        getline(ss, hora, ',');
        getline(ss, ip_origen, ',');
        getline(ss, puerto_origen_s, ',');
        getline(ss, nombre_origen, ',');
        getline(ss, ip_destino, ',');
        getline(ss, puerto_destino_s, ',');
        ss >> nombre_destino;

        
        /* Insertar la fila con los campos separados en un vector */
        lineas.push_back(Registro(Fecha(stoi(dia), stoi(mes), stoi(año)), hora, ip_origen, 
            puerto_origen_s, nombre_origen, ip_destino, puerto_destino_s, nombre_destino));
    }

    /* Cerrar el archivo */
    file.close();

    /* Regresar el vector de líneas leídas */
    return lineas;
}

/* Imprime un vector */
template<class T>
void printVector(vector<T> vect){
    std::copy(vect.begin(), vect.end(),  std::ostream_iterator<T>(std::cout, " | "));
}

/* Menu de opciones que se pueden realizar con el archivo csv. */
int menu(VectorRegistros &registros){
    int option = 0;
    int inOption = 0;
    std::string stringAux; 

    cout << "   ---MENU---   " << endl;
    cout << "1. Obtener numero de registros." << endl;
    cout << "2. Obtener records registrados en algun dia." << endl;
    cout << "3. Buscar nombre en nombre origen." << endl;
    cout << "4. Desifrar direccion de red interna." << endl;
    cout << "5. Buscar servicio en nombre destino." << endl;
    cout << "6. Buscar puertos destino menores a una cantidad." << endl;
    cout << "7. Obtener fecha de un dia dado." << endl;
    cout << "0. Salir." << endl;
    cout << "Opcion: ";

    cin >> option;
    cout << endl;

    switch (option){
    case 1:
        cout << "Registros totales: " << registros.cantidadRegistros() << endl << endl;
        break;

    case 2:
        cout << "1. Fecha en especifico" << endl;
        cout << "2. Dia dado (Ejemplo: 1, 2, etc)" << endl;
        cout << "Opción: ";
        cin >> inOption;
        cout << endl;

        if( inOption == 1){
            int dia, mes, año;

            cout << "Ingrese el dia: ";
            cin >> dia;
            cout << "Ingrese el mes: ";
            cin >> mes;
            cout << "Ingrese el año: ";
            cin >> año;

            cout << "Registros el: " << dia << "/" << mes << "/" << año << ": " <<
            registros.buscarPorDia(Fecha(dia, mes, año)) << endl << endl;
        } else {
            int dia;

            cout << "Ingrese el numero de dia: ";
            cin >> dia;
            
            cout << "Registros del " << dia << "º dia: " <<
            registros.buscarPorDia(dia) << endl << endl;
        }
        break;
        
    case 3:
        cout << "Ingrese el nombre que desea buscar: ";
        cin >> stringAux;

        if( registros.buscarNombre(stringAux) ){
            cout << stringAux << " se encuentra en los registros." << endl << endl;
        } else {
            cout << stringAux << " no se encuentra en los registros." << endl << endl;
        }
        break;

    case 4:
        cout << "La direccion de red interna de la compañia es: ";
        cout << registros.desifrarRedInterna() << endl << endl;
        break;

    case 5:
        cout << "Ingrese el servicio que desea buscar: ";
        cin >> stringAux;

        if( registros.buscarCorreo(stringAux) ){
            cout << stringAux << " se encuentra en los registros." << endl << endl;
        } else {
            cout << stringAux << " no se encuentra en los registros." << endl << endl;
        }
        break;

    case 6:
        int puerto;
        cout << "Ingrese el numero de puerto debajo del que se desea buscar: ";
        cin >> puerto;
        
        cout << endl << "Puertos debajo de " << puerto << ": " << endl;
        printVector<int>(registros.buscarPuertosBajo(puerto));
        cout << endl << endl;
        break; 

    case 7:
        int dia;

        cout << "Ingrese el numero de dia: ";
        cin >> dia;
        cout << registros.fechaDeDia(dia) << endl << endl;
        break;

    default:
        break;
    }

    return option;
}

int main(){
    int opcion = 0, opcionA = 0;
    std::string archivo;

    cout << "\nEliga una opcion." << endl;
    cout << "1. Procesar archivo csv del equipo (equipo 6). " << endl;
    cout << "2. Procesar otro archivo csv. " << endl;
    cout << "Opcion: ";
    cin >> opcion;

    if (opcion == 1){
        archivo = "equipo6.csv";
    } else {
        cout << "Ingrese el directorio del archivo: ";
        cin >> archivo;
    }

    /* Lectura de los datos como un objeto Registro */
    VectorRegistros registros(read_csv_persona(archivo));

    cout << "*    Archivo procesando actualmente: " << archivo << "    *" << endl << endl;

    do{
        opcion = menu(registros);
    } while (opcion != 0);

    return 0;
}