#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <string.h>  
#include <time.h>  
#include <windows.h>  
const int mapH = 8;    
const int mapW = 16;    
char Map[mapH][mapW];   //地图  数据类型char[][]
int  key;  //按键保存  
int  sLength = 1, overOrNot = 0;
int  dx[4] = {0, 0, -1, 1};  
int  dy[4] = {-1, 1, 0, 0};  
struct Snake   //蛇的每个节点  
{  
 int x, y;  
 int now;   //方向 0,1,2,3分别为左右上下  
}Snake[mapH*mapW];  
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

int main()   
{  
 init();  

 return 0;  
}  
void init()  //地图的初始化  
{  
 int i, j;  
 int headx = 0;
 int heady = 0;  
 
 memset(Map, '.', sizeof(Map));  //初始化地图全部为空'.'  

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

}  



void food_init()  //在地图上随机产生食物  
{  
	int fx, fy;  
	while(1)  
	{  
		fx = rand()%mapH;                                                                                                     
		fy = rand()%mapW;       
		if(Map[fx][fy] == '.')  //不能出现在蛇所占有的位置  
		{   
			Map[fx][fy] = sFood;  
			break;  
		}  
	}  
}  

void Show()  //刷新显示地图  
{  
	int i, j;  
	while(1)  
	{    
		Sleep(500); //   milli_delay(500);
		move();  
		if(overOrNot)  /游戏结束  
		{   
			printf("\n       Game Over\n");  
			getchar();  
			break;  
		}  
		for(i = 0; i < mapH; i++)   
		{   
			for(j = 0; j < mapW; j++)  
			printf("%c", Map[i][j]);  
			printf("\n");  
		}  
	}  
}  


void Move()  
{  
	int i, x, y;  
    int t = sLength;
	x = Snake[0].x;  
	y = Snake[0].y;  
	Map[x][y] = '.';  
	Snake[0].x = Snake[0].x + dx[ Snake[0].now ];  
	Snake[0].y = Snake[0].y + dy[ Snake[0].now ];  
	checkBorder();   //蛇头是否越界  
	checkHead(x, y);  //蛇头移动后的位置情况 
	if(sLength == t)  //未吃到食物  
    for(i = 1; i < sLength; i++)  
	{  
		if(i == 1)   //尾节点设置为空再移动  
			Map[ Snake[i].x ][ Snake[i].y ] = '.';  
     
		if(i == sLength-1)  
		{  
			Snake[i].x = x;  
			Snake[i].y = y;  
			Snake[i].now = Snake[0].now;  
		}  
		else   //其他蛇身即走到前一个蛇身位置  
		{  
			Snake[i].x = Snake[i+1].x;  
			Snake[i].y = Snake[i+1].y;  
			Snake[i].now = Snake[i+1].now;  
		}  
		Map[ Snake[i].x ][ Snake[i].y ] = '#';    
	}  
}  

void checkBorder()  //检查蛇头是否越界  
{  
	if(Snake[0].x < 0 || Snake[0].x >= mapH || Snake[0].y < 0 || Snake[0].y >= mapW)  
		overOrNot = 1;  
}  

void checkHead(int x, int y)   
{  
    
	if(Map[ Snake[0].x ][ Snake[0].y ] == '.')  //为空  
		Map[ Snake[0].x ][ Snake[0].y ] = '@';  
	else if(Map[ Snake[0].x ][ Snake[0].y ] == '*')  //食物  
	{  
		Map[ Snake[0].x ][ Snake[0].y ] = '@';    
		Snake[sLength].x = x;     
		Snake[sLength].y = y;  
		Snake[sLength].now = Snake[0].now;  
		Map[ Snake[sLength].x ][ Snake[sLength].y ] = '#';   
		sLength++;  
		food_init();  
	}  
	else 
		overOrNot = 1;  
}