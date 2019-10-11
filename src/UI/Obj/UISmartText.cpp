/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/UISmartText.cpp
*/

#include "UISmartText.hpp"
#include "Alphabet.hpp"

UISmartText::UISmartText(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene,
irr::s32 id, std::string text, irr::core::position2df pos, float fontSize,
bool usePercentage, bool clickable): AInterfaceObj(guiScene, id), _driver(driver),
_text(text), _fontSize(fontSize), _clickable(clickable)
{
    if (usePercentage == true) {
        _pos.X = pos.X * static_cast<float>(_driver->getScreenSize().Width) / 100;
        _pos.Y = pos.Y * static_cast<float>(_driver->getScreenSize().Height) / 100;
        _fontSize = fontSize * static_cast<float>(_driver->getScreenSize().Width) / 100;
    } else {
        _pos.X = pos.X;
        _pos.Y = pos.Y;
        _fontSize = fontSize;
    }
    _rect.UpperLeftCorner.X = pos.X;
    _rect.UpperLeftCorner.Y = pos.Y;
    _rect.LowerRightCorner.X = pos.X + _fontSize * _text.size();
    _rect.LowerRightCorner.Y = pos.Y + _fontSize;
    updateText();
    if (_clickable == true)
        createCollisionBox();
}

UISmartText::~UISmartText()
{
//     // std::cout << "UISmartText::~UISmartText" << std::endl;
    for (int i = 0; i < _images.size(); i += 1) {
        if(_images[i].second) {
            delete _images[i].second;
        }
    }
}

void UISmartText::updateText(void)
{
    int i = 0;
    int j = 0;
    irr::video::ITexture *texture = nullptr;

    for (int i = 0; i < _images.size(); i += 1)
        delete _images[i].second;
    _images.clear();
    std::transform(_text.begin(), _text.end(), _text.begin(), ::toupper);
    for (char const &c: _text) {
        j = 0;
        for(;alphabet_path[j].c != c && alphabet_path[j].c != '@'; j += 1);
        if (alphabet_path[j].c == '@')
            j = 0;
        texture = _driver->getTexture(alphabet_path[j].idle);
        if (!texture)
            continue;
        _images.push_back(std::make_pair(alphabet_path[j].c, new UIImage(_driver,
        _guiScene, _id, irr::core::rect<irr::f32>(_pos.X + i * _fontSize, _pos.Y,
        _pos.X + (i + 1) * _fontSize, _pos.Y + _fontSize),
        texture, false)));
        i += 1;
    }
}

void UISmartText::setText(std::string text)
{
    _text = text;
    updateText();
}

void UISmartText::setFont(int size)
{
    _fontSize = size;
    updateText();
}

void UISmartText::setPos(irr::core::position2di &pos)
{
    _pos = pos;
    updateText();
}

std::string UISmartText::getText(void) const
{
    return (_text);
}

irr::core::position2di UISmartText::getPos(void) const
{
    return (_pos);
}

void UISmartText::setVisible(bool visible)
{
//     // std::cout << "UISmartText::setVisible" << std::endl;
    for (int i = 0; i < _images.size(); i += 1)
        _images[i].second->setVisible(visible);
}


void UISmartText::setHover(void)
{
    int j = 0;

    // std::cout << "UISmartText::setHover" << std::endl;
    for (int i = 0; i < _images.size(); i += 1) {
        j = 0;
        for(;alphabet_path[j].c != _images[i].first && alphabet_path[j].c != '@'; j += 1);
        if (alphabet_path[j].idle == NULL)
            j = 0;
        if(_images[i].second)
            _images[i].second->setTexture(_driver->getTexture(alphabet_path[j].hover));
    }
}

void UISmartText::setIdle(void)
{
    int j = 0;

    for (int i = 0; i < _images.size(); i += 1) {
        j = 0;
        for(;alphabet_path[j].c != _images[i].first && alphabet_path[j].c != '@'; j += 1);
        if (alphabet_path[j].idle == NULL)
            j = 0;
        if(_images[i].second)
            _images[i].second->setTexture(_driver->getTexture(alphabet_path[j].idle));
    }
}

void UISmartText::setClicked(void)
{
    int j = 0;

    for (int i = 0; i < _images.size(); i += 1) {
        j = 0;
        for(;alphabet_path[j].c != _images[i].first && alphabet_path[j].c != '@'; j += 1);
        if (alphabet_path[j].idle == NULL)
            j = 0;
        if(_images[i].second)
            _images[i].second->setTexture(_driver->getTexture(alphabet_path[j].clicked));
    }
}

void UISmartText::setParent(irr::gui::IGUIElement *elem)
{
    for (int i = _images.size(); i < _images.size(); i += 1) {
        elem->addChild(_images[i].second->getIrrElement());
    }
}

void UISmartText::createCollisionBox(void)
{
    _collisionBox = _guiScene->addButton(_rect, 0, _id);
    _collisionBox->setUseAlphaChannel(true);
    _collisionBox->setDrawBorder(false);
    _collisionBox->setScaleImage(true);
    _collisionBox->setImage(_driver->getTexture("./ressources/UI/global/empty.png"), {0, 0, 100, 100});
}
