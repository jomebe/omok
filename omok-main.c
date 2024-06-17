// UP, DOWN, LEFT, RIGHT 키를 정의
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
// 필요한 헤더 파일 포함

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>


// gotoxy 함수: 콘솔의 커서 위치를 설정
void gotoxy(int x, int y){
    COORD pos={x,y}; //x, y 좌표 설정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //커서 설정
}

// dx, dy 배열: 8방향 검사를 위한 좌표
int dx[9] = { 0, 1, 1, 1, 0, -1, -1, -1 }, dy[9] = { -1, -1, 0, 1, 1, 1, 0, -1 };
// field 2차원 배열: 게임 보드
int field[101][101] = { {0, 1000001, 1000002, 1000003, 1000004, 1000005, 1000006, 1000007, 1000008, 1000009, 1000010, 1000011, 1000012, 1000013, 1000014, 1000015},
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
						 {'O', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

// print_field 함수: 게임 보드를 콘솔에 출력
void print_field()
{
	int i, j;
	for (i = 0; i <= 15; i++)
	{
		for (j = 0; j <= 15; j++)
		{
			if (field[i][j] >= 1000001 && field[i][j] <= 1000015) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("%2d ", field[i][j]-1000000);
			}
			else if (field[i][j] == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				printf("%2c ", '-');
			}
			else if (field[i][j] == -1) {//X설치
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf("%2c ", 'X');
			}
			// printf(" \u25CF ");
			else if (field[i][j] == -2) {//O설치
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf("%2c ", 'O');
			}
			else if (field[i][j] == -3)//X예상
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("%2c ", 'X');
			}
			else if (field[i][j] == -4)//O예상
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("%2c ", 'O');
			}
			else if (field[i][j] == -5)//X불가능
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("%2c ", 'X');
			}
			else if (field[i][j] == -6)//O불가능
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("%2c ", 'O');
			}
			else if (field[i][j] == -7) {//X방금설치
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("%2c ", 'X');
			}
			// printf(" \u25CF ");
			else if (field[i][j] == -8) {//O방금설치
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("%2c ", 'O');
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("%2c ", field[i][j]);
			}
		}
		printf("\n");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
