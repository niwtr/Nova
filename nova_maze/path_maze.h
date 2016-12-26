#ifndef PATH_MAZE_H
#define PATH_MAZE_H
#include <list>
#include "astar.hpp"
using namespace std;

enum class pixel_type
{
    wall,
    pass,
    colored,
    checked,
    film,
    magic,
    temp=-1
};


class Maze
{

public:
    int i;
    int j;
    pixel_type state;
};


class cell{
public:
    int i;
    int j;
};

class path_maze : public nova_kernel::Path<cell>
{

private:
    Maze ** board;
    cell state;
    cell achievement;


    static long long _id;
    long long ID;

public :
    path_maze();
    path_maze(cell state, Maze ** board);
    path_maze(path_maze * lastone, cell new_state);


    inline void set_board(Maze ** board){this->board=board;}
    inline void set_destination(cell dst){this->achievement=dst;}
    inline void set_state(cell state){this->state=state;}
    inline cell get_achievement(){return this->achievement;}
    list<path_maze> get_next();
    double total_cost;
    double cost_so_far;

    inline cell get_state(){return this->state;}
    bool is_goal();
    int cost_fn(path_maze next);
    int cost_left_fn(path_maze next);
    bool operator<(const path_maze & p) const;
    bool operator==(const path_maze & p) const;

};


#endif // PATH_MAZE_H
