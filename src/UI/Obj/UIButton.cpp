/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/UIButton.cpp
*/

#include "UIButton.hpp"
#include "sound.hpp"

UIButton::UIButton(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene,
irr::s32 id, irr::core::rect<irr::f32> rect, const wchar_t *text, const wchar_t *tooltipText,
MusicPlayer &musicPlayer, bool userPercentage):
AInterfaceObj(guiScene, id), _driver(driver), _text(text), _sbName(""),
_tooltipText(tooltipText), _musicPlayer(musicPlayer)
{
    _type = BUTTON_TYPE::BASIC;
    if (userPercentage == true)
        _rect = posFromPercentage(rect, _driver->getScreenSize());
    else
        _rect = convertRectfToRecti(rect);
    _type = UI_OBJ_TYPE::BUTTON;
    _sb = nullptr;
    _texture_idle = nullptr;
    _texture_over = nullptr;
    _labelText = nullptr;
    _buttonObj = _guiScene->addButton(_rect, 0, _id, _text, _tooltipText);
}

UIButton::UIButton(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene,
irr::s32 id, irr::core::rect<irr::f32> rect, irr::core::rect<irr::s32> textureRect,
const irr::io::path &sbName, const irr::io::path &idleTexturePath, const irr::io::path &overTexturePath,
const irr::io::path &clickedTexturePath, MusicPlayer &musicPlayer, bool userPercentage):
AInterfaceObj(guiScene, id), _driver(driver), _textureRect(textureRect),
_sbName(sbName), _musicPlayer(musicPlayer)
{
    _type = BUTTON_TYPE::SPRITED;
    if (userPercentage == true)
        _rect = posFromPercentage(rect, _driver->getScreenSize());
    else
        _rect = convertRectfToRecti(rect);
    _sb = nullptr;
    _texture_idle = nullptr;
    _texture_over = nullptr;
    _labelText = nullptr;
    _buttonObj = nullptr;
    _buttonObj = _guiScene->addButton(_rect, 0, _id);
    _buttonObj->setUseAlphaChannel(true);
    _buttonObj->setDrawBorder(false);
    _buttonObj->setScaleImage(true);
    _sb = _guiScene->getSpriteBank(_sbName);
    if (!_sb)
        _sb = _guiScene->addEmptySpriteBank(_sbName);
    if (!_sb) {
        // std::cout << "Failed to init spriteBank" << std::endl;
        return;
    }
    _texture_idle = _driver->getTexture(idleTexturePath);
    _texture_over = _driver->getTexture(overTexturePath);
    _texture_clicked = _driver->getTexture(clickedTexturePath);
    _sb->addTextureAsSprite(_texture_idle);
    _sb->addTextureAsSprite(_texture_over);
    _sb->addTextureAsSprite(_texture_clicked);
    _buttonObj->setImage(_texture_idle, _textureRect);
    _buttonObj->setPressedImage(_texture_clicked, _textureRect);
}

UIButton::UIButton(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene,
irr::s32 id, irr::core::rect<irr::f32> rect, irr::core::rect<irr::s32> textureRect,
const irr::io::path &texturePath, std::string text, irr::core::position2df pos,
float fontSize, MusicPlayer &musicPlayer, bool usePercentage): AInterfaceObj(guiScene, id), _driver(driver),
_textureRect(textureRect), _musicPlayer(musicPlayer)
{
    _type = BUTTON_TYPE::TEXTED;
    if (usePercentage == true)
        _rect = posFromPercentage(rect, _driver->getScreenSize());
    else
        _rect = convertRectfToRecti(rect);
    _texture_idle = _driver->getTexture(texturePath);
    _imageText = new UIImage(_driver, _guiScene, -1, rect, _texture_idle);
    _labelText = new UISmartText(_driver, _guiScene, _id, text, pos, fontSize);
    _buttonObj = _guiScene->addButton(_rect, 0, _id);
    _buttonObj->setUseAlphaChannel(true);
    _buttonObj->setDrawBorder(false);
    _buttonObj->setScaleImage(true);
    _buttonObj->setImage(_driver->getTexture("./ressources/UI/global/empty.png"), {0, 0, 100, 100});
}

UIButton::~UIButton()
{
}

bool UIButton::setLabelText(std::string &text)
{
    if (!_labelText)
        return false;
    _buttonObj->remove();
    _labelText->setText(text);
    _buttonObj = _guiScene->addButton(_rect, 0, _id);
    _buttonObj->setUseAlphaChannel(true);
    _buttonObj->setDrawBorder(false);
    _buttonObj->setScaleImage(true);
    _buttonObj->setImage(_driver->getTexture("./ressources/UI/global/empty.png"), {0, 0, 100, 100});
    return true;
}


bool UIButton::setOver(void)
{
    // std::cout << "UIButton::setOver" << std::endl;
	_musicPlayer.playSoundPlayer("BUTTON_HOVER");
    if (_type == BUTTON_TYPE::SPRITED)
        _buttonObj->setImage(_texture_over, _textureRect);
    else if (_type == BUTTON_TYPE::TEXTED)
        _labelText->setHover();
    return true;
}

bool UIButton::setIdle(void)
{
    if (_type == BUTTON_TYPE::SPRITED)
        _buttonObj->setImage(_texture_idle, _textureRect);
    else if (_type == BUTTON_TYPE::TEXTED)
        _labelText->setIdle();
    return true;
}

bool UIButton::setClicked(void)
{
    _musicPlayer.playSoundPlayer("BUTTON_CLICKED");
    if (_type == BUTTON_TYPE::SPRITED)
        _buttonObj->setImage(_texture_clicked, _textureRect);
    else if (_type == BUTTON_TYPE::TEXTED)
        _labelText->setClicked();
    return true;
}

void UIButton::setVisible(bool visible)
{
    _buttonObj->setVisible(visible);
}
