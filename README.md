# Algoritmos de ordenação

Autor: Kauã da Silva Santos

O arquivo ordenacao.cpp contém Bubble, Selection, Insertion, Merge e Quick sort, com comentários linha a linha. Cada algoritmo recebe uma cópia do vetor {5, 3, 4, 1, 2}.

## Compilar no Windows (PowerShell com g++)

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic ordenacao.cpp -o ordenacao.exe
.\ordenacao.exe
```

## Verificação automática

```powershell
.\ordenacao.exe --test
```

São 1.000 entradas, verificadas nos cinco algoritmos contra std::sort: 5.000 verificações. Incluem vetor vazio, valores negativos e repetidos.

## Contagem

- Comparações: somente entre valores, não entre índices.
- Trocas: permutas entre posições diferentes; autotrocas não contam.
- Insertion: movimentos são deslocamentos para a direita; inserir a chave não entra nesse contador.
- Merge: movimentos são escritas no vetor original na intercalação; cópias para auxiliares não entram.
- Bubble não tem parada antecipada; Quick usa Lomuto e último elemento como pivô.

O PDF traz o passo a passo e os contadores acumulados. etapas.tsv contém a saída correspondente, separada por tabulações.

## Entrega

Envie ordenacao.cpp e README.md para seu repositório Git. Entregue o link do repositório e o PDF conforme a orientação do professor. O pacote não publica automaticamente no GitHub.
