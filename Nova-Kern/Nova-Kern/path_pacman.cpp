//
// Created by 牛天睿 on 16/12/10.
// Copyright (c) 2016 Anzalized. All rights reserved.
//

#include <cmath>
#include "path_pacman.h"


vec2i path_pacman::board={
        {0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,1,0,0,0,0},
        {0,0,1,0,0,1,0,0,0,0},
        {0,1,0,0,0,1,0,1,0,0},
        {0,0,0,0,0,1,0,0,1,1},
        {1,1,0,1,1,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
};

int path_pacman::_id=0;
/* also sets id. */
path_pacman::path_pacman() {
    this->ID=_id;
    _id++;
}
path_pacman::path_pacman(pairi state) {
    this->ID=_id;
    _id++;
    this->state=state;
}



path_pacman::path_pacman(path_pacman* lastone, pairi new_state){
    this->ID=_id;_id++;
    this->state=new_state;
    this->achievement=lastone->get_achievement();
}

list<path_pacman> path_pacman::get_next() {
    pairi state=this->state;
    list<path_pacman> rst;
    int y=state.first,
    x=state.second;
    if(y-1>=0 && this->board[y-1][x]!=1)
        rst.push_back(path_pacman(this , pairi(y-1,x)));

    if(y+1<this->board.size() && this->board[y+1][x]!=1)
        rst.push_back(path_pacman(this, pairi(y+1,x)));

    if(x+1<this->board[y].size() && this->board[y][x+1]!=1)
        rst.push_back(path_pacman(this, pairi(y,x+1)));

    if(x-1>=0 && this->board[y][x-1]!=1)
        rst.push_back(path_pacman(this, pairi(y,x-1)));

    return rst;
}

bool path_pacman::is_goal() {
/*
    cout<<"Y: "<<state.first<<" X: "<<state.second<<" "<<"isgoal? "<<(
            (this->state.first==this->achievement.first &&
                    this->state.second==this->achievement.second)?"yes":"no")<<endl;
                    */
    return (this->state.first==this->achievement.first &&
            this->state.second==this->achievement.second);
}

int path_pacman::cost_fn(path_pacman next) {
    return 1;
}
/* use euclid dst */
int path_pacman::cost_left_fn(path_pacman next) {
    int diffy=this->state.first-next.get_state().first,
    diffx=this->state.second-next.get_state().second;
    return (int)sqrt(diffx*diffx+diffy*diffy);
}

void path_pacman::output() {
    cout<<"y: "<<this->state.first<<"x: "<<this->state.second<<endl;
}

bool path_pacman::operator<(const path_pacman &p) const {
    return this->ID<p.ID;
}

bool path_pacman::operator==(const path_pacman &p) const {
    return (this->state.first==p.state.first && this->state.second==p.state.second);
}
