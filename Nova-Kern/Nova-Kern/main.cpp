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

    int init[3][3]={{2,8,3},{1,6,4},{7,-1,5}};
    //int init[3][3]={{2,3,8},{1,6,4},{7,-1,5}};
    Path8 p=Path8(init);
    a_star<Path8> astar_digit8;
    astar_digit8.init_paths(p);
    Path8 final_digit8; // to store the final path.
    astar_digit8.search(final_digit8);

    astar_digit8.traverse(final_digit8);//output the result



    /* pacman */

    path_pacman pp=path_pacman(pair<int,int>(0,0));
    pp.set_destination(pair<int,int>(9,9));
    a_star<path_pacman> astar_pacman;
    astar_pacman.init_paths(pp);
    path_pacman final_pacman; // to store the final path.
    astar_pacman.search(final_pacman);
    astar_pacman.traverse(final_pacman); //output the result.



    return 0;
}
