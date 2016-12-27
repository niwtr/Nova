#ifndef DEF_H
#define DEF_H


#define for_in(var, name)\
    for(auto & var : name)


#define for_through(varName, lb, ub, step)\
    for(auto varName=lb;varName<ub;varName=varName+step)

#define Func(fn_name, args...)\
    auto fn_name=[](args...)

#define Var auto
#define Var_ref auto&
#define elif else if

#define ref_Func(fn_name, args...)\
    auto fn_name=[&](args...)

#define captured_Func(fn_name, args...)\
    auto fn_name=[=](args...)

#define unless(X) if(not(X))
#endif // DEF_H
