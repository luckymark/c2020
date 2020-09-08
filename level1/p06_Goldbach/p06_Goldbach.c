#include <stdio.h>//任何一个大于2的偶数都可由两个素数组成
int main()
{
    int n,b[100]={0},c,i,j,m=0,flag=0;//m,i,j计数，c为余数
    scanf("%d",&n);
    if(n%2!=0) {printf("no!please inpute even number");return 0;}
    for(i=2;i<n;i++)//小于n的所有素数
    {
        for(j=2;j<=i;j++)
        {
            c=i%j;
            if(c==0&&j!=i) break;//这个i不是素数
<<<<<<< HEAD
            if(c==0&&j==i) {b[m]=i;m+=1;break;}//把素数放入数组 ,共m个
=======
            if(c==0&&j==i)
            {
                b[m]=i;
                m+=1;
                break;
            }//把素数放入数组 ,共m个
>>>>>>> d8d4165c6d1a6c4d5aa568cac24ba154e3e7026c
        }
    }
    i=m-1,j=0;
        while(i>=0 && flag==0)
    {
        for(j=0;j<=m-1;j++)
        {
<<<<<<< HEAD
            if(n==b[i]+b[j]){flag=1;break;}
=======
            if(n==b[i]+b[j])
            {
                flag=1;
                break;
            }
>>>>>>> d8d4165c6d1a6c4d5aa568cac24ba154e3e7026c
        }
        i-=1;
    }
    i+=1;
    printf("%d=%d+%d",n,b[i],b[j]);
    return 0;
}//写完感觉不对劲，是要一次性验证码？