#include<cstdio>
#include<list>
#include<map>
#include<iostream>
#include<fstream>

#define endline std::cout << std::endl
class g_map;
int gen = 0;
void pause(int n);
void printMap(std::pair<int,int> pos, g_map map);
void printMap(g_map map);
class g_map{
public:
	g_map(int i,int j):x(i),y(j){};
	const int wall(int i,int j) const;
	const int len() const;
	const int wid() const;
	void set(int i,int j,int n);

private:
	int x,y,a[102][102];
};



class player{

public:
	player(int x,int y,g_map ma):cur_x(x),cur_y(y),map(ma){movVer = 5; movDia = 7;hOffset = 6;wallOffset = 4;};
	void aStar(int x,int y);
	bool wanttomove();
	std::pair<int,int> move();

private:
	int movVer,movDia,hOffset,wallOffset;
	int cur_x, cur_y, target_x,target_y;
	std::list<std::pair<int,int> > Route;
	g_map map;
	std::map<std::pair<int,int>,std::pair<int,int> > route;
};

int main()
{
//input map
std::ifstream fin;
fin.open("map.txt");
g_map italy(20,20);
int n;
for(int i = 1; i<=20; i++)
	for(int j = 1; j<=20; j++){
		fin >> n;italy.set(i,j,n);}
italy.set(1,1,0);
italy.set(20,20,0);
std::cout << "Input complete Press Enter to Continue\n";
//getchar();
printMap(italy);
player cattafi(1,1,italy);
cattafi.aStar(20,20);
std::cout <<"Calc complete,generated"<<gen<<"blocks\n";
while(cattafi.wanttomove()){
	printMap(cattafi.move(),italy);
	//pause(10000);
}
return 0;
}



