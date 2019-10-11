/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/UIEditBox.cpp
*/

#include "UIEditBox.hpp"

UIEditBox::UIEditBox(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene,
irr::s32 id, const irr::io::path &backgroundTextPath, std::string defaultText,
irr::core::rect<irr::f32> rect, irr::core::position2df textPos, float textSize, int maxCharacter,
bool usePercentage):
AInterfaceObj(guiScene, id), _driver(driver), _rect(rect), _defaultText(defaultText), _textPos(textPos),
_textSize(textSize), _maxCharacter(maxCharacter)
{
    _background = new UIImage(_driver, _guiScene, id, _rect, _driver->getTexture(backgroundTextPath));
    _input = new UISmartText(_driver, _guiScene, id, _defaultText, _textPos, _textSize);
    _inputText = "";
    _clicked = false;
    _clock = 0;
    _clockTimeSet = 7;
}

UIEditBox::~UIEditBox()
{
    // std::cout << "~UIText" << std::endl;
}

void UIEditBox::setVisible(bool visible)
{
    _background->setVisible(visible);
    _input->setVisible(visible);
}

void UIEditBox::setClicked(void)
{
    _clicked = true;
    if (_inputText.size() == 0)
        _input->setText(_inputText);
}

void UIEditBox::setUnclicked(void)
{
    _clicked = false;
    if (_inputText.size() == 0)
        _input->setText(_defaultText);
}


bool UIEditBox::isClicked(void) const
{
    return (_clicked);
}

void UIEditBox::setText(std::string &text)
{
    _inputText = text;
    _input->setText(_inputText);
}

void UIEditBox::addCharacter(char c)
{
    if (((_inputText[_inputText.size() - 1] == c && _clock <= -5) ||
    (_inputText[_inputText.size() - 1] != c && _clock <= 0))
     && _inputText.size() < _maxCharacter) {
        // std::cout << "IN LOOP" << std::endl;
        _inputText += c;
        _input->setText(_inputText);
        _clock = _clockTimeSet;
    }
}

void UIEditBox::removeCharacter(void)
{
    if (_clock <= 0 && _inputText.size() > 0) {
        _inputText.pop_back();
        _input->setText(_inputText);
        _clock = _clockTimeSet;
    }
}

void UIEditBox::update(void)
{
    _clock -= 1;
}

std::string UIEditBox::getText(void) const
{
    return (_inputText);
}
