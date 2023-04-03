#include "ej2.h"


bool resolver(const std::vector<int>& V, int n, int m, int r) {
    std::vector<std::vector<int>> M(n);
    for (int i = 0; i < n; ++i) {
        M[i] = std::vector<int>(m, -1);
    }
    return solucion(V, M, n, m, r, 0, V[0] % m);
}


bool solucion(const std::vector<int>& V, std::vector<std::vector<int>>& M, int& n, int& m, int& r, int k, int s) {
    // k = espacio a agregar una operacion, s = resultado actual modulo m
    if (k == n-1) {
        return (s == r); 
    }
    if (M[k][s] == -1) {
        M[k][s] =   solucion(V, M, n, m, r, k+1, (s + V[k+1]) % m) ||
                    solucion(V, M, n, m, r, k+1, (m + (s - V[k+1]) % m) % m) || // resuelve modulo negativo
                    solucion(V, M, n, m, r, k+1, (s * V[k+1]) % m) ||
                    solucion(V, M, n, m, r, k+1, modexp(s, V[k+1], m)); // resuelve overflow con exponente grande
    }
    return M[k][s];
}


long long modexp(int b, int e, int m) {
    // idea: el modulo de una potencia se puede calcular de a potencias de dos y un excedente.                                                
    // por ejemplo: b^11 mod 5 = (b^3)*((b^2)^2)^2) mod 5 
    //                         = (b*(b*(b mod 5) mod 5) mod 5) * (((b^2 mod 5)^2 mod 5)^2 mod 5)
    // r = el producto de la derecha, c = el producto de la izquierda
    long long r = b, c = 1;
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
    return (r * c) % m;
}
