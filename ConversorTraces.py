import os

def abrir(arq):
    with open(arq, 'r') as arquivo:
        for linha in arquivo: # para cada linha no arquivo
            if not linha.startswith("=="): # para separar as linhas que são úteis
                linha2 = removefim(linha) # remove o tamanho da operação
                linha1 = separacomeco(linha) # separa a operação
                escrevearquivo(linha1, linha2) # junta os dois e escreve no arquivo


def escrevearquivo(linha1, linha2):
    novoarquivo = "reference_string.txt" # define o nome do arquivo
    linha1 = linha1.strip() # retira os espaços no fim e começo por exemplo " maça " vira "maça"
    linha2 = linha2.strip() # idem
    linha2 = int(linha2, 16) # converte o numero da pagina de hexadecimal para decimal

    with open(novoarquivo, "a") as arquivo:
        arquivo.write(f"{linha1}{linha2}\n") # escreve os dois em uma linha só sem espaços

def separacomeco(linha):
    novalinha = linha[:3] # separa os 3 primeiros caracteres da string e os retorna
    return novalinha 


def removefim(linha):
    novalinha = linha[3:-6] # separa os 3 primeiros caracteres e os 6 últimos 
    return novalinha # retornando apenas o numero da página

arquivos = os.listdir("./")
for file in arquivos:
    if file.endswith('.trace'): #procura no diretório atual o arquivo .trace e abre
        abrir(file)
