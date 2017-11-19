
#ifndef MATRIZ_ESPARSA_H
#define MATRIZ_ESPARSA_H

typedef struct matriz_esparsa MATRIZ_ESPARSA;

typedef struct CELULA {
	int linha;
	int coluna;
	double valor;
	struct CELULA *direita;        //ponteiro p próxima celula na linha
	struct CELULA *abaixo;		   //ponteiro p próxima celula na coluna
} CELULA;

struct matriz_esparsa {
	CELULA **linhas;
	CELULA **colunas;
	int nr_linhas;
	int nr_colunas;
};

/* 1 */ MATRIZ_ESPARSA *criar_matriz(int nr_linhas, int nr_colunas); //cria matriz

/* 2 */ void apagar_matriz (MATRIZ_ESPARSA *matriz); //apaga a matriz

/* 3 */ int set_matriz(MATRIZ_ESPARSA *matriz, int linha, int coluna, double valor); //atribui valor

/* 4 */ double get_matriz(MATRIZ_ESPARSA *matriz, int linha, int coluna); //recupera valor

/* 5 */ MATRIZ_ESPARSA *somar_matriz(MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2); //Soma duas matrizes

/* 6 */ MATRIZ_ESPARSA *multiplicar_matriz( MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2); //Multiplica duas matrizes

/* 7 */ MATRIZ_ESPARSA *transposta_matriz(MATRIZ_ESPARSA *matriz); //Calcula e retorna a matriz transposta

/* 8 */ double determinante_matriz(MATRIZ_ESPARSA *matriz); //calcula o determinante da matriz;

/* 8.1 */ double det_3x3(MATRIZ_ESPARSA *matriz); //calcula det 3x3

/* 9 */ void print_matriz(MATRIZ_ESPARSA *matriz); //mostra a matriz;

/* 10 */ void resumo_matriz(MATRIZ_ESPARSA *matriz); //Mostra os elementos que não são zero da matriz;

/* 11 */ MATRIZ_ESPARSA *ler_matriz(const char nome[]); //Lê a matriz e a imprime

#endif
