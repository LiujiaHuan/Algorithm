#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int* vexs;
    int** arcs;
    int vexNum;
    int arcNum;
}Graph;

typedef struct Node {
    int data;
    struct Node* next;
}Node;

Node* initStack() {
    Node* stack = (Node*)malloc(sizeof(Node));
    stack -> data = 0;
    stack -> next = NULL;
    return stack;
}

int isEmpty(Node* stack) {
    if (stack -> next == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

void push(Node* stack, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node -> data = data;
    node -> next = stack -> next;
    stack -> next = node;
    stack -> data ++;
}

int pop(Node* stack) {
    if (!isEmpty(stack)) {
        Node* node = stack -> next;
        stack -> next = node -> next;
        return node -> data;
    }
    else {
        return -1;
    }
}

int* findInDegrees(Graph* G) {
    int* inDegrees = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++) {
        inDegrees[i] = 0;
    }
    for (int i = 0 ; i < G -> vexNum; i++) {
        for (int j = 0; j < G -> vexNum; j++) {
            if (G -> arcs[i][j])
                inDegrees[j] = inDegrees[j] + 1;
        }
    }
//    for(int i = 0 ;i<G -> vexNum;i++){
//        printf("rudu:%d\n",inDegrees[i]);
//    }
    return inDegrees;
}

bool topologicalSort(Graph* G) {
    int index = 0;
    int* top = (int*)malloc(sizeof(int) * G -> vexNum);
    int* inDegrees = findInDegrees(G);
    Node* stack = initStack();
    for (int i = 0 ; i < G -> vexNum; i++) {
        if (inDegrees[i] == 0) {
            push(stack, i);
        }
    }
    while (!isEmpty(stack)) {
        int vex = pop(stack);
        top[index++] = vex;
        for (int i = 0 ; i < G -> vexNum; i++) {
            if (G -> arcs[vex][i]) {
                inDegrees[i] = inDegrees[i] - 1;
                if (inDegrees[i] == 0)
                    push(stack, i);
            }
        }
    }
//    for (int i = 0; i < index; i++) {
//        printf("%d ", G -> vexs[top[i]]);
//    }
    if(G ->vexs[top[1]]==1){
        return true;
    }
    else{
        return false;
    }

    printf("\n");
}

Graph* initGraph(int vexNum) {
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G -> vexs = (int*)malloc(sizeof(int) * vexNum);
    G -> arcs = (int**)malloc(sizeof(int*) * vexNum);
    for (int i = 0 ; i < vexNum; i++) {
        G -> arcs[i] = (int*)malloc(sizeof(int) * vexNum);
    }
    G -> vexNum = vexNum;
    G -> arcNum = 0;
    return G;
}

void createGraph(Graph* G, int* vexs, int* arcs) {
    for (int i = 0 ; i < G -> vexNum; i++) {
        G -> vexs[i] = vexs[i];
       // printf("%d %d  %d %d\n",arcs[0],arcs[1],arcs[2],arcs[3]);
        for (int j = 0; j < G -> vexNum; j++) {
            G -> arcs[i][j] = *(arcs + i * G -> vexNum + j);
           // printf("%d\n",*(arcs + i * G -> vexNum + j));
            if (G -> arcs[i][j] != 0)
                G -> arcNum ++;
        }
    }
    G -> arcNum /= 2;
}


bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize){
    if(numCourses==1 || numCourses==0)
        return 1;
    printf("%d",prerequisitesSize);
    Graph* G = initGraph(numCourses);
    int num[100];
    //int *pre = (int*)prerequisites;
    for(int i = 0 ; i < numCourses;i++){
        num[i] = i;
    }
    //创建visit数组,初始化
    int* visited = (int*)malloc(sizeof(int) * G -> vexNum);
    for (int i = 0; i < G -> vexNum; i++)
        visited[i] = 0;

    //创建矩阵
    int **arcs = (int**)calloc(numCourses,sizeof(int*));

    *arcs = (int*) calloc((numCourses*numCourses),sizeof (int));
    //*(arcs+1)=(*arcs+numCourses);
    for (int i = 1; i < numCourses; ++i) {
        *(arcs+i)=(*arcs+(i*numCourses));
    }



    // for(int i = 0; i < prerequisitesSize;i++){
    //    arcs[*(pre+i*prerequisitesSize)][*(pre+i*prerequisitesSize+1)] = 1;
    // }
    for(int i = 0; i < prerequisitesSize;i++){
       arcs[prerequisites[i][1]][prerequisites[i][0]] = 1;
    }

    //printf("%d %d\n%d %d\n",arcs[0][0],arcs[0][1],arcs[1][0],arcs[1][1]);
    createGraph(G,num,(*arcs));
    if(topologicalSort(G))  return true;
    else{
        return false;
    }
//    printf("vexnum%d\n",G -> vexNum);
//    printf("arcnum %d\n",G -> arcNum);
    return 0;
}
