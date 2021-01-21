#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main()
{
  printf("Running test 5 to test calloc\n");

  int * ptr = ( int * ) calloc ( 10,sizeof(int) );
  int i;
  for(i=0;i<10;i++)
  {
	  printf("%d: %d\n",i,ptr[i]);
	  assert(ptr[i]==0);
  }
  return 0;
}
