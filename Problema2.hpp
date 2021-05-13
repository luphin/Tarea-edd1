#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class arr_extensible{
private:
    int* A;
    int* B;

public:
    arr_extensible(unsigned long i);
    arr_extensible(unsigned long i, int v);
    bool setValue(unsigned long i, int v);
    int getValue(unsigned long i);
    void append(int v);
    void remove();
    unsigned long size();
};

/*****
* Constructor arr_extensible
******
* Inicializa el TDA "arr_extensible" de un tamaño especifico 
******
* Input:
* unsigned long n : Tamaño del arreglo extensible A
******
* Returns:
* A[], "retorna" A definido como el arreglo de tamaño n
*****/
arr_extensible::arr_extensible(unsigned long n){
    A = new int[n];
};

/*****
* Constructor arr_extensible
******
* Inicializa el TDA "arr_extensible" de un tamaño especifico y
* con sus variables definidas con un valor determinado
******
* Input:
* unsigned long n : Tamaño del arreglo extensible A
* int v : valor con que se definen las variables de A
******
* Returns:
* A[], "retorna" A definido como el arreglo de tamaño n, con
* sus variables evaluadas en v
*****/
arr_extensible::arr_extensible(unsigned long n, int v);{
    A = new int[n];
    for (int x = 0; x < i; i++){
        A[x] = v;
    };
};

/*****
* bool setValue
******
* Cambia el valor de un elemento de A por el indicado en input
******
* Input:
* unsigned long i : Posición en A del valor a cambiar
* int v : valor con que se reemplazará A[i]
******
* Returns:
* bool, Retorna False si i es mayor que el tamaño de A
*       Retorna True si i es menor que el tamaño de A
*****/
bool arr_extensible::setValue(unsigned long i, int v){
    if (0 =< i < sizeof(A)){
        A[i] = v;
        B[i] = v;
        return True;
    } else {
        return False;
    };
};

/*****
* int getValue
******
* Obtiene el valor de A en una posición i
******
* Input:
* unsigned long i : La posicion de A de la cual se obtendrá el valor
******
* Returns:
* A[i], Retorna el valor de A en la posición i
*****/
int arr_extensible::getValue(unsigned long i){
    if (0 =< i < sizeof(A)){
        return A[i];
    } else {
        cerr << "Error de acceso al arreglo" << endl;
        exit(1);
    };
};

/*****
* void append
******
* Añade un valor v al final del arreglo A
******
* Input:
* int v : El valor a agregar al final de A
******
* Returns:
* void, Al ser una función del tipo void, no requiere return
*****/
void arr_extensible::append(int v){
    B = new int[sizeof(A) + 1];
    for (int x = 0 ; x < sizeof(A) ; x++){
        B[x] = A[x];
    };
    B[sizeof(A) + 1] = v;
    delete[] A;
    A = new int[sizeof(B)];
    for (int x = 0 ; x < sizeof(B) ; x++){
        A[x] = B[x];
    };
    delete[] B;
};

/*****
* void remove
******
* Elimina el último elemento de A
******
* Input:
* Esta función no requiere input
******
* Returns:
* void, Al ser una función del tipo void, no requiere return
*****/
void arr_extensible::remove(){
    B = new int[sizeof(A) - 1]
    for (int x = 0 ; x < sizeof(B) ; x++){
        B[x] = A[x];
    };
    delete[] A;
    A = new int[sizeof(B)];
    for (int x = 0 ; x < sizeof(B) ; x++){
        A[x] = B[x];
    };
    delete[] B;
};

/*****
* unsigned long size
******
* Obtiene el tamaño de A
******
* Input:
* Esta función no requiere input
******
* Returns:
* unsigned long, Retorna el valor del tamaño de A
*****/
unsigned long arr_extensible::size(){
    unsigned long tam;
    tam = sizeof(A);
    return tam;
};