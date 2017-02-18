#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#define MAX_SEARCH_DEPTH 5000

namespace astar_api{

using std::vector;
using std::merge;
using std::list;
using std::map;
using std::cout;
using std::endl;



    template <class State>
    class Path{
    protected:
        State state;
        State achievement;
        int ID;
    public:

        double total_cost;
        double cost_so_far;
        list<Path<State>> & get_next()              =delete;
        bool is_goal()                              =delete;
        int cost_fn(Path<State> & next)             =delete;
        int cost_left_fn(Path<State> & next)        =delete;
        void output()                               =delete;
        bool operator<(const Path<State> &p)const   =delete;
        bool operator==(const Path<State> &p)const  =delete;
    };



    template<typename Path>
class a_star {
private:
    list <Path> paths;
    list <Path> old_paths;
    Path end_path;
    map <Path, Path> path_precursor;
    constexpr static int depth_limit=MAX_SEARCH_DEPTH;


    bool better_path_p(Path & p1, Path & p2){
        return p1.total_cost<p2.total_cost;
    }

    void insert_path(Path && p, list <Path> & paths){
        paths.emplace_back(p);
        paths.sort([&](Path p1, Path p2){return better_path_p(p1,p2);});
    }

    bool find_path(Path p, list<Path> paths, typename list<Path>::iterator & old){
        auto result=std::find(paths.begin(),paths.end(), p);//state=
        if(result!=paths.end()){
            old=result;
            return true;
        }else return false;
    }
    void _get_all_paths(Path & end_path, list<Path> & container){
        container.push_front(end_path);
        typename map<Path, Path>::iterator it;
        it=this->path_precursor.find(end_path);
        if(it!=this->path_precursor.end()){
            _get_all_paths(it->second, container);
        }
    }
    void _traverse(Path & start){
        start.output();
        typename map<Path, Path>::iterator it;
        it=this->path_precursor.find(start);
        if(it!=this->path_precursor.end()){
            _traverse(it->second);
        }
    }

public:


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
                this->end_path=paths.front();
                return false;
            }

            if (paths.empty())return false;

            else if (paths.front().is_goal()) {
                this->end_path=paths.front();
                return true;
            }
            else {

                Path path = paths.front();
                paths.pop_front();
                insert_path(std::move(path), old_paths);

                for (Path p : path.get_next()) {

                    double cost = path.cost_so_far + path.cost_fn(p);

                    double cost2 = path.cost_left_fn(p);

                    p.cost_so_far = cost;
                    p.total_cost = cost + cost2;

                    path_precursor.insert(std::make_pair(p, std::move(path)));

                    typename list<Path>::iterator old;

                    if (find_path(p, paths, old)) {
                        if (better_path_p(p, *old)) {
                            paths.erase(old);
                            insert_path(std::move(p), paths);
                        }
                    }
                    else if (find_path(p, old_paths, old)) {
                        if (better_path_p(p,*old)) {
                            insert_path(std::move(p), paths);
                            paths.erase(old);
                        }
                    }
                    else {
                        insert_path(std::move(p), paths);
                    }
                }
            }
        }

    }


    void traverse(){
        _traverse(this->end_path);
    }


    void get_all_paths(list<Path> & container){
        _get_all_paths(this->end_path, container);
    }



    bool get_next_path(Path & next){
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
