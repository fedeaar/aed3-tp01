#include <iostream>
#include <vector>
#include <random>


typedef long long longl;


//
// GLOBAL
//

longl c = 0, n = 0, r, m;
std::vector<longl> V;
std::vector<std::vector<char>> M;


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
        M[i] = std::vector<char>(m, -1);
    }
    return solucion(0, V[0] % m);
}


// TESTS

longl powxy(longl x, longl y, longl m) { // otra imple de modexp para comparar
    if (y == 0) return 1;
    if (y%2 == 1) return (x*powxy(x, y-1, m)) % m;
    longl t = powxy(x, y/2, m);
    return (t*t) % m;
}

void test(int cantidad) {
    // cosas para RNG
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distN(1, 10000);
    std::uniform_int_distribution<std::mt19937::result_type> distM(1, 100000);
    std::uniform_int_distribution<std::mt19937::result_type> dist4(1, 4);
    // tests
    for (int i = 0; i < cantidad; ++i) {
        n = distN(rng);
        m = distM(rng);
        V.resize(n);
        std::vector<int> ops(n - 1);
        
        V[0] = distN(rng);
        longl res = V[0];
        for (int j = 1; j < n; ++j) {
            V[j] = distN(rng);
            ops[j-1] = dist4(rng);
            switch (ops[j-1]) {
                case(1):
                    res = res + V[j];
                    break;
                case(2):
                    res = res - V[j];
                    break;
                case(3):
                    res = res * V[j];
                    break;
                case(4):
                    res = powxy(res, V[j], m);
                    break;
            }
        }
        r = (m + res % m) % m;

        std::cout << "test: " << i << ", n: " << n << ", r: " << r << ", m: " << m << ", mem M: " << n * m * sizeof(char) / 1e6 << " mb." << std::endl;
        
        if (!resolver()) {
            std::cout << "\t error, posible solucion: ";
            for (int j = 0; j < n-1; ++j) {
                std::cout << V[j];
                switch(ops[j]) {
                    case(1):
                        std::cout << '+';
                        break;
                    case(2):
                        std::cout << '-';
                        break;
                    case(3):
                        std::cout << '*';
                        break;
                    case(4):
                        std::cout << '^';
                        break;
                }
            }
            std::cout << V[n-1] << std::endl;
        }
    }
}


//
// MAIN
//

int main(int argc, char** argv) {
    // std::cin >> c;
    // for (longl i = 0; i < c; ++i) {
    //     std::cin >> n >> r >> m;
    //     V.resize(n);
    //     for (longl j = 0; j < n; ++j) {
    //         std::cin >> V[j]; 
    //     }
    //     std::string rta;
    //     if (resolver()) {
    //         rta = "Si";
    //     } else {
    //         rta = "No";
    //     }
    //     std::cout << rta << std::endl;
    // }
    test(1000);
    return 0;
}
