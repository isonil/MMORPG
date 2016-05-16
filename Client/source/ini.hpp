#ifndef INI_HPP
#define INI_HPP

#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <map>

class IniFileClass
{
    private:
        void cutBorderWhiteSpaces(std::string &str);

    public:
        class IniGroupClass
        {
            public:
                std::string name;
                std::map <std::string, std::string> value;
        };

        std::map <std::string, IniGroupClass> group;

        bool read(const std::string &path, bool displayWarnings = false);

        IniFileClass() {}
        IniFileClass(const std::string &path, bool displayWarnings = false) {
            read(path, displayWarnings);
        }
};

#endif
