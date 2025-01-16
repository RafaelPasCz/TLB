import os

def abrir(arq):
    with open(arq, 'r') as arquivo:
        for linha in arquivo:
            if not linha.startswith("=="):
                linha2 = removefim(linha)
                linha1 = separacomeco(linha)
                escrevearquivo(linha1, linha2)


def escrevearquivo(linha1, linha2):
    novoarquivo = "reference_string.txt"
    linha1 = linha1.strip()
    linha2 = linha2.strip()
    linha2 = int(linha2, 16)

    with open(novoarquivo, "a") as arquivo:
        arquivo.write(f"{linha1}{linha2}\n")

def separacomeco(linha):
    novalinha = linha[:3]
    return novalinha


def removefim(linha):
    novalinha = linha[3:-6]
    return novalinha

arquivos = os.listdir("./")
for file in arquivos:
    if file.endswith('.trace'):
        abrir(file)
        file.close()
