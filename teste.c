#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define TAM 20000
#define VERCOMPTROCAS 0

#if (VERCOMPTROCAS)
	#define COMP COMPARACOES++
	#define SWAP TROCAS++
	#define RESET COMPARACOES=TROCAS=0
#else
	#define COMP ;
	#define SWAP ;
	#define RESET ;
#endif

#define RESTAURARVETOR 1

#if (RESTAURARVETOR)
	#define RESETARRAY copyArray(vetor, v, TAM);
#else
	#define RESETARRAY ;
#endif

#define ALEATORIO 1
#define DECRESCENTE 0

int COMPARACOES = 0;
int TROCAS = 0;

void showArray(int v[], int n);

void swap(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;

	SWAP;
}

void bubbleSort(int v[], int n) {
	if (n < 1) //Caso base, chegou-se no último elemento
		return;

	for (int i = 0; i<n-1; i++)
	{
		COMP;
		if (v[i] > v[i + 1])  //Se o elemento atual (v[i]) é maior que o seguinte (v[i+1])
		{
			swap(&v[i], &v[i + 1]); //Os dois são invertidos
		}
	}
	bubbleSort(v, n - 1); //Chama a função novamente com o vetor de tamanho n-1, já que a partir de vetor[n] os itens já estão ordenados
}

void selectionSort(int v[], int n) {
	int i, j, min;
	for (i = 0; i < (n - 1); i++)  //Loop externo que controla a posição sendo ordenada (ou até onde se está ordenado)
	{
		min = i;
		for (j = (i + 1); j < n; j++) { //Loop interno que percorre de i+1 procurando a posição do menor valor
			COMP;
			if (v[j] < v[min])
				min = j;
		}
		COMP;
		if (i != min) { //Se foi encontrado um valor menor, faz a troca
			swap(&v[i], &v[min]);
		}
	}
}

void insertionSort(int v[], int n) {
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = v[i];
		j = i - 1;
		
		COMP;
		while (j >= 0 && v[j] > key) {
			COMP;
			SWAP;
			v[j + 1] = v[j];
			j = j - 1;
		}
		v[j + 1] = key;
	}
}

void merge(int v[], int comeco, int meio, int fim) {
	int com1 = comeco, com2 = meio + 1, comAux = 0, tam = fim - comeco + 1;
	int *vetAux;
	vetAux = (int*)malloc(tam * sizeof(int));

	while (com1 <= meio && com2 <= fim) {
		COMP;
		if (v[com1] < v[com2]) {
			vetAux[comAux] = v[com1];
			com1++;
		}
		else {
			vetAux[comAux] = v[com2];
			com2++;
		}
		comAux++;
		SWAP;
	}

	while (com1 <= meio) {  //Caso ainda haja elementos na primeira metade
		vetAux[comAux] = v[com1];
		comAux++;
		com1++;
		SWAP;
		COMP;
	}

	while (com2 <= fim) {   //Caso ainda haja elementos na segunda metade
		vetAux[comAux] = v[com2];
		comAux++;
		com2++;
		SWAP;
		COMP;
	}

	for (comAux = comeco; comAux <= fim; comAux++) { //Move os elementos de volta para o v original
		v[comAux] = vetAux[comAux - comeco];
		SWAP;
	}

	free(vetAux);
}

void mergeSort(int v[], int comeco, int fim) {
	if (comeco < fim) {
		int meio = (fim + comeco) / 2;

		mergeSort(v, comeco, meio);
		mergeSort(v, meio + 1, fim);
		merge(v, comeco, meio, fim);
	}
}

void shellSort(int v[], int n) {
	int i, j, value;

	int h = 1;
	while (h < n) {
		h = 3 * h + 1;
	}
	while (h > 0) {
		for (i = h; i < n; i++) {
			value = v[i];
			j = i;
			COMP;
			while (j > h - 1 && value <= v[j - h]) {
				v[j] = v[j - h];
				j = j - h;
				SWAP;
			}
			v[j] = value;
		}
		h = h / 3;
	}
}

void quickSort(int v[], int begin, int end)
{
	int i, j, pivo;
	i = begin;
	j = end - 1;
	pivo = v[(begin + end) / 2];
	do
	{
		COMP;
		while (v[i] < pivo && i < end)
		{
			i++;
			COMP;
		}
		COMP;
		while (v[j] > pivo && j > begin)
		{
			j--;
			COMP;
		}
		COMP;
		if (i <= j)
		{
			swap(&v[i], &v[j]);
			i++;
			j--;
		}
		COMP;
	} while (i <= j);
	COMP;
	if (j > begin)
		quickSort(v, begin, j+1);
	COMP;
	if (i < end)
		quickSort(v, i, end);
}

