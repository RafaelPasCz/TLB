using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

void AbrirArquivo(const string &nomeArquivo,int numero) {
    int numPosDado; // tamanho da TLB de dados (só é utilizado se o usuario inserir o numero pela interface do terminal) 
    int numPosInstr; // tamanho da TLB de instruções  (mesma coisa que acima)
    int instrHits = 0; // numero de hits da TLB de instruções
    int instrMisses = 0; // numero de misses da TLB de instruções 
    int dadoHits = 0; // numero de hits da TLB de dados
    int dadoMisses = 0; //numero de misses da TLB de dados

  /*  cout << "Digite o numero de entradas na TLB de instruções";
    cin >> numPosInstr;
    cout << "Digite o numero de entradas na TLB de paginas: ";
    cin >> numPosDado;*/
    numPosInstr = numero; // definido pelo numero que o ususario inseriu como argumento junto com o comando de executar
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
    queue<int> fifoQueueDado; //define as filas para a substituição de linhas
    queue<char> fifoQueueInstr; //um para dados outro pra instruções
    ifstream Arquivo(nomeArquivo); //abre o arquivo

    if (!Arquivo) {
        cout << "Erro ao abrir o arquivo" << endl;
        return;
    }

    string linha;
    while (getline(Arquivo, linha)) { //para cada linha no arquivo
        bool dadoEncontrado = false; //setamos os encontrados para false para cada nova linha
        bool instrEncontrado = false;
        string op = linha.substr(0, 1); //separa o primeiro caractere da linha, para obter o tipo da operação
        string linhaPag = linha.substr(1); //remove o tipo da operação, para procurar/adicionar na TLB

        if(op == "I") { //se o tipo da operação for de instruções
        // Verifica se a instrução já está na TLB
        for (int j = 0; j < numPosInstr; j++) { //para cada entrada na TLB 
            if (TLBInstrEntries[j] == linhaPag) {  // Verifica se está na TLB
                instrHits++; //se sim, hits++
                instrEncontrado = true; 
                break; //interrompe o laço
            }
        }

        if (!instrEncontrado) {  // Se não encontrou na TLB, é um miss
            instrMisses++; //misses ++

            // Se a TLB está cheia, remove o elemento mais antigo (FIFO)
            if (fifoQueueInstr.size() == numPosInstr) {
                int idx = fifoQueueInstr.front();  // Pega o índice do item mais antigo no vetor de instruções
                fifoQueueInstr.pop();  // Remove da fila (não da TLB!!!)

                // Substitui o valor na TLB
                TLBInstrEntries[idx] = linhaPag;
            } else {
                // Se a TLB não está cheia, encontra a próxima posição livre
                for (int j = 0; j < numPosInstr; j++) {
                    if (TLBInstrEntries[j] == "") {  // Encontra uma posição vazia
                        TLBInstrEntries[j] = linhaPag; //adicionamos o valor à TLB
                        fifoQueueInstr.push(j);  // Adiciona o índice para o fim da fila
                        break; //interrompe o laço
                    }
                }
            }
        }
        
    }
//aqui começa a TLB de instruções, com a mesma lógica
/*________________________________________________________________________________________________________________________*/
     else{

        for (int j = 0; j < numPosDado; j++) {
            if (TLBDadoEntries[j] == linhaPag) {  // Verifica se a linha está na TLB
                dadoHits++; // se sim, hits++
                dadoEncontrado = true;
                break; //interrompe o laço
            }
        }

            if (!dadoEncontrado) {  // Se não encontrou a linha na TLB, é um miss
                dadoMisses++; //misses++

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
                            TLBDadoEntries[j] = linhaPag; //adiciona a TLB
                            fifoQueueDado.push(j);  // Adiciona o índice para o fim da fila 
                            break; //interrompe o laço
                        }
                    }
                }
            }
        }
    }
    Arquivo.close(); //fecha o arquivo ao fim da execução

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
    f = fopen("resultado.txt","a"); //joga o resultado para um arquivo, para melhor analise
    fprintf(f,"%i\ninstr hit rate: %f\npag hit rate: %f\n",numPosDado, instrHitRate*100, dadoHitRate*100);
    

}

int main(int argc, char* argv[]) {
    int numero = atoi(argv[1]); // recebe o argumento dado na linha de comando
    AbrirArquivo("reference_string.txt",numero); // chamada da função
    return 0;
}
