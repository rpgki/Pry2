/* 
 * File:   Simulador.h
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 06:46 PM
 */

#ifndef SIMULADOR_H
#define	SIMULADOR_H

#include <memory>
using namespace std;

#include "Grafo.h"

class Simulador {
    // Representa el proceso de simulaciÃ³n de la infecciÃ³n en la red de computadoras.
    
public:
    
    // EFE: Construye un simulador que transformarÃ¡ al grafo g.
    Simulador(Grafo& g);

    // Destruye a *this retornando toda la memoria asignada dinÃ¡micamente.
    ~Simulador();


    // REQ: el grafo asociado (el pasado al constructor) estÃ© bien construido.
    // MOD: el grafo asociado.    
    // EFE: inicializa el simulador con los siguientes parÃ¡metros:
    //      ios o initial-outbreak-size [1..N], N cantidad de vÃ©rtices: cantidad
    //           de vÃ©rtices infectados al comienzo de la simulaciÃ³n.
    //      vsc o virus-spread-chance [0..0.1]: probabilidad de infecciÃ³n.
    //      mvcf o virus-check-frecuency [1..20]: mÃ¡xima frecuencia de chequeo antivirus.
    //      rc o recovery-chance [0..0.1]: probabilidad de recuperaciÃ³n de infecciÃ³n.
    //      grc o gain-resistance-chance [0..1]: probabilidad de lograr resistencia.   
    void iniciarSimulacion(int ios, double vsc, int mvcf, double rc, double grc);
    
    // REQ: el grafo asociado (el pasado al constructor) estÃ© bien construido.
    // MOD: el grafo asociado.
    // EFE: aplica al grafo asociado una transformaciÃ³n con base en las reglas de 
    //      cambio de estado para los vÃ©rtices:
    //      1. un vÃ©rtice sÃ³lo puede ser infectado por alguno de sus vecinos infectados
    //         con probabilidad vsc.
    //      2. sÃ³lo un vÃ©rtice infectado cuyo temporizador de chequeo de virus estÃ¡ en cero
    //         puede recuperarse con probabilidad rc.
    //      3. sÃ³lo un vÃ©rtice recuperado puede ganar resistencia con probabilidad grc.
    //      4. SÃ³lo las transformaciones #2 y #3 pueden ser simultÃ¡neas. 
    void simular();

private:
    Grafo& grafo;
    // se deben agregar mÃ¡s variables de estado.
};

#endif	/* SIMULADOR_H */