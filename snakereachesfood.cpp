#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

int BOARDSIZE=10;

class food;
class snake;

class board;

class food{
public:
	int food_x,food_y;

    food(){
    	srand(time(NULL));
		food_x=rand()%BOARDSIZE+1;
		food_y=rand()%BOARDSIZE+1;
	}

	void generate_next_food(){
		srand(time(NULL));
		food_x=rand()%BOARDSIZE+1;
		food_y=rand()%BOARDSIZE+1;
	}

};

food maggi;



class snake{
public:
	int head_x,head_y;
	int dir;
	int **is_body;

	snake(){
		is_body=(int **)malloc((BOARDSIZE+1)*sizeof(int *));
		for(int i=0;i<=100;i++){
			is_body[i]=(int *)malloc((BOARDSIZE+1)*sizeof(int));
		}
		for(int i=0;i<=BOARDSIZE;i++){
		}
		srand(time(NULL));
		head_x=rand()%BOARDSIZE+1;
		srand(time(NULL));
		head_y=rand()%BOARDSIZE+1;
		srand(time(NULL));
		dir=rand()%4+1;
		for(int i=1;i<=100;i++){
			for(int j=1;j<=100;j++){
				is_body[i][j]=0;
			}
		}
		is_body[head_x][head_y]=1;
	}
	
	pair<int,int> get_tail(){
		for(int i=1;i<=BOARDSIZE;i++){
			for(int j=1;j<=BOARDSIZE;j++){
				if(is_body[i][j]==1){
					if(head_x==i&&head_y==j)
					continue;
					int count=0;
					if((i-1)>=1&&(i-1)<=BOARDSIZE){
						count+=is_body[i-1][j];
					}
					else if((j+1)>=1&&(j+1)<=BOARDSIZE){
						count+=is_body[i][j+1];
					}
					else if((i+1)>=1&&(i+1)<=BOARDSIZE){
						count+=is_body[i+1][j];
					}
					else if((j-1)>=1&&(j-1)<=BOARDSIZE){
						count+=is_body[i][j-1];
					}
					if(count==1){
						return make_pair(i,j);
					}
				}
			}
		}
	}
	
	int get_direction(){
		if(maggi.food_x<head_x){
			dir=1;
		}
		else if(maggi.food_y>head_y){
			dir=2;
		}
		else if(maggi.food_x>head_x){
			dir=3;
		}
		else if(maggi.food_y<head_y){
			dir=4;
		}
		return dir;
	}

	void move(){
		dir=get_direction();
		pair<int,int> tail=get_tail();
		is_body[tail.first][tail.second]=0;
		if(dir==1){
			is_body[head_x-1][head_y]=1;
			head_x=head_x-1;
		}
		else if(dir==2){
			is_body[head_x][head_y+1]=1;
			head_y=head_y+1;
		}
		else if(dir==3){
			is_body[head_x+1][head_y]=1;
			head_x=head_x+1;
		}
		else{
			is_body[head_x][head_y-1]=1;
			head_y=head_y-1;
		}
	}

};

snake shubham;



class board{
public:

	board(){
		draw();
	}

	void draw(){
		for(int i=0;i<=BOARDSIZE+1;i++){
			if((i==0)||(i==BOARDSIZE+1)){
				for(int a=0;a<=BOARDSIZE;a++){
					printf("/");
				}
				printf("\n");
				continue;
			}
			for(int j=0;j<=BOARDSIZE+1;j++){
				if(j==0){
					cout<<"/";
					continue;
				}
				else if(j==BOARDSIZE+1){
					cout<<"/\n";		
				}
				else if(shubham.is_body[i][j]){
						if(shubham.head_x==i&&shubham.head_y==j)
					    	cout<<"O";
					    else
					    	cout<<"-";

				}
			    else if(maggi.food_x==i&&maggi.food_y==j){
						cout<<"m";
				}
				else{
					cout<<" ";
				}
			}
		}
	}

	void update_board(){
		if(abs(shubham.head_x-maggi.food_x)==1&&abs(shubham.head_y-maggi.food_y)!=1){
			while(shubham.is_body[maggi.food_x][maggi.food_y]==1){
				maggi.generate_next_food();
				cout<<maggi.food_x<<" "<<maggi.food_y;
			}
			pair<int,int> tail=shubham.get_tail();
			shubham.move();
			shubham.is_body[tail.first][tail.second]=1;		
		}
		else if(abs(shubham.head_x-maggi.food_x)==1&&abs(shubham.head_y-maggi.food_y)==1){
			while(shubham.is_body[maggi.food_x][maggi.food_y]==1){
				maggi.generate_next_food();
				cout<<maggi.food_x<<" "<<maggi.food_y;
			}
			pair<int,int> tail=shubham.get_tail();
			shubham.move();
			shubham.is_body[tail.first][tail.second]=1;		
		}
		else{
			shubham.move();
		}
		draw();
	}

};



int main(){
	board b;
	int x=1;
	while(x<=10){
		usleep(1000000);
		b.update_board();
		cout<<"food:\n";
		cout<<maggi.food_x<<"\n";
		cout<<maggi.food_y<<"\n\n";
		cout<<"snake:\n";
		cout<<shubham.head_x<<"\n";
		cout<<shubham.head_y<<"\n\n";
		cout<<"direction of move:\n";
		cout<<shubham.dir<<"\n";
		x+=1;
	}
	
	getchar();
	return 0;
}
