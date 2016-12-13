//
// Created by 牛天睿 on 16/12/10.
// Copyright (c) 2016 Anzalized. All rights reserved.
//

#ifndef NOVA_KERN_PATH8_H
#define NOVA_KERN_PATH8_H


#include "astar.hpp"

using namespace nova_kernel;


class Path8 : public Path<int[3][3]> {

private:

    static int achievement[3][3];
    int state[3][3];
    /* TODO : replace thisone with a safer method. */
    static int _id;  //global id counter.

    int ID;

    /* aux fns */
    int matrix_diff(int b[3][3]);
    void find__1(int & i, int & j);
    void rotatef(int b[3][3], int i1, int j1, int i2, int j2);
    void printm();

public:


    /* members */
    double cost_so_far;
    double total_cost;


    Path8();
    Path8(int state[3][3]);


    list<Path8> get_next(); /* path containing get next state */
    /* check wether the state has achieved goal. */
    inline bool is_goal(){return this->matrix_diff(this->achievement)==0;}
    inline int cost_fn(Path next){return 1;}
    inline int cost_left_fn(Path p){return this->matrix_diff(this->achievement);}

    /* used in the map */

    bool operator<(const Path8 &p) const{return (this->ID < p.ID);}



    /* use state eq */
    bool operator==(const Path8 &p)const{
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(this->state[i][j]!=p.state[i][j])return false;
            }
        }
        return true;
    }

    inline void output(){this->printm();}


};

#endif //NOVA_KERN_PATH8_H
