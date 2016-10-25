/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 
/* 
 * File:   Datos.cpp
 * Author: Alan
 * 
 * Created on 11 de octubre de 2016, 12:41 PM
 */
 
#include "Datos.h"
 
Datos::Datos(Grafo& g): grafo(g) {
    VecDatos.reserve(g.obtTotVrt());
    int cont = 0;
    for(float i = 2.0 / g.obtTotVrt(); i <= 2.0; i += 2.0 / g.obtTotVrt()){
            VecDatos[cont].crdX = (0.825 * cos(i * 3.1416));
            VecDatos[cont].crdY = (0.825 * sin(i * 3.1416));
            cont++;
    }
    for(int j = 0; j < g.obtTotVrt(); j++){
            VecDatos[j].std = g.obtEst(j);
    }
}
 
Datos::~Datos() {
}
 
float Datos::obtCrdX(int vert) {
    return VecDatos[vert].crdX;
}
 
float Datos::obtCrdY(int vert) {
    return VecDatos[vert].crdY;
}
 
Grafo::E Datos::obtEst(int vert) {
    return VecDatos[vert].std;
}

