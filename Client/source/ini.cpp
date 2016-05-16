#include "ini.hpp"

void IniFileClass::cutBorderWhiteSpaces(std::string &str)
{
    int wspaceQuantity = 0;
    for(size_t i=0; i<str.size(); ++i) {
        if(iswspace(str[i])) wspaceQuantity = (int)i+1;
        else break;
    }
    if(wspaceQuantity) {
        if(wspaceQuantity < (int)str.size()) str = str.substr(wspaceQuantity);
        else str = "";
    }
    wspaceQuantity = 0;
    for(int i=(int)str.size()-1; i>=0; --i) {
        if(iswspace(str[i])) wspaceQuantity = (int)str.size()-i;
        else break;
    }
    if(wspaceQuantity) str = str.substr(0, str.size()-wspaceQuantity);
}

bool IniFileClass::read(const std::string &path, bool displayWarnings)
{
    group.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        if(displayWarnings) printf("Ini parse warning: Could not open file '%s'.\n", path.c_str());
        return false;
    }

    std::string currentGroup = "none";
    group["none"].name = "none";
    std::string line;
    int lineNumber = 0;

    while(std::getline(in, line)) {
        ++lineNumber;
        cutBorderWhiteSpaces(line);
        if(line.empty()) continue;

        size_t openBracket = line.find('[');
        if(openBracket != std::string::npos) {
            if(displayWarnings && openBracket != 0) {
                printf("Ini parse warning: Extra characters before '[' in file '%s' line %d.\n", path.c_str(), lineNumber);
            }
            std::string newGroup;
            bool closeBracket = false;
            for(size_t i=openBracket+1; i<line.size(); ++i) {
                if(line[i] == ']') {
                    closeBracket = true;
                    if(displayWarnings && i != line.size()-1) {
                        printf("Ini parse warning: Extra characters after ']' in file '%s' line %d.\n", path.c_str(), lineNumber);
                    }
                    break;
                }
                else newGroup += line[i];
            }
            if(displayWarnings && !closeBracket) {
                printf("Ini parse warning: Missing ']' in file '%s' line %d.\n", path.c_str(), lineNumber);
            }
            currentGroup = newGroup;
            group[currentGroup].name = currentGroup;
        }
        else {
            size_t equalSign = line.find('=');
            if(equalSign != std::string::npos) {
                std::string key = line.substr(0, equalSign);
                std::string value;
                if(equalSign+1 < line.size()) value = line.substr(equalSign+1);
                cutBorderWhiteSpaces(key);
                cutBorderWhiteSpaces(value);
                if(displayWarnings) {
                    if(group[currentGroup].value.find(key) != group[currentGroup].value.end()) {
                        printf("Ini parse warning: Key redeclaration in file '%s' line %d.\n", path.c_str(), lineNumber);
                    }
                }
                group[currentGroup].value[key] = value;
            }
            else if(displayWarnings) {
                printf("Ini parse warning: Missing '=' in file '%s' line %d.\n", path.c_str(), lineNumber);
            }
        }
    }

    in.close();
    return true;
}
