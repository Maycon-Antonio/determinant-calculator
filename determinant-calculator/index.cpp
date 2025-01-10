#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

#define ORDEM_MATRIZ 10

#define C_RESET     "\x1b[0m"
#define C_BLACK     "\033[30m"
#define BG_GRAY     "\033[47m"

typedef struct {
	char direcao;
	int posicao;
}Vetor;

void abertura () {
	printf("-------------------------------\n");
	printf("| CALCULADORA DE DETERMINANTE |\n");
	printf("|         (MATRIZES)          |\n");
	printf("-------------------------------");
	printf("\n\n\n\nPressione ENTER para continuar ->");
	getch();
	system("cls");
}

void inicializarMatriz (float matriz[ORDEM_MATRIZ][ORDEM_MATRIZ], int ordem) {
	for (int i = 0; i < ordem; i++) {
		for (int j = 0; j < ordem; j++) {
			matriz[i][j] = 0;
		}
	}
}

void imprimirMatriz (float matriz[ORDEM_MATRIZ][ORDEM_MATRIZ], int ordem, int linha, int coluna) {
	for (int i = 0; i < ordem; i++) {
		printf("| ");
		for (int j = 0; j < ordem; j++) {
			if (i == linha && j == coluna) {
				printf(BG_GRAY C_BLACK "%.1f" C_RESET, matriz[i][j]);
				printf(" ");
			} else {
				printf("%.1f ", matriz[i][j]);
			}
		}
		printf("|\n");
	}
}

void imprimirMatriz (float matriz[ORDEM_MATRIZ][ORDEM_MATRIZ], int ordem) {
	for (int i = 0; i < ordem; i++) {
		printf("| ");
		for (int j = 0; j < ordem; j++) {
			printf("%.1f ", matriz[i][j]);
		}
		printf("|\n");
	}
}

void preencherMatriz (float matriz[ORDEM_MATRIZ][ORDEM_MATRIZ], int ordem) {
	for (int i = 0; i < ordem; i++) {
		for (int j = 0; j < ordem; j++) {
			printf("\tMATRIZ\n");
			imprimirMatriz(matriz, ordem, i, j);
			printf("\nInforme os valores:\n");
			scanf("%f", &matriz[i][j]);
			system("cls");
		}
	}
	printf("\tMATRIZ\n");
	imprimirMatriz(matriz, ordem);
	Sleep(1000);
	system("cls");
}

Vetor encontrarMelhorVetor (float matriz[ORDEM_MATRIZ][ORDEM_MATRIZ], int ordem) {
	Vetor melhorVetor;
	melhorVetor.direcao = 'x';
	melhorVetor.posicao = 0;
	int quantidadeDeZerosX, quantidadeDeZerosY, maior = 0;
	for (int i = 0; i < ordem; i++) {
		quantidadeDeZerosX = 0;
		quantidadeDeZerosY = 0;
		for (int j = 0; j < ordem; j++) {
			if (matriz[i][j] == 0) {
				quantidadeDeZerosX++;
			}
			if (matriz[j][i] == 0) {
				quantidadeDeZerosY++;
			}
		}
		if (quantidadeDeZerosX > maior) {
			maior = quantidadeDeZerosX;
			melhorVetor.direcao = 'x';
			melhorVetor.posicao = i;
		}
		if (quantidadeDeZerosY > maior) {
			maior = quantidadeDeZerosY;
			melhorVetor.direcao = 'y';
			melhorVetor.posicao = i;
		}
	}
	return melhorVetor;
}

