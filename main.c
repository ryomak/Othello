#include <stdio.h>
#include <string.h>
#define LEN 8

void Init();
void Display();
void DecideTurn();
int ctoi(char);
void Locate(char*,int*,int*);
void PlayerMove();
void COMMove();
int CheckFlip(int,int,int,int);
int Check(int,int,int);
void Flip(int,int,int,int);
int Put(int,int,int);
void ShowAnswer(int,int);
int Judge(int);
void Counter();


int Board[8][8] = {
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
};

//初期data
//player の順番
//1...先行
//２...後攻
int offence;
// ターン
int turn = 1;
//ゲームがつづくか
int available = 0;
//1ならx −１ならo
int Player ;
int COM ;
//方向 左上から時計回り
int vec_x[]={-1,0,1,1,1,0,-1,-1};
int vec_y[]={1,1,1,0,-1,-1,-1,0};



void Display(){
	int y,x;
	printf(" abcdefgh\n");
	for(y=0;y<LEN;y++){
		printf("%d",y+1);
		for(x=0;x<LEN;x++){
			switch (Board[y][x]){
			case 0:
				printf("-");
				break;
			case 1:
				printf("x");
				break;
			case -1:
				printf("o");
				break;
			default:
				printf("N");
			}
		}
		printf("\n");
	}
}

void DecideTurn(){
	char c;
	printf("先行(x)か後攻(o)か選んでください ");
	while(1){
		scanf("%c",&c);
		if ((c == 'x') || (c == 'o')){
			break;
		}else{
			printf("先行(x)か後攻(o)か選んでください ");

		}
	}
	if (c == 'x'){
		offence = 1;
		Player = 1;
		COM = -1;
	}else{
		offence = 2;
		Player = -1;
		COM = 1;
	}
}

void Init(){
	DecideTurn();
	available = 1;
	//o
	Board[3][3] = -1;
	Board[4][4] = -1;
	//x
	Board[4][3] = 1;
	Board[3][4] = 1;
	Display();
}

//a=0,b=1
int ctoi(char c) {
	if (c >= '1' && c <= '9') {
		return c - '1';
	}
	return -1;
}

void Locate(char* str,int* x,int* y){
	*y = ctoi(str[0]);
	switch(str[2]){
		case 'a':*x = 0; break;
		case 'b':*x = 1; break;
		case 'c':*x = 2; break;
		case 'd':*x = 3; break;
		case 'e':*x = 4; break;
		case 'f':*x = 5; break;
		case 'g':*x = 6; break;
		case 'h':*x = 7; break;
		default: *x = -1; break;
	}
}
int Check(int turn,int x,int y){
	int vec;
	if(Board[y][x] == 0){
		for(vec=0;vec<LEN;vec++){
			if(CheckFlip(turn,x,y,vec) == 1) return 1;
		}
	}
	return 0;
}
int Put(int turn,int x,int y){
	int vec,flag=0;
	if(Board[y][x] != 0) return 0;
	for(vec=0;vec<LEN;++vec){
		if(CheckFlip(turn,x,y,vec) == 1){
			Flip(turn,x,y,vec);
			flag = 1;
		}
	}
	if(flag == 1){
		Board[y][x] = turn;
		return 1;
	}
	return 0;
}

int CheckFlip(int turn,int x,int y,int vec){
	int flag = 0;
	while(1){
		y += vec_y[vec];
		x += vec_x[vec];
		if( x < 0 || y < 0 || x > 7 || y > 7) return 0;
		if(Board[y][x] == 0) return 0;
		if(Board[y][x] == (turn*-1)){
			flag = 1;
			continue;
		}
		if(flag == 1) break;
		return 0;
	}
	return 1;
}

void Flip(int turn,int x,int y,int vec){
	while(1){
		y += vec_y[vec];
		x += vec_x[vec];
		if(Board[y][x] == turn)break;
		Board[y][x] = turn;
	}
}



void PlayerMove(){
	while(1){
		printf("石を置く場所を指定してください ");
		char s[10];
		scanf("%s",s);
		int x = -1;
		int y = -1;
		Locate(s,&x,&y);
		if((x!=-1)&&(y!=-1)){
			if(Put(Player,x,y)){
				break;
			}
		}
	}
	turn = turn*-1;
	Display();
}

void ShowAnswer(int x,int y){
	printf("%d,",y+1);
	switch(x){
		case 0:printf("a"); break;
		case 1:printf("b"); break;
		case 2:printf("c"); break;
		case 3:printf("d"); break;
		case 4:printf("e"); break;
		case 5:printf("f"); break;
		case 6:printf("g"); break;
		case 7:printf("h"); break;
	}
	printf("\n");
}

void COM1Move(){
	printf("コンピュータ1の手 ");
	int ans_x;
	int ans_y;
	int x,y;
	for(x=0;x<8;x++){
		for(y=0;y<8;y++){
			if(Check(Player,x,y)==1){
				ans_x = x;
				ans_y = y;
				break;
			}
		}
	}
	Put(Player,ans_x,ans_y);
	ShowAnswer(ans_x,ans_y);
	turn = turn*-1;
	Display();
}

void COMMove(){
	printf("コンピュータの手 ");
	int ans_x;
	int ans_y;
	int x,y;
		for(x=0;x<8;x++){
			for(y=0;y<8;y++){
				if(Check(COM,x,y)==1){
					ans_x = x;
					ans_y = y;
					break;
				}
			}

		}
	Put(COM,ans_x,ans_y);
	ShowAnswer(ans_x,ans_y);
	turn = turn*-1;
	Display();
}
//0...自分の手はある
//1...相手は出せる
//2...どちらも出せない
int Judge(int turn){
	int x,y;
	for(x=0;x<LEN;x++){
		for(y=0;y<LEN;y++){
			if(Check(turn,x,y) == 1) return 0;
		}
	}
	//パスしてターン変更した場合
	for(x=0;x<LEN;x++){
		for(y=0;y<LEN;y++){
			if(Check(turn*-1,x,y) == 1) return 1;
		}
	}
	return 2;
}

void Counter(){
	printf("~~~~\n");
	int x,y;
	int o_point = 0;
	int x_point = 0;
	for(x=0;x<LEN;x++){
		for(y=0;y<LEN;y++){
			switch(Board[y][x]){
				case 1: x_point++; break;
				case -1: o_point++; break;
				default: break;
			}
		}
	}

	printf("o:%d\n",o_point);
	printf("x:%d\n",x_point);
	if(x_point>o_point){
		printf("winner: x\n");
	}else if(x_point == o_point){
		printf("draw\n");
	}else{
		printf("winner: o\n");
	}
	available = 0;
}

void Move(){
	if(offence == 1){
		if(turn == 1){
			COM1Move();
		}else{
			COMMove();
		}
	}else{
		if(turn == 1){
			COMMove();
		}else{
			COM1Move();
		}
	}
}

int main(){
	Init();
	while(available){
		switch(Judge(turn)){
		case 0: Move();break;
		case 1: turn = turn*-1; Move();break;
		case 2: Counter(); break;
		default: available = 0;break;
		}
	}
	return 0;
}
