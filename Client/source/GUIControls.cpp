#include "GUIControls.hpp"

void GUIControlManagerClass::logic(bool mouseAlwaysOutside)
{
    logicControls(editBox, mouseAlwaysOutside);
    logicControls(button, mouseAlwaysOutside);
    logicControls(checkBox, mouseAlwaysOutside);
}

void GUIControlManagerClass::render() const
{
    renderControls(editBox);
    renderControls(button);
    renderControls(checkBox);
}

int EditBoxClass::getCharacterNumber(int atX) const
{
    if(atX < x) atX = x;
    else if(atX > x+w) atX = x+w;

    atX -= x;
    atX += movementX;

    int lastWidth = -1;
    for(size_t i=0; i<text.size(); ++i) {
        int currentWidth = getTextWidth(text.substr(0, i+1), 11);
        if(currentWidth >= atX) {
            if(i == 0) {
                if(atX < currentWidth-atX) return 0;
                else return 1;
            }
            else {
                if(currentWidth-atX <= atX-lastWidth) {
                    return i+1;
                }
                else return i;
            }
        }
        lastWidth = currentWidth;
    }

    return text.size();
}

int EditBoxClass::getCharacterPosition(int character) const
{
    if(character < 0) return -movementX;
    else if(character >= (int)text.size()) return getTextWidth(text, 11)-movementX;
    else return getTextWidth(text.substr(0, character), 11)-movementX;
}

void EditBoxClass::clearSelectedText()
{
    if(text.empty()) return;
    if(selectingFrom < 0) return;

    int leftCut = cursorPosition;
    int rightCut = selectingFrom;
    if(leftCut > rightCut) std::swap(leftCut, rightCut);
    if(leftCut < 0) leftCut = 0;
    if(leftCut >= (int)text.size()) leftCut = text.size()-1;
    if(rightCut < 0) rightCut = 0;
    if(leftCut == rightCut) return;

    std::string oldText = text;
    text = oldText.substr(0, leftCut);
    if(rightCut < (int)oldText.size()) {
        text += oldText.substr(rightCut);
    }

    if(selectingFrom < cursorPosition) {
        cursorPosition = selectingFrom;
    }

    selectingFrom = cursorPosition;
}

