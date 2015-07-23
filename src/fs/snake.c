#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <string.h>  
#include <time.h>  
#include <windows.h>  

const int mapH = 8;    
const int mapW = 16;    
char Map[mapH][mapW];   //地图  数据类型char[][]

int food[8][2] = {{4,3},{6, 1}, {2, 0}, {8, 9}, {3, 4}, {1,12}, {0, 2}, {5, 13}}; 
int foodNum = 0;
int eat = -1;
int win = 4;

int key;  //按键保存  
int sLength = 1, overOrNot = 0;
int dx[4] = {0, 0, -1, 1};  
int dy[4] = {-1, 1, 0, 0};  
struct Snake{   //蛇的每个节点  
	int x, y;  
	int now;   //方向 0,1,2,3分别为左右上下  
}Snake[mapH*mapW];  //Snakke[0]表示蛇头，之后节点倒排，Snake[1]表示蛇尾。

const char sHead = '@';    
const char sBody = 'O';   
const char sFood = '#';    
const char sNode = '.'; 

void init(); 
void food_init(); //产生食物
void show();
void move();
void checkBorder();
void checkHead(int x, int y);
void action();

int main()   
{  
 init();  
 show();
 return 0;  
}  
void init()  //地图的初始化  
{  
	int i, j;  
	int headx = 0;
	int heady = 0;  
 
	memset(Map, '.', sizeof(Map));  //初始化地图全部为'.'  

	srand(time(0));                                                                                      
	Map[headx][heady] = sHead;  
	Snake[0].x = headx;  
	Snake[0].y = heady;  
	Snake[0].now = -1;  

	food_init();   //随机产生食物  
	for(i = 0; i < mapH; i++)   //地图显示  
	{   
		for(j = 0; j < mapW; j++)  
			printf("%c", Map[i][j]);  
		printf("\n");  
	} 
	printf("按任意方向键 开始游戏\n"); 

	_getch();                                             
	action();

}  



void food_init()  //在地图上随机产生食物  
{  
	int fx, fy;  
	while(1)  
	{  
		fx = food[foodNum][0];                                                                                                     
		fy = food[foodNum][1];       
		if(Map[fx][fy] == '.')  
		{   
			eat++;
			Map[fx][fy] = sFood;  
			break;  
		}
		foodNum ++;
	}  
}  


void show()  //刷新显示地图  
{  
	int i, j;  
	while(1)  
	{    
		Sleep(500); //延迟  milli_delay(500);
		action();   
		move();  
		if(overOrNot)  //游戏结束  
		{   
			printf("\n       Game Over\n");  
			getchar();  
			break;  
		} 
		if(eat == win)
		{
			printf("\n       Congratulations\n");  
			getchar();  
			break; 
		}
		system("cls");   //  =>clear()
		for(i = 0; i < mapH; i++)   
		{   
			for(j = 0; j < mapW; j++)  
			printf("%c", Map[i][j]);  
			printf("\n");  
		}  

		printf("按任意方向键 开始游戏\n");
		printf("eat:%d\n",eat); 
		for(i=0; i < sLength; i++){
			printf("x:%d",Snake[i].x);
			printf("\n");
			printf("y:%d",Snake[i].y);
			printf("\n");
		}
	}  

}  


void move()   //蛇的移动  
{  
	int i, x, y;  
    int t = sLength;
	x = Snake[0].x;  
	y = Snake[0].y;  

	Map[x][y] = '.';  //防止只有蛇头的情况下出现错误

	Snake[0].x = Snake[0].x + dx[ Snake[0].now ];  
	Snake[0].y = Snake[0].y + dy[ Snake[0].now ];  

	checkBorder(); 
	checkHead(x, y);   
	if(sLength == t)  //未吃到食物
		for(i = 1; i < sLength; i++)  //要从蛇尾节点开始  
		{  
			if(i == 1)   //尾节点设置为空再移动  
				Map[ Snake[i].x ][ Snake[i].y ] = '.';  
     
			if(i == sLength-1)  //为蛇头后面的蛇身节点,特殊处理  
			{  
				Snake[i].x = x;  
				Snake[i].y = y;  
				Snake[i].now = Snake[0].now;  
			}  
			else 
			{  
				Snake[i].x = Snake[i+1].x;  
				Snake[i].y = Snake[i+1].y;  
				Snake[i].now = Snake[i+1].now;  
			}  
			Map[ Snake[i].x ][ Snake[i].y ] = 'O'; //移动后要置为'#'蛇身   
		}  
}  

void checkBorder()  //检查蛇头是否越界  
{  
	if(Snake[0].x < 0 || Snake[0].x >= mapH || Snake[0].y < 0 || Snake[0].y >= mapW)  
		overOrNot = 1;  
}  

void checkHead(int x, int y)  //检查下一步蛇头会遇到什么 
{  
    
	if(Map[ Snake[0].x ][ Snake[0].y ] == '.')
		Map[ Snake[0].x ][ Snake[0].y ] = '@';  
	else if(Map[ Snake[0].x ][ Snake[0].y ] == '#')
	{  
		Map[ Snake[0].x ][ Snake[0].y ] = '@';    
		Snake[sLength].x = x;   //新增加节点记录蛇头后一节点的位置  
		Snake[sLength].y = y;  
		Snake[sLength].now = Snake[0].now;  
		Map[ Snake[sLength].x ][ Snake[sLength].y ] = 'O';   
		sLength++;  
		food_init();  
	}  
	else 
		overOrNot = 1;  
}

void action()  //取出按键,并判断方向  
{  
	if(_kbhit() != 0) //检查当前是否有键盘输入，若有则返回一个非0值，否则返回0  
	{   
		while(_kbhit() != 0)  //可能存在多个按键,要全部取完,以最后一个为主  
		key = _getch(); //将按键从控制台中取出并保存到key中  
		switch(key)  
		{   
			case 75:  Snake[0].now = 0;  
			break;   
			case 77:  Snake[0].now = 1;       
			break;    
			case 72:  Snake[0].now = 2;  
			break;   
			case 80:  Snake[0].now = 3;  
			break;  
		}  
	}  
} 