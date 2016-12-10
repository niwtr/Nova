#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>



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
        start.output();
        typename map<Path, Path>::iterator it;
        it=this->path_precursor.find(start);
        if(it!=this->path_precursor.end()){

            traverse(it->second);
        }
    }

};

};