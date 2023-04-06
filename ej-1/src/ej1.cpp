//
// Created by usuario1 on 4/4/2023.
//
#include "ej1.h"

//Se declaran todas las variables globales para no tener que pasar como parámetro

vector<bool> numerosUtilizados; //Este vector revisa si i ya está en el número mágico, para 0 <= i <= n*n
vector<vector<int>> cuadradoMagico;
vector<int> sumasParciales; // Este vector guarda las sumas parciales de cada fila o columna, para revisar más
                            // rápidamente la válidez del cuadrado. de tamaño 2n + 2, 0 <= i < n representa las
                            // filas, n <= j < 2n representa las columnas y 2n, 2n+1 las diagonales
int limiteCuadrado;
int numeroMagico;
int cuadradosRestantes;

void generarCuadradoMagico(int n) {
    vector<vector<int>> cuadradoAHacer(n, vector<int>(n,0));
    cuadradoMagico = cuadradoAHacer;
}

void imprimirMatriz() {
    for (int i = 0; i < cuadradoMagico.size(); i++) {
        for (int j = 0; j < cuadradoMagico[0].size();j++) {
            cout << cuadradoMagico[i][j] << " ";
        }
        cout << "\n";
    }
}

int sumarFilaActual(int x) {
    int suma = 0;
    for (int j = 0; j <= limiteCuadrado; j++) {
        suma += cuadradoMagico[x][j];
    }
    return suma;
}

int sumarColActual(int y) {
    int suma = 0;
    for (int i = 0; i <= limiteCuadrado; i++) {
        suma += cuadradoMagico[i][y];
    }
    return suma;
}

bool excedeAlNumeroMagico(int sumaFilaActual, int sumaColumnaActual, int x, int y) {
    bool excede = (sumaFilaActual > numeroMagico) || (sumaColumnaActual > numeroMagico);
    //Si todavia quedan numeros por llenar, es imposible que sea una solucion valida
    bool igualPeroQuedaEnFila = sumaFilaActual == numeroMagico && y < limiteCuadrado;
    bool igualPeroQuedaEnColumna = sumaColumnaActual == numeroMagico && x < limiteCuadrado;
    return excede || igualPeroQuedaEnFila || igualPeroQuedaEnColumna;
}

bool noSumaLoSuficiente(int sumaFilaActual, int sumaColumnaActual, int x, int y) {
    return (y == limiteCuadrado && sumaFilaActual < numeroMagico) ||
    (x == limiteCuadrado && sumaColumnaActual < numeroMagico);
}


bool diagonalesValidas() {
    return (sumasParciales[(limiteCuadrado+1)*2 + 1] == numeroMagico) &&
    (sumasParciales[(limiteCuadrado+1)*2] == numeroMagico);
}

bool nEsimoCuadrado(int x, int y) {
    if (x == limiteCuadrado +1) {
        if(!diagonalesValidas()) return false;
        if (cuadradosRestantes == 1) return true;

        cuadradosRestantes--;
        return false;
    }
    for (int i = 1; i < numerosUtilizados.size(); i++) { //Se saltea el 0 porque no es parte del cuadrado
        if (!numerosUtilizados[i]) { //Revisa si i no está todavía en el cuadrado mágico
            int sumFilaActual = sumasParciales[x] + i;
            int sumColActual = sumasParciales[limiteCuadrado+1 + y] + i;
            //Si la fila/columna excede al número mágico, todos los valores posibles de i también lo harán
            if(excedeAlNumeroMagico(sumFilaActual,sumColActual,x,y)) return false;
            if (!noSumaLoSuficiente(sumFilaActual,sumColActual,x,y)) {
                cuadradoMagico[x][y] = i;
                numerosUtilizados[i] = true;
                sumasParciales[x] += i;
                sumasParciales[limiteCuadrado+1 + y] += i;
                if (x == y) sumasParciales[(limiteCuadrado+1)*2] += i;
                if (x + y == limiteCuadrado) sumasParciales[(limiteCuadrado+1)*2 + 1] += i;
                if (y < limiteCuadrado) {
                    if (nEsimoCuadrado(x, y + 1)) return true;
                } else {
                    if (nEsimoCuadrado(x + 1, 0)) return true;
                }
                sumasParciales[x] -= i;
                sumasParciales[limiteCuadrado+1 + y] -= i;
                if (x == y) sumasParciales[(limiteCuadrado+1)*2] -= i;
                if (x + y == limiteCuadrado) sumasParciales[(limiteCuadrado+1)*2 + 1] -= i;
                cuadradoMagico[x][y] = 0;
                numerosUtilizados[i] = false;
            }
        }
    }
    return false;
}

void resolver(int n,int k) {
    //Se inicializan todas las variables globales
    generarCuadradoMagico(n);
    limiteCuadrado = n-1;
    for (int i = 0; i < (n*n)+1; i++) {
        numerosUtilizados.push_back(false);
    }
    for (int i = 0; i < 2*n + 2; i++) {
        sumasParciales.push_back(0);
    }
    numeroMagico = (n*n*n + n)/2;
    cuadradosRestantes = k;
    bool existeSolucion = nEsimoCuadrado(0,0);
    if (existeSolucion) imprimirMatriz();
    else {
        cout << -1;
    }
}