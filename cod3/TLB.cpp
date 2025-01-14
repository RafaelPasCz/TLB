using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

void AbrirArquivo(const string &nomeArquivo) {
    int NumPos;
    int hits = 0;
    int misses = 0;

    cout << "Digite o numero de entradas na TLB: ";
    cin >> NumPos;

    // TLB usando um vetor para armazenar os valores
    string TLBentries[NumPos];
    for (int i = 0; i < NumPos; i++) {
        TLBentries[i] = "";  // Inicializa a TLB com valores vazios
    }

    // Fila para controlar a ordem de inserção (FIFO)
    queue<int> fifoQueue;

    ifstream Arquivo(nomeArquivo);

    if (!Arquivo) {
        cout << "Erro ao abrir o arquivo" << endl;
        return;
    }

    string linha;
    while (getline(Arquivo, linha)) {
        bool encontrado = false;

        // Verifica se a linha já está na TLB
        for (int j = 0; j < NumPos; j++) {
            if (TLBentries[j] == linha) {  // Verifica se a linha está na TLB
                hits++;
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {  // Se não encontrou a linha na TLB, é um miss
            misses++;

            // Se a TLB está cheia, remove o elemento mais antigo (FIFO)
            if (fifoQueue.size() == NumPos) {
                int idx = fifoQueue.front();  // Pega o índice do item mais antigo
                fifoQueue.pop();  // Remove da fila

                // Substitui o valor na TLB
                TLBentries[idx] = linha;
            } else {
                // Se a TLB não está cheia, encontra a próxima posição livre
                for (int j = 0; j < NumPos; j++) {
                    if (TLBentries[j] == "") {  // Encontra uma posição vazia
                        TLBentries[j] = linha;
                        fifoQueue.push(j);  // Adiciona o índice à fila FIFO
                        break;
                    }
                }
            }
        }
    }

    Arquivo.close();

    // Calculando a taxa de acertos
    float hitRate = (float)hits / (hits + misses);

    cout << "Hits: " << hits << endl;
    cout << "Misses: " << misses << endl;
    cout << "Hit Rate: " << hitRate * 100 << "%" << endl;  // Exibe a taxa de acertos em porcentagem
}

int main() {
    AbrirArquivo("reference_string.txt"); // Exemplo de chamada da função
    return 0;
}
