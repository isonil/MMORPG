#include "global.hpp"

sf::Clock globalClock;
char *currentPacketData;
double globalTime;
double deltaTime;

LogManagerClass logManager;

char *getString(const char *format, const va_list &va)
{
    if(format == NULL) {
        char *str = new char[10];
        sprintf(str, "NULL");
        return str;
    }
    int size = vsnprintf(NULL, 0, format, va);
    if(size < 0) {
        char *str = new char[50];
        sprintf(str, "getString size error");
        return str;
    }
    char *str = new char[size+1];
    vsnprintf(str, size+1, format, va);
    return str;
}

/*
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
}*/

LONG crashHandler(struct _EXCEPTION_POINTERS *exInfo)
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
            << " >Additional information:" << std::endl
            << "   Game version: " << VERSION << std::endl;
        out.precision(0);
        out << "   Game time: " << std::fixed << globalTime << std::endl;
        if(currentPacketData) out << "   Exception occured while processing packet: " << currentPacketData << std::endl;
        else out << "   Exception occured in server logic." << std::endl;
        out.close();
        logManager.saveMessage("crash", "Application crashed.");
    }
    else {
        logManager.saveMessage("crash", "Application crashed, could not create 'crash.txt' file.");
    }
    return EXCEPTION_EXECUTE_HANDLER;
}
