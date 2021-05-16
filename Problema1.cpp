#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct FlujoNeto {
    int hora;
    int minuto;
    int personas;
};

/*****
* int Conversion
******
* La funcion recibe un valor string, el cual va a cumplir con la forma hh:mm,esto lo verdifica, en el caso que se cumpla,
almacena la hora y los minutos en dos variables, para luego transformarlo todo a minutos y asi sumarlos. Al no cumplir con el formato,
* termina el programa y dice que existe un error con el formato de la hora.
******
* Input:
* string hora: entrega un string con la hora que se quiere revisar.
* .......
******
* Returns:
* retorna un Int, en el cual va a estar almacenada la hora, pero trasformada en minutos.
*****/

int Conversion(string hora){//pasa la hora a minutos.
    char var=':';
    if(hora.length()==5 && hora.find(var)!= string::npos){
        string x= "";           //almacena hora
        string y= "";           //almcena minutos

        for(long unsigned i=0; i<hora.length(); i++){
            if (i<2){
                x+=hora[i];
            }
            if (i>2){
                y+=hora[i];
            }
        }

        int time1 = stoi(x);    //pasar x a int
        int time2 = stoi(y);    //pasar y a int

        int final = (time1*60)+time2;
        return final;
    }
    else{
        cerr<<"Error con formato de hora"<<endl;
        exit(1);
    }

}

/*****
* int archivoBinario
******
* La funcion abre y recorre el archivo binario 'flujo-publico.dat', pasando asi por cada struc almacenado en el mismo, al pasar por cada struc,
* consulta .hora, .minuto y .personas para asi saber si esta en la hora que se solicita y agregar o restar lkas personas que dice el archivo.
******
* Input:
* sting nombre: nombre del archivo binario
* int min: variable con la suma de la hora que se esta consultando, estaria en minutos.
* .......
******
* Returns:
* Retorna un int, el cual va a ser la cantidad de personas que hay en el local hasta la hora entregada.
*****/

int archivoBinario(string nombre, int min){
    //int n, i;
    FlujoNeto Aux;
    fstream binario; 
    int personasB=0;                                    //almacena las personas hasta esa hora del archivo binario.
    
    binario.open(nombre, ios::in|ios::binary);
    if(!binario.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1);                                        //Error al abrir archivo
    }

    while(binario.read((char*)&Aux, sizeof(FlujoNeto))){//lee linea por linea del archivo binario
        int total=(Aux.hora*60)+Aux.minuto;
        if(total<=min){                                 //si esta dentro del rango de horas los valores del struc, se suma la cantidad a la variable personasB
            personasB+=Aux.personas;
        }
    }
    binario.close();
    return personasB;
}

/*****
* int archivoTexto
******
* Abre el archivo txt dos veces, una para saber cuantos trabajadores hay en la empresa, y otra, recorre las lineas del mismo y separa los valores, para asi ocuparlos al hacer comparaciones, 
* se agregan los s(va a tener el caracter'E'o'S') + codigo(rut de los trabajdores), en el caso que no este en el Array, se agrega en un aposicion que esta determinanda
* por una variable. Si el valor ya estaba pero,  junto al rut este una 'E' y la nueva linea tenga una 'S', entonces la cambia.
******
* Input:
* string nombre: nombre del archivo a leer
* int min: variable con la suma de la hora que se esta consultando, estaria en minutos.
* .......
******
* Returns:
* Retorna tjtotal, que son los trabajadores que hay en ese momento en el local, esto lo saca del Array, en el cual 
* va a contar solos los valores que posean una 'E' en el inicio.
*****/

