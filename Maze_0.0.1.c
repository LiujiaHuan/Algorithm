/**------------------------------**
    user:Liujiahuan
    For:XUPT 2nd ACM new student ACM competition
    Editon:0.0.1
    Description:Just finish normal maze without monster and door&keys
**------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <id3/globals.h>
int ans = 5000;
int n = 0,m = 0;//长,宽
int h = 0,feet=0;//血量,步数初始化
int beginx = 0,beginy = 0;//定位初始位置
int flag[50][50]={0};//防止局部递归成环,标记数组
int hash[8] = {0};//为0.0.2版本开发,hash数组保存是否拿到钥匙
void dfs(char **matrix,int x,int y,int blood,int feet){
    if(x<0||x>m-1||y>n-1||y<0||blood==0){//出界,碰撞,血量没了,这个必须放前面,不然会数组越界访问
        feet--;
        return;
    }

    if(matrix[x][y]=='m'){//遇到怪物,扣血
        blood--;
    }
    if(blood==0||matrix[x][y] == '#'){//血量为0,或者撞墙
        feet--;
        return;
    }
    if(matrix[x][y] == 'e'){//到达终点
        if(feet<ans) {
            ans = feet;
        }
        feet--;
        return;
    }
    if(flag[x][y]==0) {//继续递归,并判断是否成环
        flag[x][y] = 1;
        dfs(matrix, x + 1, y, blood, feet + 1);//向右
        dfs(matrix, x, y + 1, blood, feet + 1);//向下
        dfs(matrix, x - 1, y, blood, feet + 1);//向左
        dfs(matrix, x, y - 1, blood, feet + 1);//向上
    }
}
int main(){
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
    dfs(matrix,beginy,beginx,h,feet);
    printf("%d",ans);
}
