#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

/* 
	-------------- RESTRIÇÔES --------------
	
	--> Resultado da multiplicação de matrizes só existe se o número de colunas da primeira for igual ao número de linhas da segunda
	--> Só será possível somar duas matrizes quando elas forem iguais em "n" e "m"
*/

// Pega o tamanho da matriz (n x m) através de arquivo 
void get_size(int *n1, int *m1, int *n2, int *m2){
	char *txt = "sizes.txt";
	FILE *arq;
	
	arq = fopen(txt, "r");
	
	if(arq == NULL){
		printf("\n Não foi possível abrir o arquivo.");
		return;
	}else{
		fscanf(arq, "%d %d", n1, m1);
		fscanf(arq, "%d %d", n2, m2);
	}
	
	fclose(arq);
	
}

// Printa a matriz
void print_mat(int n, int m, int matriz[n][m]){
	int i, j;
	
	printf("\n");
	for(i = 0; i < n; i ++){
		printf("\n");
		for(j = 0; j < m; j ++){
			printf(" %d", matriz[i][j]);
		}
	}

}

// Sorteia todas as posições da matriz
void sort_mat(int n, int m, int matriz[n][m]){
	int i, j;

	for(i = 0; i < n; i ++){
		for(j = 0; j < m; j ++){
			matriz[i][j] = rand()%10 + 1;
		}
	}
	
}

// Multiplicação de matriz
void mult_mat(int n1, int m1, int n2, int m2, int matriz1[n1][m1], int matriz2[n2][m2], int m12[m1][n2], int cond){
	int temp = 0, i, j, k;
	
	if(cond == 0){   // A.B
		for(i = 0; i < m1; i ++){
			for(j = 0; j < n2; j ++){
				temp = 0;
				for(k = 0; k < n2; k ++){
					temp += matriz1[i][k] * matriz2[k][j];
					
				}
				m12[i][j] = temp;
			}
		}
		printf("\n\n Resultado de A.B: ");
		print_mat(n1, m2, m12);
	}else{   // B.A
		for(i = 0; i < n1; i ++){
			for(j = 0; j < m2; j ++){
				temp = 0;
				for(k = 0; k < m1; k ++){
					temp += matriz2[i][k] + matriz1[k][j];	
				}
				m12[i][j] = temp;
			}
		}
		printf("\n\n Resultado de B.A: ");
		print_mat(n1, m2, m12);
	}
	
}

// Multiplica a matriz por um escalar
void mult_scale_mat(int n, int m, int matriz[n][m], int escalar){
	int i, j;
	
	for(i = 0; i < n; i ++){
		for(j = 0; j < m; j ++){
			matriz[i][j] *= escalar;
		}
	}
	printf("\n\n Multiplicado pelo escalar: %d", escalar);
	print_mat(n, m, matriz);
	
}

// Soma duas matrizes
void sum_mats(int n, int m, int matrizA[n][m], int matrizB[n][m], int cond){
	int i, j;
	
	if(cond == 0){  // A + B
		for(i = 0; i < n; i ++){
			for(j = 0; j < m; j ++){
				matrizA[i][j] += matrizB[i][j];
			}
		}
		printf("\n\n Resultado de A+B: ");
		print_mat(n, m, matrizA);
	}else if(cond == 1){  // B + A
		for(i = 0; i < n; i ++){
			for(j = 0; j < m; j ++){
				matrizB[i][j] += matrizA[i][j];
			}
		}
		printf("\n\n Resultado de B+A: ");
		print_mat(n, m, matrizB);
	}else{
		printf("\n\n Operação não reconhecida!!\n");
	}
}

// Soma a matriz por um escalar
void sum_scale_mat(int n, int m, int matriz[n][m], int escalar){
	int i, j;
	
	for(i = 0; i < n; i ++){
		for(j = 0; j < m; j ++){
			matriz[i][j] += escalar;
		}
	}
	printf("\n\n Somado pelo escalar: %d", escalar);
	print_mat(n, m, matriz);
	
}

// Mostra o menu
void menu(int n1, int m1, int n2, int m2, int matrizA[n1][m1], int matrizB[n2][m2]){
	printf("\n A[%d][%d]", n1, m1);
	print_mat(n1, m1, matrizA);
	printf("\n\n B[%d][%d]", n2, m2);
	print_mat(n2, m2, matrizB);
	
	printf("\n\n Menu de matrizes:");
	printf("\n 1 - Multiplicação A.B");
	printf("\n 2 - Multiplicação B.A");
	printf("\n 3 - Multiplicação A.Escalar");
	printf("\n 4 - Multiplicação B.Escalar");
	printf("\n 5 - Adição A+B");
	printf("\n 6 - Adição B+A");
	printf("\n 7 - Adição A + Escalar");
	printf("\n 8 - Adição B + Escalar");
	printf("\n 0 - Sair\n :");
	
}

int main(){
	srand(time(NULL));
	setlocale(LC_ALL, "portuguese");
	
	int n1, m1, n2, m2; // n = número de linhas da matriz    ||   m = número de colunas da matriz
	int cond = 1, escalar;
	
	get_size(&n1, &m1, &n2, &m2);
	
	int matrizA[n1][m1], matrizB[n2][m2], matrizR[m1][n2];  // Matrizes
	
	sort_mat(n1, m1, matrizA);
	sort_mat(n2, m2, matrizB);
	
	menu(n1, m1, n2, m2, matrizA, matrizB);
	scanf("%d", &cond);

	switch(cond){
		case 1:  // Mult A.B
			if(m1 == n2){
				mult_mat(n1, m1, n2, m2, matrizA, matrizB, matrizR, 0);
			}else{
				printf("\n\n Não é possível fazer a multiplicação!!\n");
			}
		break;
		
		case 2:  // Mult B.A
			if(m1 == n2){
				mult_mat(n1, m1, n2, m2, matrizA, matrizB, matrizR, 1);
			}else{
				printf("\n\n Não é possível fazer a multiplicação!!\n");
			}
		break;
		
		case 3:  // Mult A.Escalar
			printf("\n Digite o escalar: ");
			scanf("%d", &escalar);
			mult_scale_mat(n1, m1, matrizA, escalar);
		break;
		
		case 4:  // Mult B.Escalar
			printf("\n Digite o escalar: ");
			scanf("%d", &escalar);
			mult_scale_mat(n2, m2, matrizA, escalar);
		break;
		
		case 5:  // Adic A+B
			if(n1 == n2 && m1 == m2){
				sum_mats(n1, m1, matrizA, matrizB, 0);
			}else{
				printf("\n\n Não é possível fazer a adição!!\n");
			}
		break;
		
		case 6:  // Adic B+A
			if(n1 == n2 && m1 == m2){
				sum_mats(n2, m2, matrizA, matrizB, 1);
			}else{
				printf("\n\n Não é possível fazer a adição!!\n");
			}
		break;
		
		case 7:  // Adic A+Escalar
			printf("\n Digite o escalar: ");
			scanf("%d", &escalar);
			sum_scale_mat(n1, m1, matrizA, escalar);
		break;
		
		case 8:  // Adic B+Escalar
			printf("\n Digite o escalar: ");
			scanf("%d", &escalar);
			sum_scale_mat(n2, m2, matrizB, escalar);
		break;

	}
	
	printf("\n\n\n >>>>> FIM DO PROGRAMA <<<<<\n\n");
	return 0;
	
}
