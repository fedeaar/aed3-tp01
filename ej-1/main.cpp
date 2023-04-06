#include <iostream>
#include "./src/ej1.h"
int main() {
    int n = 0;
    int k = 0;
    std::cout << "Seleccione un valor para n: ";
    std::cin >> n;
    std::cout << "Seleccione un valor para k: ";
    std::cin >> k;
    resolver(n,k);

    return 0;
}