void EditBoxClass::logic(LMBActionEnum LMBAction)
{
    if(LMBAction == LMB_NEW_PRESSED) {
        setFocused();
        cursorPosition = getCharacterNumber(mx);
        selectingFrom = cursorPosition;
    }
    else if(LMBAction == LMB_NEW_PRESSED_OUTSIDE) {
        isFocused = false;
        selectingFrom = -1;
    }
    else if((LMBAction == LMB_PRESSED ||
             LMBAction == LMB_PRESSED_OUTSIDE) &&
            selectingFrom >= 0) {
        if(mx < x) {
            toMove -= deltaTime*(x-mx)/9.f;
        }
        else if(mx > x+w) {
            toMove += deltaTime*(mx-x-w)/9.f;
        }
        cursorPosition = getCharacterNumber(mx);
    }

    movementX += (int)toMove;
    toMove -= (int)toMove;
    if(movementX < 0) movementX = 0;
    int textWidth = getTextWidth(text, 11);
    if(textWidth < w) movementX = 0;
    else {
        if(movementX > textWidth-w) {
            movementX = textWidth-w;
        }
    }

    if(isFocused && !keyBuffHandled) {
        keyBuffHandled = true;
        for(size_t i=0; i<keyBuff.size(); ++i) {
            if(keyBuff[i].code == sf::Keyboard::Back) {
                if(text.size()) {
                    if(selectingFrom >= 0 &&
                       selectingFrom != cursorPosition) {
                        clearSelectedText();
                    }
                    else {
                        if(cursorPosition > 0 &&
                           cursorPosition <= (int)text.size()) {
                            text.erase(cursorPosition-1, 1);
                            --cursorPosition;
                            selectingFrom = cursorPosition;
                        }
                    }
                }
                setFocused();
            }
            else if(keyBuff[i].code == sf::Keyboard::Delete) {
                if(text.size()) {
                    if(selectingFrom >= 0 &&
                       selectingFrom != cursorPosition) {
                        clearSelectedText();
                    }
                    else {
                        if(cursorPosition >= 0 &&
                           cursorPosition < (int)text.size()) {
                            text.erase(cursorPosition, 1);
                        }
                    }
                }
                setFocused();
            }
            else if(keyBuff[i].code == sf::Keyboard::Left) {
                if(cursorPosition > 0) {
                    --cursorPosition;
                    if(!keyBuff[i].shift) {
                        selectingFrom = cursorPosition;
                    }
                }
                setFocused();
            }
            else if(keyBuff[i].code == sf::Keyboard::Right) {
                if(cursorPosition < (int)text.size()) {
                    ++cursorPosition;
                    if(!keyBuff[i].shift) {
                        selectingFrom = cursorPosition;
                    }
                }
                setFocused();
            }
            else if(!keyBuff[i].control && sfKeyArray[keyBuff[i].code][keyBuff[i].shift]) {
                if(text.size() < lengthLimit || (selectingFrom >= 0 &&
                                                 selectingFrom != cursorPosition)) {
                    char newChar = sfKeyArray[keyBuff[i].code][keyBuff[i].shift];
                    char newCharStr[2] = {newChar, 0};
                    if(selectingFrom >= 0 &&
                       selectingFrom != cursorPosition) {
                        clearSelectedText();
                    }
                    if(cursorPosition >= 0 && cursorPosition < (int)text.size()) {
                        text.insert(cursorPosition, newCharStr);
                    }
                    else if(cursorPosition >= (int)text.size()) {
                        text += newChar;
                    }
                    ++cursorPosition;
                    selectingFrom = cursorPosition;
                }
                setFocused();
            }
            else if(keyBuff[i].control) {
                if(keyBuff[i].code == sf::Keyboard::A) {
                    selectingFrom = 0;
                    cursorPosition = text.size();
                    setFocused();
                }
                else if((keyBuff[i].code == sf::Keyboard::X ||
                         keyBuff[i].code == sf::Keyboard::C) &&
                        selectingFrom >= 0 &&
                        selectingFrom != cursorPosition &&
                        !text.empty()) {
                    int leftCut = cursorPosition;
                    int rightCut = selectingFrom;
                    if(leftCut > rightCut) std::swap(leftCut, rightCut);
                    if(leftCut < 0) leftCut = 0;
                    if(leftCut >= (int)text.size()) leftCut = text.size()-1;
                    if(rightCut < 0) rightCut = 0;
                    if(rightCut >= (int)text.size()) rightCut = text.size()-1;
                    //setClipboardData(text.substr(leftCut, rightCut-leftCut+1);
                    if(keyBuff[i].code == sf::Keyboard::X) {
                        clearSelectedText();
                    }
                    setFocused();
                }
                else if(keyBuff[i].code == sf::Keyboard::V) {
                    if(selectingFrom >= 0 &&
                       selectingFrom != cursorPosition) {
                        clearSelectedText();
                    }
                    //getClipboardData();
                    setFocused();
                }
            }
        }

        int pos = getCharacterPosition(cursorPosition);
        if(pos >= w) {
            movementX += pos-w;
        }
        else if(pos < 0) {
            movementX += pos;
        }
        if(movementX < 0) movementX = 0;
        int textWidth = getTextWidth(text, 11);
        if(textWidth < w) movementX = 0;
        else {
            if(movementX > textWidth-w) {
                movementX = textWidth-w;
            }
        }

        //If return or tab key appeared in keyBuff we save it and set
        //keyBuffHandled to false in order to let further functions/methods
        //handle this key, otherwise enter key would be already handled here.
        std::vector <sf::Event::KeyEvent> newKeyBuff;
        for(size_t i=0; i<keyBuff.size(); ++i) {
            if(keyBuff[i].code == sf::Keyboard::Return ||
               keyBuff[i].code == sf::Keyboard::Tab ||
               keyBuff[i].code == sf::Keyboard::Escape) {
                newKeyBuff.push_back(keyBuff[i]);
                keyBuffHandled = false;
            }
        }
        keyBuff = newKeyBuff;
    }
    if(globalTime >= timeout_cursorBlink) {
        cursorVisible = !cursorVisible;
        timeout_cursorBlink = globalTime+500.0;
    }
}

