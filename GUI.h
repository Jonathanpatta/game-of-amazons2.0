#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "game.h"
#include "board.h"

class GUIgame : public Game
{
    public:
        int screenheight;
        int screenwidth;
        int framerate;
        int turn;
        int selected;
        bool shoot;
        sf::Font font;
        sf::Texture whitetile;
        std::vector<std::vector<sf::RectangleShape>> gboard;

        
    
    public:
        GUIgame();
        void gameloop();
        void createboard();
        void handlemouseclick(int,int);
        void movepaint(int,std::vector<std::vector<std::vector<int>>>&);
        void addarrow(Player&,int,int);
        void moveplayer(Player&,int,int,std::vector<std::vector<std::vector<int>>>&);
        void drawboard(sf::RenderWindow &);
};

GUIgame::GUIgame()
    : Game(8)
{
    screenheight = 600;
    screenwidth = 600;
    framerate = 60;
    shoot = false;
    turn = 0;
    selected = 0;
    if(!font.loadFromFile("C:\\Users\\Jonathan\\Documents\\random programs\\gitgoa\\game-of-amazons2.0\\textures\\fonts\\OpenSans-Bold.ttf")){
        printf("failed to load text file");
    }
    if(!whitetile.loadFromFile("C:\\Users\\Jonathan\\Documents\\random programs\\gitgoa\\game-of-amazons2.0\\textures\\tiles\\white_tile.jpg")){
        printf("failed to load white tile");
    }
    gameloop();
}

void GUIgame::createboard()
{
    int line=2;
    for(int i=0;i<board.size;i++){
        std::vector<sf::RectangleShape> t;
        for(int j=0;j<board.size;j++){ 
            float len = screenheight/board.size-line;
            sf::RectangleShape rect(sf::Vector2f(len,len));
            rect.setPosition(sf::Vector2f(j*(len+line)+line/2,i*(len+line)+line/2));
            //rect.setFillColor(sf::Color::White);
            if(board.board[i][j]==0){
                rect.setFillColor(sf::Color::White);
                //rect.setTexture(&whitetile);
            }
            if(board.board[i][j]==1 || board.board[i][j]==2){
                rect.setFillColor(sf::Color::Blue);
            }
            if(board.board[i][j]==3 || board.board[i][j]==4){
                rect.setFillColor(sf::Color::Red);
            }     
            t.push_back(rect);
        }
        gboard.push_back(t);
    }
    
}

void GUIgame::drawboard(sf::RenderWindow &window)
{
    for(int i=0;i<gboard.size();i++){
        for(int j=0;j<gboard[0].size();j++){
            window.draw(gboard[i][j]);
            
            
            sf::Text text;
            std::string s = std::to_string(i)+std::to_string(j);
            text.setString(s);
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(12);
            text.setPosition(gboard[i][j].getPosition().x,gboard[i][j].getPosition().y);
            text.setFont(font);
            window.draw(text);
        }
    }
}

void GUIgame::movepaint(int p,std::vector<std::vector<std::vector<int>>> &t)
{
    for(int i=0;i<t.size();i++){
        for(int j=0;j<t[i].size();j++){
            gboard[ t[i][j][0] ][ t[i][j][1] ].setFillColor(sf::Color::White);//.setTexture(&whitetile);
        }
    }

    for(int i=0;i<t.size();i++){
        if(p==i){
            for(int j=0;j<t[i].size();j++){
                gboard[ t[i][j][0] ][ t[i][j][1] ].setFillColor(sf::Color::Green);
            }
        }
    }
}

void GUIgame::addarrow(Player &p,int i, int j)
{
    if(board.canmove(p,i,j)){
        for (int i=0;i<board.size;i++){
            for(int j=0;j<board.size;j++){
                if(board.board[i][j]==0){
                    gboard[i][j].setFillColor(sf::Color::White);//.setTexture(&whitetile);//.setFillColor(sf::Color::White);
                }
            }
        }
        gboard[i][j].setFillColor(sf::Color::Black);
        selected=0;
        shoot = false;
        board.shoot(p,i,j);
        turn++;
    }
}

void GUIgame::moveplayer(Player &p,int i,int j,std::vector<std::vector<std::vector<int>>> &t)
{
    if(board.canmove(p,i,j)){
        for (int i=0;i<board.size;i++){
            for(int j=0;j<board.size;j++){
                if(board.board[i][j]==0){
                    gboard[i][j].setFillColor(sf::Color::White);//.setTexture(&whitetile);//.setFillColor(sf::Color::White);
                }
            }
        }
        gboard[p.r][p.c].setFillColor(sf::Color::White);//.setTexture(&whitetile);//.setFillColor(sf::Color::White);
        board.move(p,i,j);
        t[p.tile-1]=board.listmoves(p);
        movepaint(p.tile-1,t);
        if(p.tile==1 || p.tile==2)
            gboard[i][j].setFillColor(sf::Color::Blue);
        if(p.tile==3 || p.tile==4)
            gboard[i][j].setFillColor(sf::Color::Red);
        shoot=true;
    }
}

