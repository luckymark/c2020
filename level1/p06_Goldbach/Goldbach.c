//任何一个大于2的偶数都可以分为两个质数之和
#include<stdio.h>
#include<stdbool.h>

#define MAXN 101
bool isprime[MAXN]={0};
int prime[MAXN];

int isPrime(int n){
    int count=0;
    for(int i=2;i<=n;i++){
        if(isprime[i]==0){
            prime[count]=i;count++; //把素数导入数组prime[]
            for(int j=i+i;j<=n;j+=i){
                isprime[j]=1;
            }
        }
    }return count;
}

struct node{
    int flag;
    int number;
    int prime1;
    int prime2;
}even[100]={0};//从even[2]开始


void solve(){
    even[2].flag=1;
    even[2].number=4;
    even[2].prime1=2;
    even[2].prime2=2;
    for(int i=1;i<MAXN;i++){
        for(int j=i;;j++){
            int temp=prime[i]+prime[j];
            if(temp>100) break;
            if(even[temp/2].flag==0) {
                even[temp/2].flag=1;
                even[temp/2].number=temp;
                even[temp/2].prime1=prime[i];
                even[temp/2].prime2=prime[j];
            }
        }
    }
}

int main(){
    isPrime(100);
    solve();
    for(int i=2;i<51;i++){
        if(even[i].flag==1){
            printf("%d %d %d\n",even[i].number,even[i].prime1,even[i].prime2);
        }else {
            printf("%d\n",even[i].number);
            break;
        }
    }
    return 0;
}