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


using std::vector;
using std::merge;
using std::list;
using std::map;
using std::cout;
using std::endl;


int id=0;


int matrix_diff(int a[3][3] ,const int b[3][3]){
    int count=0;
    for(int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            if(a[i][j]!=b[i][j])
                count++;
        }
    }
    return count;
}




void find__1(int m[3][3], int & i, int & j){
    for(int x=0;x<3;x++){
        for(int y=0;y<3;y++){

            if(m[x][y]==-1)
            {
                i=x;j=y;
                return;
            }
        }

    }

}

void rotatef(int a[3][3], int b[3][3], int i1, int j1, int i2, int j2){

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            b[i][j]=a[i][j];
        }
    }
    int temp=b[i1][j1];
    b[i1][j1]=b[i2][j2];
    b[i2][j2]=temp;
    
}




void printm(int m[3][3]){
    for(int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}


template <typename State>
class Path{
protected:
    State state;
    State achievement;
    int ID;
public:
    double total_cost;
    double cost_so_far;
    list<Path<State>> get_next();
    bool is_goal();
    int cost_fn(Path<State> next);
    int cost_left_fn(Path<State> next);
    void output();
    bool operator<(const Path<State> &p)const;
    bool operator==(const Path<State> &p)const;
};



template<typename Path>
class a_star {


private:
    list <Path> paths;
    list <Path> old_paths;
    map <Path, Path> path_precursor;

    
    
    
    bool better_path_p(Path p1, Path p2){
        return p1.total_cost<p2.total_cost;
    }
    void insert_path(Path p, list <Path> & paths){
        paths.push_back(p);
        paths.sort([&](Path p1, Path p2){return better_path_p(p1,p2);});

    }


    bool find_path(Path p, list<Path> paths, typename list<Path>::iterator & old){
        auto result=std::find(paths.begin(),paths.end(), p);//state=
        if(result!=paths.end()){
            old=result;
            return true;
        }else {return false;}
    }



public:

    void init_paths(Path p){
        this->paths.push_back(p);
    }
    
    bool search(Path & rst){

        while(true) {

            if (paths.empty())return false;

            else if (paths.front().is_goal()) {
                rst = paths.front();
                return true;
            }
            else {


                Path path = paths.front();
                paths.pop_front();
                insert_path(path, old_paths);


                for (Path p : path.get_next()) {

                    double cost = path.cost_so_far + path.cost_fn(p);

                    double cost2 = path.cost_left_fn(p);

                    p.cost_so_far = cost;
                    p.total_cost = cost + cost2;

                    path_precursor.insert(std::make_pair(p, path));

                   typename list<Path>::iterator old;

                    if (find_path(p, paths, old)) {

                        if (better_path_p(p, *old)) {

                            paths.remove(*old);

                            insert_path(p, paths);
                        }
                    }
                    else if (find_path(p, old_paths, old)) {
                        if (better_path_p(p, *old)) {

                            insert_path(p, paths);
                            old_paths.remove(*old);
                        }
                    }
                    else {
                        insert_path(p, paths);
                    }
                }


            }
        }

    }
    void traverse(Path start){
        typename map<Path, Path>::iterator it;
        it=this->path_precursor.find(start);
        if(it!=this->path_precursor.end()){
            it->second.output();
            traverse(it->second);
        }
    }





};


class Path8 : public Path<int[3][3]> {
    
private:
    int ID;
    
public:
    
    Path8(){
        this->ID=id;
        id++;
    }
    Path8(int state[3][3]){
        this->ID=id;
        id++;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                this->state[i][j]=state[i][j];
            }
        }
        this->total_cost=0;
        this->cost_so_far=0;
    }
    
    static int achievement[3][3];
    int state[3][3];
    
    double total_cost;
    double cost_so_far;
    
    void output(){
        printm(this->state);
    }
    list<Path8> get_next(){
        
        int i,j;
        find__1(this->state, i,j);
        
        list<Path8> pl;
        int b[3][3]={0,0,0,0,0,0,0,0,0};
        
        if(i-1>=0)
        {
            
            rotatef(this->state, b, i, j, i-1, j);
            Path8 newp=Path8(b);
            pl.push_back(newp);
        }
        
        if(i+1<3){
            rotatef(this->state, b, i, j, i+1, j);
            Path8  newp=Path8(b);
            pl.push_back(newp);
        }
        
        if(j-1>=0){
            rotatef(this->state, b, i, j, i, j-1);
            Path8 newp= Path8(b);
            pl.push_back(newp);
            
        }
        if(j+1<3){
            rotatef(this->state, b, i, j, i, j+1);
            Path8 newp=Path8(b);
            pl.push_back(newp);
            
        }
        
        return pl;
    }
    bool is_goal(){
        return matrix_diff(this->state, this->achievement)==0;
    }
    int cost_fn(Path next){
        return 1;
    }
    int cost_left_fn(Path p){
        return matrix_diff(this->state, this->achievement);
    }
    
    
    bool operator<(const Path8 &p) const{
        return (this->ID < p.ID);
    }
    
    bool operator==(const Path8 &p)const{
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(this->state[i][j]!=p.state[i][j])return false;
            }
        }
        return true;
    }
    
    
};




int Path8::achievement[3][3]={{1,2,3},{8,-1,4},{7,6,5}};
/******************************************/




int main(int argc, const char * argv[]) {


    int init[3][3]={{2,8,3},{1,6,4},{7,-1,5}};
    //int init[3][3]={{2,3,8},{1,6,4},{7,-1,5}};
    Path8 p=Path8(init);

    a_star<Path8> a;
    a.init_paths(p);
    Path8 ph;
    a.search(ph);




    printm(ph.state);
    a.traverse(ph);


    return 0;
}