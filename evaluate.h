#ifndef _EVALUATE_H_
#define _EVALUATE_H_
#define w_num 3
#define FIRST 1
#define MIDDLE 25
#define FINAL 50

int eva_board[8][8] = {
  {50, -12,  0,   -1,  -1,  0, -12,  50},
  {-12,-15, -3,  -3,   -3, -3, -15, -12},
  {	0,  -3,  0,   -1,  -1,  0,  -3,   0},
  {-1,  -3, -1,   -1,  -1, -1,  -3,  -1},
  {-1,  -3, -1,   -1,  -1, -1,  -3,  -1},
  { 0,  -3,  0,   -1,  -1,  0,  -3,   0},
  {-12,-15, -3,   -3,  -3, -3, -15, -12},
  {50, -12,  0,   -1,  -1,  0, -12,  50}
};

//[評価関数1~5][着手可能数][駒数の差]
const int w_first[w_num] = {1,2,0};
const int w_middle[w_num] = {1,6,4};
const int w_final[w_num] = {0,0,1};

#endif
