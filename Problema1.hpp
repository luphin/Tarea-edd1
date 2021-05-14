#include <string>
#include <fstream>

using namespace std;



int archivoBinario(string nombre, int hora, int min){

    int n, i;
    FlujoNeto Aux;
    fstream binario; 
    int personasB; //almacena las personas hasta esa hora del archivo binario.
    
    binario.open(nombre, ios::in|ios::binary);
    if(!binario.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1); //Error al abrir archivo
    }


    while(binario.read((char*)&Aux, sizeof(FlujoNeto))){//lee linea por linea del archivo binario
        if(Aux.hora<=hora && Aux.minutos <= min){ //si esta dentro del rango de horas los valores del struc, se suma la cantidad a la variable personasB
            personasB+=Aux.personas;
        }
    }
    binario.close();

    return personasB;
}

int archivoTexto(string nombre, int hora, int min){

    string trabajadores[100]; //se abre un array para almacena 100n valores, si en algun punto estan todos los trabajadores en el local
    string data;//alamacena los datos
    int contador=0;//lleva la cuenat de los datos dentro del array, es una variable global

    ifstream texto;
    texto.open(nombre,ios::in);

    if(!texto.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1); //Error al abrir archivo  
    }
    
    while(getline(texto, data)){
        string h = "";//almacena la hora
        string m = "";//almacena los minutos
        string IS = "";//almacena 'E' o 'S'
        string codigo = "";//almacena el rut del trabajador
        bool flag = false;
        for(int i = 0; i<data.lenght();i++){//con un for se recorre la linea del .txt que se leyo y se extraen los valores
            if (i==0){
                IS+=data[i]; //IS de ingreso y salida
            }
            if (1 < i && i< 11){
                codigo+=data[i]; //codigo almacena rut de la persona
            }
            if (11< i && i< 14){
                h+=data[i]; // h almacena la hora
            }
            if (14<i){
                m+=data[i]; // m almacena la m
            }
        }
        if(stoi(h)<=hora && stoi(m)<=min){//entra solo si esta dentro de los rangos de hora
            if (contador == 0 ){//al no existir ningun valor en el array, entyonces agrega el primero y cambia contador(se le suma 1)
                trabajadores[contador]= IS+codigo;
                contador+=1;
            }
            else{//ya existen valores en el array, entonces hay que revisar que el valor no este o si ya esta, verificarlo.
                for(int x=0; x<contador; x++){
                    if(trabajadores[x].find(codigo)!= string::npos){//si el rut(almacenado en la variable codigo) esta dentro de alguna posicion del array
                        if(trabajadores[x][0]!=IS){//verifica si el trabajador esta o no dentro de la tienda, esto se verifica con la 'E' o 'S'.
                            trabajadores[x]=IS+codigo;//Al ser diferente, se agrega la nueva, es  decir si se tenia 'E20...', ahora se va atener 'S20...' porque el sujeto salio del trabajo.
                            flag=true;//cambia una variable para una futura condicional
                        }
                    }
                }
                if (flag==false){
                    //En el caso que no se encuentre dentro de los valores del array el rut de la persona, entonces se agrega a la ultima posicion del array que esta determinada con la variable contador
                    trabajadores[contador]= IS+codigo;
                    contador+=1;
                }
            }   
        }
    }
    texto.close();
    int tjtotal=0 //variable que va a llevar la suma de cuantos trabajadores hay en la tienda, es decir que tengan una 'E' tbtoral=> trabajadores total
    for(int cont=0; cont<contador; cont++){ //itera dentro del array, solo hasta la distancia que tenga la variable contador
        if (trabajadores[cont][0]=="E"){ // revisa si el valor en esa posicion, tiene en la posicion 0 una 'E', si es asi, se suma 1 a la variable tjtotal
            tjtotal+=1;
        }
    }
    return tjtotal
}

int cantidadPersonas(string hora){

    string x= ""; //almacena hora
    string y= ""; //almcena minutos

    for(int i=0; i<hora.length(); i++){
        if (i<2){
            x+=hora[i];
        }
        if (i>2){
            y+=hora[i];
        }
    }

    int time1 = stoi(x);//pasar x a int
    int time2 = stoi(y);//pasar y a int

    int dato1 = archivoBinario("flujo-publico.dat", time1, time2);
    int dato2 = archivoTexto("asistencia.txt", time1, time2);


    return dato1 + dato2;
}
