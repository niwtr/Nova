#ifndef PATH8_H
#define PATH8_H
#include "astar.hpp"

using namespace nova_kernel;


class Path8 : public Path<int[3][3]> {

private:

    static int achievement[3][3];
    //int state[3][3];
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

    int state[3][3];
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
int Path8::matrix_diff(int b[3][3]){
    int count=0;
    for(int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            if(this->state[i][j]!=b[i][j])
                count++;
        }
    }
    return count;
}


void Path8::find__1(int & i, int & j){
    for(int x=0;x<3;x++){
        for(int y=0;y<3;y++){
            if(this->state[x][y]==-1)
            {
                i=x;j=y;
                return;}}}}



void Path8::rotatef(int b[3][3], int i1, int j1, int i2, int j2){

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            b[i][j]=this->state[i][j];
        }
    }
    int temp=b[i1][j1];
    b[i1][j1]=b[i2][j2];
    b[i2][j2]=temp;

}


void Path8::printm(){
    for(int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            cout<<this->state[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}


Path8::Path8(){this->ID=_id;_id++;}

Path8::Path8(int state[3][3]){
    this->ID=_id;
    _id++;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            this->state[i][j]=state[i][j];
        }
    }
    this->total_cost=0;
    this->cost_so_far=0;
}


list<Path8> Path8::get_next(){

    int i,j;
    find__1(i,j);

    list<Path8> pl;
    int b[3][3]={0,0,0,0,0,0,0,0,0};

    if(i-1>=0)
    {

        rotatef(b, i, j, i-1, j);
        Path8 newp=Path8(b);
        pl.push_back(newp);
    }

    if(i+1<3){
        rotatef(b, i, j, i+1, j);
        Path8  newp=Path8(b);
        pl.push_back(newp);
    }

    if(j-1>=0){
        rotatef(b, i, j, i, j-1);
        Path8 newp= Path8(b);
        pl.push_back(newp);

    }
    if(j+1<3){
        rotatef(b, i, j, i, j+1);
        Path8 newp=Path8(b);
        pl.push_back(newp);

    }

    return pl;
}


int Path8::achievement[3][3]={{1,2,3},{8,-1,4},{7,6,5}};
int Path8::_id=0;
#endif // PATH8_H
