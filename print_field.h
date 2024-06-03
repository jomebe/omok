#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
void print_field(int **field)
{
	int i, j;
	for (i = 0; i <= 15; i++)
	{
		for (j = 0; j <= 15; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			if (field[i][j] >= 1 && field[i][j] <= 15)
				printf("%2d ", field[i][j]);
			else if (field[i][j] == 0)
				printf("%2c ", '-');
			else if (field[i][j] == -1)
				printf("%2c ", 'X');
			// printf(" \u25CF ");
			else if (field[i][j] == -2)
				printf("%2c ", 'O');
			else if (field[i][j] == -3)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("%2c ", 'X');
			}
			else if (field[i][j] == -4)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("%2c ", 'O');
			}
			else
				printf("%2c ", field[i][j]);
		}
		printf("\n");
	}
}