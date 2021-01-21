#include <stdlib.h>
#include <stdio.h>

int main()
{
  printf("Running test 6 to test realloc\n");

  int * ptr = ( int * ) malloc ( 3*sizeof(int) );
  int i;
  int *ptr_new;
  
  *ptr=10;
  *(ptr+1)=20;
  *(ptr+2)=20;
  
  ptr_new=(int*)realloc(ptr,sizeof(int)*4);
  *(ptr_new+3)=30;
  for(i=0;i<4;i++)
	printf("%d ",*(ptr_new+i));


  return 0;
}
