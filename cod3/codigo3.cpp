#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   

using namespace std;
const int TAMANHO = 1000;
int main() {
    srand(time(0)); // inicializa o gerador de numeros aleatórios


    vector<int> vetor1(TAMANHO), vetor2(TAMANHO), vetor3(TAMANHO), vetor4;

    // preenche os vetores 1 e 2 
    for (int i = 0; i < TAMANHO; i++) {
        vetor1[i] = rand() % 100 + 1; // inicializa os três vetores
        vetor2[i] = rand() % 100 + 1; 
        vetor3[i] = rand() % 100 + 1;
    }


    // Preenche o vetor 3 com a soma de elementos aleatórios de vetor1 e vetor2
    while (vetor3.size() < TAMANHO) {
        int pos1 = rand() % TAMANHO; // posição aleatória do vetor 1
        int pos2 = rand() % TAMANHO; // .... vetor 2
        int pos3 = rand() % TAMANHO; // .... vetor 3

        int resultado = (vetor1[pos1] + vetor2[pos2]) / vetor3[pos3]; // soma os valores e divide
        vetor4.push_back(resultado);                // adiciona ao vetor 3
    }

    // exibir o vetor 3
    // cout << "Vetor 3: ";
    // for (int num : vetor3) {
    //     cout << num << " ";
    // }
    // cout << endl;

    return 0;
}

