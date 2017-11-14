// Fill out your copyright notice in the Description page of Project Settings.

#include "TheArena2.h"
#include "ArenaGameMode.h"



#include<stdio.h>
#include<conio.h>
void newMatriz(int Matriz[]){ 
	int  j, i;
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
			Matriz[i][j] = ' ';
}

void printFirst(int Matriz[]){
	printf(" JOGO DA VELHA \n");
	for (int i = 0; i<3; i++)
	{
		printf("\t\t %c \xBA %c \xBA %c\n", Matriz[i][0], Matriz[i][1], Matriz[i][2]);
		if (i<3 - 1)
		{
			printf("\t\t ÍÍÍ\xCEÍÍÍ\xCEÍÍÍ\n");
		}
	}
}

int doSomething(int l, int Matriz[], char O, char X){
	if (Matriz[i - 1][j - 1] == ' ')
	{
		if (l % 2)Matriz[i - 1][j - 1] = X;
		else Matriz[i - 1][j - 1] = O;
		l++;
	}
	return l;
}

int main(void)
{
	char Matriz[3][3];
	char O = 'O', X = 'X';
	int l = 0;
	int i = 3, j = 3;
	newMatriz(Matriz);

	while (l <= 9)
	{
		printFirst();

		printf("\n\n\n\n\n\n\n\n\n\n\n\nINSIRA AS COORDENADAS, ");
		if (l % 2)printf("PLAYER 2\nLINHA: ");
		else printf("PLAYER 1\nLINHA: ");

		scanf("%d", &i);
		printf("COLUNA: ");
		scanf("%d", &j);

		if (Matriz[i - 1][j - 1] == ' ')
		{
			if (l % 2)Matriz[i - 1][j - 1] = X;
			else Matriz[i - 1][j - 1] = O;
			l++;
		}

		l = doSomething(l, Matriz, O, X);

		if ((Matriz[0][0] == O && Matriz[0][1] == O && Matriz[0][2] == O) ||
			(Matriz[1][0] == O && Matriz[1][1] == O && Matriz[1][2] == O) ||
			(Matriz[2][0] == O && Matriz[2][1] == O && Matriz[2][2] == O) ||
			(Matriz[0][0] == O && Matriz[1][0] == O && Matriz[2][0] == O) ||
			(Matriz[0][1] == O && Matriz[1][1] == O && Matriz[2][1] == O) ||
			(Matriz[0][2] == O && Matriz[1][2] == O && Matriz[2][2] == O) ||
			(Matriz[0][0] == O && Matriz[1][1] == O && Matriz[2][2] == O) ||
			(Matriz[0][2] == O && Matriz[1][1] == O && Matriz[2][0] == O))
		{
			printf("\n\a\t\tJogador 1, VOCE VENCEU!!!");
			break;
		}
		if ((Matriz[0][0] == X && Matriz[0][1] == X && Matriz[0][2] == X) ||
			(Matriz[1][0] == X && Matriz[1][1] == X && Matriz[1][2] == X) ||
			(Matriz[2][0] == X && Matriz[2][1] == X && Matriz[2][2] == X) ||
			(Matriz[0][0] == X && Matriz[1][0] == X && Matriz[2][0] == X) ||
			(Matriz[0][1] == X && Matriz[1][1] == X && Matriz[2][1] == X) ||
			(Matriz[0][2] == X && Matriz[1][2] == X && Matriz[2][2] == X) ||
			(Matriz[0][0] == X && Matriz[1][1] == X && Matriz[2][2] == X) ||
			(Matriz[0][2] == X && Matriz[1][1] == X && Matriz[2][0] == X))
		{
			printf("\n\n\n\n\a\t\tJogador 2, VOCE VENCEU!!!");
			break;
		}

		if (l == 9)
		{
			printf("PARTIDA EMPATADA");
			break;
		}

	}
	getch();
	return(0);
}
