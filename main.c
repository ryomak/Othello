/*
	 MoveのCOM1MoveをPlayerMoveにすると変更できる
	 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "define.h"
#include "evaluate.h"


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
//minmax search
int SEARCH_LEVEL = 2;
//alphabeta search
int SEARCH_LEVEL1 =6;
//moveが行われた数
int move_cnt;

//weight
int weight[w_num];
//最終誤差表示
char str[30];


//==============main=====================-=====
int main(){
	Init();
	while(available){
		if(move_cnt==FINAL){
			SEARCH_LEVEL1=60-FINAL;
			strcpy(str,"最終予想誤差");
		}
		SetWeight(move_cnt++);

		switch(Judge(turn)){
			case 0: Move();break;
			case 1: turn = turn*-1; Move();break;
			case 2: Counter(); break;
			default: available = 0;break;
		}

	}
	return 0;
}
//============ゲームの仕組み=======================
void Move(){
	if(offence == 1){
		if(turn == 1){
			PlayerMove();
			//COM1Move();
		}else{
			COMMove();
		}
	}else{
		if(turn == 1){
			COMMove();
		}else{
			PlayerMove();
			//COM1Move();
		}
	}
}

//0...自分の手はある
//1...相手は出せる
//2...どちらも出せない
int Judge(int next_turn){
	int x,y;
	for(x=0;x<LEN;x++){
		for(y=0;y<LEN;y++){
			if(Check(next_turn,x,y) == 1) return 0;
		}
	}
	//パスしてターン変更した場合
	for(x=0;x<LEN;x++){
		for(y=0;y<LEN;y++){
			if(Check(next_turn*-1,x,y) == 1) return 1;
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

//==================表示=======================
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


//===========初期化============================
void Init(){
	DecideTurn();
	available = 1;
	//o
	Board[3][3] = -1;
	Board[4][4] = -1;
	//x
	Board[4][3] = 1;
	Board[3][4] = 1;
	move_cnt = 0;
	Display();
}

void DecideTurn(){
	char c;

	printf("先行(x)か後攻(o)か選んでください \n");
	printf("例: 3,a \n");
	while(1){
		scanf("%c",&c);
		if ((c == 'x') || (c == 'o')){
			break;
		}else{
			printf("先行(x)か後攻(o)か選んでください \n");

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

//=================ヘルパー===============
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

//===============ひっくり返す仕組み===============
int Check(int next_turn,int x,int y){
	int vec;
	if(Board[y][x] == 0){
		for(vec=0;vec<LEN;vec++){
			if(CheckFlip(next_turn,x,y,vec) == 1) return 1;
		}
	}
	return 0;
}
int Put(int next_turn,int x,int y){
	int vec,flag=0;
	if(Board[y][x] != 0) return 0;
	for(vec=0;vec<LEN;++vec){
		if(CheckFlip(next_turn,x,y,vec) == 1){
			Flip(next_turn,x,y,vec);
			flag = 1;
		}
	}
	if(flag == 1){
		Board[y][x] = next_turn;
		return 1;
	}
	return 0;
}

int CheckFlip(int next_turn,int x,int y,int vec){
	int flag = 0;
	while(1){
		y += vec_y[vec];
		x += vec_x[vec];
		if( x < 0 || y < 0 || x > 7 || y > 7) return 0;
		if(Board[y][x] == 0) return 0;
		if(Board[y][x] == (next_turn*-1)){
			flag = 1;
			continue;
		}
		if(flag == 1) break;
		return 0;
	}
	return 1;
}

void Flip(int next_turn,int x,int y,int vec){
	while(1){
		y += vec_y[vec];
		x += vec_x[vec];
		if(Board[y][x] == next_turn)break;
		Board[y][x] = next_turn;
	}
}
//=========player===========r============
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

//======COMPUTER===========================
//最弱
void COM1Move(){
	printf("コンピュータ1の手 ");
	int ans_x=-1;
	int ans_y=-1;
	int x,y;
	int i =0;
	int num =0;
	for(x=0;x<LEN;x++){
		for(y=0;y<LEN;y++){
			if(Check(Player,x,y)==1){
				i++;
			}
		}
	}
	int hand[i];
	for(x=0;x<LEN;x++){
		for(y=0;y<LEN;y++){
			if(Check(Player,x,y)==1){
				hand[num]=x+y*LEN	;
				num++;
			}
		}
	}
	srand((unsigned int)time(NULL));
	int rn = rand()%i;
	ans_x=hand[rn]%LEN;
	ans_y=hand[rn]/LEN;

	if((ans_x == -1) || ans_y == -1){
		turn = turn*-1;
	}else{
		Put(Player,ans_x,ans_y);
		ShowAnswer(ans_x,ans_y);
		turn = turn*-1;
		Display();
	}
}

void COMMove(){
	printf("コンピュータの手 \n");
	int ans_x = -1;
	int ans_y = -1;
	int val = AlphaBeta(Board,COM,SEARCH_LEVEL1,-10000,10000,move_cnt);
	ans_x = val%LEN;
	ans_y = val/LEN;
	ShowAnswer(ans_x,ans_y);
	Put(COM,ans_x,ans_y);
	turn = turn*-1;
	Display();
}

//===================α-β法============================
int AlphaBeta(int board[LEN][LEN],int flag,int level,int alpha,int beta,int cnt){
	// ノードの評価値
	int value;
	// 子ノードから伝播してきた評価値
	int childValue;
	// 最大の評価値を持つ場所
	int bestX = -1;
	int bestY = -1;

	//weight更新
	SetWeight(cnt);
	//copy
	int undo_board[LEN][LEN];
	int i;

	int x,y;
	if(level==0){
		return Evaluate(board);
	}
	if(Judge(flag)==1){
		flag = flag * -1;
	}else if(Judge(flag)==2){
		return Evaluate(board);
	}
	if(flag==Player){
		value = 10000;
	}else{
		value = -10000;
	}
	for(x=0;x<LEN;x++){
		for(y=0;y<LEN;y++){
			if(Check(flag,x,y)==1){
				for(i=0;i<LEN;i++) memcpy( undo_board[i], board[i], sizeof(int)*LEN );
				Put(flag,x,y);
				childValue = AlphaBeta(board,flag*-1, level - 1,alpha,beta,cnt+1);
				if(flag==Player){
					if (childValue <= value) {
						value = childValue;
						//beta更新
						beta = value;
						bestX = x;
						bestY = y;
					}
					if(level != SEARCH_LEVEL1){
						if (value < alpha) {  // αカット
							// 打つ前に戻す
							for(i=0;i<LEN;i++) memcpy( board[i], undo_board[i], sizeof(int)*LEN );
							return value;
						}
					}
				}else{
					if (childValue >= value) {
						value = childValue;
						alpha = value;
						bestX = x;
						bestY = y;
					}
					if(level != SEARCH_LEVEL1){
						if (value > beta) {  // βカット
							// 打つ前に戻す
							for(i=0;i<LEN;i++) memcpy( board[i], undo_board[i], sizeof(int)*LEN );
							return value;
						}
					}
				}
				for(i=0;i<LEN;i++) memcpy( board[i], undo_board[i], sizeof(int)*LEN );
			}
		}
	}
	if (level == SEARCH_LEVEL1) {
		// ルートノードなら最大評価値を持つ場所を返す
		//printf("user:%d (x,y)=(%d,%d)\n",flag,bestX,bestY);
		printf("%s eval:%d\n",str,value);
		return bestX+bestY*LEN;
	} else {
		// 子ノードならノードの評価値を返す
		return value;
	}

}


//こっちは駒の個数をどれだけ多く置けるかを計算する
//[評価関数][着手可能数][最終取れる駒数]
int Evaluate(int board[LEN][LEN]){
	int x,y;
	int eval=0;
	int com = 0;
	int player = 0;
	for(x=0;x<LEN;x++){
		for(y=0;y<LEN;y++){
			eval += weight[0]*eva_board[y][x]*board[y][x];
			if(board[y][x]==COM)com++;
			if(board[y][x]==Player)player++;
			if(Check(COM,x,y) == 1){
				eval += weight[1]*COM;
			}
		}
	}
	if(COM==1){
		eval += weight[2]*(com-player);
		return eval;
	}else{
		eval -= weight[2]*(com-player);
		return -eval;
	}
}

//重り設定
void SetWeight(int cnt){
	switch(cnt){
		case FIRST: memcpy(weight, w_first,sizeof(int)*w_num);break;
		case MIDDLE: memcpy(weight, w_middle,sizeof(int)*w_num);break;
		case FINAL:memcpy(weight, w_final,sizeof(int)*w_num);break;
		default: break;
	}
}
