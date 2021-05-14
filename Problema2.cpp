#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class arr_extensible{
private:
    int* A;
    int* B;
    unsigned long len;

public:
    arr_extensible();
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
    len = n;
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
arr_extensible::arr_extensible(unsigned long n, int v){
    A = new int[n];
    len = n;
    unsigned long x;
    for (x = 0; x < n; x++){
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
    unsigned long z = 0;
    if (z <= i && i < len){
        A[i] = v;
        return true;
    } else {
        return false;
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
    unsigned long z = 0;
    if (z <= i && i < len){
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
    len++;
    B = new int[len];
    long unsigned x;
    for (x = 0 ; x < len - 1 ; x++){
        int auxiliar = A[x];
        B[x] = auxiliar;
    };
    B[len - 1] = v;
    delete[] A;
    A = new int[len];
    for (long unsigned x = 0 ; x < len ; x++){
        int auxiliar = B[x];
        A[x] = auxiliar;
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
    len--;
    B = new int[len];
    for (long unsigned x = 0 ; x < len - 1 ; x++){
        B[x] = A[x];
    };
    delete[] A;
    A = new int[len];
    for (long unsigned x = 0 ; x < len - 1 ; x++){
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
    return len;
};


/*-----------------------------------*/
int main(){
    unsigned long tamano = 40, pos1 = 12;
    int valor1 = 15, valor2 = 80;
    arr_extensible A();
    arr_extensible B(tamano);
    arr_extensible C(tamano, valor1);
    for (unsigned long x = 0 ; x < C.size() ; x++){
        cout << C.getValue(x) << " ";
    };
    cout << endl;
    C.setValue(pos1, valor2);
    for (unsigned long x = 0 ; x < C.size() ; x++){
        cout << C.getValue(x) << " ";
    };
    cout << endl;
    C.append(valor2);
    for (unsigned long x = 0 ; x < C.size() ; x++){
        cout << C.getValue(x) << " ";
    };
    cout << endl;
    C.remove();
    for (unsigned long x = 0 ; x < C.size() ; x++){
        cout << C.getValue(x) << " ";
    };
    cout << endl;
    C.remove();
    for (unsigned long x = 0 ; x < C.size() ; x++){
        cout << C.getValue(x) << " ";
    };
    cout << endl;
    return 0;
};