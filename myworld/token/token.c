#include<sched.h>
#include<pthread.h>
#include<string.h>
extern int printf(const char* format,...);
int token=0;
char cache[100];
#define n 2
#define m 2
int compare_and_exchange( volatile int* destination,int comparand,int new)
{
	asm
	(
		"lock cmpxchg %1,(%2) \n\t"
		"jnz lab1\n\t"
		"mov $0x1,%%eax\n\t"
		"jmp lab2\n\t"
		"lab1:\n\t"
		"mov $0,%%eax\n\t"
		"lab2:\n\t"
		:																				         :"a"(comparand),"c"(new),"d"(destination)
	);
}
void write(char* buff,int size)
{
	int native_token=token;
	int temp,i;
	for( i=0;i<size;i+=m)
	{
		temp=native_token+i*n;
		int new=temp+m;
		if(compare_and_exchange(&token,temp,new))
		{
			int j;
			for(j=0;i<m;j++)
			{
				//cache[native_token+j]=buff[temp+j];
			}
		}
		else
		{
			printf("yield! ");
			sched_yield();
		}
	}
}

typedef struct block
{
	char* buff;
	int size;
}block;
void* fun(void*buff)
{
	block* b=(block*)buff;
	write(b->buff,b->size);
}
int main(void)
{
	pthread_t threads[n];
	char thread1[40],thread2[40];
	memset(thread1,1,40);
	memset(thread2,2,40);
	block block1;
	block1.buff=(char*)&thread1;
	block1.size=40;
	block block2;
	block2.buff=(char*)&thread2;
	block2.size=40;
//	for(int i=0;i<n;i++)
	{
		pthread_create(threads,0,fun,(void*)&block1);
		pthread_create(threads+1,0,fun,(void*)&block2);
		pthread_join(threads[0],0);
		pthread_join(threads[1],0);
	}
	int i;
	for( i=0;i<100;i+=2)
	{
		printf("%d%d ",cache[i],cache[i+1]);
	}
}
