/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/UIText.cpp
*/

#include "UILateralText.hpp"

UILateralText::UILateralText(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene, int id,
IInterfaceObj *leftButton, IInterfaceObj *rightButton, std::vector<std::string> texts,
irr::core::position2df pos, float fontSize, bool userPercentage):
AInterfaceObj(guiScene, id), _texts(texts), _driver(driver), _pos(pos), _fontSize(fontSize)
{
    _leftButton = static_cast<UIButton *>(leftButton);
    _rightButton = static_cast<UIButton *>(rightButton);
    if (texts.size() < 1)
        return;
    _actualIdx = 0;
    float win_width = _driver->getScreenSize().Width;
    _textZone = new UISmartText(_driver, _guiScene, -1,
    _texts[_actualIdx], _pos, (_fontSize * 100.0) / WINDOW_WIDTH);
}

UILateralText::~UILateralText()
{
    // std::cout << "~UILateralText" << std::endl;
}

void UILateralText::nextTextLeft()
{
    // std::cout << "UILateralText::nextTextLeft" << std::endl;

    if (_actualIdx - 1 < 0)
        _actualIdx = _texts.size() - 1;
    else
        _actualIdx -= 1;
    _textZone->setText(_texts[_actualIdx]);
}
void UILateralText::nextTextRight()
{
    // std::cout << "UILateralText::nextTextRight" << std::endl;
    // std::cout << "_texts.size() = " << _texts.size() << std::endl;
    if (_actualIdx + 1 >= _texts.size())
        _actualIdx = 0;
    else
        _actualIdx += 1;
    _textZone->setText(_texts[_actualIdx]);
}

int UILateralText::getIdx(void) const
{
    return (_actualIdx);
}

bool UILateralText::setIdx(int idx)
{
    if (idx < 0 || idx >= _texts.size())
        return false;
    _textZone->setText(_texts[idx]);
}

void UILateralText::setVisible(bool visible)
{
    _leftButton->setVisible(visible);
    _rightButton->setVisible(visible);
    _textZone->setVisible(visible);
}