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
            else
                aux = false;
            if (aux == true &&(numAzar <= beta)) { // se re-alambra
                // se borra j de la lstAdy de i
                vectorNodos.at(i).lstAdy.erase(vectorNodos.at(i).lstAdy.begin()+j);
                vectorNodos.at(j).lstAdy.erase(vectorNodos.at(j).lstAdy.begin()+i);
                
                vector<int>sonAdyDeI;
                sonAdyDeI.reserve(N);
                int cntNoAdyDeI = 0;

                // se cuentan e identifican todos los nodos no adyacentes a i
                for (int k = 0; k < N; k++) {
                    it = find(vectorNodos.at(i).lstAdy.begin(),vectorNodos.at(i).lstAdy.end(),k); //Se guarda un iterador si se encuentra el vertice adyacente en k.
                    if(it != vectorNodos.at(i).lstAdy.end()) //Si se encuentra el vertice en el vector entonces el auxiliar es verdadero.
                        aux = true;
                    else
                        aux = false;
                    if (aux == true && (k != i)) {
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
                vectorNodos.at(i).lstAdy.push_back(nuevaAdy);
                vectorNodos.at(nuevaAdy).lstAdy.push_back(i);
            }
        }
}

Grafo::Grafo(const Grafo& orig) {

}

Grafo::Grafo(string nArch) {
    NdoVrt v;
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
                v.lstAdy.push_back(stoi(aux));
                vectorNodos.emplace(vectorNodos.begin()+pos,v);
                //vectorNodos.at(pos).lstAdy.push_back(stoi(aux)); //se cambia el caracter a entero y se asigna a la lista correspondiente a cada vertice
                aux = "";
            }
        }
        v.lstAdy.push_back(stoi(aux));
        vectorNodos.emplace(vectorNodos.begin()+pos,v);
        //vectorNodos.at(pos).lstAdy.push_back(stoi(aux)); //se cambia el caracter a entero y se asigna a la lista correspondiente a cada vertice
        aux = "";
        pos = pos + 1; //se aumenta el contador de posiciones para el arreglo de vertices
    }
}

Grafo::~Grafo() {

}

bool Grafo::xstVrt(int vrt) const {
    bool res = false;
    if (vrt < cntVrt) { //Se verifica que el vertice ingresado por el usuario efectivamente exista.
        res = true;
    }
    return res;
}

bool Grafo::xstAdy(int vrtO, int vrtD) const {
    bool res = false; //se inicializa la variable resultado en falso
    vector<int>::const_iterator itr; //se inicializa la variable de iteracion
    itr = find(vectorNodos.at(vrtO).lstAdy.begin(),vectorNodos.at(vrtO).lstAdy.end(),vrtD); //Se busca la posicion de vrtD en el vector de adyacencias de vrtO
    if(itr != vectorNodos.at(vrtO).lstAdy.end()) { //si encuentra que existe adyacencia entre vrtO y vrtD entonces el resultado es verdadero
        res = true;
    }
    return res;
}

const vector<int>& Grafo::obtAdy(int vrt) const {
    return vectorNodos.at(vrt).lstAdy; //Retorna un vector con las adyacencias para vrt
}

int Grafo::obtTotVrt() const {
    return cntVrt; //Retorna la cantidad de vertices en *this
}

int Grafo::obtTotAdy() const {
    int totAdy; //Se inicializa una variable para almacenar el total de adyacentes en *this.
    for (int i = 0; i < cntVrt; i++) { //Se recorre el arreglo para sumar la cantidad de adyacencias total
        totAdy += vectorNodos.at(i).lstAdy.size();
    }
    return totAdy;
}

int Grafo::obtTotAdy(int vrt) const {
    int totAdy; //se crea una variable para almacenar el total de adyacencias
    totAdy = vectorNodos.at(vrt).lstAdy.size(); //se guarda el total de adyacencias para el vertice vrt
    return totAdy; //se retorna el total de adyacencias para vrt
}

double Grafo::obtPrmAdy() const {
    double promAdy; //Se inicializa una variable para almacenar el promedio
    for (int i = 0; i < cntVrt; i++) { //Se suman todas las adyacencias por vértice
        promAdy += vectorNodos.at(i).lstAdy.size();
    }
    promAdy = promAdy / cntVrt; //Se divide el total de adyacencias por la cantidad total de vertices
    return promAdy;
}

