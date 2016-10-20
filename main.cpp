/* 
 * File:   main.cpp
 * Author: alan.calderon
 *
 * Created on 1 de septiembre de 2016, 06:48 PM
 */

#include <iostream>
#include <vector>
using namespace std;

#include "Grafo.h"
#include "Simulador.h"

// EFE: despliega en la ventana dibujos de nodos y arcos
void display(void){
    
}

// EFE: despliega en la ventana el estado de g.
void visualizar(Grafo&g){
    
}

int main(int argc, char** argv) {
    Grafo grf(200, 88, 0.5); // 200 nodos, con promedio de 88 adyacencias por nodo y beta = 0.5
    Simulador sml(grf);
    visualizar(grf);
    return 0;
}