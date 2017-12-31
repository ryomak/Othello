#ifndef _EVALUATE_H_
#define _EVALUATE_H_
#define w_num 3
#define FIRST 0
#define MIDDLE 30
#define FINAL 50

int eva_board[8][8] = {
{150, -40,  20,   5,   5,  20, -20, 150},
  {-40, -40,  -5,  -5,  -5,  -5, -40, -40},
  { 20,  -5,  15,   3,   3,  15,  -5,  20},
  {  5,  -5,   3,   3,   3,   3,  -5,   5},
  {  5,  -5,   3,   3,   3,   3,  -5,   5},
  { 20,  -5,  15,   3,   3,  15,  -5,  20},
  {-40, -40,  -5,  -5,  -5,  -5, -40, -40},
  {150, -40,  20,   5,   5,  20, -40, 150}
};
//[評価関数1~5][着手可能数][取れる数]
const int w_first[w_num] = {1,8,6};
const int w_middle[w_num] = {1,2,8};
const int w_final[w_num] = {0,2,2};

#endif
