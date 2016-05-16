#include "utility.hpp"

void util::clamp_ws(std::string &str)
{
    int wspace_quantity = 0;
    for(size_t i=0; i<str.size(); ++i) {
        if(iswspace(str[i])) wspace_quantity = (int)i+1;
        else break;
    }
    if(wspace_quantity) {
        if(wspace_quantity < (int)str.size()) str = str.substr(wspace_quantity);
        else str = "";
    }
    wspace_quantity = 0;
    for(int i=(int)str.size()-1; i>=0; --i) {
        if(iswspace(str[i])) wspace_quantity = (int)str.size()-i;
        else break;
    }
    if(wspace_quantity) str = str.substr(0, str.size()-wspace_quantity);
}

std::string util::cutExtension(const std::string &str)
{
    size_t dot = str.rfind('.');
    if(dot != std::string::npos) {
        return str.substr(0, dot);
    }
    return str;
}

std::string util::getExtension(const std::string &str)
{
    size_t dot = str.rfind('.');
    if(dot != std::string::npos) {
        if(dot+1 < str.size()) return str.substr(dot+1);
        else return "";
    }
    return "";
}