void GUIgame::handlemouseclick(int i, int j)
{
    std::vector<std::vector<std::vector<int>>> t;
    auto moves11 = board.listmoves(board.p11);
    auto moves12 = board.listmoves(board.p12);
    auto moves21 = board.listmoves(board.p21);
    auto moves22 = board.listmoves(board.p22);
    t.push_back(moves11);
    t.push_back(moves12);
    t.push_back(moves21);
    t.push_back(moves22);
    if (turn%2==0){        
        
        if (!shoot){
            if (selected==1){
                for(int x=0;x<t[0].size();x++){
                    if(t[0][x][0]==i && t[0][x][1]==j){
                        moveplayer(board.p11,i,j,t);
                        break;
                    }
                }
            }
            else if (selected==2){
                for(int x=0;x<t[1].size();x++){
                    if(t[1][x][0]==i && t[1][x][1]==j){
                        moveplayer(board.p12,i,j,t);
                        break;
                    }
                }
            }
            else{
                if (board.p11.ispos(i,j) && t[0].size()!=0){
                    movepaint(0,t);
                    selected = 1;
                }
                if (board.p12.ispos(i,j) && t[1].size()!=0){
                    movepaint(1,t);
                    selected = 2;
                }
            }
        }
        if(shoot){
            if (selected==1){
                for(int x=0;x<t[0].size();x++){
                    if(t[0][x][0]==i && t[0][x][1]==j){
                        addarrow(board.p11,i,j);
                        break;
                    }
                }
            }
            if (selected==2){
                for(int x=0;x<t[1].size();x++){
                    if(t[1][x][0]==i && t[1][x][1]==j){
                        addarrow(board.p12,i,j);
                        break;
                    }
                }
            }
            /*else{
                if (board.p11.ispos(i,j)){
                    movepaint(0,t);
                    selected = 1;
                }
                if (board.p12.ispos(i,j)){
                    movepaint(1,t);
                    selected = 2;
                }
            }*/
        }
    }
    if (turn%2==1){
        if (!shoot){
            if (selected==3){
                for(int x=0;x<t[2].size();x++){
                    if(t[2][x][0]==i && t[2][x][1]==j){
                        moveplayer(board.p21,i,j,t);
                        break;
                    }
                }
            }
            else if (selected==4){
                for(int x=0;x<t[3].size();x++){
                    if(t[3][x][0]==i && t[3][x][1]==j){
                        moveplayer(board.p22,i,j,t);
                        break;
                    }
                }
            }
            else{
                if (board.p21.ispos(i,j) && t[2].size()!=0){
                    movepaint(2,t);
                    selected = 3;
                }
                if (board.p22.ispos(i,j) && t[3].size()!=0){
                    movepaint(3,t);
                    selected = 4;
                }
            }
        }
        if(shoot){
            if (selected==3){
                //printf("%d",selected);
                for(int x=0;x<t[2].size();x++){
                    if(t[2][x][0]==i && t[2][x][1]==j){
                        //printf("hello");
                        addarrow(board.p21,i,j);
                        break;
                    }
                }
            }
            if (selected==4){
                for(int x=0;x<t[3].size();x++){
                    if(t[3][x][0]==i && t[3][x][1]==j){
                        addarrow(board.p22,i,j);
                        break;
                    }
                }
            }
            /*else{
                if (board.p11.ispos(i,j)){
                    movepaint(0,t);
                    selected = 1;
                }
                if (board.p12.ispos(i,j)){
                    movepaint(1,t);
                    selected = 2;
                }
            }*/
        }
    }
    
}

void GUIgame::gameloop()
{
    sf::RenderWindow window(sf::VideoMode(screenheight,screenwidth),"game of amazons!");    
    window.setFramerateLimit(framerate);
    createboard();
    while(window.isOpen())
    {
        //Timer timer;
        sf::Event event;
        window.clear(sf::Color(30,30,30,255));
        while (window.pollEvent(event))
        {            
            
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed){
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                int j = (int) x*board.size/screenwidth;
                int i = (int) y*board.size/screenheight;
                handlemouseclick(i,j);
            }
        }
        drawboard(window);
        if(isgameend()){
            sf::Text text;
            text.setFont(font);
            text.setPosition(0,0);
            text.setCharacterSize(72);
            if(board.listmoves(board.p11).size()==0&&board.listmoves(board.p12).size()==0){
                text.setString("Player2 won!!");
                text.setFillColor(sf::Color::Red);
            }
            else{
                text.setString("Player1 won!!");
                text.setFillColor(sf::Color::Blue);            
            }
            window.draw(text);
        }
        window.display();

    }
}