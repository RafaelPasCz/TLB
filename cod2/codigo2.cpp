#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   

using namespace std;
const int TAMANHO = 10000;
int main() {
    srand(time(0)); // inicializa o gerador de numeros aleatórios


    vector<int> vetor1(TAMANHO), vetor2(TAMANHO), vetor3;

    // preenche os vetores 1 e 2 com valores aleatorios positivos entre 1 e 100
    for (int i = 0; i < TAMANHO; i++) {
        vetor1[i] = rand() % 100 + 1;
        vetor2[i] = rand() % 100 + 1;
    }


    // Preenche o vetor 3 com a soma de elementos aleatórios de vetor1 e vetor2
    while (vetor3.size() < TAMANHO) {
        int pos1 = rand() % TAMANHO; // posição aleatória do vetor 1
        int pos2 = rand() % TAMANHO;

        int soma = vetor1[pos1] + vetor2[pos2]; // soma os valores
        vetor3.push_back(soma);                // adiciona ao vetor 3
    }

    // exibir o vetor 3
    // cout << "Vetor 3: ";
    // for (int num : vetor3) {
    //     cout << num << " ";
    // }
    // cout << endl;

    return 0;
}