void EditBoxClass::render() const
{
    if(style != Transparent) {
        sf::RectangleShape rect(sf::Vector2f(w+2, h));
        rect.setOutlineThickness(1);
        rect.setFillColor(sf::Color(50, 50, 50, 30));
        rect.setOutlineColor(sf::Color(100, 100, 100, 150));
        rect.setPosition(x-1, y);
        window.draw(rect);
    }

    sf::Text text_;
    text_.setCharacterSize(11);
    text_.setColor(sf::Color(200, 200, 200));
    text_.setPosition(x-movementX, y);

    std::string displayText;
    if(passwordMode) {
        displayText.resize(text.size(), '*');
    }
    else displayText = text;

    if(!isFocused && text.empty()) {
        text_.setColor(sf::Color(100, 100, 100, 200));
        text_.setString(helpText);
    }
    else text_.setString(displayText);

    glEnable(GL_SCISSOR_TEST);
    glScissor(x, (int)window.getSize().y-y-h, w, h);

    if(selectingFrom >= 0 &&
       selectingFrom != cursorPosition) {
        sf::RectangleShape rect;
        int x1 = getCharacterPosition(selectingFrom);
        int x2 = getCharacterPosition(cursorPosition);
        if(x1 > x2) std::swap(x1, x2);
        rect.setSize(sf::Vector2f(x2-x1, 11));
        rect.setPosition(x+x1, y+2);
        rect.setFillColor(sf::Color(20, 20, 100));
        window.draw(rect);
    }

    window.draw(text_);

    if(isFocused && cursorVisible) {
        int cursorX = -movementX;
        if(cursorPosition <= 0) cursorX = -movementX;
        else if(cursorPosition >= (int)text.size()) cursorX = getTextWidth(text_)-movementX;
        else cursorX = getCharacterPosition(cursorPosition);

        sf::VertexArray line(sf::Lines, 2);

        line[0].position = sf::Vector2f(x+cursorX, y+2);
        line[1].position = sf::Vector2f(x+cursorX, y+13);
        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;
        window.draw(line);
    }

    glDisable(GL_SCISSOR_TEST);
}

void ButtonClass::logic(LMBActionEnum LMBAction)
{
    alpha += deltaTime*4.f;
    if(alpha > 155.f) alpha += deltaTime*2.f;
    if(alpha > 255.f) alpha = 255.f;

    if(LMBAction == LMB_NEW_PRESSED) {
        isBeingPressed = true;
    }
    if(isBeingPressed) {
        if(LMBAction == LMB_FREE) {
            isBeingPressed = false;
            wasPressed = true;
        }
        else if(LMBAction == LMB_FREE_OUTSIDE) isBeingPressed = false;
    }
}

