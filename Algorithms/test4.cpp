//渗透问题  weight quick union + find
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 100
#define times 5

typedef struct
{
	bool open;   //open表示已点亮，full表示水已充满
    int p;
    int sz;
}Node;


//地址转换
Node* address(Node* n,int i,int j)
{
	return n+i*N+j+1;
}

//初始化网格
void init(Node* n)
{
	int i,length = N*N+2;
	for(i=0; i<length; i++,n++)
    {
        n->open = false;
        n->p = i;
        n->sz = 1;
    }
}

//判断该网格是否点亮
bool isOpen(Node* n,int i,int j)
{
	return address(n,i,j)->open;
}

int root(Node* n,int i,int j)
{
    int id = i*N+j+1;
    while((n+id)->p != id) id = (n+id)->p;
    return id;
}


void update(Node* n,int r,bool last)
{
    if(last && r <= N) address(n,N,0)->p = r;
}

void modify(Node* n,int i1,int j1,int r2,bool last)
{
    if(i1<0 || i1>N-1 || j1<0 || j1>N-1) return;
    else
    {
        if(isOpen(n,i1,j1))
        {
            int r1=root(n,i1,j1);
            if(r1==r2) return;
            if(((n+r1)->sz) < ((n+r2)->sz))
            {
                (n+r1)->p = r2;
                (n+r2)->sz += (n+r1)->sz;
                update(n,r2,last);
            }
            else
            {
                (n+r2)->p = r1;
                (n+r1)->sz += (n+r2)->sz;
                update(n,r1,last);
            }
        }
    }
}

//修改上下左右 即+1 -1 +N -N
void Union(Node* n,int i,int j)
{
    int r2=root(n,i,j);
    bool last = (i==N-1);
    modify(n,i-1,j,r2,last);  //上
    modify(n,i+1,j,r2,last);  //下
    modify(n,i,j-1,r2,last);  //左 
    modify(n,i,j+1,r2,last);  //右
}
//点亮任意一个点
void open(Node* n)
{
	int i,j;
	i=rand()%N;
	j=rand()%N;
	if(!address(n,i,j)->open)
	{
		address(n,i,j)->open=true;
		Union(n,i,j);
	}
	else open(n);
}
//判断是否渗透
bool percolates(Node* n)
{
    if(address(n,N,0)->p <= N) return true;
    return false;
}


//多次模拟，取平均
double Monte_CS(Node* n)
{
	int sum=0;
	init(n);
	do{
		open(n);     
		sum++;
	}while(!percolates(n));
	return (double)sum/N/N;
}
//主函数
int main()
{
	Node* n = (Node*)malloc(sizeof(Node)*(N*N+2));
	double results[times];
	int i;
    double sum;
	srand((unsigned)time(NULL));
	for(i=0,sum=0;i<times;i++)
	{
		results[i]=Monte_CS(n);
        sum+=results[i];
		printf("the %dth *p is %.4lf\n",i+1,results[i]);
	}
	printf("the average of *p is %.4lf\n",sum/times);
	return 0;
}
