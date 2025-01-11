1 - Utilize esse comando para gerar os traces:
  valgrind --log-file=main.trace --tool=lackey --trace-mem=yes ./main
*Caso você queira gerar traces de outro arquivo, substitua o nome "main" pelo nome do seu arquivo

2 - Em seguida abra o ConversorTraces.py para converter os endereços nos numeros das paginas
3 - Será gerado um arquivo chamado "reference_string.txt"
4 - Utilize o programa "TBL.cpp" para encontrar os hits, miss e porcentagem de acerto.
