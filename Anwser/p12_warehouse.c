#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define MAX 5010

FILE *fpRead;
struct data
{
    char name[25];
    char version[25];
    int number;
};
struct data mes[MAX];
int tot;
int comp(struct data x,struct data y)
{
    if(strcmp(x.name,y.name)==0 && strcmp(x.version,y.version)==0 && (x.number==y.number))
        return 1;
    return 0;
}

int main()
{

    int cho,i,j;
    struct data one;
    fpRead=fopen("Goods.txt","r");
    fscanf(fpRead,"%d",&tot);
    for(i=0;i<tot;i++)
    {
        fscanf(fpRead,"%s%s%d",mes[i].name,mes[i].version,&mes[i].number);
    }
	fclose(fpRead);
    while(1)
    {
        printf("Please input the function you have chosen£º");
        scanf("%d",&cho);
        int flag=0;
        switch(cho)
        {
            case 1:
                for(i=0;i<tot;i++)
                    printf("%s %s %d\n",mes[i].name,mes[i].version,mes[i].number);
                break;
            case 2:
                scanf("%s %s %d",mes[tot].name,mes[i].version,&mes[i].number);
                tot++;
                break;
            case 3:
                scanf("%s %s %d",one.name,one.version,&one.number);
                for(i=0;i<tot;i++)
                {
                    if(comp(one,mes[i]))
                    {
                        for(j=i;j<tot-1;j++)
                        {
                            mes[j].number=mes[j+1].number;
                            strcpy(mes[j].version,mes[j+1].version);
                            strcpy(mes[j].name,mes[j+1].name);
                        }
                        tot--;
                        break;
                    }
                }
                break;
            default:
                flag=1;
                fpRead=fopen("Goods.txt","w");
                fprintf(fpRead,"%d\n",tot);
                for(i=0;i<tot;i++)
                {
                    fprintf(fpRead,"%s %s %d\n",mes[i].name,mes[i].version,mes[i].number);
                }
                fclose(fpRead);
        }
        if(flag)
            break;
    }
    return 0;
}


