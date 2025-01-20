using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

void AbrirArquivo(const string &nomeArquivo,int numero) {
    int numPosDado;
    int numPosInstr;
    int instrHits = 0;
    int instrMisses = 0;
    int dadoHits = 0;
    int dadoMisses = 0;

  /*  cout << "Digite o numero de entradas na TLB de instruções";
    cin >> numPosInstr;
    cout << "Digite o numero de entradas na TLB de paginas: ";
    cin >> numPosDado;*/
    numPosInstr = numero;
    numPosDado = numero;
    // TLB usando um vetor para armazenar os valores
    string TLBDadoEntries[numPosDado];
    string TLBInstrEntries[numPosInstr];

    for (int i = 0; i < numPosDado; i++) {
        TLBDadoEntries[i] = "";  // Inicializa a TLB com valores vazios
    }
    
    for (int i = 0; i < numPosInstr; i++){
        TLBInstrEntries[i] = "";
    }
    // Fila para controlar a ordem de inserção (FIFO)
    queue<int> fifoQueueDado;
    queue<char> fifoQueueInstr;
    ifstream Arquivo(nomeArquivo);

    if (!Arquivo) {
        cout << "Erro ao abrir o arquivo" << endl;
        return;
    }

    string linha;
    while (getline(Arquivo, linha)) {
        bool dadoEncontrado = false;
        bool instrEncontrado = false;
        string op = linha.substr(0, 1);
        string linhaPag = linha.substr(1);

        if(op == "I") {
        // Verifica se a instrução já está na TLB
        for (int j = 0; j < numPosInstr; j++) {
            if (TLBInstrEntries[j] == linhaPag) {  // Verifica se está na TLB
                instrHits++;
                instrEncontrado = true;
                break;
            }
        }

        if (!instrEncontrado) {  // Se não encontrou na TLB, é um miss
            instrMisses++;

            // Se a TLB está cheia, remove o elemento mais antigo (FIFO)
            if (fifoQueueInstr.size() == numPosInstr) {
                int idx = fifoQueueInstr.front();  // Pega o índice do item mais antigo
                fifoQueueInstr.pop();  // Remove da fila

                // Substitui o valor na TLB
                TLBInstrEntries[idx] = linhaPag;
            } else {
                // Se a TLB não está cheia, encontra a próxima posição livre
                for (int j = 0; j < numPosInstr; j++) {
                    if (TLBInstrEntries[j] == "") {  // Encontra uma posição vazia
                        TLBInstrEntries[j] = linhaPag;
                        fifoQueueInstr.push(j);  // Adiciona o índice à fila FIFO
                        break;
                    }
                }
            }
        }
        
    }
/*________________________________________________________________________________________________________________________*/
     else{

        // Verifica se a linha já está na TLB
        for (int j = 0; j < numPosDado; j++) {
            if (TLBDadoEntries[j] == linhaPag) {  // Verifica se a linha está na TLB
                dadoHits++;
                dadoEncontrado = true;
                break;
            }
        }

            if (!dadoEncontrado) {  // Se não encontrou a linha na TLB, é um miss
                dadoMisses++;

                // Se a TLB está cheia, remove o elemento mais antigo (FIFO)
                if (fifoQueueDado.size() == numPosDado) {
                    int idx = fifoQueueDado.front();  // Pega o índice do item mais antigo
                    fifoQueueDado.pop();  // Remove da fila
    
                    // Substitui o valor na TLB
                    TLBDadoEntries[idx] = linhaPag;
                } else {
                    // Se a TLB não está cheia, encontra a próxima posição livre
                    for (int j = 0; j < numPosDado; j++) {
                        if (TLBDadoEntries[j] == "") {  // Encontra uma posição vazia
                            TLBDadoEntries[j] = linhaPag;
                            fifoQueueDado.push(j);  // Adiciona o índice à fila FIFO
                            break;
                        }
                    }
                }
            }
        }
    }
    Arquivo.close();

    // Calculando a taxa de acertos
    float dadoHitRate = (float)dadoHits / (dadoHits + dadoMisses);
    float instrHitRate = (float)instrHits / (instrHits + instrMisses);

    cout << "instrHits: " << instrHits << endl;
    cout << "instrMisses: " << instrMisses << endl;
    cout << "instr Hit Rate: " << instrHitRate * 100 << "%" << endl;

    cout << "pagHits: " << dadoHits << endl;
    cout << "pagMisses: " << dadoMisses << endl;
    cout << "pag Hit Rate: " << dadoHitRate * 100 << "%" << endl;  // Exibe a taxa de acertos em porcentagem
    FILE* f;
    f = fopen("resultado.txt","a");
    fprintf(f,"%i\ninstr hit rate: %f\npag hit rate: %f\n",numPosDado, instrHitRate*100, dadoHitRate*100);
    

}

int main(int argc, char* argv[]) {
    int numero = atoi(argv[1]);
    AbrirArquivo("reference_string.txt",numero); // Exemplo de chamada da função
    return 0;
}
