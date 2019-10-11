/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/UIText.cpp
*/

#include "UIText.hpp"

UIText::UIText(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene,
wchar_t *text, irr::core::rect<irr::f32> rect, irr::s32 id, const irr::io::path &fontPath,
bool userPercentage, bool display, bool border, bool wordWrap,
bool fillBackground, irr::gui::IGUIElement *parent):
AInterfaceObj(guiScene, id, display), _driver(driver), _text(text), _border(border),
_wordWrap(wordWrap), _fillBackground(fillBackground), _parent(parent) 
{
    _type = UI_OBJ_TYPE::TEXT;
    if (userPercentage == true)
        _rect = posFromPercentage(rect, _driver->getScreenSize());
    _textObj = guiScene->addStaticText(_text, _rect, _border, _wordWrap, _parent, _id, _fillBackground);
    if (!_textObj)
        return;
    _font = guiScene->getFont(fontPath);
    if (!_font) {
        std::cerr << "UIText::UIText: Can't load font" << std::endl;
        return;
    }
    _textObj->setOverrideFont(_font);
}

UIText::~UIText()
{
    // std::cout << "~UIText" << std::endl;
}

void UIText::setVisible(bool visible)
{
    _textObj->setVisible(visible);
}
