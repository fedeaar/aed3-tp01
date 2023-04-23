#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef pair<int, int> actividad;
typedef pair<int, actividad> actividad_enumerada;


//
// SOLUCION
//

void sort(vector<actividad_enumerada>& V, int n) {
    vector<vector<actividad_enumerada>> counts(2*n + 1, vector<actividad_enumerada>());
    for (int i = 0; i < V.size(); ++i) {
        actividad_enumerada v = V[i];
        counts[v.second.second].push_back(v);
    }
    int k = 0;
    for (int i = 0; i < counts.size(); ++i) { 
        for (int j = 0; j < counts[i].size(); ++j) {
            V[k] = counts[i][j];
            ++k;
        }
    }
    return;
}

vector<actividad_enumerada> act(vector<actividad_enumerada>& V, int n) {
    sort(V, n);
    vector<actividad_enumerada> res;
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
// EXPERIMENTO (usamos como template el experimento hecho en clase)
//

vector<int> read_input(int size) {
    vector<int> input(size); string file_name = "inputs/input_" + to_string(size);
    cout << file_name << endl;
    ifstream read_file(file_name);
    for (int i=0; i<size; i++) read_file >> input[i];
    read_file.close();
    return input;
}


double measure(vector<actividad_enumerada> V, int n) {
    auto start = chrono::high_resolution_clock::now();
    act(V, n);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
}


//
// MAIN
//

int main() {
    int repeat = 10;
    ofstream output_file; output_file.open("runtime.csv");
    output_file << "n,time\n";
    
    int limit = 1<<27;
    for (int n=65536; n<limit; n*=2) {
        vector<int> input = read_input(n);
        vector<actividad_enumerada> V;
        for (int i = 0; i < n/2; i+= 2) {
            V.push_back(make_pair(i/2+1, make_pair(input[i],input[i+1])));
        }
        double counter = 0;
        for (int ignore=0; ignore<repeat; ignore++) counter += measure(V, n);
        
        output_file << n << "," << counter / repeat << endl;
    }

    output_file.close();
    return 0;
}
