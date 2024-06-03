// UP, DOWN, LEFT, RIGHT Ű�� ����
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
// �ʿ��� ��� ���� ����
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
// gotoxy �Լ�: �ܼ��� Ŀ�� ��ġ�� ����
void gotoxy(int x, int y){
	COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// dx, dy �迭: 8���� �˻縦 ���� ��ǥ
int dx[9] = {0, 1, 1, 1, 0, -1, -1, -1}, dy[9] = {-1, -1, 0, 1, 1, 1, 0, -1};

// field 2���� �迭: ���� ����
int field[1001][1001] = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
						 {'A', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'B', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'C', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'D', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'E', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'F', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'G', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'H', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'I', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'J', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'K', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'L', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'M', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'N', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {'O', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
						 
// print_field �Լ�: ���� ���带 �ֿܼ� ���
void print_field()
{
	int i, j;
	for (i = 0; i <= 15; i++)
	{
		for (j = 0; j <= 15; j++)
		{
			if (field[i][j] >= 1 && field[i][j] <= 15){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("%2d ", field[i][j]);
			}
			else if (field[i][j] == 0){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				printf("%2c ", '-');
			}
			else if (field[i][j] == -1){//X��ġ
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf("%2c ", 'X');
			}

			// printf(" \u25CF ");
			else if (field[i][j] == -2){//O��ġ
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf("%2c ", 'O');
			}
			else if (field[i][j] == -3)//X����
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("%2c ", 'X');
			}
			else if (field[i][j] == -4)//O����
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("%2c ", 'O');
			}
			else if (field[i][j] == -5)//X�Ұ���
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("%2c ", 'X');
			}
			else if (field[i][j] == -6)//O�Ұ���
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("%2c ", 'O');
			}
			else{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("%2c ", field[i][j]);
			}
		}
		printf("\n");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
// checkfive �Լ�: 5��(gomok)�� �˻�
int checkfive(int color)
{
	int i, j, d, check = 1, x1, y1, k;
	for (i = 1; i <= 15; i++)
	{
		for (j = 1; j <= 15; j++)
		{
			if (field[i][j] == color)
			{
				check = 1;
				for (d = 0; d < 8; d++)
				{
					if (field[i + dy[d]][j + dx[d]] == color)
					{
						y1 = i;
						x1 = j;
						while (field[y1 + dy[d]][x1 + dx[d]] == color)
						{
							y1 = y1 + dy[d];
							x1 = x1 + dx[d];
							check++;
							if (color == -2 && check == 5)
								if (field[y1 + dy[d]][x1 + dx[d]] == color)
								{
									check = -1;
									return -1;
								}
							if (check == 5)
								break;
						}
						if (check == 5)
						{
							y1 = i;
							x1 = j;
							int ck = 1;
							// printf("[%d]", d);
							while (field[y1 + dy[d]][x1 + dx[d]] == color)
							{
								field[y1][x1] = color - 2;
								y1 = y1 + dy[d];
								x1 = x1 + dx[d];
								ck++;
								if (ck == 6)
									break;
							}
							field[y1][x1] = color - 2;

							return color;
						}
						else
							break;
					}
				}
			}
		}
	}
	return 0;
}
char y, cy, b;
int x, a, cx, chk;
// main �Լ�: ���� ����
int main()
{
	system("cls");
	int ch = 0;
	int i, j, turn = -2;
	int running = 1;
	while (running)
	{
		if (turn == -2)//O
		{
		aa:
			x = 7;
			y = 'H';
			while (1)
			{
				int original;
				original = field[y - 'A' + 1][x];
				if(original!=0)
					field[y-'A'+1][x] = -6;
				else
					field[y - 'A' + 1][x] = -4;
				gotoxy(0, 0);
				print_field();
				field[y - 'A' + 1][x] = original;
				printf("O turn!\n");
				int key = _getch();
				switch (key)
				{
				case 13:
					break;
				case LEFT:
					if (1 <= x - 1 && x - 1 <= 15)
						x--;
					break;
				case RIGHT:
					if (1 <= x + 1 && x + 1 <= 15)
						x++;
					break;
				case UP:
					if (1 <= (y - 1 - 'A' + 1) && (y - 1 - 'A' + 1) <= 15)
						y--;
					break;
				case DOWN:
					if (1 <= (y + 1 - 'A' + 1) && (y + 1 - 'A' + 1) <= 15)
						y++;
					break;
				}
				if (key == 13 && field[y - 'A' + 1][x] == 0)
				{ // enter
					field[y - 'A' + 1][x] = -2;
					ch++;
					break;
				}
			}
			chk = checkfive(-2);
			switch (chk)
			{
			case -2:
				gotoxy(0, 0);
				print_field();
				printf("O WIN  ");
				running = 0;
				break;
			case -1:
				gotoxy(0, 0);
				field[y - 'A' + 1][x] = 0;
				print_field();
				printf("6���� ���� �����Դϴ�. �ٽ� �Է����ּ���.\n");
				Sleep(1000);
				goto aa;
			default:
				turn = -1;
			}
		}
		else//x
		{
			x = 7;
			y = 'H';
			while (1)
			{
				int original;
				original = field[y - 'A' + 1][x];
				if(original!=0)
					field[y-'A'+1][x] = -5;
				else
					field[y - 'A' + 1][x] = -3;
				gotoxy(0, 0);
				
				// system("cls");
				print_field();
				// printf("%d %d\n", y - 'A' + 1, x);
				field[y - 'A' + 1][x] = original;
				printf("X turn!\n");
				int key = _getch();
				switch (key)
				{
				case 13:
					break;
				case LEFT:
					if (1 <= x - 1 && x - 1 <= 15)
						x--;
					break;
				case RIGHT:
					if (1 <= x + 1 && x + 1 <= 15)
						x++;
					break;
				case UP:
					if (1 <= (y - 1 - 'A' + 1) && (y - 1 - 'A' + 1) <= 15)
						y--;
					break;
				case DOWN:
					if (1 <= (y + 1 - 'A' + 1) && (y + 1 - 'A' + 1) <= 15)
						y++;
					break;
				}
				if (key == 13 && field[y - 'A' + 1][x] == 0)
				{ // enter
					field[y - 'A' + 1][x] = -1;
					ch++;
					break;
				}
			}
			field[y - 'A' + 1][x] = -1;
			chk = checkfive(-1);
			switch (chk)
			{
			case -1:
				gotoxy(0, 0);
				print_field();
				printf("X WIN  ");
				running = 0;
				break;
			default:
				turn = -2;
			}
		}
	}
}