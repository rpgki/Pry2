/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PbaSimulador.cpp
 * Author: Carlos
 *
 * Created on 23 de octubre de 2016, 01:57 PM
 */

#include <stdlib.h>
#include <iostream>
#include "Simulador.h"

/*
 * Simple C++ Test Suite
 */

//void testSimulador() {
//    Grafo& g;
//    Simulador simulador(g);
//    if (true /*check result*/) {
//        std::cout << "%TEST_FAILED% time=0 testname=testSimulador (PbaSimulador) message=error message sample" << std::endl;
//    }
//}

void testSimular() {
    Grafo g("redMini.txt");
    // Se infectan los vertices 1 y 2
    g.modEst(1, Grafo::I);
    g.modEst(2, Grafo::I);
    // Primera prueba: Que un vertice en estado susceptible pase a infectado.
    Simulador simulador(g);
    simulador.iniciarSimPba(1.0, 5, 0.2, 0.2);
    simulador.simularPba();
    if (g.obtEst(3) != Grafo::I && g.obtEst(4) != Grafo::I) {
        std::cout << "%TEST_FAILED% time=0 testname=testSimular (PbaSimulador) message=error el metodo simular fallo al cambiar el estado de 3 y 4 a infectado" << std::endl;
    }
    Grafo g2("redMini.txt");
    // Se infectan los vertices 1 y 2
    g2.modEst(1, Grafo::I);
    g2.modEst(2, Grafo::I);
    // Segunda prueba: Que un vertice en estado infectado pase a susceptible.
    Simulador simulador2(g2);
    simulador2.iniciarSimPba(0.2, 5, 1.0, 0.0);
    simulador2.simularPba();
    if (g2.obtEst(1) != Grafo::S && g2.obtEst(2) != Grafo::S) {
        std::cout << "%TEST_FAILED% time=0 testname=testSimular (PbaSimulador) message=error el metodo simular fallo al cambiar el estado de 1 y 2 a susceptible" << std::endl;
    }
    Grafo g3("redMini.txt");
    // Se infectan los vertices 1 y 2
    g3.modEst(1, Grafo::I);
    g3.modEst(2, Grafo::I);
    // Tercera prueba: Que un vertice en estado infectado pase a resistente.
    Simulador simulador3(g3);
    simulador3.iniciarSimPba(0.2, 5, 1.0, 1.0);
    simulador3.simularPba();
    if (g3.obtEst(1) != Grafo::R && g3.obtEst(2) != Grafo::R) {
        std::cout << "%TEST_FAILED% time=0 testname=testSimular (PbaSimulador) message=error el metodo simular fallo al cambiar el estado de 1 y 2 a resistente" << std::endl;
    }
    Grafo g4("redMini.txt");
    // Se infectan los vertices 1 y 2
    g3.modEst(1, Grafo::I);
    g3.modEst(2, Grafo::I);
    // Cuarta prueba: Que un vertice en estado susceptible no cambie su estado al no tener adyacentes infectados.
    Simulador simulador4(g4);
    simulador4.iniciarSimPba(0.5, 5, 0.5, 0.5);
    simulador4.simularPba();
    if (g4.obtEst(0) != Grafo::S) {
        std::cout << "%TEST_FAILED% time=0 testname=testSimular (PbaSimulador) message=error el metodo simular fallo al no mantener susceptible al vertice 0" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% PbaSimulador" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    //    std::cout << "%TEST_STARTED% testSimulador (PbaSimulador)" << std::endl;
    //    testSimulador();
    //    std::cout << "%TEST_FINISHED% time=0 testSimulador (PbaSimulador)" << std::endl;

    std::cout << "%TEST_STARTED% testSimular (PbaSimulador)" << std::endl;
    testSimular();
    std::cout << "%TEST_FINISHED% time=0 testSimular (PbaSimulador)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

