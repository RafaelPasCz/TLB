#include <iostream>
#include <cstdlib> 
#include <ctime>   
using namespace std;
const int TAMANHO = 20; // tamanho das matrizes

void multiplicarMatrizes(int matriz1[][TAMANHO], int matriz2[][TAMANHO], int resultado[][TAMANHO]) {
    // inicializa a matriz resultado
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            resultado[i][j] = 0;
        }
    }

    // multiplicação das matrizes
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            for (int k = 0; k < TAMANHO; k++) {
                resultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }
}

// preencher uma matriz com números aleatórios
void preencherMatrizAleatoria(int matriz[][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            matriz[i][j] = rand() % 999 + 1; // Gera números de 1 a 999
        }
    }
}

// exibir uma matriz
void exibirMatriz(int matriz[][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0)); // inicializa o gerador de números aleatórios

    int matriz1[TAMANHO][TAMANHO], matriz2[TAMANHO][TAMANHO], resultado[TAMANHO][TAMANHO];

    preencherMatrizAleatoria(matriz1);
    preencherMatrizAleatoria(matriz2);


    multiplicarMatrizes(matriz1, matriz2, resultado);

    // cout << "Matriz resultante da multiplicação:" << endl;
    // exibirMatriz(resultado);

    return 0;
}


