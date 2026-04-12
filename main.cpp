#include "src.h"
#include <iostream>
#define endl '\n'
void print_board()
{
    std::cout<<endl;
    for(int i=1;i<=3;i++)
    {
        std::cout<<" "<<chess[(i-1)*3+1]<<" | "<<chess[(i-1)*3+2]<<" | "<<chess[(i-1)*3+3]<<endl;
        if(i<3) std::cout<<"-----------"<<endl;
    }
    std::cout<<endl;
}

bool check_win(char player)
{
    const int lines[8][3]={{1,2,3},{4,5,6},{7,8,9},{1,4,7},{2,5,8},{3,6,9},{1,5,9},{3,5,7}};
    for(int i=0;i<8;i++)
    {
        if(chess[lines[i][0]]==player&&chess[lines[i][1]]==player&&chess[lines[i][2]]==player) return true;
    }
    return false;
}

int main()
{
    for(int i=1;i<=9;i++) chess[i]=' ';
    char human='X',ai='O';
    int turn=0;
    std::cout<<"=== TIC-TAC-TOE MINIMAX ==="<<endl;
    std::cout<<"You are 'X', AI is 'O'."<<endl;
    std::cout<<"Enter num (1-9) to place your piece."<<endl;
    print_board();
    while(true)
    {
        if(turn==0)
        {
            int move;
            std::cout<<"Your move: ";
            std::cin>>move;
            if(move<1||move>9||chess[move]!=' ')
            {
                std::cout<<"[Invalid] Try again."<<endl;
                continue;
            }
            chess[move]=human;
        }
        else
        {
            std::cout<<"AI is thinking..."<<endl;
            std::pair<int,int> res=chess_go(ai);
            int move=(res.first-1)*3+res.second;
            chess[move]=ai;
        }
        print_board();
        if(check_win(human)) {std::cout<<">> YOU WIN! <<"<<endl;break;}
        if(check_win(ai)) {std::cout<<">> AI WINS! <<"<<endl;break;}
        bool full=true;
        for(int i=1;i<=9;i++) if(chess[i]==' ') {full=false;break;}
        if(full) {std::cout<<">> DRAW! <<"<<endl;break;}
        turn=1-turn;
    }
    return 0;
}
