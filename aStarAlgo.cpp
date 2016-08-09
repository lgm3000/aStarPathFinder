#define endline	std::cout << "\n"
#define Ver	4
#define Dia	6

#include<iostream>
#include<cstdlib>
#include<cstdio>

class point{
public:
	void update(int i,int j,int ox,int oy,int ng);

//private:
	int x,y,o_x,o_y,f,g,h;
};

static point aka[22][22],mini;

static int map[22][22] = {0},min;

void printMap();
void printMapF();
void printMapG();
void printMapH();
void pause(int n);
void surroundCheck(int x,int y);

int main()
{

	srand (time(NULL));
	for(int i=0;i<22;i++) map[i][0] = map[i][21] = map[0][i] = map[21][i] = -1;

	map[2][1] = -1;
	map[2][2] = -1;
	map[2][3] = -1;
	map[1][5] = -1;
	map[2][5] = -1;
	map[3][5] = -1;
	map[4][5] = -1;

	map[5][4] = -1;
	map[5][5] = -1;
	map[5][6] = -1;
	map[5][7] = -1;
	map[16][17] = -1;
	map[17][17] = -1;
	map[18][17] = -1;
	map[19][17] = -1;
	map[20][17] = -1;

	for(int i = 0;i< 60; i++){map[(rand()*1000)%10+10][rand()*1000%15 + 5] = -1;}
	
	for(int i=20;i>0;i--){
		for(int j=20;j>0;j--) aka[i][j].h = (40-i-j)*(Ver+1);
}
	


	int i = 1, j = 1;


	do{
		map[i][j] = 2;
		surroundCheck(i,j);
		printMapF();
//		printMapG();	
		printMap();
		if(!(i == mini.o_x&&j==mini.o_y))		
			{map[i][j] = 8;}
		else	
			map[mini.o_x][mini.o_y] = 9;
		i = mini.x;j = mini.y;
		getchar();
	}while(!(i==20&&j==20));
	
	i = 20;j = 20;
	do{
		map[i][j] = 6;
		mini = aka[i][j];
		i = mini.o_x;
		j = mini.o_y;
	}while(!(i==1&&j==1));
	printMap();

	


}
void pause(int n){
for(int i = 0;i< n ;i++)
	for(int j = 0;j< n ;j++) j=j;
}

void printMap(){
	for(int i=0;i<22;i++){
		for(int j=0;j<22;j++) {std::cout.width(3);std::cout << map[i][j];}
		endline;
	}
	endline;

}
void printMapF(){
	for(int i=0;i<22;i++){
		for(int j=0;j<22;j++) {std::cout.width(3);std::cout << (aka[i][j].f * (map[i][j]==1?1:0));}
		endline;
	}
	endline;

}
void printMapG(){
	for(int i=0;i<22;i++){
		for(int j=0;j<22;j++) {std::cout.width(3);std::cout << aka[i][j].g;}
		endline;
	}
	endline;

}
void printMapH(){
	for(int i=0;i<22;i++){
		for(int j=0;j<22;j++) {std::cout.width(3);std::cout << aka[i][j].h;}
		endline;
	}
	endline;

}


void point::update(int i,int j,int ox,int oy,int ng){
	x= i;y = j;o_x = ox;o_y = oy;g = ng;f = g + h;
}

void addLive(int o_x,int o_y,int x,int y,int code, int newg){
	aka[x][y].update(x,y,o_x,o_y,newg);
	map[x][y] = 1;
	if(aka[x][y].f < min) mini = aka[x][y];
}


void surroundCheck(int x,int y){
	if(map[x-1][y-1] == 0 && (map[x-1][y]!=-1 && map[x][y-1]!=-1))	addLive(x,y,x-1,y-1,1,aka[x][y].g+Dia);
	if(map[x+1][y+1] == 0 && (map[x+1][y]!=-1 && map[x][y+1]!=-1))	addLive(x,y,x+1,y+1,8,aka[x][y].g+Dia);
	if(map[x-1][y+1] == 0 && (map[x-1][y]!=-1 && map[x][y+1]!=-1))	addLive(x,y,x-1,y+1,3,aka[x][y].g+Dia);
	if(map[x+1][y-1] == 0 && (map[x+1][y]!=-1 && map[x][y-1]!=-1))	addLive(x,y,x+1,y-1,6,aka[x][y].g+Dia);
	if(map[x-1][y] == 0)	addLive(x,y,x-1,y  ,2,aka[x][y].g+Ver);
	if(map[x+1][y] == 0)	addLive(x,y,x+1,y  ,7,aka[x][y].g+Ver);
	if(map[x][y-1] == 0)	addLive(x,y,x  ,y-1,4,aka[x][y].g+Ver);
	if(map[x][y+1] == 0)	addLive(x,y,x  ,y+1,5,aka[x][y].g+Ver);

	min = 999999;
	for(int i = 1;i<21;i++)
		for(int j = 1;j<21;j++)
			if(map[i][j] == 1 && aka[i][j].f < min) {mini = aka[i][j];min = mini.f;}
}
