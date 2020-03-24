#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 100
int a[N+2][N+2];
int p[N*N][2];

//取消重复点亮次数
int same(int a1,int a2,int k)
{
    int i,j;
    for(i=0;i<k;i++)
    {
        if(a1==p[i][0]&&a2==p[i][1])
        return 1;
    }
    return 0;
}

int compare(int a,int b,int c,int d,int e)
{
    int i,j,m;
    int q[5];
    q[0]=a,q[1]=b,q[3]=c,q[4]=d,q[5]=e;
    for(i=0;i<5;i++)
    {
        if(q[i]<=0)q[i]=N*N+1;
    }
    for(i=0;i<4;i++)
    {
        for(j=i+1;j<5;j++)
        {
            if(q[j]<q[i])
            {
                m=q[i];
                q[i]=q[j];
                q[j]=m;
            }
        }
    }
    return q[0];
}

void dig(int a1,int a2)
{
    int s,s0;
    int i,j;
    int hanbanzi;
    s=(a1-1)*N+a2;
    if(s>0&&s<=N)
    {
        a[a1][a2]=1;
    }
    s0=compare(a[a1][a2],a[a1-1][a2],a[a1+1][a2],a[a1][a2-1],a[a1][a2+1]);
    a[a1][a2]=s0;
    if(a[a1-1][a2]>0)
    {
        hanbanzi=a[a1-1][a2];
        for(i=1;i<=N;i++)
        {
            for(j=1;j<=N;j++)
            {
                if(a[i][j]==hanbanzi) a[i][j]=s0;
            }
        }
    }
    if(a[a1+1][a2]>0)
    {
        hanbanzi=a[a1+1][a2];
        for(i=1;i<=N;i++)
        {
            for(j=1;j<=N;j++)
            {
                if(a[i][j]==hanbanzi) a[i][j]=s0;
            }
        }
    }
    if(a[a1][a2-1]>0)
    {
        hanbanzi=a[a1][a2-1];
        for(i=1;i<=N;i++)
        {
            for(j=1;j<=N;j++)
            {
                if(a[i][j]==hanbanzi) a[i][j]=s0;
            }
        }
    }
    if(a[a1][a2+1]>0)
    {
        hanbanzi=a[a1][a2+1];
        for(i=1;i<=N;i++)
        {
            for(j=1;j<=N;j++)
            {
                if(a[i][j]==hanbanzi) a[i][j]=s0;
            }
        }
    }
}

int main()
{
    int i,j,k;
    int T1,T2;
    int q=0;
    a[N+2][N+2]={-1};
    p[N*N][2]={-1};
    system("dade/t");
	system("time/t");
    printf("\n");
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
        {
            a[i][j]=0;
        }
    }
    srand((unsigned int)time(NULL));
    for(i=0,k=0;;i++)
    {
        T1=rand()%N,T2=rand()%N;
        if(same(T1,T2,k)==0)
        {
            p[k][0]=T1,p[k][1]=T2;
            k++;
        }
        //printf("%d %d   ",T1,T2);
        a[T1+1][T2+1]=T1*N+T2+1;
        dig(T1+1,T2+1);
        //printf("%d \n",a[T1+1][T2+1]);
        for(j=1;j<=N;j++)
        {
            if(a[N][j]==1) q=1;
        }
        if(q==1)break;
    }
    //printf("\n");
    // for(i=1;i<=N;i++)
    // {
    //     for(j=1;j<=N;j++)
    //     {
    //         printf("%d\t",a[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d\n",k);
    system("dade/t");
	system("time/t");
    return 0;
}