#pragma once

#include <iostream>
#include "board.h"

class Player
{
    private:
    public:
        int r,c;

        Player(int,int);
        void printpos();
        void updatepos(int,int);

        
};

Player::Player(int x_=0,int y_=0){
    r=x_;
    c=y_;
}

void Player::printpos(){
    std::cout<<"{"<<r<<","<<c<<"}\n";
}

void Player::updatepos(int r_,int c_){
    r=r_;
    c=c_;
}