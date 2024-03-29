#include <iostream>
#include <vector>

using namespace std;


//
// GLOBAL
//

vector<bool>        numerosUtilizados; //Este vector revisa si i ya está en el número mágico, para 0 <= i <= n*n
vector<vector<int>> cuadradoMagico;
vector<int>         sumasParciales;     // Este vector guarda las sumas parciales de cada fila o columna, para revisar más
                                        // rápidamente la válidez del cuadrado. de tamaño 2n + 2, 0 <= i < n representa las
                                        // filas, n <= j < 2n representa las columnas y 2n, 2n+1 las diagonales
vector<int>         sumasMaximas;       // cada posicion i guarda cuánto más se podria sumar a la fila/columna/diagonal, 
                                        // dado que ya tenemos i elementos determinados
vector<int> parImpar;                   // Este vector contiene la diferencia de numeros par e impar entre cada columna,
                                        // sin contar los 0. de tamaño 2n, 0 <= i < n representa las
                                        //filas y n <= j < 2n representa las columnas
int limiteCuadrado;
int numeroMagico;
int cuadradosRestantes;


//
// UTILS
//

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


// 
// PODAS
//

bool excedeAlNumeroMagico(int x, int y, int i) {
    //Si una fila, columna, o diagonal excede al número mágico, no podrá formarse un cuadrado mágico.
    //Podemos podar antes de que se complete la fila/columna/diagonal porque no hay números negativos.
    int sumaFilaActual = sumasParciales[x] + i;
    int sumaColActual  = sumasParciales[limiteCuadrado+1 + y] + i;
    int sumDiagonal    = sumasParciales[(limiteCuadrado+1)*2] + i * (x == y);
    int sumDiagonal2   = sumasParciales[(limiteCuadrado+1)*2 + 1] + i * (x + y == limiteCuadrado);
    bool excede = (sumaFilaActual > numeroMagico) || (sumaColActual > numeroMagico) || (sumDiagonal > numeroMagico) || (sumDiagonal2 > numeroMagico);
    //Si todavia quedan numeros por llenar, es imposible que sea una solucion valida, el 0 no está en el cuadrado
    bool igualPeroQuedaEnFila = sumaFilaActual == numeroMagico && y < limiteCuadrado;
    bool igualPeroQuedaEnColumna = sumaColActual == numeroMagico && x < limiteCuadrado;
    bool igualPeroQuedaEnDiagonal = sumDiagonal == numeroMagico && (x < limiteCuadrado || y < limiteCuadrado);
    bool igualPeroQuedaEnDiagonal2 = sumDiagonal2 == numeroMagico && (x < limiteCuadrado);
    return excede || igualPeroQuedaEnFila || igualPeroQuedaEnColumna || igualPeroQuedaEnDiagonal || igualPeroQuedaEnDiagonal2;
}


bool noSumaLoSuficiente(int x, int y, int i) {
    //Si una fila,columna o diagonal no llega al número mágico incluso si se llenan los casilleros restantes con
    //los máximos valores posibles, podamos.
    int sumaFilaActual = sumasParciales[x] + i;
    int sumaColActual  = sumasParciales[limiteCuadrado+1 + y] + i;
    int sumDiagonal    = sumasParciales[(limiteCuadrado+1)*2] + i * (x == y);
    int sumDiagonal2   = sumasParciales[(limiteCuadrado+1)*2 + 1] + i * (x + y == limiteCuadrado);
    return (sumaFilaActual + sumasMaximas[y] < numeroMagico) ||
           (sumaColActual + sumasMaximas[x] < numeroMagico) ||
           (x == y && sumDiagonal + sumasMaximas[x] < numeroMagico) ||
           (x + y == limiteCuadrado && sumDiagonal2 + sumasMaximas[x] < numeroMagico);
}


