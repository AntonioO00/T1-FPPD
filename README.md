# Trabalho de Concorrência T1: Jantar dos Filósofos
### Objetivo

O objetivo deste trabalho é aplicar os conceitos de concorrência por meio do estudo e comparação de soluções clássicas para o problema do Jantar dos Filósofos. Os principais pontos abordados incluem compreender os mecanismos de sincronização utilizados, identificar formas de evitar deadlock e starvation e analisar o desempenho das soluções em sistemas multicore. O trabalho também realiza uma comparação entre as soluções concorrentes implementadas e uma versão sequencial do problema.
Descrição do Problema

O problema do "Jantar dos Filósofos", formulado por Edsger Dijkstra em 1965, exemplifica questões de concorrência e o acesso a recursos compartilhados. No cenário, cinco filósofos estão sentados ao redor de uma mesa com um garfo entre cada par de filósofos adjacentes. Cada filósofo alterna entre os estados de pensar e comer. Para comer, o filósofo precisa adquirir os dois garfos adjacentes. A solução deve garantir que não haja deadlock nem starvation, mantendo um bom nível de concorrência e permitindo que vários filósofos pensem ou comam simultaneamente.
Soluções Implementadas

Foram desenvolvidas e analisadas três soluções para o problema:

    Versão Sequencial (Baseline):
        Implementação em que os filósofos realizam as operações de pensar e comer de forma sequencial, um de cada vez.
        Serve como referência para comparar o nível de concorrência e o tempo total de execução com as versões concorrentes.

    Solução Clássica 1: Algoritmo de Dijkstra:
        Utiliza um algoritmo baseado em semáforos para gerenciar o acesso aos garfos, garantindo que nenhum deadlock ocorra.
        Implementado para demonstrar o uso de semáforos e controle de concorrência.

    Solução Clássica 2: Hierarquia de Recursos:
        Os filósofos adquirem os garfos de acordo com uma hierarquia predefinida, evitando ciclos de espera e, consequentemente, deadlock.
        Implementação com mutexes e locks para garantir acesso seguro aos garfos.

Mecanismos de Sincronização Utilizados

As soluções concorrentes utilizam diferentes mecanismos de sincronização:

    Semáforos: Utilizados para gerenciar o estado de cada filósofo e o acesso aos garfos.
    Mutexes e Locks: Empregados para evitar condições de corrida e gerenciar a hierarquia de acesso.
    Threads: Cada filósofo é implementado como uma thread separada, permitindo a execução paralela das operações de pensar e comer.

## Implementação

Os códigos foram desenvolvidos nas linguagens Java e C (adapte conforme necessário), utilizando threads para representar cada filósofo e semáforos/mutexes para sincronizar o acesso aos recursos.
Análise de Desempenho e Concorrência

Cada solução foi executada em um ambiente com múltiplos núcleos e avaliada quanto ao tempo total de execução e o número de vezes que cada filósofo conseguiu comer em um determinado período. A análise comparativa incluiu:

    Tempo de execução: Medido para 100 ciclos de pensar e comer para cada filósofo.
    Número de refeições: Quantas vezes cada filósofo conseguiu comer em um tempo fixo.
    Nível de concorrência: Comparado com a versão sequencial.
