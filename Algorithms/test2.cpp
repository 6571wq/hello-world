//渗透问题  quick union + find
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 4
#define times 1

typedef struct
{
	bool open;   //open表示已点亮，full表示水已充满
    int p;
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
	Node* q = n;
	for(i=0;i<length;i++,q++)
    {
        q->open = false;
        q->p = i;
    }
    printf("\n%d\n",address(n,N,0)->p);
}

//判断该网格是否点亮
bool isOpen(Node* n,int i,int j)
{
	return address(n,i,j)->open;
}

int root(Node* n,int id)
{
    while((n+id)->p != id) id = (n+id)->p;
    return id;
}


void update(Node* n,int r,int i)
{
    printf("%d\n",r);
    if(i==(N-1) && r<=N) address(n,N,0)->p = r;
}

void modify(Node* n,int i1,int j1,int i2,int j2)
{
    if(i1<0 || i1>N-1 || j1<0 || j1>N-1) return;
    else
    {
        if(isOpen(n,i1,j1))
        {
            int r1=root(n,i1*N+j1+1);
            int r2=root(n,i2*N+j2+1);
            if(r1 > r2)
            {
                (n+r1)->p = r2;
                update(n,r2,i2);
            }
            else
            {
                (n+r2)->p = r1;
                update(n,r1,i2);
            }
        }
    }
}

//修改上下左右 即+1 -1 +N -N
void Union(Node* n,int i,int j)
{
    modify(n,i-1,j,i,j);  //上
    modify(n,i+1,j,i,j);  //下
    modify(n,i,j-1,i,j);  //左 
    modify(n,i,j+1,i,j);  //右
}
//点亮任意一个点
void open(Node* n)
{
	int i,j;
	i=rand()%N;
	j=rand()%N;
	if(!address(n,i,j)->open)
	{
        printf("*******%d %d**********\n",i,j);
		address(n,i,j)->open=true;
		Union(n,i,j);
	}
	else open(n);
}
//判断是否渗透
bool percolates(Node* n)
{
    int i,j;
    Node* q = n;
    q++;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++,q++) printf("%d\t",q->p);
        printf("\n");
    }
    printf("%d\n",address(n,N,0)->p);
    if(address(n,N,0)->p <= N) return true;
    return false;
}


//多次模拟，取平均
double Monte_CS(Node* n)
{
	int sum=0;
	init(n);
	do
    {
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
    if(N<=1) printf("the N is too little");
    else
    {
        for(i=0,sum=0;i<times;i++)
        {
            results[i]=Monte_CS(n);
            sum+=results[i];
            printf("the %dth *p is %.4lf\n",i+1,results[i]);
        }
        printf("the average of *p is %.4lf\n",sum/times);
    }
    return 0;
}
