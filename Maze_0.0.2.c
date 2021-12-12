/**------------------------------**
    user:Liujiahuan
    Time:2021/12/12
    For:XUPT 2nd ACM new student ACM competition
    Editon:0.0.2
    Description:Just finish normal maze without monster and door&keys
**------------------------------*/
#include <stdio.h>
#include <stdlib.h>
int ans = 5000;
int ansblood=0;
int key[8] = {0};//keys
int n = 0,m = 0;//长,宽
int h = 0,feet=0;//血量,步数初始化
int beginx = 0,beginy = 0;//定位初始位置
int hash[8] = {0};//为0.0.2版本开发,hash数组保存是否拿到钥匙
void dfs(char **matrix,int x,int y,int blood,int feet,int key[8],int flag[50][50]){//
    if(x<0||x>m-1||y>n-1||y<0||flag[x][y]==1){//出界,碰撞,血量没了,这个必须放前面,不然会数组越界访问
        feet--;
        return;
    }

 //   printf("now is %d %d\n",x,y);
    if(blood<=0){
      //  printf(" %d %d failed,back\n",x,y);
        feet--;
        return;
    }
    if(matrix[x][y]=='m'){//遇到怪物,扣血
        blood--;
    }

    if(matrix[x][y]=='A'||matrix[x][y]=='B'||matrix[x][y]=='C'||matrix[x][y]=='D'||matrix[x][y]=='E'||matrix[x][y]=='F'||matrix[x][y]=='G'||matrix[x][y]=='H'){
        key[matrix[x][y]-'A']=1;
    }
    if(matrix[x][y]=='1'||matrix[x][y]=='2'||matrix[x][y]=='3'||matrix[x][y]=='4'||matrix[x][y]=='5'||matrix[x][y]=='6'||matrix[x][y]=='7'||matrix[x][y]=='0') {
        if(key[matrix[x][y]-'0']!=1){
            feet--;
          //  printf(" %d %d failed,back\n",x,y);
            return;
        }
       // printf("i have key %d",matrix[x][y]-'0');
    }

    if(matrix[x][y] == '#'){//血量为0,或者撞墙
      //  printf(" %d %d failed,back\n",x,y);
        feet--;
        return;
    }
    if(matrix[x][y] == 'e'){//到达终点
        if(feet<ans) {
            ans = feet;
            ansblood =blood;
            //printf("ansblood is %d\n",ansblood);
        }
        feet--;
        return;
    }
    flag[x][y] = 1;
  //  printf("blood is %d\n",blood);
    dfs(matrix, x + 1, y, blood, feet + 1,key,flag);//向右
    dfs(matrix, x, y + 1, blood, feet + 1,key,flag);//向下
    dfs(matrix, x - 1, y, blood, feet + 1,key,flag);//向左
    dfs(matrix, x, y - 1, blood, feet + 1,key,flag);//向上
    flag[x][y] = 0;

}
int main(){
    int flag[5][5]={0};//防止局部递归成环,标记数组
    int key[8] = {0};//keys
    scanf("%d %d %d",&n,&m,&h);
    char **matrix = (char**)malloc(sizeof(char*)*m);//开辟合适大小矩阵
    for(int i = 0; i < m ;i++){
        matrix[i] = (char*)malloc(sizeof(char*)*n);
        scanf("%s",matrix[i]);
        for(int j = 0; j <n;j++){
            if(matrix[i][j] == 's'){
                beginx = j;
                beginy = i;
            }
        }
    }
    dfs(matrix,beginy,beginx,h,feet,key,flag);
    printf("%d\n",ans);
    printf("%d",ansblood);
}
