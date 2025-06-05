# Trabalho-2-ALEST-2
Repositório criado para armazenar o segundo trabalho da disciplina de Algoritmos e Estruturas de Dados II.  

LINK DA RUBRICA: https://mflash.github.io/alest2/trab/t2-251-jsdgfutdfvytgfkmnx/

Para implementar o Trabalho 2 da disciplina Algoritmos e Estruturas de Dados II, intitulado "As Velas se Erguem Novamente", é necessário desenvolver um algoritmo que calcule o mínimo de combustível necessário para que os vikings percorram uma sequência de portos em um mapa, considerando restrições de movimentação e penalidades por mudança de direção. 


---

## 🧭 Entendimento do Problema

Calcular o menor consumo de combustível para que um barco viking:

Parta do porto 1.

Visite os portos de 2 a 9, em ordem crescente.

Retorne ao porto 1 após visitar o último porto acessível. 


## Regras de Navegação

Movimentos permitidos: Norte, Sul, Leste e Oeste.

Cada movimento consome 1 unidade de combustível.

Mudança de direção consome 3 unidades de combustível adicionais.

'.' representa água navegável; '*' representa terreno intransitável.

Se um porto estiver inacessível, ele deve ser ignorado. 



---

## 🧱 Estrutura de Dados e Representação

Mapa

Representar o mapa como uma matriz de caracteres, onde cada célula indica:

'.' para água navegável.

'*' para terreno intransitável.

'1' a '9' para portos. 


Portos

Armazenar as coordenadas dos portos em um dicionário para acesso rápido. 


---

## 🔍 Algoritmo de Busca

Estratégia

Utilizar o algoritmo de Dijkstra modificado para considerar penalidades por mudança de direção. 

## Implementação

1. Para cada par de portos consecutivos (incluindo o retorno ao porto 1), executar o algoritmo de Dijkstra:

Inicializar uma fila de prioridade com a posição atual, custo acumulado e direção anterior.

Para cada movimento possível (N, S, L, O):

Se a nova posição for navegável:

Se a direção for a mesma da anterior, adicionar 1 ao custo.

Se a direção for diferente, adicionar 4 ao custo (1 pelo movimento + 3 pela mudança de direção).


Atualizar a fila de prioridade com a nova posição, custo acumulado e direção atual.

2. Se não for possível alcançar o próximo porto, ignorá-lo e continuar para o seguinte. 
 
---

🎥 Apresentação do Trabalho

1. Introdução ao Problema (1 ponto)
Texto

2. Soluções e Algoritmos (3 pontos)
Texto 

3. Resultados (3 pontos)
Texto

4. Conclusão (1 ponto)
Texto

---

📁 Entrega

Enviar um arquivo ZIP contendo:

Código-fonte do projeto.

Arquivo LEIAME.txt com a URL do vídeo de apresentação.
