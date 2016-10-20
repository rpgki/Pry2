/* 
 * File:   Grafo.h
 * Author: alan.calderon
 *
 * Created on 1 de septiembre de 2016, 06:49 PM
 */

#ifndef GRAFO_H
#define	GRAFO_H

#include <memory>
#include <string>
#include <vector>
using namespace std;

class Grafo {
    // Representa la red de computadores sobre la cual se diseminarÃ¡ el virus.
    
public:
    
    /* TIPO PÃšBLICO DE ESTADOS DE VÃ‰RTICES */
    enum E{ // representa el tipo de estados de la red de infecciÃ³n
        S, // representa un vÃ©rtice susceptible de infecciÃ³n
        I, // representa un vÃ©rtice infectado
        R, // representa un vÃ©rtice resistente
    };
    
    /* CONSTRUCTORES */
    // REQ: ( cntVrt >> K >> ln(cntVrt) >> 1 ) && ( 0 <= beta <= 1 ) && ( K mod 2 == 0)
    // Construye un grafo siguiendo el algoritmo de Watts y Strogatz para "pequeÃ±os mundos".
    // Ver:https://en.wikipedia.org/wiki/Watts_and_Strogatz_model
    Grafo(int cntVrt, int K, double beta);
    
    // Construye una copia idÃ©ntica a orig.
    Grafo(const Grafo& orig);
    
    // Construye una red con base en los datos en el archivo de nombre nArch.
    // El archivo debe ser *.txt con datos separados por comas.
    // En la primera lÃ­nea aparecerÃ¡ un entero que representa la cantidad de vÃ©rtices.
    // Luego en cada lÃ­nea aparecerÃ¡ primero el estado de un vÃ©rtice y las posiciones
    // de los adyacentes, todo separado por comas.
    Grafo(string nArch);
    
    // Destruye a *this retornando toda la memoria asignada dinÃ¡micamente.
    ~Grafo();
    
    /* MÃ‰TODOS OBSERVADORES BÃSICOS */
    
    // EFE: retorna true si existe un vÃ©rtice con Ã­ndice vrt.
    bool xstVrt(int vrt) const;
    
    // REQ: existan en *this vÃ©rtices con Ã­ndices vrtO y vrtD.
    // EFE: retorna true si existe un arco entre los vÃ©rtices con Ã­ndice vrtO y vrtD.
    bool xstAdy(int vrtO, int vrtD) const;
    
    // REQ: que exista en *this un vÃ©rtice con Ã­ndice vrt.
    // EFE: retorna un vector de enteros con las posiciones de los vÃ©rtices
    //      adyacentes al vÃ©rtice indicado por vrt.
    // NOTA: no permite la modificaciÃ³n del vector en el contexto de invocaciÃ³n.
    const vector<int>& obtAdy(int vrt) const;

    // EFE: retorna el total de vÃ©rtices en *this.
    int obtTotVrt() const;
    
    // EFE: retorna el total de adyacencias en *this.
    int obtTotAdy() const; 
    
    // REQ: que exista en *this un vÃ©rtice con Ã­ndice vrt.
    // EFE: retorna el total de adyacencias del vÃ©rtice vrt.
    int obtTotAdy(int vrt) const;    
    
    // REQ: que exista en *this un vÃ©rtice con Ã­ndice vrt.
    // EFE: retorna el promedio simple de adyacencias por nodo.
    double obtPrmAdy() const;
    
    // REQ: que exista en *this un vÃ©rtice con Ã­ndice vrt.
    // EFE: retorna el estado del vÃ©rtice con Ã­ndice vrt.
    E obtEst(int vrt) const;

    // REQ: que exista en *this un vÃ©rtice con Ã­ndice vrt.
    // EFE: retorna el valor del temporizador de chequeo de antivirus del vÃ©rtice con Ã­ndice vrt.
    int obtTmpChqVrs(int vrt) const; 

    // REQ: que exista en *this un vÃ©rtice con Ã­ndice vrt.
    // EFE: retorna el valor del contador de chequeo de antivirus del vÃ©rtice con Ã­ndice vrt.	
    int obtCntChqVrs(int vrt) const;
    
    /* MÃ‰TODOS OBSERVADORES ESPECIALES */
    
    // REQ: que exista en *this un vÃ©rtice con Ã­ndice vrt.
    // EFE: retorna el "local clustering coefficient" o coeficiente local de agrupamiento
    //      para el vÃ©rtice indicado por vrt.
    //      La definiciÃ³n aparece en: http://en.wikipedia.org/wiki/Clustering_coefficient
    //      Se calcula como el cociente entre la cantidad efectiva de arcos entre los
    //      vecinos del vÃ©rtice indicado por vrt dividida por la cantidad total de posibles
    //      arcos entre todos los vecinos del vÃ©rtice indicado por vrt.
    double coeficienteAgrupamiento(int vrt) const;
    
    // EFE: calcula el coeficiente de agrupamiento de todo el grafo como el
    //      promedio simple del coeficiente de agrupamiento de todos sus nodos.
    double coeficienteAgrupamiento() const;
    
    /* MÃ‰TODOS MODIFICADORES */
    
    // REQ: que exista en *this un vÃ©rtice con Ã­ndice vrt.
    // MOD: *this.
    // EFE: cambia el estado del vÃ©rtice cuyo Ã­ndice es vrt a ne.
    void modEst(int vrt, E ne);

    // REQ: que exista en *this un vÃ©rtice con Ã­ndice vrt.
    // MOD: *this.
    // EFE: cambia el valor del temporizador de chequeo de virus del vÃ©rtice vrt por el valor nt.
    void modTmpChqVrs(int vrt, int nt);
    
    // REQ: que exista en *this un vÃ©rtice con Ã­ndice vrt.
    // MOD: *this.
    // EFE: incrementa en uno el valor del contador de chequeo de virus.
    void actCntChqVrs(int vrt);

    // REQ: ios << this->obtTotVrt().
    // MOD: *this.
    // EFE: cambia el estado a I (infectado) a ios vÃ©rtices escogidos al azar.
    //      ios o initial-outbreak-size: cantidad inicial de nodos infectados.
    void infectar(int ios);
    
    // MOD: *this
    // EFE: asigna el valor del temporizador para cada vÃ©rtice con un nÃºmero al azar entre 1 y maxTmp.
    //      vcf o virus-check-frecuency: frecuencia mÃ¡xima de chequeo antivirus.
    void azarizarTmpChqVrs(int vcf);
    
private:
    struct NdoVrt {
        E std; // representa el estado del nodo
        int tmpChqVrs; // representa la frecuencia del chequeo de virus en el nodo
        int cntChqVrs; // representa el contador de chequeo de virus: va de 0 a tmpChqVrs        
        vector<int> lstAdy; // representa la lista de nodos adyacentes
        NdoVrt(): std(S), tmpChqVrs(1), cntChqVrs(0){};
    };
    
    vector<NdoVrt> vectorNodos;
};

#endif	/* GRAFO_H */