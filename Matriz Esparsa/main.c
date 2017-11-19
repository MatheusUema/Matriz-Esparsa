#include <stdio.h>
#include <stdlib.h>

#include "matriz_esparsa.h"

/*
 *
 */
int main(int argc, char** argv) {
  MATRIZ_ESPARSA *matriz, *matriz2, *matriz3, *matriz4;

  matriz = ler_matriz("m1.txt");

  /* matriz = ler_matriz("m1.txt");
  matriz2 = somar_matriz(matriz, matriz);
  matriz3 = multiplicar_matriz(matriz2, matriz2);

  printf("Matriz 1\n");
  print_matriz(matriz);
  printf("Soma \n");
  print_matriz(matriz2);
  printf("Multiplicação\n");
  print_matriz(matriz3);
  printf("Transposta\n");
  print_matriz(transposta_matriz(matriz3));

  apagar_matriz(matriz);
  apagar_matriz(matriz2);
  apagar_matriz(matriz3);

  matriz = ler_matriz("m50x50.txt");
  matriz2 = somar_matriz(matriz, matriz);
  matriz3 = multiplicar_matriz(matriz2, matriz2);

  printf("Matriz 50x50\n");
  resumo_matriz(matriz);
  printf("Soma \n");
  resumo_matriz(matriz2);
  printf("Multiplicação\n");
  resumo_matriz(matriz3);
  printf("Transposta\n");
  resumo_matriz(transposta_matriz(matriz3));




  matriz4 = ler_matriz("m4x4.txt");
  printf("Matriz 4x4\n");
  print_matriz(matriz4);
  printf("Determinante: %lf\n", determinante_matriz(matriz4));

  apagar_matriz(matriz);
  apagar_matriz(matriz2);
  apagar_matriz(matriz3);
  apagar_matriz(matriz4);   */


  return (EXIT_SUCCESS);
}
