#include <string>
#include <fstream>

using namespace std;

struct FlujoNeto {
    int hora;
    int minuto;
    int personas;
};

int cantidadPersonas(string hora){

    string tiempo1 = hora[0] + hora[1];
    string tiempo2 = hora[3] + hora[4];

    int time1 = stoi(tiempo1)//pasar tiempo 1 a int
    int time2 = stoi(tiempo2)//pasar tiempo 2 a int
    /*
    Buscar manera de transformar de string a int para asi poder obtener con mas exactitud
    los valores que se necesitan cuando se pide de una hora especifica, ejemplo: 12:30,
    que tambien se cuenten las personas que estan a esa hora en la tienda, o si nos dan 
    las 12:39.
    */
    int dato1 = archivoBinario("flujo-publico.dat");
    int dato2 = archivoTexto("asistencia.txt");


    return dato1 + dato2;
}


int archivoBinario(string nombre){

    FlujoNeto fn; 
    int personasB = 0; //almacena las personas hasta esa hora del archivo binario.
    fstream binario;
    binario.open(nombre, ios::in|ios::binary);
    if(!binario.is_open()){
        cerr << "Error al abrir el archivo\n";
        return 1; //Error al abrir archivo
    }
    //recorre el archivo, por los structs
    while(binario.read((char*)&fn, sizeof(FlujoNeto))){ //tomar los valores del archivo
        if(fn.hora <= time1){ //revisa la hora
            if(fn.minuto <= time2){ //revisa los minutos
                personasB += fn.personas; //suma las personas
            }
        }
    }
    binario.close();

    return personasB;
}

int archivoTexto(string nombre){

    int trabajadores[];
    string data;//alamacena los datos

    ifstream texto;
    texto.open(nombre);

    if(!texto.is_open()){
        cerr << "Error al abrir el archivo\n";
        return 1; //Error al abrir archivo  
    }

    while(getline(texto, data)){
        /*
        Buscar manera de almacenar datos, en si los cod de rut de las personas, para
        asi ir agregando y quitando, al final obtener el tamano y retornarlo.
        --no se pueden ocupar vectores

        Se necesita la hora en int, para saber si la persona pertenece a la hora o no.
        --no utilizar metodos no visto en clases: System (Int32.Parse(string)), 
        sstream (istringstream(string)) 

        Se podria buscar un metodo para que cuando se lea el archivo solo se lea hasta
        la ultima linea que tiene la hora solicitada.

        Al tener esas dos cosas el problema estaria termiando. 

        
        */
    }
    return ;
}