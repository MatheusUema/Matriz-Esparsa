#include <stdlib.h>
#include <stdio.h>
#include "matriz_esparsa.h"

/* 1 */MATRIZ_ESPARSA *criar_matriz(int nr_linhas, int nr_colunas) {
	MATRIZ_ESPARSA *matriz = (MATRIZ_ESPARSA *) malloc (sizeof (MATRIZ_ESPARSA)); //Alocamos a memória necessária para uma matriz

	if (matriz != NULL) {
		int i;
		matriz->nr_colunas = nr_colunas;
		matriz->nr_linhas = nr_linhas;
		matriz->colunas = (CELULA **) malloc (sizeof (CELULA*) *nr_colunas);
		matriz->linhas = (CELULA **) malloc (sizeof (CELULA *) *nr_linhas);

		if (matriz->colunas != NULL && matriz->linhas != NULL){
			for ( i = 1; i <= nr_colunas; i++){
				matriz->colunas[i] = (CELULA *) malloc(sizeof(CELULA));
				matriz->colunas[i]->abaixo = NULL;
			}

			for (i = 1; i <= nr_linhas; i++){
				matriz->linhas[i] = (CELULA *) malloc(sizeof(CELULA));
				matriz->linhas[i]->direita = NULL;
			}
		}
	}

	return matriz;
}

/* 2 */ void apagar_matriz (MATRIZ_ESPARSA *matriz) {
	int i;
	for( i = 0; i < (matriz)->nr_linhas; i++) {
		CELULA *paux = (matriz)->linhas[i]->direita;

		while (paux != NULL){
			CELULA *prem = paux;
			paux = paux->direita;
			free(prem);
		} //libera a memória das posições que continham algum valor

	}

	free((matriz)->linhas);
	free((matriz)->colunas);
	free((matriz));
	matriz = NULL;

}

/* 3 */int set_matriz(MATRIZ_ESPARSA *matriz, int linha, int coluna, double valor) {
		if ( linha <= matriz->nr_linhas && coluna <= matriz->nr_colunas) {  //Condição inicial: linha e coluna estar dentro da linha e coluna da matriz;
			CELULA *paux = matriz->linhas[linha];                         //Cria um ponteiro auxiliar que aponta pra linha desejada;

			while(paux->direita != NULL && paux->direita->coluna <= coluna) {  //
				paux = paux->direita;
			}

			if (paux->coluna == coluna){
				paux->valor = valor;
			} else {
				CELULA *pnovo = (CELULA *) malloc(sizeof(CELULA));
				if (pnovo != NULL) {
					pnovo->linha = linha;
					pnovo-> coluna = coluna;
					pnovo->valor = valor;
					pnovo->direita = paux->direita;
					paux->direita = pnovo;

					paux = matriz->colunas[coluna];
					while (paux->abaixo != NULL && paux->abaixo->linha <= linha) {
						paux = paux->abaixo;
					}

					pnovo->abaixo = paux->abaixo;
					paux->abaixo = pnovo;
				}
			}
			return 1;
		}
		return 0;

}

/* 4 */double get_matriz(MATRIZ_ESPARSA *matriz, int linha, int coluna) {
	if (linha <= matriz->nr_linhas && coluna <= matriz->nr_colunas) {
		CELULA *pauxiliar = matriz->linhas[linha];

		while(pauxiliar->direita != NULL && pauxiliar->direita->coluna <= coluna){
			pauxiliar= pauxiliar->direita;
		}

		if( pauxiliar->coluna == coluna){
			return pauxiliar->valor;
		}
	}
	return 0;
}

/* 5 */MATRIZ_ESPARSA *somar_matriz(MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2) {
    MATRIZ_ESPARSA *matriz = criar_matriz(m1->nr_linhas, m1->nr_colunas);
    if(m1 != NULL && m2 != NULL){

        if(m1->nr_linhas == m2->nr_linhas && m1->nr_colunas == m2->nr_colunas){


            int i,j;
            double d3;
            for( i = 0; i< matriz->nr_linhas;i++){
                for(j = 0; j < matriz->nr_colunas;j++){

                    d3 = get_matriz(m1, i,j) + get_matriz(m2, i, j);

                    set_matriz(matriz, i,j, d3);

                }
            }
        }

        return matriz;
    }
    return NULL;

}

/* 6 */MATRIZ_ESPARSA *multiplicar_matriz( MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2) {
          //  MATRIZ_ESPARSA *m3 = criar_matriz(int lin, int col);
            int lin, col;
            if(m1 != NULL && m2 != NULL){
                if(m1->nr_colunas == m2->nr_linhas){
                    lin = m1->nr_linhas;
                    col = m2->nr_colunas;

                    MATRIZ_ESPARSA *m3 = criar_matriz( lin,  col);

                    int i, a, b;
                    a = 1;
                    b = 1;
                    double val = 0;

                    while(a <= m1->nr_linhas){
                        for( i = 1; i <= m1->nr_colunas; i++){

                            val = val + (get_matriz(m1, a, i)*get_matriz(m2,i,b) );

                        }

                        set_matriz(m3, a, b, val);
                        val = 0;
                        b++;
                        if(b == m2->nr_colunas+1){
                            a++;
                            b=1;
                        }

                    }
                    return m3;
            }
    }
    return NULL;

}

/* 7 */MATRIZ_ESPARSA *transposta_matriz(MATRIZ_ESPARSA *matriz) {
    if( matriz != NULL) {
        MATRIZ_ESPARSA *Matriz_Transp = criar_matriz(matriz->nr_colunas, matriz->nr_linhas);

        int i,j;
        double val;

        for(i = 1; i <= matriz->nr_linhas; i++){
            for(j = 1;j <= matriz->nr_colunas; j++){
                val = get_matriz(matriz, i, j);
                set_matriz(Matriz_Transp, j , i , val);

            }
        }

        return Matriz_Transp;
    }

    return NULL;

}