// checkfive 함수: 5목(gomok)을 검사
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
                            if (color == -2 && check == 6)
                                return -1; // 6-in-a-row rule violated
                            if (check == 5)
                                break;
                        }
                        if (check == 5)
                        {
                            y1 = i;
                            x1 = j;
                            int ck = 1;
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
void AIcacl(int arr[101][101]){
	int i,j;
	int min=INT_MAX;
	int minx,miny;
	for (i = 1; i <= 15; i++){
		//printf("%d",i);
		for (j = 1; j <= 15; j++){
			if(arr[i][j]<min){
				min=arr[i][j];
				miny=i;
				minx=j;
			}
        }
	}
	field[miny][minx]=-1;
	printf("\n%c %d\n",miny+'A'-1,minx);

}
int omokAI(){
	int ai_field[101][101]={0};
	int i,j,d;
	for (i = 1; i <= 15; i++){
		for (j = 1; j <= 15; j++){
			if(field[i][j]==-2){//흑돌 O
				for(d=0;d<8;d++){
					if(field[i+dy[d]][j+dx[d]]==0)
						ai_field[i+dy[d]][j+dx[d]]--;
				}
			}
			if(field[i][j]==-1){//백돌 X
				for(d=0;d<8;d++){
					if(field[i+dy[d]][j+dx[d]]==0)
						ai_field[i+dy[d]][j+dx[d]]++;
				}
			}
        }
	}
	int isthree = 0;
	int isjumpthree = 0;
	int isattacktwo =0;
		for (i = 1; i <= 15; i++){//5목 공격
			for (j = 1; j <= 15; j++){
				int tcnt=0;
				int tx,ty;//흑돌 O
					for(d=0;d<8;d++){
						tx=j;
						ty=i;
						tcnt=0;
						while(tcnt!=4 && field[ty][tx]==-1){
							tcnt++;
							tx+=dx[d];
							ty+=dy[d];
						}
						if(tcnt==4){//AI돌이 4개가 연속으로 있을때
							if(field[i-dy[d]][j-dx[d]]==0){//앞에다두기
								ai_field[i-dy[d]][j-dx[d]]-=50;
								AIcacl(ai_field);
								return 0;
							}
							else if(field[ty][tx]==0){//뒤에다두기
								ai_field[ty][tx]-=50;
								AIcacl(ai_field);
								return 0;
							}
						}
					}
			}
		}
	//뛴 삼목이랑 삼목이 아닐때 4목 공격
		for (i = 1; i <= 15; i++){
			for (j = 1; j <= 15; j++){
				int tcnt=0;
				int tx,ty;//흑돌 O
				for(d=0;d<8;d++){
					tx=j;
					ty=i;
					tcnt=0;
					while(tcnt!=3 && field[ty][tx]==-1){
						tcnt++;
						tx+=dx[d];
						ty+=dy[d];
					}
					if(tcnt==3){//AI돌이 3개가 연속으로 있을때
						if(field[i-2*dy[d]][j-2*dx[d]]!=-2){//둘곳의앞이 유저의 돌이 아닐때
							if(field[i-dy[d]][j-dx[d]]==0){//앞에다두기
								ai_field[i-dy[d]][j-dx[d]]-=50;
								AIcacl(ai_field);
								return 0;
							}
						}
						else if(field[ty+dy[d]][tx+dx[d]]!=-2){
								if(field[ty][tx]==0){//뒤에다두기
								ai_field[ty][tx]-=50;
								AIcacl(ai_field);
								return 0;
							}
						}
					}
				}
			}
		}
	for (i = 1; i <= 15; i++){//3목 방어
		for (j = 1; j <= 15; j++){
			int tcnt=0;
			int tx,ty;//흑돌 O
				for(d=0;d<8;d++){
					tx=j;
					ty=i;
					tcnt=0;
					while(tcnt!=3 && field[ty][tx]==-2){
						tcnt++;
						tx+=dx[d];
						ty+=dy[d];
					}
					if(tcnt==3){
						if(field[i-dy[d]][j-dx[d]]==0){
						    ai_field[i-dy[d]][j-dx[d]]-=50;
							AIcacl(ai_field);
							return 0;
						}
						else if(field[ty][tx]==0){
						    ai_field[ty][tx]-=50;
							AIcacl(ai_field);
							return 0;
						}
					}
				}
        }
	}

	for (i = 1; i <= 15; i++){//뛴 3목 방어
		for (j = 1; j <= 15; j++){
			int tcnt=0;
			int tx,ty;//흑돌 O
				for(d=0;d<8;d++){
					tx=j;
					ty=i;
					tcnt=0;
					while(tcnt!=2 && field[ty][tx]==-2){
						tcnt++;
						tx+=dx[d];
						ty+=dy[d];
					}
					if(field[ty+dy[d]][tx+dx[d]]==-2 && tcnt==2){
						isjumpthree=1;
						if(field[ty][tx]==0){
						    ai_field[ty][tx]-=50;
							AIcacl(ai_field);
							return 0;
						}
						else if(field[i-dy[d]][j-dx[d]]==0){
						    ai_field[i-dy[d]][j-dx[d]]-=50;
							AIcacl(ai_field);
							return 0;
						}
						else if(field[ty+2*dy[d]][tx+2*dx[d]]==0){
						    ai_field[ty+2*dy[d]][tx+2*dx[d]]-=50;
							AIcacl(ai_field);
							return 0;
						}
					}
				}
        }
	}
	
	
//뛴 삼목이랑 삼목이 아닐때 3목 공격
		for (i = 1; i <= 15; i++){
			for (j = 1; j <= 15; j++){
				int tcnt=0;
				int tx,ty;//흑돌 O
					for(d=0;d<8;d++){
						tx=j;
						ty=i;
						tcnt=0;
						while(tcnt!=2 && field[ty][tx]==-1){
							tcnt++;
							tx+=dx[d];
							ty+=dy[d];
						}
						if(tcnt==2){//AI돌이 두개가 연속으로 있을때
							isattacktwo=1;
							if(field[i-2*dy[d]][j-2*dx[d]]!=-2){//둘곳의앞이 유저의 돌이 아닐때
								if(field[i-dy[d]][j-dx[d]]==0){//앞에다두기
									ai_field[i-dy[d]][j-dx[d]]-=50;
									AIcacl(ai_field);
									return 0;
								}
							}
							else if(field[ty][tx]==0){//뒤에다두기
								ai_field[ty][tx]-=50;
								AIcacl(ai_field);
								return 0;
							}
						}
					}
			}
		}
//공격도 아니고 수비도 아닌 병신일때 2목 공격
		for (i = 1; i <= 15; i++){
			for (j = 1; j <= 15; j++){
				int tcnt=0;
				int tx,ty;//흑돌 O
				if(field[i][j]==-1){
					for(d=0;d<8;d++){
						tx=j+dx[d];
						ty=i+dy[d];
						
						tcnt=0;
						while(tcnt!=4 && field[ty][tx]==0){
							tcnt++;
							tx+=dx[d];
							ty+=dy[d];
						}
						if(tcnt==4 && field[i-dy[d]][j-dx[d]]!=-2){//AI돌이 한방향으로 둘 수 있는 곳이 현재위치 제외 4개일때
							ai_field[i+dy[d]][j+dx[d]]-=50;
							AIcacl(ai_field);
							return 0;
						
						}
					}
				}
			}
		}
	AIcacl(ai_field);
	return 0;
}


char y, cy, b;
int x, cx, chk;
int again_respond;
// main 함수: 게임 진행
int main()
{
	int i, j;
	system("cls");
	//field 배열 초기화
	for (i = 1; i <= 15; i++)
	{
		for (j = 1; j <= 15; j++)
		{
			field[i][j] = 0;
		}
	}
	printf("STARTING OMOK GAME\n");
	//게임모드 선택
	printf("1. 1 VS 1 MODE\n");
	printf("2. 1 VS AI MODE\n");

	int mode;
	scanf("%d", &mode);
	if (mode != 1 && mode != 2)
	{
		printf("썅껏");
		return 0;
	}
	system("cls");
	int turn = -2;
	int running = 1;
	while (running && mode == 1)
	{
		if (turn == -2)//O
		{
		aa2:
			x = 7;
			y = 'H';
			while (1)
			{	
				int original;
				original = field[y - 'A' + 1][x];
				if (original != 0)
					field[y - 'A' + 1][x] = -6;
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
				printf("6목은 착수 금지입니다. 다시 입력해주세요.\n");
				Sleep(1000);
				goto aa2;
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
				if (original != 0)
					field[y - 'A' + 1][x] = -5;
				else
					field[y - 'A' + 1][x] = -3;
				gotoxy(0, 0);

				
				system("cls");
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

	while (running && mode == 2) {
		if (turn == -2)//O
		{
			
		aa1:
			system("cls");
			x = 7;
			y = 'H';
			while (1)
			{
				int original;
				original = field[y - 'A' + 1][x];
				if (original != 0)
					field[y - 'A' + 1][x] = -6;
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
				printf("6목은 착수 금지입니다. 다시 입력해주세요.\n");
				Sleep(1000);
				goto aa1;
			default:
				turn = -1;
			}
		}
		if (turn == -1){//AI X
			printf("test");
			omokAI();
			system("cls");
       		gotoxy(0, 0);
        	print_field();
			// return 0;
			chk = checkfive(-1);
			switch (chk){
			case -1:
				gotoxy(0, 0);
				print_field();
				printf("AI WIN  ");
				running = 0;
				break;
			default:
				turn = -2;
			}
		}
	}







	printf("\nplay again?\n");
	printf("1. YES\n");
	printf("2. NO\n");
	scanf("%d", &again_respond);

	if (again_respond == 1)
	{
		system("cls");
		main();
	}
	printf("썅것");
}