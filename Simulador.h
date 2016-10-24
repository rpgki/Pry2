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
    
    // REQ: el grafo asociado (el pasado al constructor) esté bien construido.
    // MOD: el grafo asociado.
    // EFE: una copia del metodo que inicia la simulacion sin aleatorizar los vertices infectados
    //      ya que simplemente se usa para controlar las pruebas para el simulador.
    //      vsc o virus-spread-chance [0..0.1]: probabilidad de infección.
    //      mvcf o virus-check-frecuency [1..20]: máxima frecuencia de chequeo antivirus.
    //      rc o recovery-chance [0..0.1]: probabilidad de recuperación de infección.
    //      grc o gain-resistance-chance [0..1]: probabilidad de lograr resistencia.
    void iniciarSimPba(double vsc, int mvcf, double rc, double grc);
    
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
    
    // REQ: el grafo asociado (el pasado al constructor) esté bien construido.
    // MOD: el grafo asociado solo para pruebas.
    //      Aplica la siguiente regla de cambio de estado para los vértices:
    //      1. un vértice sólo puede ser infectado por alguno de sus vecinos infectados
    //         con probabilidad vsc.
    //      2. sólo un vértice infectado cuyo temporizador de chequeo de virus está en cero
    //         puede recuperarse con probabilidad rc.
    //      3. sólo un vértice recuperado puede ganar resistencia con probabilidad grc.
    //      4. Sólo las transformaciones #2 y #3 pueden ser simultáneas.
    void simularPba();

private:
    Grafo& grafoAct;
    int tam; // Cantidad de vertices infectados al azar.
    double prbInf; // Probabilidad de infeccion
    int maxFrqChqVrs; // Numero maximo temporizador de chequeo de virus.
    double rec; // Probabilidad de recuperacion.
    double resis; // Probabilidad volverse resistente.
};

#endif	/* SIMULADOR_H */