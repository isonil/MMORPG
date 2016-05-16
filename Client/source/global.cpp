#include "global.hpp"

sf::RenderWindow window;
sf::Clock globalClock;
sf::RenderTexture colorMapFBO;
sf::RenderTexture normalMapFBO;
sf::RenderTexture heightMapFBO;
sf::RenderTexture shadowMapFBO;
sf::RenderTexture ambientShadowMapFBO;
sf::RenderTexture lightDiffuseMap1FBO;
sf::RenderTexture lightDiffuseMap2FBO;
sf::RenderTexture lightSpecularMap1FBO;
sf::RenderTexture lightSpecularMap2FBO;
sf::RenderTexture sceneFBO;
std::vector <sf::Event::KeyEvent> keyBuff;
double globalTime;
double deltaTime;
int mx, my, mb;
int playerCharacterIndex;
char *currentPacketData;
bool isConnectedToServer;
bool LMBEventHandled, RMBEventHandled;
bool keyBuffHandled;

LogManagerClass logManager;

LARGE_INTEGER queryPerformance_frequency;
bool queryPerformance_isAvailable;

void loadTexture(sf::Texture &tex, const std::string &path, bool checkIfExists)
{
    if(checkIfExists && !fileExists(path)) return;
    if(!tex.loadFromFile(path)) {
        error("Could not load texture '%s'.", path.c_str());
    }
}

void loadImage(sf::Image &img, const std::string &path, bool checkIfExists)
{
    if(checkIfExists && !fileExists(path)) return;
    if(!img.loadFromFile(path)) {
        error("Could not load image '%s'.", path.c_str());
    }
}

void loadSample(SAMPLE **sample, const std::string &path, bool checkIfExists)
{
    if(checkIfExists && !fileExists(path)) return;
    if(!(*sample = load_sample(path.c_str()))) {
        error("Could not load sound file '%s'.", path.c_str());
    }
}

bool fileExists(const std::string &path)
{
    std::ifstream in(path.c_str());
    return in;
}

int getTextWidth(sf::Text &text)
{
    sf::String old = text.getString();
    text.setString('.'+text.getString()+'.');
    int width1 = text.getLocalBounds().width;
    text.setString('.');
    int width2 = text.getLocalBounds().width;
    text.setString(old);
    return width1-2*width2;
}

int getTextWidth(const std::string &text, int characterSize)
{
    sf::Text text_;
    text_.setCharacterSize(characterSize);
    text_.setString(text);

    text_.setString('.'+text+'.');
    int width1 = text_.getLocalBounds().width;
    text_.setString('.');
    int width2 = text_.getLocalBounds().width;
    return width1-2*width2;
}

char scanCodeToChar(int scancode, bool shift)
{
    if(scancode >= KEY_A && scancode <= KEY_Z) {
        if(shift) return scancode_to_ascii(scancode)+'A'-'a';
        else return scancode_to_ascii(scancode);
    }
    else if(scancode >= KEY_0 && scancode <= KEY_9) {
        if(shift) {
            if(scancode == KEY_1) return '!';
            else if(scancode == KEY_2) return '@';
            else if(scancode == KEY_3) return '#';
            else if(scancode == KEY_4) return '$';
            else if(scancode == KEY_5) return '%';
            else if(scancode == KEY_6) return '^';
            else if(scancode == KEY_7) return '&';
            else if(scancode == KEY_8) return '*';
            else if(scancode == KEY_9) return '(';
            else if(scancode == KEY_0) return ')';
        }
        else return scancode_to_ascii(scancode);
    }
    else if(scancode == KEY_SLASH) {
        if(shift) return '?';
        else return '/';
    }
    else if(scancode == KEY_SPACE) return ' ';
    else if(scancode == KEY_TILDE) {
        if(shift) return '~';
        else return '`';
    }
    else if(scancode == KEY_MINUS) {
        if(shift) return '_';
        else return '-';
    }
    else if(scancode == KEY_EQUALS) {
        if(shift) return '+';
        else return '=';
    }
    else if(scancode == KEY_OPENBRACE) {
        if(shift) return '{';
        else return '[';
    }
    else if(scancode == KEY_CLOSEBRACE) {
        if(shift) return '}';
        else return ']';
    }
    else if(scancode == KEY_COLON || scancode == KEY_SEMICOLON) {
        if(shift) return ':';
        else return ';';
    }
    else if(scancode == KEY_QUOTE) {
        if(shift) return '"';
        else return '\'';
    }
    else if(scancode == KEY_BACKSLASH || scancode == KEY_BACKSLASH2) {
        if(shift) return '|';
        else return '\\';
    }
    else if(scancode == KEY_COMMA) {
        if(shift) return '<';
        else return ',';
    }
    else if(scancode == KEY_STOP) {
        if(shift) return '>';
        else return '.';
    }
    return '\0';
}

LONG crashHandler(_EXCEPTION_POINTERS *exInfo)
{
    std::string exception = "";
    switch(exInfo->ExceptionRecord->ExceptionCode) {
        case EXCEPTION_DATATYPE_MISALIGNMENT:
            exception = "DATATYPE MISALIGNMENT";
            break;
        case EXCEPTION_ACCESS_VIOLATION:
            exception = "ACCESS VIOLATION";
            break;
        case EXCEPTION_ILLEGAL_INSTRUCTION:
            exception = "ILLEGAL INSTRUCTION";
            break;
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
            exception = "ARRAY BOUNDS EXCEEDED";
            break;
        case EXCEPTION_INT_DIVIDE_BY_ZERO:
            exception = "INT DIVIDE BY ZERO";
            break;
        case EXCEPTION_INT_OVERFLOW:
            exception = "INT OVERFLOW";
            break;
        case EXCEPTION_STACK_OVERFLOW:
            exception = "STACK OVERFLOW";
            break;
        case EXCEPTION_FLT_DIVIDE_BY_ZERO:
            exception = "FLT DIVIDE BY ZERO";
            break;
        default:
            exception = "";
            break;
    }
    std::ofstream out("crash.txt", std::ios::app);
    if(out) {
        out << '[';
        dateAndTimeToFile(out);
        out << "] Application crashed." << std::endl
            << " >Exception code: ";
        if(!exception.empty()) out << exception << std::endl;
        else out << exInfo->ExceptionRecord->ExceptionCode << std::endl;
        out << " >Exception address: " << exInfo->ExceptionRecord->ExceptionAddress << std::endl
            << " >Exception flags: " << exInfo->ExceptionRecord->ExceptionFlags << std::endl
            << " >Additional informations:" << std::endl
            << "   Game version: " << VERSION << std::endl;
        out.precision(0);
        out << "   Game time: " << std::fixed << globalTime << std::endl;
        if(isConnectedToServer) out << "   Connected to the server." << std::endl
                                    << "   Player ID: " << playerCharacterIndex << std::endl;
        else out << "   Not connected to the server." << std::endl;
        if(currentPacketData) out << "   Exception occured while processing packet: " << currentPacketData << std::endl;
        else out << "   Exception occured in client logic." << std::endl;
        out.close();
        logManager.saveMessage("crash", "Application crashed.");
    }
    else {
        logManager.saveMessage("crash", "Application crashed, could not create 'crash.txt' file.");
    }
    /*if(continue)
    {
       exInfo->ContextRecord->Eip++;
       return EXCEPTION_CONTINUE_EXECUTION;
    }
    */
    allegro_message("It seems that an unexpected error has occured.\nWe would be thankful if you could send us crash report (crash.txt and log.txt).\n-Dev team");
    return EXCEPTION_EXECUTE_HANDLER;
}
