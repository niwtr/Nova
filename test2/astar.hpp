#ifndef ASTAR_H
#define ASTAR_H
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <QVector>

//using namespace std;


namespace nova_kernel{

using std::vector;
using std::merge;
using std::list;
using std::map;
using std::cout;
using std::endl;

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
    Path end_path;
    map <Path, Path> path_precursor;

    constexpr static int depth_limit=100;



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
    void _get_all_paths(Path end_path, list<Path> & container){
        container.push_front(end_path);
        typename map<Path, Path>::iterator it;
        it=this->path_precursor.find(end_path);
        if(it!=this->path_precursor.end()){
            _get_all_paths(it->second, container);
        }
    }
    void _traverse(Path start){
        start.output();
        typename map<Path, Path>::iterator it;
        it=this->path_precursor.find(start);
        if(it!=this->path_precursor.end()){

            _traverse(it->second);
        }
    }

public:

    vector<vector<int> > CHANGES;

    void init_path(Path p){
        this->paths.push_back(p);
    }
    void clear(){
        this->old_paths.clear();
        this->path_precursor.clear();
        this->paths.clear();
        this->end_path=Path();
    }


    bool search(){

        int depth=0;

        while(true) {

            if((depth++)>depth_limit)
            {
                cout<<"Warning: Approaching depth limit, protentially no solution."<<endl;
                //rst=paths.front();
                this->end_path=paths.front();
                return false;
            }

            if (paths.empty())return false;

            else if (paths.front().is_goal()) {
                //rst = paths.front();
                this->end_path=paths.front();
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


    void traverse(){
        _traverse(this->end_path);
    }


    Path copy_old_path(Path  container){
        Path res;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                res.state[i][j]=container.state[i][j];
            }
        }
        return res;
    }

   vector<int> find_change_path(Path path1, Path path2){
        int x1=0,y1=0,x2=0,y2=0;
        vector<int> res;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(path1.state[i][j]==-1){
                    x1=i;
                    y1=j;
                }
                else if(path2.state[i][j]==-1){
                    x2=i;
                    y2=j;
                }
            }
        }
        res.push_back(path1.state[x2][y2]);
        if(y1>y2){
            res.push_back(1);
        }
        else if(y1<y2){
            res.push_back(2);
        }
        else if(x1>x2){
            res.push_back(3);
        }
        else if(x1<x2){
            res.push_back(4);
        }
        return res;
    }

    void get_all_paths(list<Path> & container){
        _get_all_paths(this->end_path, container);
        Path p1;
        vector<int> ch;
        int i=1;
        for(auto c : container){
            if(i>=2){
               ch=find_change_path(p1,c);
               CHANGES.push_back(ch);
            }
            p1=copy_old_path(c);
            i++;
        }
    }


    vector<vector<int> > calculate_location(auto ch, int arry[3][3])
    {
        int num1=0,num2=0;
        vector<int> temp;
        vector<vector<int> > res;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(arry[i][j]==-1){
                    temp.push_back(j*70);
                    temp.push_back(i*60);cout<<i<<"  "<<j<<"-------------------"<<endl;
                }
            }
        }

        for(auto c : ch){
            switch (c[1]) {
            case 1:
                num1=temp[0]-70;
                num2=temp[1];
                break;
            case 2:
                num1=temp[0]+70;
                num2=temp[1];
                break;
            case 3:
                num1=temp[0];
                num2=temp[1]-60;
                break;
            case 4:
                num1=temp[0];
                num2=temp[1]+60;
                break;
            default:
                break;
            }
            temp.push_back(num1);
            temp.push_back(num2);
            res.push_back(temp);
            temp.clear();
            temp.push_back(num1);
            temp.push_back(num2);
        }
        return res;
    }

    bool get_next_path(Path current, Path & next){
        list<Path> _c;
        get_all_paths(_c);
        auto it=_c.begin();
        it++;
        if(_c.size()>=2){
            next=*it;
            return true;
        }else return false;
    }




};

};
#endif // ASTAR_H
