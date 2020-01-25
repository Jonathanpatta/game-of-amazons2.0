#pragma once

#include <iostream>
#include "board.h"

class Player
{
    private:
    public:
        int r,c;
        int tile;

        Player(int,int,int);
        void printpos();
        void updatepos(int,int);

        
};

Player::Player(int x_=0,int y_=0,int tile_=1){
    r=x_;
    c=y_;
    tile=tile_;
}

void Player::printpos(){
    std::cout<<"{"<<r<<","<<c<<"}\n";
}

void Player::updatepos(int r_,int c_){
    this->r=r_;
    this->c=c_;
}