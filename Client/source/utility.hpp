#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <algorithm>
#include <string>
#include <cstring>

namespace util
{
    inline int rand(int from, int to)
    {
        if(to > from) std::swap(from, to);
        return ::rand()%(to-from+1)+from;
    }

    template <class T> T saturate (const T var)
    {
        if(var < 0) return 0;
        else if(var > 1) return 1;
        else return var;
    }

    template <class T> T abs (const T var)
    {
        if(var < 0) return -var;
        else return var;
    }

    template <class T> int sign (const T var)
    {
        if(var < 0) return -1;
        else if(var > 0) return 1;
        else return 0;
    }

    template <class T1, class T2> int sign (const T1 var, const T2 eps)
    {
        if(abs(var) <= eps) return 0;
        else if(var < 0) return -1;
        else return 1;
    }

    template <class T1, class T2> bool equal (const T1 var1, const T1 var2, const T2 eps)
    {
        if(abs(var1-var2) <= eps) return true;
        else return false;
    }

    template <class T> T clamp (const T var, const T from, const T to)
    {
        if(var < from) return from;
        else if(var > to) return to;
        else return var;
    }

    void clamp_ws(std::string &str);
    std::string cutExtension(const std::string &str);
    std::string getExtension(const std::string &str);
}

#endif
