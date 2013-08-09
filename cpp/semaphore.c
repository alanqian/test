// 11:00-12:00 Linux�µĶ��̱߳��
/* File sem.c */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXSTACK 100
int stack[MAXSTACK][2];
int size = 0;
sem_t sem;

/* ���ļ�1.dat��ȡ���ݣ�ÿ��һ�Σ��ź�����һ*/
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

/*���ļ�2.dat��ȡ����*/
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

/*�����ȴ������������ݣ���ȡ���ݺ��ͷſռ䣬�����ȴ�*/
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
	/* ��ֹ��������˳��������ڴ������ڵȴ�*/
	pthread_join(t1, NULL);
}

��Linux�£�����������gcc -lpthread sem.c -o sem���ɿ�ִ���ļ�sem�� �������ȱ༭�������ļ�1.dat��2.dat���������ǵ����ݷֱ�Ϊ1 2 3 4 5 6 7 8 9 10�� -1 -2 -3 -4 -5 -6 -7 -8 -9 -10 ����������sem���õ����µĽ����

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
����countֵΪ0ʱ�� decrement������pthread_cond_wait�������������򿪻�����count_lock����ʱ�������õ����� increment_countʱ��pthread_cond_signal()�����ı�������������֪decrement_count()ֹͣ���������߿��������������̷ֱ߳��������������������������ʲô���Ľ����
��������pthread_cond_broadcast��pthread_cond_t *cond�������������б���������������cond�ϵ��̡߳���Щ�̱߳����Ѻ��ٴξ�����Ӧ�Ļ����������Ա���С��ʹ�����������
