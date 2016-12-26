#include "path_maze.h"
#include <cmath>
path_maze::path_maze()
{
    this->ID=_id;
    _id++;
}

path_maze::path_maze(cell state, Maze **board)
{
    this->ID=_id;
    _id++;
    this->state=state;
    this->board=board;
}

path_maze::path_maze(path_maze *lastone, cell new_state)
{
    this->ID=_id;_id++;
    this->state=new_state;
    this->achievement=lastone->get_achievement();
    this->board=lastone->board;
}




list<path_maze> path_maze::get_next(){

    list<path_maze> rst;
    cell state=this->state;
    int y=state.i,x=state.j;
    cell temp;
    for (int dir=0;dir<4;dir++){
        switch (dir) {
        case 0:
            temp.i=y-1;temp.j=x;
            break;
        case 1:
            temp.i=y+1;temp.j=x;
            break;
        case 2:
            temp.i=y;temp.j=x-1;
            break;
        default:
            temp.i=y;temp.j=x+1;
            break;
        }
        if(board[temp.i][temp.j].state==pixel_type::pass){
            rst.push_back(path_maze(this, temp));
        }
    }

    return rst;
}

bool path_maze::is_goal()
{
    return (
                this->state.i==this->achievement.i
                &&
                this->state.j==this->achievement.j
           );
}

int path_maze::cost_fn(path_maze next){return 1;}

int path_maze::cost_left_fn(path_maze next) {
    int diffy=this->state.i-next.get_state().i,
    diffx=this->state.j-next.get_state().j;
    return (int)sqrt(diffx*diffx+diffy*diffy);
}

bool path_maze::operator<(const path_maze &p) const {
    return this->ID<p.ID;
}

bool path_maze::operator==(const path_maze &p) const {
    return (this->state.i==p.state.i && this->state.j==p.state.j);
}