int archivoTexto(string nombre, int min){

    string *trabajadores;                                           //Puntero a Array 
    //string trabajadores[100];
    string data;                                                    //alamacena los datos
    int contador=0;                                                 //lleva la cuenat de los datos dentro del array, es una variable global

    ifstream texto;
    texto.open(nombre,ios::in);

    ifstream text;
    text.open(nombre,ios::in);

    if(!texto.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1);                                                    //Error al abrir archivo  
    }

    int numero_trabajadores=0; 
    string total;
    while(getline(texto, data)){                                    //Recorre las lineas del archivo txt
        long unsigned cont;
        string codigo;
        for(cont=2; cont<data.length();cont++){                     //Busca la informacion del rut de la persona dentro del string
            if (data[cont]==' '){
                break;
            }
            else{
                codigo+=data[cont];
            }
        }
        if(total.find(codigo)== string::npos){                      //busca el rut dentro de un string, si no esta, lo agrega
            total+= " " + codigo;
            numero_trabajadores+=1;
        }
    }
    trabajadores= new string[numero_trabajadores];                  //crea un array con tamano numero_trabajadores

    while(getline(text, data)){
        string h, codigo ;                                          //almacena la hora y rut en h y codigo respectivamente
        char s=data[0];                                             //almacena 'E' o 'S'
        bool flag = false;
        long unsigned crono;
        for(crono=2; crono<data.length();crono++){                  //busca el rut de la persona y lo almacena en codigo
            if (data[crono]==' '){
                break;
            }
            else{
                codigo+=data[crono];
            }
        }
        for(crono=data.length()-5;crono<data.length();crono++){     //almacena la hora dentro del string
            h+=data[crono];
        }
        int cp=Conversion(h);
        if(cp <= min){                                              //entra solo si esta dentro de los rangos de hora
            if (contador == 0 ){                                    //al no existir ningun valor en el array, entonces agrega el primero y cambia contador(se le suma 1)
                trabajadores[contador] = s+codigo;
                contador+=1;
            }
            else{                                                   //ya existen valores en el array, entonces hay que revisar que el valor no este o si ya esta, verificarlo.
                for(int x=0; x < contador; x++){
                    if(trabajadores[x].find(codigo)!= string::npos){//si el rut(almacenado en la variable codigo) esta dentro de alguna posicion del array
                        char pl = trabajadores[x][0];
                        if(pl!=s){                                  //verifica si el trabajador esta o no dentro de la tienda, esto se verifica con la 'E' o 'S'.
                            trabajadores[x]=s+codigo;               //Al ser diferente, se agrega la nueva, es  decir si se tenia 'E20...', ahora se va atener 'S20...' porque el sujeto salio del trabajo.
                        }
                        flag=true;                                  //cambia una variable para una futura condicional
                        
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
    text.close();

    int tjtotal=0;                                                   //variable que va a llevar la suma de cuantos trabajadores hay en la tienda, es decir que tengan una 'E' tbtoral=> trabajadores total
    for(int c=0; c < contador ; c++){                              //itera dentro del array, solo hasta la distancia que tenga la variable contador
        char crt = trabajadores[c][0];
        char entrada = 'E';
        if (crt == entrada){                                         // revisa si el valor en esa posicion, tiene en la posicion 0 una 'E', si es asi, se suma 1 a la variable tjtotal
            tjtotal+=1;
        }
    }
    delete [] trabajadores;
    return tjtotal;
}

/*****
* int cantidadPersonas
******
* Funcion que que utilzia archivoTexto y archivoBinario, para asi, tomar los returns de estas funciones y sumarlos, asi obtener la cantidad 
* de personas totales en el local. Tambien se llama a la funcion Conversion. En si es una funcion que junta todas las demas funciones para 
* realizar el procedimiento fundamental.
******
* Input:
* string clock: string con la hora que se entrego en el imput (es lahora de la cula se quieren saber los datos)
* .......
******
* Returns:
* TipoRetorno, Descripción retorno
*****/

int cantidadPersonas(string clock){
    
    int dato1,dato2;
    int time = Conversion(clock);
    dato1 = archivoBinario("flujo-publico.dat", time);
    dato2 = archivoTexto("asistencia.txt", time);

    int personasfinales= dato1+dato2;
    return personasfinales;
}

//Funcion Principal int main()
int main(){
    string hora;

    cout << "Ingrese la hora que desea examinar(formato hora hh:mm): ";
    cin >> hora;

    //ingresa un string hora y retorna un int cantidad de personas
    int resultado = cantidadPersonas(hora);

    cout <<archivoTexto("asistencia.txt", Conversion(hora)) <<endl;
    cout<< archivoBinario("flujo-publico.dat", Conversion(hora))<<endl;
    cout << "A las " << hora << " hay " << resultado << " personas." << endl; 


    return 0;
}
