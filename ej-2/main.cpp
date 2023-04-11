#include <iostream>
#include <vector>

typedef long long longl;


//
// GLOBAL
//

longl c = 0, n = 0, r, m;
std::vector<longl> V;
std::vector<std::vector<short>> M;


//
// SOLUCION
//

longl modexp(longl b, longl e, longl m) {
    // idea: el modulo de una potencia se puede calcular de a potencias de dos y un excedente.                                                
    // por ejemplo: b^11 mod 5 = (b^3)*((b^2)^2)^2) mod 5 
    //                         = (b*(b*(b mod 5) mod 5) mod 5) * (((b^2 mod 5)^2 mod 5)^2 mod 5)
    // r = el producto de la derecha, c = el producto de la izquierda
    longl r = b, c = 1;
     std::cout << b << ' ' << e << ' ' << m << ' ';
    while (e > 1) {
        r = (r * r) % m;
        if (e % 2 == 1) {
            c = (b * c) % m;
        }
        e = e / 2;
    }
    if (e == 1) {
        c = (b * c) % m;
    }
    std::cout << (r * c) % m << std::endl;
    return (r * c) % m;
}


bool solucion(longl k, longl s) {
    // k = espacio a agregar una operacion, s = resultado actual modulo m
    if (k == n-1) {
        return (s == r); 
    }
    if (M[k][s] == -1) {
        bool res = false;
        if (solucion(k+1, (s + V[k+1]) % m)) {
            std::cout << '+';
            res = true;
        } else if (solucion(k+1, (m + (s - V[k+1]) % m) % m)) {
            std::cout << '-';
            res = true;
        } else if (solucion(k+1, (s * V[k+1]) % m)) {
            std::cout << '*';
            res = true;
        } else if (solucion(k+1, modexp(s, V[k+1], m))) {
            std::cout << '^';
            res = true;
        }
        M[k][s] = res;
        std::cout << std::endl;
    }
    return M[k][s];
}


bool resolver() {
    M.resize(n);
    for (longl i = 0; i < n; ++i) {
        M[i] = std::vector<short>(m, -1);
    }
    return solucion(0, V[0] % m);
}


//
// MAIN
//

int main(int argc, char** argv) {
    std::cin >> c;
    for (longl i = 0; i < c; ++i) {
        std::cin >> n >> r >> m;
        V.resize(n);
        for (longl j = 0; j < n; ++j) {
            std::cin >> V[j]; 
        }
        std::string rta;
        if (resolver()) {
            rta = "Si";
        } else {
            rta = "No";
        }
        std::cout << rta << std::endl;
    }
    return 0;
}
