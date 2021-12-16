#include<stdio.h>
#include<malloc.h>
#include<math.h>
typedef struct Node{
	int data;
	struct Node* next;
}Node;



Node* creatNode(){
	Node *new_node = (Node*)malloc(sizeof(Node*));
	new_node -> next =NULL;
	return new_node;
}



void insert(Node *now_node){//正向建立链表
	int data;
	scanf("%d",&data);
	if(data!= -1){
		Node *new_node = creatNode();
		now_node -> next = new_node;
		new_node ->data = data;
		now_node = now_node -> next;
		insert(now_node);
	}
}



void print(Node *node){
    printf("--");//格式输出
	printf("%d",node -> data);//打印数据

	if(node -> next != NULL&&node->next->data!= 0) print(node -> next);
	//若下一个是0，即到了逆序的尾节点
	


Node* reverse(Node *now_node){
	Node *pre_node;//前序指针
	Node *temp;//temp指针
	while(now_node->next!=NULL){
		temp = now_node -> next;//如果不用temp保存，则变更now_node的next会和后面失去连接
		now_node -> next =pre_node;//指向上一个
		pre_node = now_node;//pre_node更新
		now_node = temp;//前往下一个节点
	}
	now_node -> next = pre_node;
	//处理最后一个节点，因为最后一个节点的下一个是NULL所以while不会处理
	return now_node;//返回“第一个节点”
}



int main(){
	Node *head = creatNode();//创建单链表
	insert(head);
	printf("正向输出");
   	print(head -> next);
    	printf("链表逆置")//链表逆置
    	printf("\n");
    	Node *Reverse = reverse(head -> next);
    	print(Reverse);
}