void player::aStar(int x,int y){
	route.clear();
	int len = map.len(), wid = map.wid(), p = cur_x, q = cur_y;
	
	int f[len+2][wid+2],g[len+2][wid+2],h[len+2][wid+2],l[len+2][wid+2];

	std::list<std::pair<int,int> > livePoint;
	std::list<std::pair<int,int> >::iterator it;
	for(int i = 0; i < len+2; i++)
		for(int j = 0; j < wid+2; j++) 
			{l[i][j] = map.wall(i,j);
			f[i][j] = g[i][j] = h[i][j] = 0;			
			}
	for(int i=0;i<len+2;i++) l[i][wid+1] = l[i][0] = -1;
	for(int i=0;i<wid+2;i++) l[len+1][i] = l[0][i] = -1;

	//Give H value to matrix
	//Using distance, + wall offset algorithm
	for(int i = x+1; i <= len; i++) h[i][y] = h[i-1][y] + hOffset + -l[i][y] * wallOffset;
	for(int i = x-1; i >= 1  ; i--) h[i][y] = h[i+1][y] + hOffset + -l[i][y] * wallOffset;
	for(int i = 1; i <= len; i++)
		for(int j = y+1; j <= wid; j++) h[i][j] = h[i][j-1] + hOffset + -l[i][j] * wallOffset;
	for(int i = 1; i <= len; i++)
		for(int j = y-1; j >= 1  ; j--) h[i][j] = h[i][j+1] + hOffset + -l[i][j] * wallOffset;



		
	std::pair<int,int> op(p,q);
	l[p][q] = 1;
	while(p!=x || q!=y){
		int i;
		if(l[p-1][q-1] == 0 && (l[p-1][q]!=-1 && l[p][q-1]!=-1)){
			g[p-1][q-1] = g[p][q]+movDia;f[p-1][q-1] = g[p-1][q-1]+h[p-1][q-1];l[p-1][q-1] = 1;
			i=0;	
			it = livePoint.begin();
			l[p-1][q-1] = 1;
			while(it != livePoint.end() && f[it->first][it->second]<f[p-1][q-1]) it++;
			std::pair<int,int> pr(p-1,q-1);
			livePoint.insert(it,pr);
			route[pr] = op;
			gen++;
		}
		if(l[p+1][q+1] == 0 && (l[p+1][q]!=-1 && l[p][q+1]!=-1)){
			g[p+1][q+1] = g[p][q]+movDia;f[p+1][q+1] = g[p+1][q+1]+h[p+1][q+1];l[p+1][q+1] = 1;
			i=0;	
			it = livePoint.begin();
			l[p+1][q+1] = 1;
			while(it != livePoint.end() && f[it->first][it->second] < f[p+1][q+1]) it++;
			std::pair<int,int> pr(p+1,q+1);
			livePoint.insert(it,pr);
			route[pr] = op;
			gen++;
		}
		if(l[p-1][q+1] == 0 && (l[p-1][q]!=-1 && l[p][q+1]!=-1)){
			g[p-1][q+1] = g[p][q]+movDia;f[p-1][q+1] = g[p-1][q+1]+h[p-1][q+1];l[p-1][q+1] = 1;
			i=0;	
			it = livePoint.begin();		
			l[p-1][q+1] = 1;
			while(it != livePoint.end() && f[it->first][it->second]<f[p-1][q+1]) it++;
			std::pair<int,int> pr(p-1,q+1);
			livePoint.insert(it,pr);
			route[pr] = op;
			gen++;
		}
		if(l[p+1][q-1] == 0 && (l[p+1][q]!=-1 && l[p][q-1]!=-1)){
			g[p+1][q-1] = g[p][q]+movDia;f[p+1][q-1] = g[p+1][q-1]+h[p+1][q-1];l[p+1][q-1] = 1;
			i=0;	
			it = livePoint.begin();		
			l[p+1][q-1] = 1;
			while(it != livePoint.end() && f[it->first][it->second]<f[p+1][q-1]) it++;
			std::pair<int,int> pr(p+1,q-1);
			livePoint.insert(it,pr);
			route[pr] = op;
			gen++;
		}
		if(l[p-1][q] == 0){
			g[p-1][q] = g[p][q]+movVer;f[p-1][q] = g[p-1][q]+h[p-1][q];l[p-1][q] = 1;
			i=0;	
			it = livePoint.begin();
			l[p-1][q] = 1;
			while(it != livePoint.end() && f[it->first][it->second]<f[p-1][q]) it++;
			std::pair<int,int> pr(p-1,q);
			livePoint.insert(it,pr);
			route[pr] = op;
			gen++;
		}
		if(l[p+1][q] == 0){
			g[p+1][q] = g[p][q]+movVer;f[p+1][q] = g[p+1][q]+h[p+1][q];l[p+1][q] = 1;
			i=0;	
			it = livePoint.begin();
			l[p+1][q] = 1;
			while(it != livePoint.end() && f[it->first][it->second]<f[p+1][q]) it++;
			std::pair<int,int> pr(p+1,q);
			livePoint.insert(it,pr);
			route[pr] = op;
			gen++;
		}
		if(l[p][q-1] == 0){
			g[p][q-1] = g[p][q]+movVer;f[p][q-1] = g[p][q-1]+h[p][q-1];l[p][q-1] = 1;
			i=0;	
			it = livePoint.begin();
			l[p][q-1] = 1;
			while(it != livePoint.end() && f[it->first][it->second]<f[p][q-1]) it++;
			std::pair<int,int> pr(p,q-1);
			livePoint.insert(it,pr);
			route[pr] = op;
			gen++;
		}
		if(l[p][q+1] == 0){
			g[p][q+1] = g[p][q]+movVer;f[p][q+1] = g[p][q+1]+h[p][q+1];l[p][q+1] = 1;
			i=0;	
			it = livePoint.begin();
			l[p][q+1] = 1;
			while(it != livePoint.end() && f[it->first][it->second]<f[p][q+1]) it++;
			std::pair<int,int> pr(p,q+1);
			livePoint.insert(it,pr);
			route[pr] = op;
			gen++;
		}
		
		p = livePoint.begin()->first;
		q = livePoint.begin()->second;
		op.first  = p;
		op.second = q;
		livePoint.pop_front();
		
		for(int i=0;i<len+2;i++){
			for(int j=0;j<wid+2;j++) {std::cout.width(3);std::cout << f[i][j] << " ";}
			//for(int j=0;j<wid+2;j++) {std::cout.width(2);std::cout << g[i][j] << " ";}
			//for(int j=0;j<wid+2;j++) {std::pair<int,int> pr(i,j);std::cout << route[pr].first << ","<<route[pr].second << "|";}
			endline;
		}
		endline;
		

	}
	std::pair<int,int> pr(x,y);
	op.first  = cur_x;
	op.second = cur_y;
	while(pr != op){
		/*std::cout <<"cur"<< pr.first << "," <<pr.second;
		endline;
		std::cout <<"next"<<route[pr].first << "," <<route[pr].second;
		endline;
		endline;*/
		Route.push_front(pr);
		pr = route[pr];
	}

}
std::pair<int,int> player::move(){
	std::list<std::pair<int,int> >::iterator it = Route.begin();
	std::pair<int,int> tmp = *it;
	Route.pop_front();
	return *it;

}
bool player::wanttomove(){
	if(Route.begin()!=Route.end()) return true;
	return false;
}

const int g_map::len() const{
	return x;
}
const int g_map::wid() const{
	return y;
}
const int g_map::wall(int i,int j) const{
	return a[i][j];
}
void g_map::set(int i,int j,int n){
	a[i][j] = n;
}

void printMap(std::pair<int,int> pos, g_map map){
	std::cout << "+-";
	for(int i=1;i<=map.len();i++)	std::cout << "--";
	std::cout << "-+\n";
	for(int i=1;i<=map.len();i++){
		std::cout << "| ";
		for(int j=1;j<=map.wid();j++)
			if(pos.first==i&&pos.second == j) std::cout << "0 ";
			else if(map.wall(i,j)) std::cout << "# ";
			else std::cout << "  ";
		std::cout << " |\n";
		}
	std::cout << "+-";
	for(int i=1;i<=map.len();i++)	std::cout << "--";
	std::cout << "-+\n";
}
void printMap(g_map map){
	std::cout << "+-";
	for(int i=1;i<=map.len();i++)	std::cout << "--";
	std::cout << "-+\n";
	for(int i=1;i<=map.len();i++){
		std::cout << "| ";
		for(int j=1;j<=map.wid();j++)
			if(map.wall(i,j)) std::cout << "# ";
			else if(i==1 && j==1) std::cout << "0 ";
			else std::cout << "  ";
		std::cout << " |\n";
		}
	std::cout << "+-";
	for(int i=1;i<=map.len();i++)	std::cout << "--";
	std::cout << "-+\n";
}


void pause(int n){
for(int i = 0;i< n ;i++)
	for(int j = 0;j< n ;j++) j=j;
}
