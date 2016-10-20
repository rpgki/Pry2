/* 
 * File:   Grafo.cpp
 * Author: Alan
 * 
 * Created on 2 de abril de 2015, 02:25 PM
 */

#include "Grafo.h"

Grafo::Grafo(int N, int K, double beta) {
    cntVrt = N; //Se guarda la cantidad de vertices escogidas por el usuario
    vectorNodos.reserve(cntVrt); //Se asigna el tamaño de memoria al vector
    bool aux; //Se crea auxiliar para buscar elementos dentro del vector de adyacencias
    //int auxInt; //Auxiliar para borrar un elemento de la lista de adyacencias
    vector<int>::iterator it; //Se inicializa el iterador para el vector de adyacentes.

    for(int i = 0; i < N; i++){ //Se alambran los vértices con sus vecinos de acuerdo al parámetro K
        for(int j = 0; j < N; j++){
            if((abs(i-j)%(N - 1 -(K/2)) > 0) && ((abs(i-j)%(N - 1 -(K/2)) <= K/2)))
                vectorNodos.at(i).lstAdy.push_back(j);
        }
    }

    // Se construye el generador de números al azar basado en una semilla tomada
    // del reloj del sistema:    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    // Se cargan los dados
    std::uniform_real_distribution<double> dados_0_1(0.0, 1.0);


    //#2: se re-alambran las conexiones usando beta
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++) {
            // Genera un número al azar entre 0 y 1
            int numAzar = dados_0_1(generator);
            it = find(vectorNodos.at(i).lstAdy.begin(),vectorNodos.at(i).lstAdy.end(),j); //Se guarda un iterador si se encuentra el vertice adyacente en i.
            if(it != vectorNodos.at(i).lstAdy.end()) //Si se encuentra el vertice en el vector entonces el auxiliar es verdadero.
                aux = true;
            if (aux == true &&(numAzar <= beta)) { // se re-alambra
                // se borra j de la lstAdy de i
                vectorNodos.at(i).lstAdy.erase(vectorNodos.at(i).lstAdy.begin()+(j-1));
                vectorNodos.at(j).lstAdy.erase(vectorNodos.at(j).lstAdy.begin()+(i-1));

                int* sonAdyDeI = new int[N];
                int cntNoAdyDeI = 0;

                // se cuentan e identifican todos los nodos no adyacentes a i
                for (int k = 0; k < N; k++) {
                    if (!arrNdoVrt_ptr[i].lstAdy.bus(k) && (k != i)) {
                        sonAdyDeI[k] = false;
                        cntNoAdyDeI++;
                    } else sonAdyDeI[k] = true;
                }

                // seleccionar entre todas las no-adyacencias una basándose en 
                // la distribución uniforme
                std::uniform_int_distribution<int> dados_0_N(0, cntNoAdyDeI - 1);
                int posNuevaAdy = dados_0_N(generator);

                // se busca nueva adyacencia en el vector de no-adyacencias
                int nuevaAdy = 0;
                int cuentaFalse = 0;
                for (int k = 0; k < N; k++) {
                    if (!sonAdyDeI[k]) {
                        if (cuentaFalse == posNuevaAdy)
                            nuevaAdy = k;
                        cuentaFalse++;
                    }
                }

                // se re-alambra o sustituye j por k
                arrNdoVrt_ptr[i].lstAdy.agr(nuevaAdy);
                arrNdoVrt_ptr[nuevaAdy].lstAdy.agr(i);
            }
        }
}

Grafo::Grafo(const Grafo& orig) {

}

Grafo::Grafo(string nArch) {
    string hilera; //se inicializa la variable que contendra las hileras del archivo
    string aux; //en esta variable se guarda cada caracter de la hilera
    int pos = 0; //contador para posicion del arreglo que contendra los nodos
    ifstream grafo(nArch); //se lee el archivo que contiene el grafo

    if (!grafo) { // operador ! sobrecargado
        cerr << "No se pudo abrir el archivo de entrada" << endl;
        exit(1);
    }

    getline(grafo, hilera); //se lee la primera linea del archivo
    cntVrt = stoi(hilera); //se convierte la primera linea a entero
    vectorNodos.reserve(cntVrt); //Se asigna el tamaño de memoria al vector
    while (getline(grafo, hilera)) { //mientras no se acaben las hileras del archivo
        for (int i = 0; i < hilera.size() - 1; i++) { //este ciclo lee todos los caracteres de la hilera
            if (hilera[i] != ' ') {
                aux = aux + hilera[i]; //se guarda el caracter en aux
            } else {
                vectorNodos.at(pos).lstAdy.push_back(stoi(aux)); //se cambia el caracter a entero y se asigna a la lista correspondiente a cada vertice
                aux = "";
            }
        }
        vectorNodos.at(pos).lstAdy.push_back(stoi(aux)); //se cambia el caracter a entero y se asigna a la lista correspondiente a cada vertice
        aux = "";
        pos = pos + 1; //se aumenta el contador de posiciones para el arreglo de vertices
    }
}

Grafo::~Grafo() {

}

bool Grafo::xstVrt(int vrt) const {

}

bool Grafo::xstAdy(int vrtO, int vrtD) const {

}

const vector<int>& Grafo::obtAdy(int vrt) const {

}

int Grafo::obtTotVrt() const {

}

int Grafo::obtTotAdy() const {

}

int Grafo::obtTotAdy(int vrt) const {

}

double Grafo::obtPrmAdy() const {

}

Grafo::E Grafo::obtEst(int vrt) const {

}

int Grafo::obtTmpChqVrs(int vrt) const {

}

int Grafo::obtCntChqVrs(int vrt) const {

}

double Grafo::coeficienteAgrupamiento(int vrt) const {

}

double Grafo::coeficienteAgrupamiento() const {
    
}

void Grafo::modEst(int vrt, E ne) {

}

void Grafo::modTmpChqVrs(int vrt, int nt) {

}

void Grafo::actCntChqVrs(int vrt) {

}

void Grafo::infectar(int ios) {

}

void Grafo::azarizarTmpChqVrs(int maxTmp) {

}