float calcularDeterminante (float matriz[ORDEM_MATRIZ][ORDEM_MATRIZ], int ordem) {
    float determinante = 0;
    float subMatriz[ORDEM_MATRIZ][ORDEM_MATRIZ];
    if (ordem == 1) {
        determinante = matriz[0][0];
    } else if (ordem == 2){
        determinante = (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
    } else if (ordem == 3) {
        determinante = (
            (matriz[0][0] * matriz[1][1] * matriz[2][2]) +
            (matriz[0][1] * matriz[1][2] * matriz[2][0]) +
            (matriz[0][2] * matriz[1][0] * matriz[2][1])
        ) - (
            (matriz[0][2] * matriz[1][1] * matriz[2][0]) +
            (matriz[0][0] * matriz[1][2] * matriz[2][1]) +
            (matriz[0][1] * matriz[1][0] * matriz[2][2])
        );
    } else {
    	Vetor melhorVetor = encontrarMelhorVetor(matriz, ordem);
    	char direcao = melhorVetor.direcao;
    	int posicao = melhorVetor.posicao;
        for (int n = 0; n < ordem; n++) {
        	if ((direcao == 'x' && matriz[posicao][n] == 0) || (direcao == 'y' && matriz[n][posicao] == 0)) {
        		continue;
			}
            int subI = 0;
            for (int i = 0; i < ordem; i++) {
                int subJ = 0;
                for (int j = 0; j < ordem; j++) {
                	if (direcao == 'x') {
                		if (i == posicao) {
                			subI--;
                			break;
						}
	                    if (j == n) {
	                        continue;
	                    }
	                } else if (direcao == 'y') {
	                	if (i == n) {
                			subI--;
                			break;
						}
	                    if (j == posicao) {
	                        continue;
	                    }
					}
                    subMatriz[subI][subJ] = matriz[i][j];
                    subJ++;
                }
                subI++;
            }
            float cofator = pow(-1, n + posicao) * calcularDeterminante(subMatriz, ordem - 1);
            if (direcao == 'x') {
            	determinante += matriz[posicao][n] * cofator;
		    } else if (direcao == 'y') {
		    	determinante += matriz[n][posicao] * cofator;
		    }
        }
    }
    return determinante;
}

main () {
	setlocale(LC_ALL, "Portuguese");
	SetConsoleTitle("Calculadora de Determinante");
	float matriz[ORDEM_MATRIZ][ORDEM_MATRIZ], determinante;
	int ordem;
	char continuar;
	abertura();
	do {
		printf("Informe a ordem da matriz:\n");
		scanf("%d", &ordem);
		system("cls");
		if (ordem <= 0) {
			printf("Ordem da matriz inválida!");
			printf("\n\n\n\nPressione ENTER para continuar ->");
			getch();
			system("cls");
			continue;
		}
		inicializarMatriz(matriz, ordem);
		preencherMatriz(matriz, ordem);
		determinante = calcularDeterminante(matriz, ordem);
		printf("O determinante da matriz:\n\n");
		imprimirMatriz(matriz, ordem);
		printf("\né: %.1f.", determinante);
		printf("\n\n\n\nPressione ENTER para continuar ->");
		getch();
		system("cls");
		printf("Calcular novamente (s/n)?\n");
		fflush(stdin);
		scanf("%c", &continuar);
		continuar = tolower(continuar);
		system("cls");
	}while (continuar == 's');
}

/*main () {
	setlocale(LC_ALL, "Portuguese");
	SetConsoleTitle("Calculadora de Determinante");
	float matriz1[ORDEM_MATRIZ][ORDEM_MATRIZ] = {
		{ 2 }
	};
	float matriz2[ORDEM_MATRIZ][ORDEM_MATRIZ] = {
		{ 2 , 3 },
		{ 4 , 1 }
	};
	float matriz3[ORDEM_MATRIZ][ORDEM_MATRIZ] = {
		{ 1 , 2 , 3 },
		{ 4 , 5 , 6 },
		{ 7 , 8 , 9 }
	};
	float matriz4[ORDEM_MATRIZ][ORDEM_MATRIZ] = {
		{ 1 , 0 , 0 , 3 },
		{ 2 , 3 , 5 , 1 },
		{ 1 , 2 , 3 ,-1 },
		{ 3 , 0 , 1 , 4 }
	};
	float matriz10[ORDEM_MATRIZ][ORDEM_MATRIZ] = {
		{ 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 },
		{ 2 , 4 , 6 , 8 , 10 , 1 , 3 , 5 , 7 , 9 },
		{ 3 , 6 , 9 , 1 , 4 , 7 , 10 , 2 , 5 , 8 },
		{ 4 , 8 , 1 , 5 , 9 , 2 , 6 , 10 , 3 , 7 },
		{ 5 , 10 , 4 , 9 , 3 , 8 , 2 , 6 , 1 , 7 },
		{ 6 , 1 , 7 , 2 , 8 , 3 , 9 , 4 , 10 , 5 },
		{ 7 , 3 , 10 , 6 , 2 , 9 , 4 , 8 , 1 , 5 },
		{ 8 , 5 , 2 , 10 , 6 , 4 , 1 , 3 , 7 , 9 },
		{ 9 , 7 , 5 , 3 , 1 , 8 , 6 , 2 , 10 , 4 },
		{ 10 , 9 , 8 , 7 , 5 , 6 , 4 , 1 , 2 , 3 }
	};
	float determinante;
	abertura();
	determinante = calcularDeterminante(matriz10, 10);
	printf("O determinante da matriz:\n\n");
	imprimirMatriz(matriz10, 10);
	printf("\né: %.1f.", determinante);
	printf("\n\n\n\nPressione ENTER para continuar ->");
	getch();
	system("cls");
}*/