void heapSort(int v[], int n) {
	int i = n / 2, pai, filho, t;
	while (1) {
		if (i > 0) {
			i--;
			t = v[i];
		}
		else {
			n--;
			if (n <= 0) return;
			t = v[n];
			v[n] = v[0];
			SWAP;
		}
		pai = i;
		filho = i * 2 + 1;
		while (filho < n) {
			COMP;
			if ((filho + 1 < n) && (v[filho + 1] > v[filho]))
				filho++;
			COMP;
			if (v[filho] > t) {
				v[pai] = v[filho];
				pai = filho;
				filho = pai * 2 + 1;
				SWAP;
			}
			else {
				break;
			}
		}
		v[pai] = t;		
	}
}

void printTest(char *s, long long int tIni, long long int tFim)
{
	printf("%20s %10lldus %5.3fms COMP: %i TROCAS: %i\n", s, tFim - tIni, (tFim-tIni)/1000.0, COMPARACOES, TROCAS);
	//printf("%s;%lldus;%5.3fms;%i;%i\n", s, tFim - tIni, (tFim-tIni)/1000.0, COMPARACOES, TROCAS);
}

void copyArray(int v1[], int v2[], int size)
{
	for (int i = 0; i < size; i++)
	{
		v2[i] = v1[i];
	}
}

void reverseArray(int v1[], int v2[], int size)
{
	for (int i = 0; i < size; i++)
	{
		v2[i] = v1[size-i-1];
	}
}

long long int tempoMS()
{
	struct timeval timer_usec; 
	long long int timestamp_usec; /* timestamp in microsecond */
	if (!gettimeofday(&timer_usec, NULL)) {
	timestamp_usec = ((long long int) timer_usec.tv_sec) * 1000000ll + 
	                    (long long int) timer_usec.tv_usec;
	}
	else {
	timestamp_usec = -1;
	}
  
	return timestamp_usec;
}

void showArray(int v[], int n)
{
	printf("\n\n");
	for (int i=0; i<n; i++)
	{
		printf("%i ", v[i]);
	}
	printf("\n\n");
}

void main()
{
	int vetor[TAM], v[TAM];
	long long int tIni, tFim;
	 
//	srand(time(NULL));
		
	for (long i = 0; i < TAM; i++)
	{
		if (ALEATORIO)
			vetor[i] = rand();
		else
			vetor[i] = i;
	}

	printf("Ordenando um vetor");

	if (!ALEATORIO)	
	{
		printf(" LINEAR");
		if (DECRESCENTE)
		{
			reverseArray(vetor, v, TAM);
			printf(" DECRESCENTE ");
			copyArray(v, vetor, TAM);
		}
		else
		{
			copyArray(vetor, v, TAM);	
			printf(" CRESCENTE ");
		}
	}
	else
	{
		copyArray(vetor, v, TAM);	
		printf(" ALEATORIO ");
	}
	
	printf("com %lld elementos\n\n", TAM);

	//showArray(v, TAM);
	//system("pause");
	
	RESET;
	
	tIni = tempoMS();
	bubbleSort(v, TAM);
	tFim = tempoMS();

	printTest("Bubble Sort", tIni, tFim);

	RESETARRAY;
	RESET;

	tIni = tempoMS();
	selectionSort(v, TAM);
	tFim = tempoMS();

	printTest("Selection Sort", tIni, tFim);

	RESETARRAY;
	RESET;

	tIni = tempoMS();
	insertionSort(v, TAM);
	tFim = tempoMS();

	printTest("Insertion Sort", tIni, tFim);

	RESETARRAY;
	RESET;

	tIni = tempoMS();
	mergeSort(v, 0, TAM);
	tFim = tempoMS();

	printTest("Merge Sort", tIni, tFim);

	RESETARRAY;
	RESET;

	tIni = tempoMS();
	shellSort(v, TAM);
	tFim = tempoMS();

	printTest("Shell Sort", tIni, tFim);

	RESETARRAY;
	RESET;

	tIni = tempoMS();
	quickSort(v, 0, TAM);
	tFim = tempoMS();

	printTest("Quick Sort", tIni, tFim);

	RESETARRAY;
	RESET;
	
	tIni = tempoMS();
	heapSort(v, TAM);
	tFim = tempoMS();

	printTest("Heap Sort", tIni, tFim);

	printf("\n\n\n\n\n");
	system("pause");
}
