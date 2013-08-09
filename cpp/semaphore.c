// 11:00-12:00 Linux下的多线程编程
/* File sem.c */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXSTACK 100
int stack[MAXSTACK][2];
int size = 0;
sem_t sem;

/* 从文件1.dat读取数据，每读一次，信号量加一*/
void ReadData1(void)
{
	FILE *fp=fopen("1.dat","r");
	while(!feof(fp)) {
		fscanf(fp,"%d %d",&stack[size][0],&stack[size][1]);
		sem_post(&sem);
		++size;
	}
	fclose(fp);
}

/*从文件2.dat读取数据*/
void ReadData2(void)
{
	FILE *fp=fopen("2.dat","r");
	while(!feof(fp))
	{
		fscanf(fp,"%d %d",&stack[size][0],&stack[size][1]);
		sem_post(&sem);
		++size;
	}
	fclose(fp);
}

/*阻塞等待缓冲区有数据，读取数据后，释放空间，继续等待*/
void HandleData1(void)
{
	while (1)
	{
		sem_wait(&sem);
		printf("Plus:%d+%d=%d\n",
			stack[size][0], stack[size][1], stack[size][0] + stack[size][1]);
		--size;
	}
}

void HandleData2(void)
{
	while(1)
	{
		sem_wait(&sem);
		printf("Multiply:%d*%d=%d\n",
			stack[size][0], stack[size][1], stack[size][0] * stack[size][1]);
		--size;
	}
}
int main(void)
{
	pthread_t t1,t2,t3,t4;
	sem_init(&sem,0,0);
	pthread_create(&t1, NULL, (void *)HandleData1, NULL);
	pthread_create(&t2, NULL, (void *)HandleData2, NULL);
	pthread_create(&t3, NULL, (void *)ReadData1, NULL);
	pthread_create(&t4, NULL, (void *)ReadData2, NULL);
	/* 防止程序过早退出，让它在此无限期等待*/
	pthread_join(t1, NULL);
}

在Linux下，我们用命令gcc -lpthread sem.c -o sem生成可执行文件sem。 我们事先编辑好数据文件1.dat和2.dat，假设它们的内容分别为1 2 3 4 5 6 7 8 9 10和 -1 -2 -3 -4 -5 -6 -7 -8 -9 -10 ，我们运行sem，得到如下的结果：

Multiply:-1*-2=2
Plus:-1+-2=-3
Multiply:9*10=90
Plus:-9+-10=-19
Multiply:-7*-8=56
Plus:-5+-6=-11
Multiply:-3*-4=12
Plus:9+10=19
Plus:7+8=15
Plus:5+6=11

// --------------------------------------------------------------------
pthread_mutex_t count_lock;
pthread_cond_t count_nonzero;
unsigned count;
void decrement_count()
{
	pthread_mutex_lock (&count_lock);
	while (count==0) {
		pthread_cond_wait(&count_nonzero, &count_lock);
	}
	count--;
	pthread_mutex_unlock(&count_lock);
}

void increment_count()
{
	pthread_mutex_lock(&count_lock);
	if (count==0)
		pthread_cond_signal(&count_nonzero);
	count=count+1;
	pthread_mutex_unlock(&count_lock);
}
　　count值为0时， decrement函数在pthread_cond_wait处被阻塞，并打开互斥锁count_lock。此时，当调用到函数 increment_count时，pthread_cond_signal()函数改变条件变量，告知decrement_count()停止阻塞。读者可以试着让两个线程分别运行这两个函数，看看会出现什么样的结果。
　　函数pthread_cond_broadcast（pthread_cond_t *cond）用来唤醒所有被阻塞在条件变量cond上的线程。这些线程被唤醒后将再次竞争相应的互斥锁，所以必须小心使用这个函数。
