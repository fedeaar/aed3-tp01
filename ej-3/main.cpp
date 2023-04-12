#include <iostream>
#include <vector>

typedef std::pair<int, int> actividad;
typedef std::pair<int, actividad> actividad_enumerada;


//
// SOLUCION
//

void sort(std::vector<actividad_enumerada>& V, int n) {
    // por enunciado, los tiempos tienen tamaño menor a 2n
    std::vector<std::vector<actividad_enumerada>> counts(2*n + 1, std::vector<actividad_enumerada>());
    for (int i = 0; i < V.size(); ++i) {
        actividad_enumerada v = V[i];
        counts[v.second.second].push_back(v);
    }
    int k = 0;
    for (int i = 0; i < counts.size(); ++i) { // 2n + n
        for (int j = 0; j < counts[i].size(); ++j) {
            V[k] = counts[i][j];
            ++k;
        }
    }
    return;
}

std::vector<actividad_enumerada> act(std::vector<actividad_enumerada>& V, int n) {
    sort(V, n);
    std::vector<actividad_enumerada> res;
    int i = 0;
    for (const actividad_enumerada& v : V) {
        if (v.second.first >= i) {
            res.push_back(v);
            i = v.second.second;
        }
    }
    return res;
}


//
// MAIN
//

int main(int argc, char** argv) {
    int n = 0;
    std::cin >> n;
    std::vector<actividad_enumerada> V(n);
    for (int i = 0; i < n; ++i) {
        actividad_enumerada v;
        v.first = i + 1;
        std::cin >> v.second.first >> v.second.second;
        V[i] = v;
    }
    std::vector<actividad_enumerada> res = act(V, n);
    std::cout << res.size() << std::endl;
    for (int i = 0; i < res.size(); ++i) {
        std::cout << res[i].first << ' ';
    }
    std::cout << std::endl;
    return 0;
}
