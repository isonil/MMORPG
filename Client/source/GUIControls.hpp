#ifndef GUI_CONTROLS_HPP
#define GUI_CONTROLS_HPP

#include <vector>
#include <utility>
#include <string>
#include <cstring>
#include <SFML/System.hpp>
#include "global.hpp"

class EditBoxClass;
class ButtonClass;
class CheckBoxClass;

template <class C> class GUIControlFinderClass
{
    public:
        std::vector <std::pair <char*, C> > GUIControl;

        C &operator [] (const char *name)
        {
            for(size_t i=0; i<GUIControl.size(); ++i) {
                if(!strcmp(GUIControl[i].first, name)) {
                    return GUIControl[i].second;
                }
            }
            size_t nameLen = strlen(name);
            char *newName = new char[nameLen+1];
            for(size_t i=0; i<nameLen; ++i) {
                newName[i] = name[i];
            }
            newName[nameLen] = 0;
            GUIControl.push_back(std::pair <char*, C> (newName, C()));
            return GUIControl.back().second;
        }

        ~GUIControlFinderClass()
        {
            for(size_t i=0; i<GUIControl.size(); ++i) {
                delete[] GUIControl[i].first;
            }
        }
};

class GUIControlManagerClass
{
    private:
        template <class C> void logicControls(GUIControlFinderClass <C> &controls, bool mouseAlwaysOutside)
        {
            bool LMBEventHandledByOtherControl = false;
            for(size_t i=0; i<controls.GUIControl.size(); ++i) {
                bool isMouseOver = controls.GUIControl[i].second.isMouseOver();
                if(mouseAlwaysOutside) isMouseOver = false;
                if(mb == 1 && !LMBEventHandled) {
                    if(isMouseOver) {
                        LMBEventHandled = true;
                        LMBEventHandledByOtherControl = true;
                        controls.GUIControl[i].second.logic(LMB_NEW_PRESSED);
                    }
                    else controls.GUIControl[i].second.logic(LMB_NEW_PRESSED_OUTSIDE);
                }
                else if(mb == 1 && LMBEventHandledByOtherControl) {
                    controls.GUIControl[i].second.logic(LMB_NEW_PRESSED_OUTSIDE);
                }
                else if(mb == 1) {
                    if(isMouseOver) controls.GUIControl[i].second.logic(LMB_PRESSED);
                    else controls.GUIControl[i].second.logic(LMB_PRESSED_OUTSIDE);
                }
                else {
                    if(isMouseOver) controls.GUIControl[i].second.logic(LMB_FREE);
                    else controls.GUIControl[i].second.logic(LMB_FREE_OUTSIDE);
                }
            }
        }
        template <class C> void renderControls(const GUIControlFinderClass <C> &controls) const
        {
            for(size_t i=0; i<controls.GUIControl.size(); ++i) {
                controls.GUIControl[i].second.render();
            }
        }

    public:
        GUIControlFinderClass <EditBoxClass> editBox;
        GUIControlFinderClass <ButtonClass> button;
        GUIControlFinderClass <CheckBoxClass> checkBox;

        void logic(bool mouseAlwaysOutside);
        void render() const;
};

class GUIControlClass
{
    public:
        int x, y, w, h;

        enum Style
        {
            Default,
            Transparent,
            Menu
        } style;

        inline bool isMouseOver() const
        {
            return mx >= x && my >= y && mx <= x+w && my <= y+h;
        }
        virtual void logic(LMBActionEnum LMBAction) = 0;
        virtual void render() const = 0;

        GUIControlClass()
            :   x(0), y(0), w(0), h(0), style(Default) {
        }
        GUIControlClass(int newX, int newY, int newW, int newH, Style newStyle)
            :   x(newX), y(newY), w(newW), h(newH), style(newStyle) {
        }
};

class EditBoxClass : public GUIControlClass
{
    private:
        bool cursorVisible;
        double timeout_cursorBlink;

    public:
        std::string text, helpText;
        bool isFocused;
        bool passwordMode;
        int lengthLimit;

        int cursorPosition;
        int selectingFrom;
        int movementX;
        float toMove;

        inline void setFocused()
        {
            cursorVisible = true;
            timeout_cursorBlink = globalTime+500.0;
            isFocused = true;
        }
        inline void reset()
        {
            text.clear();
            isFocused = false;
            selectingFrom = -1;
            cursorPosition = 0;
            movementX = 0;
            toMove = 0.f;
        }
        int getCharacterNumber(int atX) const;
        int getCharacterPosition(int character) const;
        void clearSelectedText();
        void logic(LMBActionEnum LMBAction);
        void render() const;

        EditBoxClass()
            :   cursorVisible(true),
                timeout_cursorBlink(0.0),
                isFocused(false),
                passwordMode(false),
                lengthLimit(-1),
                cursorPosition(0),
                selectingFrom(-1),
                movementX(0),
                toMove(0.f) {
        }
        EditBoxClass(int newX, int newY, int newW, int newH, const std::string &initialText = "", Style newStyle = Default)
            :   GUIControlClass(newX, newY, newW, newH, newStyle),
                cursorVisible(true),
                timeout_cursorBlink(0.0),
                text(initialText),
                isFocused(false),
                passwordMode(false),
                lengthLimit(-1),
                cursorPosition(0),
                selectingFrom(-1),
                movementX(0),
                toMove(0.f) {
        }
};

class ButtonClass : public GUIControlClass
{
    private:
        bool isBeingPressed;

    public:
        std::string text;
        bool wasPressed;
        float alpha;

        void logic(LMBActionEnum LMBAction);
        void render() const;

        ButtonClass()
            :   isBeingPressed(false),
                wasPressed(false),
                alpha(255.f) {
        }
        ButtonClass(int newX, int newY, int newW, int newH, const std::string &newText, float newAlpha = 255.f, Style newStyle = Default)
            :   GUIControlClass(newX, newY, newW, newH, newStyle),
                isBeingPressed(false),
                text(newText),
                wasPressed(false),
                alpha(newAlpha) {
        }
};

class CheckBoxClass : public GUIControlClass
{
    private:
        bool isBeingPressed;

    public:
        std::string text;
        bool isChecked;

        void logic(LMBActionEnum LMBAction);
        void render() const;

        CheckBoxClass()
            :   isBeingPressed(false),
                isChecked(false) {
        }
        CheckBoxClass(int newX, int newY, int newW, int newH, const std::string &newText = "", bool newIsChecked = false, Style newStyle = Default)
            :   GUIControlClass(newX, newY, newW, newH, newStyle),
                isBeingPressed(false),
                text(newText),
                isChecked(newIsChecked) {
        }
};

#endif
