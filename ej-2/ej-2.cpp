#include <iostream>
#include <vector>

using namespace std;

typedef long long longl;


//
// GLOBAL
//

longl c = 0, n = 0, r, m;
vector<longl> V;
vector<vector<char>> M;


//
// SOLUCION
//

longl modexp(longl b, longl e, longl m) {
    // idea: metodo binario l-r
    if (m == 1) {
        return 0;
    }
    longl r = 1;
    while (e > 0) {
        if (e % 2 == 1) {
            r = (b * r) % m;
        }
        b = (b * b) % m;
        e = e / 2;
    }
    return r;
}


bool solucion(longl k, longl s) {
    // k = espacio a agregar una operacion, s = resultado actual modulo m
    if (k == n-1) {
        return (s == r); 
    }
    if (M[k][s] == -1) {
        M[k][s] = solucion(k+1, (s + V[k+1]) % m) ||
                  solucion(k+1, (m + (s - V[k+1]) % m) % m) ||
                  solucion(k+1, (s * V[k+1]) % m) ||
                  solucion(k+1, modexp(s, V[k+1], m));
    }
    return M[k][s];
}


bool resolver() {
    M.resize(n);
    for (longl i = 0; i < n; ++i) {
        M[i] = vector<char>(m, -1);
    }
    return solucion(0, V[0] % m);
}


//
// MAIN
//

int main(int argc, char** argv) {
    cin >> c;
    for (longl i = 0; i < c; ++i) {
        cin >> n >> r >> m;
        V.resize(n);
        for (longl j = 0; j < n; ++j) {
            cin >> V[j]; 
        }
        string rta;
        if (resolver()) {
            rta = "Si";
        } else {
            rta = "No";
        }
        cout << rta << endl;
    }
    return 0;
}
