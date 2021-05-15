#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct FlujoNeto {
    int hora;
    int minuto;
    int personas;
};


int Conversion(string hora){//pasa la hora a minutos.
    string x= ""; //almacena hora
    string y= ""; //almcena minutos

    for(long unsigned i=0; i<hora.length(); i++){
        if (i<2){
            x+=hora[i];
        }
        if (i>2){
            y+=hora[i];
        }
    }

    int time1 = stoi(x);//pasar x a int
    int time2 = stoi(y);//pasar y a int

    int final = (time1*60)+time2;
    return final;
}

int archivoBinario(string nombre, int min){
    //int n, i;
    FlujoNeto Aux;
    fstream binario; 
    int personasB=0; //almacena las personas hasta esa hora del archivo binario.
    
    binario.open(nombre, ios::in|ios::binary);
    if(!binario.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1); //Error al abrir archivo
    }

    while(binario.read((char*)&Aux, sizeof(FlujoNeto))){//lee linea por linea del archivo binario
        int total=(Aux.hora*60)+Aux.minuto;
        if(total<=min){ //si esta dentro del rango de horas los valores del struc, se suma la cantidad a la variable personasB
            personasB+=Aux.personas;
        }
    }
    binario.close();
    return personasB;
}

int archivoTexto(string nombre, int min){

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
        string h, codigo ;//almacena la hora y rut en h y codigo respectivamente
        char s=data[0];//almacena 'E' o 'S'
        bool flag = false;
        long unsigned crono;

        for(crono=2; crono<data.length();crono++){
            if (data[crono]==' '){
                break;
            }
            else{
                codigo+=data[crono];
            }
        }
        for(crono=data.length()-5;crono<data.length();crono++){
            h+=data[crono];
        }
        int cp=Conversion(h);
        if(cp <= min){//entra solo si esta dentro de los rangos de hora
            if (contador == 0 ){//al no existir ningun valor en el array, entyonces agrega el primero y cambia contador(se le suma 1)
                trabajadores[contador] = s+codigo;
                contador+=1;
            }
            else{//ya existen valores en el array, entonces hay que revisar que el valor no este o si ya esta, verificarlo.
                for(int x=0; x < contador; x++){
                    if(trabajadores[x].find(codigo)!= string::npos){//si el rut(almacenado en la variable codigo) esta dentro de alguna posicion del array
                        char pl = trabajadores[x][0];
                        if(pl!=s){//verifica si el trabajador esta o no dentro de la tienda, esto se verifica con la 'E' o 'S'.
                            trabajadores[x]=s+codigo;//Al ser diferente, se agrega la nueva, es  decir si se tenia 'E20...', ahora se va atener 'S20...' porque el sujeto salio del trabajo.
                            flag=true;//cambia una variable para una futura condicional
                        }
                    }
                }
                if (flag==false){
                    //En el caso que no se encuentre dentro de los valores del array el rut de la persona, entonces se agrega a la ultima posicion del array que esta determinada con la variable contador
                    trabajadores[contador]= s+codigo;
                    contador+=1;
                }
            }   
        }
        else{
            break;
        }
    }
    texto.close();
    int tjtotal=0; //variable que va a llevar la suma de cuantos trabajadores hay en la tienda, es decir que tengan una 'E' tbtoral=> trabajadores total
    for(int c=0; c < contador-1 ; c++){ //itera dentro del array, solo hasta la distancia que tenga la variable contador
        char crt = trabajadores[c][0];
        char entrada = 'E';
        if (crt == entrada){ // revisa si el valor en esa posicion, tiene en la posicion 0 una 'E', si es asi, se suma 1 a la variable tjtotal
            tjtotal+=1;
        }
    }
    return tjtotal;
}


int cantidadPersonas(string clock){
    
    int dato1,dato2;
    int time = Conversion(clock);
    dato1 = archivoBinario("flujo-publico.dat", time);
    dato2 = archivoTexto("asistencia.txt", time);

    int personasfinales= dato1+dato2;
    return personasfinales;
}


int main(){
    string hora;

    cout << "Ingrese la hora que desea examinar: ";
    cin >> hora;

    
    //ingresa un string hora y retorna un int cantidad de personas
    int resultado = cantidadPersonas(hora);
    cout << "A las " << hora << " hay " << resultado << " personas." << endl; 


    return 0;
}
