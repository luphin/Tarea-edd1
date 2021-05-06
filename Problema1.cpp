#include <iostream>
#include "Problema1.hpp"

using namespace std;

int main(){
    string hora;

    cout << "Ingrese la hora que desea examinar:";
    cint >> hora;
    
    //ingresa un string hora y retorna un int cantidad de personas
    int resultado = cantidadPersonas(hora);
    cout << "A las " << hora << " hay " << resultado << " personas." << endl; 
    
    return 0;
}