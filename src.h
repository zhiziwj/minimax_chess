#ifndef MINIMAX_H
#define MINIMAX_H
#include <bits/stdc++.h>
char chess[10];//1~9
const int win_line[9][3]={
	{0,0,0},{1,5,9},{3,5,7},
	{1,2,3},{4,5,6},{7,8,9},
	{1,4,7},{2,5,8},{3,6,9}
};
std::pair<int,int> chess_go(char me);
inline int p(int i,int j){
	return (i-1)*3+j;
}
int E(char me){
	char op;
	if(me=='X'){
		op='O';
	}
	else{
		op='X';
	}
	for(int i=1;i<=8;i++){
		bool me_win=true,op_win=true;
		for(int j=0;j<3;j++){
			if(chess[win_line[i][j]]!=me){
				me_win=false;
			}
		}
		for(int j=0;j<3;j++){
			if(chess[win_line[i][j]]!=op){
				op_win=false;
			}
		}
		if(me_win){
			return 1e5;
		}
		else if(op_win){
			return -1e5;
		}
	}
	int score=0;
	for(int i=1;i<=8;i++){
		int my_cnt=0,op_cnt=0;
		for(int j=0;j<3;j++){
			if(chess[win_line[i][j]]==me){
				my_cnt++;
			}
			else if(chess[win_line[i][j]]==op){
				op_cnt++;
			}
		}
		if(op_cnt>0){
			if(my_cnt>0&&op_cnt==2){
				score+=10;
			}
			else if(my_cnt==0&&op_cnt==2){
				score-=20;
			}
			else if(my_cnt==0&&op_cnt==1){
				score-=1;
			}
			continue;
		}
		if(my_cnt==2&&op_cnt<1){
			score+=6;
		}
		else if(my_cnt==1){
			score+=2;
		}
	}
	if(chess[5]==me){
		score+=2;
	}
	return score;
}
int minimax(int deep,bool is_me,char me){
	char op;
	if(me=='X'){
		op='O';
	}
	else{
		op='X';
	}
	int score=E(me);
	if(score>=1e5||score<=-1e5||deep<=0){
		return score;
	}
	if(is_me){
		int maxx=-1e9;
		for(int i=1;i<=9;i++){
			if(chess[i]==' '){
				chess[i]=me;
				maxx=std::max(maxx,minimax(deep-1,false,me));
				chess[i]=' ';
			}
		}
		return maxx;
	}
	else{
		int minn=1e9;
		for(int i=1;i<=9;i++){
			if(chess[i]==' '){
				chess[i]=op;
				minn=std::min(minn,minimax(deep-1,true,me));
				chess[i]=' ';
			}
		}
		return minn;
	}
}
std::pair<int,int> chess_go(char me){
	std::pair<int,int> ans;
	int maxx=-1e6,deep=-1;//-1e6<-1e5
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			if(chess[p(i,j)]==' '){
				deep++;
			}
		}
	}
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			if(chess[p(i,j)]==' '){
				chess[p(i,j)]=me;
				int val=minimax(deep,false,me);
				chess[p(i,j)]=' ';
				if(val>maxx){
					maxx=val;
					ans=std::make_pair(i,j);
					//printf("DEBUG: AI chose row %d, col %d, score %d\n", i, j, val);
				}
			}
		}
	}
	return ans;
}
#endif 
