//渗透问题
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 100
#define times 10

typedef struct
{
	bool open,full;   //open表示已点亮，full表示水已充满
}Node;


//地址转换
Node* address(Node* n,int i,int j)
{
	return n+i*N+j;
}
//初始化网格和id[]数组即连通分量数组
void init(Node* n,int id[])
{
	int i,j;
	Node* q = n;
	id[0]=0;
	id[N*N+1]=N*N+1;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++,q++)
		{
			q->open=false;
			q->full=false;
			id[i*N+j+1]=i*N+j+1;
		}
}

//判断该网格是否点亮
bool isOpen(Node* n,int i,int j)
{
	return address(n,i,j)->open?true:false; //点亮即返回true
}

//判断该网格是否充满水
bool isFull(Node* n,int i,int j)
{
	return address(n,i,j)->full?true:false; //充满即返回true
}

void union_detail(Node* n,int id[],int i,int j,int var)
{

}

//修改上下左右 即+1 -1 +N -N
void Union(Node* n,int id[],int i,int j)
{
	int var = i*N+j+1;
	if(isOpen(n,i-N,j)) union_detail(n,id,i,j,var);
	if(isFull(n,i-N,j)) address(n,i-N,j)->full=true;
	if(isOpen(n,i+N,j)) union_detail(n,id,i,j,var);
	if(isFull(n,i+N,j)) address(n,i+N,j)->full=true;
	if(isOpen(n,i,j-1)) union_detail(n,id,i,j,var);
	if(isFull(n,i,j-1)) address(n,i,j-1)->full=true;
	if(isOpen(n,i,j+1)) union_detail(n,id,i,j,var);
	if(isFull(n,i,j+1)) address(n,i,j+1)->full=true;
}
//点亮任意一个点
void open(Node* n,int id[])
{
	int i,j;
	i=rand()%N;
	j=rand()%N;
	if(!address(n,i,j)->open)
	{
		address(n,i,j)->open=true;
		Union(n,id,i,j);
	}
	else open(n,id);
}
//判断是否渗透
bool percolates(Node* n)
{
	int i;
	//return true;
	for(i=0;i<N;i++)
		if(address(n,N-1,i)->full) return true;
}
//多次模拟，取平均
double Monte_CS(Node* n)
{
	int sum=0;
	int id[N*N+2];
	init(n,id);
	do{
		open(n,id);
		sum++;
	}while(!percolates(n));
	return sum/N/N;
}

int main()
{
	Node* n = (Node*)malloc(sizeof(Node)*N*N);
	double results[times];
	int i,sum;
	srand((unsigned)time(NULL));
	for(i=0;i<times;i++)
	{
		results[i]=Monte_CS(n);
		printf("the %dth *p is %.4lf\n",i,results[i]);
	}
	for(i=0,sum=0;i<times;i++) sum+=results[i];
	printf("the average of *p is %lf\n",sum/times);
	return 0;
}
