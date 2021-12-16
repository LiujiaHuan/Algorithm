/**------------------------------**
    user:Liujiahuan
    For:PTA6-8
	  Time:2021/12/16
    Description:
**------------------------------*/
#include <stdio.h>
#include <stdlib.h>

struct stud_node {
     int    num;
     char   name[20];
     int    score;
     struct stud_node *next;
};

struct stud_node *createlist();
struct stud_node *deletelist( struct stud_node *head, int min_score );

int main()
{
    int min_score;
    struct stud_node *p, *head = NULL;

    head = createlist();
    scanf("%d", &min_score);
    head = deletelist(head, min_score);
    for ( p = head; p != NULL; p = p->next )
        printf("%d %s %d\n", p->num, p->name, p->score);

    return 0;
}

/* 你的代码将被嵌在这里 */
struct stud_node *createlist(){
	int num;
	struct stud_node *head,*new_node,*pre;
	pre = NULL;
	scanf ("%d", &num);
	while(num!=0){
		new_node = (struct stud_node*)malloc(sizeof(struct stud_node));
		scanf("%s %d",new_node -> name,&new_node -> score);
		new_node -> num = num;
		if(pre==NULL){
			new_node -> next =NULL;
			pre = new_node;
			head =new_node;//保存头节点
		}
		else{
			new_node -> next = NULL;
			pre -> next = new_node;
			pre = new_node;//保存创建的节点
		}
		scanf("%d",&num);//num更新
	}
	return head;
}
struct stud_node *deletelist(struct stud_node *head, int min_score){
	struct stud_node *pre,*ans;
	//pre保存上一个节点，ans保存头节点，因为我们创建的时候没有用头指针，直接把头创建为节点
	//所以如果第一个就不符合要删，必须新开辟一个pre当作前置节点
	pre = (struct stud_node*)malloc(sizeof(struct stud_node));
	ans = pre;//return要从pre开始

	while(head!=NULL){//当前节点不为空
		if((head->score) < min_score){
			pre -> next = head -> next;
			head = head -> next; 
		}
        else{
            pre = head;
            head = head -> next;

        }
	}
    return ans->next;
} 
