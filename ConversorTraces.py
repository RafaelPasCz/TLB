def gerar_reference_string(pagesize=4096, trace_file='main.trace'):
    reference_string = []
    with open(trace_file, 'r') as arquivo:
        for linha in arquivo:
            if linha.startswith(' '):
                linha = linha[1:]
            if linha.startswith(('I', 'S', 'L', 'M')):  # Filtra linhas relevantes
                parts = linha.split()
                endereco = parts[1].split(',')[0]  # Extrai o endereço antes da vírgula
                end_decimal = int(endereco, 16)  # Converte de hexadecimal para decimal
                num_pagina = end_decimal // pagesize  # Calcula o número da página
                # Verifique se a conversão está correta
                reference_string.append(f"{num_pagina:05x}")  # Formata como hexadecimal
    return reference_string

# Gera a reference string e salva em um arquivo
reference_string = gerar_reference_string()
with open('reference_string.txt', 'w') as arquivo:
    arquivo.write('\n'.join(reference_string))
