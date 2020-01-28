# pragma once

#include<iostream>
#include<vector>
#include "board.h"
#include "timing.h"

class Game
{
    private:
    public:
        Board board;
    public:
        Game(int);
        void begin();
        bool isgameend();
        void move(int);
        void takehumaninput(std::vector<std::vector<int>>,int&,int&);
};

Game::Game(int boardsize)
        : board(Board(boardsize))
{

}

bool Game::isgameend(){
    //Timer timer;
    //<1ms for square boards of less than 20*20
    auto t1 = board.listmoves(board.p11);
    auto t2 = board.listmoves(board.p12);

    auto t3 = board.listmoves(board.p21);
    auto t4 = board.listmoves(board.p22);

    if(t1.size()==0 && t2.size()==0){
        return true;
    }
    if(t3.size()==0 && t4.size()==0){
        return true;
    }
    
    return false;
}

void Game::takehumaninput(std::vector<std::vector<int>> moves,int &row,int &col)
{
    std::cout<<"list of moves for player:\n";
    for(int i=0; i<moves.size(); i++){
        std::cout<<"("<< moves[i][0] <<","<< moves[i][1]<<")\n";
    }
    printf("enter row and column in format(row,col) : ");
    scanf("%d,%d",&row,&col);
}

void Game::move(int turn)
{
    if(turn==1)
    {
        int pin;
        int row,col;
        std::cout<<"press 1 for p11 or 2 for p12: ";
        std::cin>>pin;
        if(pin==1){
            auto moves = board.listmoves(board.p11);
            takehumaninput(moves,row,col);
            board.move(board.p11,row,col);
            board.p11.printpos();
            board.printboard();
            auto shootmoves = board.listmoves(board.p11);
            takehumaninput(shootmoves,row,col);
            board.shoot(board.p11,row,col);
        }
        else{
            auto moves = board.listmoves(board.p12);
            takehumaninput(moves,row,col);
            board.move(board.p12,row,col);
            board.printboard();
            auto shootmoves = board.listmoves(board.p12);
            takehumaninput(shootmoves,row,col); 
            board.shoot(board.p12,row,col);
        }        
    }
    else
    {
        int pin;
        int row,col;
        std::cout<<"press 1 for p21 or 2 for p22: ";
        std::cin>>pin;
        if(pin==1){
            auto moves = board.listmoves(board.p21);
            takehumaninput(moves,row,col);
            board.move(board.p21,row,col);
            board.printboard();
            auto shootmoves = board.listmoves(board.p21);
            takehumaninput(shootmoves,row,col);
            board.shoot(board.p21,row,col);
        }
        else{
            auto moves = board.listmoves(board.p22);
            takehumaninput(moves,row,col);
            board.move(board.p22,row,col);
            board.printboard();
            auto shootmoves = board.listmoves(board.p22);
            takehumaninput(shootmoves,row,col);
            board.shoot(board.p22,row,col);
        }
    }
    
}

void Game::begin(){
    int turn=1;
    while(!isgameend())
    {
        board.printboard();
        move(turn);

        turn = turn==1? turn=2 : turn=1;     
    }
}