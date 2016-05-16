#include "global.hpp"

wxWindow *wxMainWindow;
wxChoice *wxEntitySelection1;
wxChoice *wxEntitySelection2;
wxStaticText *wxEntityText;
wxGrid *wxEntityGrid;
wxListBox *wxScriptsListBox;
wxListBox *wxQuestsListBox;
wxListBox *wxTextsListBox;
wxCheckBox *wxGridCheckBox;
wxCheckBox *wxMinimapCheckBox;
wxChoice *wxDisplaySelection;
wxTextCtrl *wxErrorLogEditBox;

sf::RenderWindow window;
sf::Clock globalClock;
sf::RenderTexture colorMapFBO;
sf::RenderTexture normalMapFBO;
sf::RenderTexture heightMapFBO;
double globalTime;
double deltaTime;
double saved_timer;
int mx, my, mb;
bool LMBEventHandled, RMBEventHandled;

int selectionEntityType = ENTITY_TYPE_NONE;
int selectionEntityIndex = -1;
int selectionListBoxSelectionIndex = -1;
int selectionEntityX = -1;
int selectionEntityY = -1;

int editingScriptIndex;
int editingNPCTypeIndex;
int editingQuestIndex;

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

void messageBox(const char *title, const char *format, ...)
{
    if(title == NULL || format == NULL) return;
    va_list va;
    va_start(va, format);
    char *message = getString(format, va);
    MessageBoxA(NULL, message, title, MB_OK);
    va_end(va);
    delete []message;
}

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

wxColour getColorById(int id)
{
    srand(id*5);
    int r = rand()%255;
    int g = rand()%255;
    int b = rand()%255;
    if(r >= 230 && g >= 230 && b >= 230) {
        r -= 50;
    }
    if(r <= 80 && g <= 80 && b <= 80) {
        r += 80;
        g += 20;
    }
    return wxColour(r, g, b);
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
            << " >Additional information:" << std::endl;
        out.precision(0);
        out << "   Game time: " << std::fixed << globalTime << std::endl;
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
    }*/
    if(!exception.empty()) messageBox("Crash", "Application crashed. Exception: %s.", exception.c_str());
    else messageBox("Crash", "Application crashed. Exception: %d.", (int)exInfo->ExceptionRecord->ExceptionCode);
    return EXCEPTION_EXECUTE_HANDLER;
}
