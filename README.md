# 2FPR
Algoritmos de Ordenação de Vetores com cálculo de comparações e trocas

Explicando as diretivas de pré-processamento:

#define TAM 20000 -> Tamanho do vetor a ser ordenado

#define VERCOMPTROCAS 1 -> Define se serão mostradas as quantidades de comparações e trocas de elementos do vetor (1 para mostrar e 0 para não)

#if (VERCOMPTROCAS) -> Caso positivo, troca as palavras-chaves pelas instruções necessárias para incrementar e resetar os contadores
	#define COMP COMPARACOES++
	#define SWAP TROCAS++
	#define RESET COMPARACOES=TROCAS=0
#else               -> Caso negativo, substitui por linhas em branco para não comprometer o cálculo de tempo
	#define COMP ;
	#define SWAP ;
	#define RESET ;
#endif

#define RESTAURARVETOR 1 -> Define se o vetor será restaurado para o estado inicial entre as chamadas dos métodos

#if (RESTAURARVETOR) -> Caso positivo, troca a palavra-chave pela instrução necessária
	#define RESETARRAY copyArray(vetor, v, TAM);
#else
	#define RESETARRAY ;
#endif

#define ALEATORIO 1 -> Define se o vetor será aleatório ou linear
#define DECRESCENTE 0 -> No caso de ser linear, define se será em ordem decrescente (por padrão será crescente)


O ideal é executar o código mudando VERCOMPTROCAS para 0 para ter um expectivamente de tempo mais precisa e executar com 1 para ter as estatísticas.
Mesmo no caso do vetor aleatório, srand() não é utilizado, portanto os elementos aleatórios permaneceram os mesmos entre as chamadas (naquela sessão em particular).