Grafo::E Grafo::obtEst(int vrt) const {
    return vectorNodos.at(vrt).std; //Retorna el estado del vértice vrt
}

int Grafo::obtTmpChqVrs(int vrt) const {
    return vectorNodos.at(vrt).tmpChqVrs; //Retorna el temporizador del vértice vrt
}

int Grafo::obtCntChqVrs(int vrt) const {
    return vectorNodos[vrt].cntChqVrs; //Retorna el contador del chequeo de virus del vértice vrt
}

double Grafo::coeficienteAgrupamiento(int vrt) const {
    double coefLoc; //se crea la variable que almacenara el coeficiente local
    vector<int> adyLoc = Grafo::obtAdy(vrt); //se inicializa un vector que contendra las adyacencias de vrt
    double nv = 0.0; // se inicializa la variable total de arcos entre adyacencias de vrt en 0
    int kv = vectorNodos[vrt].lstAdy.size(); //se guarda el total de adyacencias para vrt
    if (kv == 0) {
        coefLoc = 0;
    } else {
        if (kv != 1) { //se calcula el coeficiente siempre y cuando haya al menos dos adyacencias
            for (int i = 0; i < kv - 1; i++) { //se lee cada elemento de la lista
                for (int j = i + 1; j < kv; j++) { //se lee el elemento siguiente a i de la lista
                    if (Grafo::xstAdy(adyLoc[i], adyLoc[j])) { //se evalua si el elemento i tiene esta conectado con algun elemento j
                        nv++; //se aumenta el contador de conexiones   
                    }
                }
            }
            coefLoc = (2 * nv) / (kv * (kv - 1)); //se calcula el coeficiente local
        }
    }
    return coefLoc; //se retorna el valor del coeficiente para vrt
}

double Grafo::coeficienteAgrupamiento() const {
    int vertices = Grafo::obtTotVrt(); //se obtiene el total de vertices en *this
    double res = 0; //se crea la variable resultado que almacenara el coeficiente global
    for (int i = 0; i < vertices; i++) { //se recorren las posiciones del arreglo que contiene a los vertices
        res += Grafo::coeficienteAgrupamiento(i); //se suma el coeficiente local para cada vertice
    }
    res = res / vertices; //se calcula el promedio el cual es el coeficiente global
    return res; //se retorna el coeficiente global
}

void Grafo::modEst(int vrt, E ne) {
    NdoVrt v;
    v.std = ne;
    vectorNodos.emplace(vectorNodos.begin()+vrt,v);
}

void Grafo::modTmpChqVrs(int vrt, int nt) {
    NdoVrt v;
    v.tmpChqVrs = nt;
    vectorNodos.emplace(vectorNodos.begin()+vrt,v);
}

void Grafo::actCntChqVrs(int vrt) {
    NdoVrt v;
    if (vectorNodos[vrt].cntChqVrs > vectorNodos[vrt].tmpChqVrs) {
        v.cntChqVrs = 0;
        vectorNodos.emplace(vectorNodos.begin() + vrt, v);
    } else {
        v.cntChqVrs = vectorNodos[vrt].cntChqVrs;
        v.cntChqVrs++;
        vectorNodos.emplace(vectorNodos.begin() + vrt, v);
    }
}

void Grafo::infectar(int ios) {
    NdoVrt v;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //Se establece la semilla
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> nmAltr(0, cntVrt - 1); //Se genera una distribución uniforme de enteros entre 0 y la cantidad de vertices - 1
    while (ios != 0) {
        int num = nmAltr(generator); //Se guarda el número generado
        if (vectorNodos[num].std != I) {// Se infectan aleatoriamente los nodos de acuerdo al valor ingresado en ios
            v.std = I;
            vectorNodos.emplace(vectorNodos.begin()+num,v);
            ios--;
        }
    }
}

void Grafo::azarizarTmpChqVrs(int maxTmp) {
    NdoVrt v;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //Se crea la semilla
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> nmAltr(1, maxTmp); //Se genera una distribución uniforme desde 1 hasta el valor ingresado por en vcf
    for (int i = 0; i < cntVrt; i++) {
        int num = nmAltr(generator); //Se guarda el número generado
        v.tmpChqVrs = num;
        vectorNodos.emplace(vectorNodos.begin()+i,v); //Se asigna el número generado al temporizador del vertice i
    }
}