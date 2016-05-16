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

std::vector <int> util::getNumbers(const std::string &str, const std::string &source)
{
    std::string strCopy = str;
    std::vector <int> ret;

    util::clamp_ws(strCopy);
    if(strCopy.empty() || strCopy[0] != '{') error("{} Parse error: Missing '{' or extra preceding characters in '%s'.", source.c_str());
    if(strCopy[strCopy.size()-1] != '}') error("{} Parse error: Missing '}' or extra characters at the end in '%s'.", source.c_str());

    bool spaceEncountered = false;
    bool commaEncountered = false;
    bool anyNumberFoundYet = false;
    bool readingDigits = false;
    std::string numberBuff;
    for(size_t i=1; i<strCopy.size()-1; ++i) {
        if(!isdigit(strCopy[i]) && readingDigits) {
            readingDigits = false;
            commaEncountered = false;
        }

        if(isdigit(strCopy[i])) {
           if(spaceEncountered && !commaEncountered) error("{} Parse error: Missing ',' in '%s'.", source.c_str());
           numberBuff += strCopy[i];
           anyNumberFoundYet = true;
           readingDigits = true;
        }
        else if(strCopy[i] == ' ') {
            if(anyNumberFoundYet) spaceEncountered = true;
        }
        else if(strCopy[i] == ',') {
            if(numberBuff.empty()) error("{} Parse error: ',' was unexpected in '%s'.", source.c_str());
            spaceEncountered = false;
            commaEncountered = true;
            int number = -1;
            sscanf(numberBuff.c_str(), "%d", &number);
            ret.push_back(number);
            numberBuff.clear();
        }
        else {
            error("{} Parse error: '%c' was unexpected in '%s'.", strCopy[i], source.c_str());
        }
    }
    if(commaEncountered && !readingDigits) error("{} Parse error: Extra ',' at the end in '%s'.", source.c_str());
    if(!numberBuff.empty()) {
        int number = -1;
        sscanf(numberBuff.c_str(), "%d", &number);
        ret.push_back(number);
    }

    return ret;
}
