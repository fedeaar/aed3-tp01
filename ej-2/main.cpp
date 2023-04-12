#include <iostream>
#include <vector>
#include <random>

typedef long long longl;


//
// SOLUCION
//

longl modexp(longl b, longl e, longl m) {
    // idea: metodo binario l-r
    if (m == 1) {
        return 0;
    }
    longl r = 1;
    b = b % m;
    while (e > 0) {
        if (e % 2 == 1) {
            r = (b * r) % m;
        }
        b = (b * b) % m;
        e = e / 2;
    }
    return r;
}


bool solucion(std::vector<longl> &V, std::vector<std::vector<char>> &M, longl &n, longl &r, longl &m, longl k, longl s) {
    // k = espacio a agregar una operacion, s = resultado actual modulo m
    if (k == n-1) {
        return (s == r); 
    }
    if (M[k][s] == -1) {
        M[k][s] = solucion(V, M, n, r, m, k+1, (s + (V[k+1] % m)) % m) ||
                  solucion(V, M, n, r, m, k+1, (m + (s - (V[k+1] % m)) % m) % m) ||
                  solucion(V, M, n, r, m, k+1, (s * (V[k+1] % m)) % m) ||
                  solucion(V, M, n, r, m, k+1, modexp(s, V[k+1], m));
    }
    return M[k][s];
}


bool resolver(std::vector<longl> &V, longl n, longl r, longl m) {
    std::vector<std::vector<char>> M(n);
    for (longl i = 0; i < n; ++i) {
        M[i] = std::vector<char>(m, -1);
    }
    return solucion(V, M, n, r, m, 0, V[0] % m);
}


//
// MAIN
//

int main(int argc, char** argv) {
    longl c = 0, n = 0, r, m;
    std::cin >> c;
    std::vector<std::string> rta(c);
    for (longl i = 0; i < c; ++i) {
        std::cin >> n >> r >> m;
        std::vector<longl> V(n);
        for (longl j = 0; j < n; ++j) {
            std::cin >> V[j]; 
        }
        if (resolver(V, n, r, m)) {
            rta[i] = "Si";
        } else {
            rta[i] = "No";
        }
    }
    for (longl i = 0; i < c; ++i) {
        std::cout << rta[i] << std::endl;
    }
    return 0;
}
