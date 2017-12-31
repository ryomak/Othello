#ifndef _DEFINE_H_
#define _DEFINE_H_

#define LEN 8



void Init();
void Display();
void DecideTurn();
int ctoi(char);
void Locate(char*,int*,int*);
void PlayerMove();
void COMMove();
void COM1Move();
int CheckFlip(int,int,int,int);
int Check(int,int,int);
void Flip(int,int,int,int);
int Put(int,int,int);
void ShowAnswer(int,int);
int Judge(int);
int Counter();
int MinMax(int[LEN][LEN],int,int);
int Evaluate(int[LEN][LEN]);
int AlphaBeta(int[LEN][LEN],int,int,int,int,int);
void Move();
void SetWeight(int);
int Game(int*,int*,int*);

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


#endif