/* det 3x3 */ double det_3x3(MATRIZ_ESPARSA *matriz) {
    int a, b, i;
            a = 1;
            b = 1;
            double valR = 0, val1 = 1, val2 = 1, val3 = 1;
            double aux;

            for( i = 1; i <= matriz->nr_linhas; i++){
                a = i;
                if( a == 2){
                    b = 1;
                    val1 = val1 * get_matriz(matriz, a, a);
                    val2 = val2 * get_matriz(matriz, a+1, a);
                    val3 = val3 * get_matriz(matriz, b, a);
                } else if (a == 3) {
                    b = 1;
                    val1 = val1 * get_matriz(matriz, a, a);
                    val2 = val2 * get_matriz(matriz, b, a);
                    val3 = val3 * get_matriz(matriz, b+1, a);
                } else {
                    val1 = val1 * get_matriz(matriz, a, a);
                    val2 = val2 * get_matriz(matriz, a+1, a);
                    val3 = val3 * get_matriz(matriz, a+2, a);
                }
            }
            valR = val1+val2+val3;
            aux = valR;
            val1 = 1;
            val2 = 1;
            val3 = 1;
            for( i = 1; i <= matriz->nr_linhas; i++){
                a = i;
                if( a == 2){
                    b = 1;
                    val1 = val1 * get_matriz(matriz, a, a);
                    val2 = val2 * get_matriz(matriz, a+1, a);
                    val3 = val3 * get_matriz(matriz, b, a);

                } else if (a == 3) {
                    b = 1;
                    val1 = val1 * get_matriz(matriz, a, b);
                    val2 = val2 * get_matriz(matriz, b, a);
                    val3 = val3 * get_matriz(matriz, b+1, b);

                } else {
                    val1 = val1 * get_matriz(matriz, a, a+2);
                    val2 = val2 * get_matriz(matriz, a+1, a+2);
                    val3 = val3 * get_matriz(matriz, a+2, a+2);

                }
            }
            valR = val1+val2+val3;

            double det;
            det = aux - valR;
            return det;
}

/* 8 */double determinante_matriz(MATRIZ_ESPARSA *matriz) {
        if(matriz->nr_linhas == matriz->nr_colunas){
            if(matriz->nr_linhas == 1){

                return get_matriz(matriz, 1, 1);

            } else if(matriz->nr_linhas == 2){

                double x = (get_matriz(matriz ,1,2)*get_matriz(matriz,2,2));
                double y = (get_matriz(matriz, 2,2)*get_matriz(matriz,2,1));
                return x-y;

            } else if (matriz->nr_linhas == 3){

               return det_3x3(matriz);

            } else if(matriz->nr_linhas >= 4){
                int col = 1, i,j, lin = 1;
                double det = 0;
                while(lin <= 4){
                    MATRIZ_ESPARSA *maux = criar_matriz(((matriz->nr_linhas) -1) ,((matriz->nr_colunas) - 1));
                    /* VAMOS FAZER TEOREMA DE LAPLACE */

                    double aux;
                    if((lin+col)%2 == 0){
                        aux = get_matriz(matriz,lin, col);
                    } else {
                        aux = (-1)*get_matriz(matriz,lin, col);
                    }

                    double val;
                    for(i = 1; i <= matriz->nr_linhas; i++){
                        if(i != lin){
                            for(j= 1;j <= matriz->nr_colunas; j++){
                                if(j != 1){
                                    val = get_matriz(matriz, i, j);
                                    if(i >= lin){
                                        set_matriz( maux, i-1, j-1, val);
                                    } else {
                                        set_matriz(maux, i, j-1, val);
                                    }
                                }
                            }
                        }
                    }

                    //printf("   %lf   \n\n", determinante_matriz(maux));
                    det = det + aux*determinante_matriz(maux);
                     /*for(i = 1; i <= maux->nr_linhas; i++){
                        for(j = 1; j <= maux->nr_colunas; j++){
                            printf(" %lf ", get_matriz(maux, i, j));
                        }
                        printf(" \n");
                    }
                    printf("\n\n");  */
                    lin++;
                }
                //printf( " %lf  ", det);


            }
        }
        return 0;
}

/* 9 */ void print_matriz(MATRIZ_ESPARSA *matriz){
    int i, j;
    for( i = 1; i<= matriz->nr_linhas; i++){
        for( j = 1; j <= matriz->nr_colunas; j++){
            printf("%lf ", get_matriz(matriz,i, j));
        }
        printf("\n");
    }
}

/* 10 */ void resumo_matriz(MATRIZ_ESPARSA *matriz){
    int i, j;
    for(i = 1; i<= matriz->nr_linhas; i++){
        for(j = 1; j <= matriz->nr_colunas; j++){
            if(get_matriz(matriz, i, j) != 0){
                printf("%lf ", get_matriz(matriz,i, j));
            }
        }
    }
}

/* 11 */ MATRIZ_ESPARSA *ler_matriz(const char nome[]) {

    FILE *file;
    file = fopen(nome, "r");

    int lin, col;
    fscanf(file,"%d %d", &lin, &col);
    int i, j;
    MATRIZ_ESPARSA *m = (MATRIZ_ESPARSA*)malloc(sizeof(MATRIZ_ESPARSA));

     m = criar_matriz(lin, col);
    for(i = 0; i < lin; i++){
        for(j = 0; j < col; j++){
            double num;
            fscanf(file,"%lf", &num);
            printf(" %f", num);
            set_matriz(m, i, j, num);
        }
    }
    fclose(file);

    return m;
}
