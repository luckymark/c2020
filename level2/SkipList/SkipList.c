#include"list.h"
int main() {
    char flag;
    //determinate the mode
    unsigned num;
    //operand
    init(0);
    //create head and set seed
    while(scanf("%c",&flag)){
        switch(flag){
            case 'i':
                scanf("%d",&num);
                insertList(num);
                puts("insert successfully!");
                break;
            case 'd':
                scanf("%d",&num);
                delList(num);
                break;
            case 'f':
                scanf("%d",&num);
                if(findList(num)){
                	printf("%d is here!\n",num );
                }
                else printf("%d is not here!\n",num );
                break;
            case 'q':
                exit(0);
        }
    }
    return 0;
}

bool randomVal(){
    if(rand()%2)return true;
    else return false;
}
void init(unsigned seed){
	system("cls");
	printf("*****Read Me*****\n"
			"i X : insert X\n"
			"d X : delete X\n"
			"f X : check X\n"
			"q : quit\n\n"
			"Please input your command:\n");
    //clear and usage

    if(seed==0)seed=time(NULL);
    srand(seed);
    //set seed

    head=(struct Node*)malloc(sizeof(struct Node));
    head->val=0;
    head->up=NULL;
    head->down=NULL;
    head->right=NULL;
    //empty list
}
bool findList(int value){
    if(head->right==NULL){
        return false;
    }
    //empty list

    struct Node* cursor=head->right;
    while(1){
        if(cursor->val==value) {
            return true;
        }
        //equal

        if(cursor->right==NULL||cursor->right->val>value){
            //mean to down
            if(cursor->down==NULL){
                return false;
            }
            else{
                cursor=cursor->down;
                continue;
            }
        }
        else cursor=cursor->right;
        //forward
    }
}
void insertList(int value){
    struct Node* new_node=(struct Node*)malloc(sizeof(struct Node));
    new_node->val=value;
    new_node->up=NULL;
    new_node->right=NULL;
    new_node->down=NULL;
    //init new node

    if(head->right==NULL){
        //empty list
        head->right=new_node;
        return;
    }

    struct Node* cursor=head->right;
    //init cursor position
    struct Node* cur_head=head;
    //highest level

    while(cur_head->down!=NULL){
        while(1){
            if(cursor->right==NULL||cursor->right->val>value){
                cur_head->val=(unsigned int)cursor;
                //store shortcut
                cursor=cursor->down;
                cur_head=cur_head->down;
                //downing level
                break;
            }
            cursor=cursor->right;
            //forward
        }
    }

    //working on level 0

    while(cursor->right){
        if(cursor->right->val>value){

            new_node->right=cursor->right;
            cursor->right=new_node;
            break;
        }
        cursor=cursor->right;
    }
    if(cursor->right==NULL){
        cursor->right=new_node;
    }
    //normal linked list

    struct Node* skip_node;
    while(randomVal()) {
        //build index

        skip_node=(struct Node*)malloc(sizeof(struct Node));
        skip_node->val=value;
        skip_node->up=NULL;
        skip_node->right=NULL;

        skip_node->down=new_node;
        new_node->up=skip_node;
        //connect

        if(cur_head->up==NULL){
            //build index level

            cur_head->up=(struct Node*)malloc(sizeof(struct Node));
            cur_head->up->val=0;
            cur_head->up->down=cur_head;
            cur_head->up->right=NULL;
            cur_head->up->up=NULL;
            //init
            
            cur_head=cur_head->up;
            head->up=cur_head;
            head=cur_head;
            head->right=skip_node;
            //renew

            break;
            //no need to continue
        }
        cur_head=cur_head->up;
        //renew
        cursor=(struct Node*)cur_head->val;
        //using shortcut

        skip_node->right=cursor->right;
        cursor->right=skip_node;
        //normal linkelist insertion

        new_node=skip_node;
        //renew between level
    }
}

void delList(int value){
    struct Node* cursor=head;
    struct Node* cur_head=head;
    struct Node* temp;
    while(cur_head) {
        if(cursor->right==NULL){
            puts("Error : Cannot find that nubmer!");
            return;
        }
        if (cursor->right->val == value) {
            break;
        }
        if (cursor->right == NULL || cursor->right->val > value) {
            cursor = cursor->down;
            cur_head=cur_head->down;
            continue;
        }
        cursor = cursor->right;
    }
    //try to find the first node with val(value)

    if(cur_head==NULL){
        puts("Error : Cannot find that nubmer!");
        return;
    }

    while(1){
        temp=cursor->right->right;
        free(cursor->right);
        cursor->right=temp;

        if(cursor->down==NULL){
        	puts("delete successfully!");
        	return;
        }
        cursor=cursor->down;
        //downing level
        
        while(cursor->right->val!=value)cursor=cursor->right;
        //refind
    }
}