 /**------------------------------**
    user:Liujiahuan
    Time:2021/12/13   17：28
    For:XUPT 2nd ACM new student ACM competition
    Editon:Final
    Description:Just finish normal maze without monster and door&keys
**------------------------------*/
#include <stdio.h>
#include <stdlib.h>
int ans = 5000;
int key[8] = {0};//keys
int ansblood=0;
int flag[5][5]={0};//防止局部递归成环,标记数组
int n = 0,m = 0;//长,宽
int h = 0,feet=0;//血量,步数初始化
int beginx = 0,beginy = 0;//定位初始位置
void dfs(char **matrix,int x,int y,int blood,int feet,int key[8],int flag[50][50]){//
    if(x<0||x>=m||y>=n||y<0||flag[x][y]==1||matrix[x][y] == '#'){//出界,碰撞,血量没了,这个必须放前面,不然会数组越界访问
        feet--;
        return;
    }
    if(matrix[x][y]=='m'){//遇到怪物,扣血
        blood--;
    }
    if(blood<=0){
      //  printf(" %d %d failed,back\n",x,y);
        feet--;
        return;
    }
    if(matrix[x][y]=='A'||matrix[x][y]=='B'||matrix[x][y]=='C'||matrix[x][y]=='D'||matrix[x][y]=='E'||matrix[x][y]=='F'||matrix[x][y]=='G'||matrix[x][y]=='H'){
        key[matrix[x][y]-'A']=1;
    }
    if(matrix[x][y]=='1'||matrix[x][y]=='2'||matrix[x][y]=='3'||matrix[x][y]=='4'||matrix[x][y]=='5'||matrix[x][y]=='6'||matrix[x][y]=='7'||matrix[x][y]=='0') {
        if(key[matrix[x][y]-'0']!=1){
            feet--;
            return;
        }
    }
    if(matrix[x][y] == 'e'){//到达终点
        if(feet<ans) {
            ans = feet;
            ansblood =blood;
        }
        feet--;
        return;
    }
    flag[x][y] = 1;
    dfs(matrix, x + 1, y, blood, feet + 1,key,flag);//向右
    dfs(matrix, x, y + 1, blood, feet + 1,key,flag);//向下
    dfs(matrix, x - 1, y, blood, feet + 1,key,flag);//向左
    dfs(matrix, x, y - 1, blood, feet + 1,key,flag);//向上
    flag[x][y] = 0;
    if(matrix[x][y]=='A'||matrix[x][y]=='B'||matrix[x][y]=='C'||matrix[x][y]=='D'||matrix[x][y]=='E'||matrix[x][y]=='F'||matrix[x][y]=='G'||matrix[x][y]=='H'){
        key[matrix[x][y]-'A']=0;
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
    dfs(matrix,beginy,beginx,h,feet,key,flag);
    printf("%d\n",ans);
}

/*样例已经过了，总结一点问题吧，
1.为什么打flag必须要在判断完全部以后？
2.为什么retrurn的时候，key的状态还是会得到保存？在这里我强行在dfs四个方向后判断这个点是不是拿了钥匙，如果拿了就要=0取消掉，突然有个想法，（或者是key其实没有保存，成功回滚了，只不过数据的原因。问题都出在了四个方向都判断了的基础上？）
3.1，2矛盾，否则flag数组也就没用了啊。。。。
4.文件作用域变量可以用于函数传递局部参数吗
*/

/*ans
1.因为你用的是上一层的递归里面的数组，所以操作的是上一个。懂我意思吧，类似这种输出结果

我的flag数组是
10000
00000
00000
00000
00000
我的flag数组是
11000
10000
00000
00000
00000

2.没错，就是你最后总结的那样
3.是的，所以flag数组回滚没问题
4.可以，和在main函数里面一样
*/
