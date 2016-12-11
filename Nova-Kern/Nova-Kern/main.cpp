//
//  main.cpp
//  Nova-Kern
//
//  Created by 牛天睿 on 16/12/5.
//  Copyright (c) 2016 Anzalized. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include "astar.hpp"
#include "path_pacman.h"
#include "Path8.h"
using std::vector;
using std::merge;
using std::list;
using std::map;
using std::cout;
using std::endl;

using namespace nova_kernel;



/******************************************/




int main(int argc, const char * argv[]) {

    /* digit 8 */

    int init[3][3] = {{2, 8, 3}, {1, 6, 4}, {7, -1, 5}};
    //int init[3][3]={{2,3,8},{1,6,4},{7,-1,5}};
    Path8 p = Path8(init);
    a_star<Path8> astar_digit8;
    astar_digit8.init_path(p);
    astar_digit8.search();
    list<Path8> lp8;
    astar_digit8.get_all_paths(lp8);//get all the paths to go.
    for(auto _p : lp8){
        _p.output();
    }


    /* pacman */

    path_pacman pp1=path_pacman(pair<int,int>(0,0));

    pp1.set_destination(pair<int,int>(9,9));

    a_star<path_pacman> astar_pacman1;
    astar_pacman1.init_path(pp1);

    astar_pacman1.search();
    path_pacman pnext;
    if(astar_pacman1.get_next_path(pp1, pnext))//get next path to go.
        pnext.output();


    return 0;
}
