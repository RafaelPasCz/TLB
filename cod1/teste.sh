
numero=8
# Loop para multiplicar o número por 2, 10 vezes
for i in {1..8}; do
  ./TLB $numero
  numero=$((numero * 2)) # Multiplica o número por 2
done

