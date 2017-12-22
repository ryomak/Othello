#ifndef _EVALUATE_H_
#define _EVALUATE_H_
#define w_num 3
#define FIRST 0
#define MIDDLE 20
#define FINAL 40

int eva_board[8][8] = {
{120, -20,  20,   5,   5,  20, -20, 120},
  {-20, -40,  -5,  -5,  -5,  -5, -40, -20},
  { 20,  -5,  15,   3,   3,  15,  -5,  20},
  {  5,  -5,   3,   3,   3,   3,  -5,   5},
  {  5,  -5,   3,   3,   3,   3,  -5,   5},
  { 20,  -5,  15,   3,   3,  15,  -5,  20},
  {-20, -40,  -5,  -5,  -5,  -5, -40, -20},
  {120, -20,  20,   5,   5,  20, -20, 120}
};
//[評価関数1~5][着手可能数][取れる数]
const int w_first[w_num] = {1,0,0};
const int w_middle[w_num] = {1,0,0};
const int w_final[w_num] = {1,0,0};

#endif