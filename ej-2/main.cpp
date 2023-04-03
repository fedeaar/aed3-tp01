#include <iostream>
#include "./src/ej2.h"


//
// MAIN
//

int main(int argc, char** argv) {
    
    int c = 0; 
    std::cin >> c;

    for (int i = 0; i < c; ++i) {
        
        int n = 0, r, m; 
        std::cin >> n >> r >> m;
        
        std::vector<int> V(n);
        for (int j = 0; j < n; ++j) {
            std::cin >> V[j]; 
        }
        
        std::string rta;
        if (resolver(V, n, m, r)) {
            rta = "Si";
        } else {
            rta = "No";
        }
        std::cout << rta << std::endl;
    }
    
    return 0;
}
