//
// Created by 牛天睿 on 16/12/10.
// Copyright (c) 2016 Anzalized. All rights reserved.
//

#ifndef NOVA_KERN_PATH_PACMAN_H
#define NOVA_KERN_PATH_PACMAN_H

#include <array>
#include "astar.hpp"

using namespace nova_kernel;

using std::pair;
using vec2i=std::vector<std::vector<int>>;
using pairi=std::pair<int,int>;


class path_pacman : public Path<pairi>{
private:


    static vec2i board;
    pairi state;
    pairi achievement;//the achievement may not be used.
    /* TODO : replace thisone with a safer method. */
    static int _id; //global id counter.
    int ID;
    //static int _id;
public:

    path_pacman();
    path_pacman(pairi state);
    path_pacman(path_pacman * lastone, pairi new_state);

    inline void set_destination(pairi dst){this->achievement=dst;}
    double total_cost;
    double cost_so_far;
    list<path_pacman> get_next();
    inline pairi get_state() {return this->state;}
    inline pairi get_achievement() {return this->achievement;}
    bool is_goal();
    int cost_fn(path_pacman next);
    int cost_left_fn(path_pacman next);
    void output();
    bool operator<(const path_pacman &p)const;
    bool operator==(const path_pacman &p)const;

};



#endif //NOVA_KERN_PATH_PACMAN_H