bool rompeParidad(int x, int y, int i) {
    //Un cuadrado mágico de n=4 no puede tener una fila o columna de todos números pares o impares.
    //Como tampoco puede haber 3 de uno y 1 de otro (la suma sería impar), tiene que haber 2 y 2 en cada fila y columna
    //Demostración empírica: generamos los 7040 cuadrados y todos cumplían esta propiedad.
    //Demostración formal: se puede realizar exhaustivamente por descarte sobre las combinaciones de los restos 
    // de la suma de filas y columnas modulo 4 que equivalen al numero mágico modulo 4. Estas no pueden incluir una fila o 
    // columna toda par o impar por descarte.
    bool par = i%2 == 0;
    //Si ya hay 3 pares o 3 impares no se puede generar un cuadrado válido.
    bool demasiadosPares = par && (parImpar[x] == 2 || parImpar[limiteCuadrado+1+y] == 2);
    bool demasiadosImpares = !par && (parImpar[x] == -2 || parImpar[limiteCuadrado+1+y] == -2);
    return demasiadosPares || demasiadosImpares;
}


//
// SOLUCION
//

bool nEsimoCuadrado(int x, int y) {
    
    // caso base, solo llegamos cuando es valido
    if (x == limiteCuadrado + 1) {
        return (--cuadradosRestantes) == 0;
    }
    for (int i = 1; i < numerosUtilizados.size(); i++) {
        
        if (numerosUtilizados[i]) continue;  // Revisa si i no está todavía en el cuadrado mágico
            
        // podas
        // Si la fila/columna excede al número mágico, todos los valores posibles de i también lo harán
        if (excedeAlNumeroMagico(x, y, i)) return false;
        // Si ya no podemos llegar al numero magico, descartamos
        // También descartamos si es un cuadrado de 4x4 y la diferencia de pares e impares ya no puede
        // ser 0
        if (noSumaLoSuficiente(x, y, i) || (limiteCuadrado == 3 && rompeParidad(x,y,i))) continue;

        // resultado parcial
        numerosUtilizados[i] = true; // Esta rama ya no va a poder utilizar este valor
        cuadradoMagico[x][y] = i;

        // actualizamos sumas parciales
        sumasParciales[x] += i;
        sumasParciales[limiteCuadrado+1 + y] += i;
        if (x == y) sumasParciales[(limiteCuadrado+1)*2] += i;
        if (x + y == limiteCuadrado) sumasParciales[(limiteCuadrado+1)*2 + 1] += i;
        bool esPar = i % 2 == 0;
        parImpar[x] += esPar - !esPar;
        parImpar[limiteCuadrado+1+y] += esPar - !esPar;
    
        // recursion
        if (y < limiteCuadrado) {
            if (nEsimoCuadrado(x, y + 1)) return true; // short circuit
        } else {
            if (nEsimoCuadrado(x + 1, 0)) return true;
        }

        // deshacemos cambios
        sumasParciales[x] -= i;
        sumasParciales[limiteCuadrado+1 + y] -= i;
        if (x == y) sumasParciales[(limiteCuadrado+1)*2] -= i;
        if (x + y == limiteCuadrado) sumasParciales[(limiteCuadrado+1)*2 + 1] -= i;

        parImpar[x] -=  esPar - !esPar;
        parImpar[limiteCuadrado+1+y] -= esPar - !esPar;
    
        numerosUtilizados[i] = false;
    }

    return false;
}

void resolver(int n,int k) {
    
    // Se inicializan todas las variables globales.
    generarCuadradoMagico(n);
    limiteCuadrado = n-1;
    //Cada número entre 1 y n*n puede estar una sola vez en el cuadrado mágico.
    numerosUtilizados.resize(n*n+1, false);
    sumasParciales.resize(2*n + 2, 0);
    parImpar.resize(2*n, 0);
    sumasMaximas.reserve(n);
    sumasMaximas[n-1] = 0;
    for (int i = 1; i < n; ++i) {
        sumasMaximas[n - i - 1] = sumasMaximas[n - i] + n*n - i + 1;
    }
    numeroMagico = (n*n*n + n) / 2;
    cuadradosRestantes = k;

    bool existeSolucion = nEsimoCuadrado(0,0);
    if (existeSolucion) {
        imprimirMatriz();
    } else {
        cout << -1 << endl;
    }
}


//
// MAIN
//

int main() {
    int n = 0;
    int k = 0;
    cin >> n;
    cin >> k;
    resolver(n, k);
    return 0;
}
