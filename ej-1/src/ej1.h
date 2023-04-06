//
// Created by usuario1 on 4/4/2023.
//

#ifndef EJ_1_EJ1_H
#define EJ_1_EJ1_H

#include <iostream>
#include <vector>
using namespace std;

bool excedeAlNumeroMagico(int sumaFilaActual, int sumaColumnaActual, int x, int y);

bool noSumaLoSuficiente(int sumaFilaActual, int sumaColumnaActual, int x, int y);

int sumarColActual(int y);

int sumarFilaActual(int x);

bool diagonalesValidas();

void generarCuadradoMagico(int n);

void resolver(int n, int k);

bool nEsimoCuadrado(int x, int y);

void imprimirMatriz();
#endif //EJ_1_EJ1_H
