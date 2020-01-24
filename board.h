#pragma once

#include <vector>
#include<string>
#include "player.h"


class Board
{
    private:
        
        

    public:
        int size;
        std::vector<std::vector<int>> board;
        Player p11,p12,p21,p22;

        Board(int);
        ~Board();


        bool occupied(int,int);
        bool canmove(Player,int,int);
        void move(Player&,int,int);
        void shoot(Player&,int,int);
        void initializeboard();
        void setstartingpositions();
        void printboard();
        std::vector<std::vector<int>> listmoves(Player);
};

Board::Board(int size_)
{
    size = size_;
    initializeboard();

    
}
Board::~ Board()
{

}

void Board::initializeboard()
{
    for(int i=0; i<size; i++){
        std::vector<int> t;
        for(int j=0; j<size; j++){
            t.push_back(0);
        }
        board.push_back(t);
    }
    setstartingpositions();
    
}

void Board::setstartingpositions()
{
    p11.r=size/2-1;
    if(size%2==1)
        p11.r+=1;
    p11.c=0;
    board[p11.r][p11.c] = 1;

    p12.r=size/2;
    p12.c=size-1;
    board[p12.r][p12.c] = 1;

    p21.r=0;
    p21.c=size/2;
    board[p21.r][p21.c] = 1;

    p22.r=size-1;
    p22.c=size/2-1;
    if(size%2==1)
        p22.c+=1;
    board[p22.r][p22.c] = 1;

    /*
    p11.printpos();
    p12.printpos();
    p21.printpos();
    p22.printpos();
    */
}

bool Board::occupied(int r,int c)
{
    if((r<0 || c<0 || r>=size || c>=size) && (r!=0 || c!=0))
        return true;

    return false;
}

bool Board::canmove(Player p,int r_,int c_){
    //to check move in all dirctions
    int direction[8][2] {{1,1},{1,-1},{-1,1},{-1,-1},{0,1},{1,0},{0,-1},{-1,0}};

    if(p.r==r_ && p.c==c_)
        return false;

    for(int i=0;i<8;i++){
        int r=r_;
        int c=c_;
        while(!occupied(r,c)){
            if(p.r==r && p.c==c)
                return true;
            r+=direction[i][0];
            c+=direction[i][1];
        }
    }

    return false;
}

void Board::printboard(){

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            std::cout<<board[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

std::vector<std::vector<int>> Board::listmoves(Player p){
    std::vector<std::vector<int>> moves;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(canmove(p,i,j)){
                moves.push_back({i,j});
            }
        }
    }
    return moves;
}

void Board::move(Player &p,int r,int c){
    if(canmove(p,r,c)){
        board[p.r][p.c] = 0;
        p.updatepos(r,c);
        board[r][c] = 1;
    }
}

void Board::shoot(Player &p,int r,int c){
    if(canmove(p,r,c)){
        board[r][c] = 2;
    }
}
