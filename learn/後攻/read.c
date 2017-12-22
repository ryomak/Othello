#include <stdio.h>

int main(void)
{
  FILE *fp;
  char *fname = "koko.txt";
  char s[100];

  fp = fopen( fname, "r" );
  if( fp == NULL ){
    printf( "%sファイルが開けません¥n", fname );
    return -1;
  }

  fclose( fp );
  return 0;
}