void ButtonClass::render() const
{
    float alpha_ = std::max(alpha, 0.f);

    if(style == Default) {
        sf::Text text_;
        text_.setCharacterSize(11);
        text_.setString(text);

        sf::RectangleShape button(sf::Vector2f(w, h));
        button.setPosition(x, y);

        sf::VertexArray line(sf::Lines, 2);

        int posX = x+(w-getTextWidth(text_))/2;
        int posY = y+(h-text_.getLocalBounds().height)/2;
        if(isBeingPressed) {
            text_.setColor(sf::Color(200, 200, 200, (int)alpha_));
            text_.setPosition(posX, posY);
            button.setFillColor(sf::Color(40, 40, 40, (int)alpha_));
            window.draw(button);
            line[0].position = sf::Vector2f(x, y);
            line[0].color = sf::Color(30, 30, 30,(int)alpha_);
            line[1].position = sf::Vector2f(x+w-1, y);
            line[1].color = sf::Color(30, 30, 30,(int)alpha_);
            window.draw(line);
            line[0].position = sf::Vector2f(x, y);
            line[0].color = sf::Color(30, 30, 30,(int)alpha_);
            line[1].position = sf::Vector2f(x, y+h-1);
            line[1].color = sf::Color(30, 30, 30,(int)alpha_);
            window.draw(line);
        }
        else {
            text_.setColor(sf::Color(230, 230, 230,(int)alpha_));
            text_.setPosition(posX-1, posY-1);
            button.setFillColor(sf::Color(60, 60, 60,(int)alpha_));
            window.draw(button);
            line[0].position = sf::Vector2f(x, y+h-1);
            line[0].color = sf::Color(90, 90, 90,(int)alpha_);
            line[1].position = sf::Vector2f(x+w-1, y+h-1);
            line[1].color = sf::Color(90, 90, 90,(int)alpha_);
            window.draw(line);
            line[0].position = sf::Vector2f(x+w-1, y);
            line[0].color = sf::Color(90, 90, 90,(int)alpha_);
            line[1].position = sf::Vector2f(x+w-1, y+h-1);
            line[1].color = sf::Color(90, 90, 90,(int)alpha_);
            window.draw(line);
        }
        window.draw(text_);
    }
    else if(style == Menu) {
        sf::Text text_;
        text_.setCharacterSize(14);
        text_.setString(text);

        text_.setPosition(x+2, y+2);
        text_.setColor(sf::Color(0, 0, 0, (int)alpha_));
        window.draw(text_);

        if(isBeingPressed) {
            text_.setColor(sf::Color(200, 200, 200, (int)alpha_));
            text_.setPosition(x+1, y+1);
        }
        else {
            text_.setColor(sf::Color(230, 230, 230,(int)alpha_));
            text_.setPosition(x, y);
        }
        window.draw(text_);
    }
}

void CheckBoxClass::logic(LMBActionEnum LMBAction)
{
    if(LMBAction == LMB_NEW_PRESSED) {
        isBeingPressed = true;
    }
    if(isBeingPressed) {
        if(LMBAction == LMB_FREE) {
            isBeingPressed = false;
            isChecked = !isChecked;
        }
        else if(LMBAction == LMB_FREE_OUTSIDE) isBeingPressed = false;
    }
}

void CheckBoxClass::render() const
{
    sf::Text text_;
    text_.setCharacterSize(11);
    text_.setString(text);
    text_.setColor(sf::Color(230, 230, 230));
    text_.setPosition(x+w+5, int(y+(h-text_.getLocalBounds().height)/2)-2);

    sf::RectangleShape checkBox(sf::Vector2f(w, h));
    checkBox.setPosition(x, y);
    checkBox.setFillColor(sf::Color(60, 60, 60));
    window.draw(checkBox);

    sf::VertexArray line(sf::Lines, 2);

    if(isChecked) {
        line[0].position = sf::Vector2f(x+3, y+3);
        line[0].color = sf::Color(110, 110, 110);
        line[1].position = sf::Vector2f(x+w-3, y+h-3);
        line[1].color = sf::Color(110, 110, 110);
        window.draw(line);
        line[0].position = sf::Vector2f(x+w-3, y+3);
        line[0].color = sf::Color(110, 110, 110);
        line[1].position = sf::Vector2f(x+3, y+h-3);
        line[1].color = sf::Color(110, 110, 110);
        window.draw(line);
    }
    window.draw(text_);
}
