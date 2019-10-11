/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/UIText.cpp
*/

#include "UILateralMenu.hpp"

UILateralMenu::UILateralMenu(irr::video::IVideoDriver *driver,
irr::gui::IGUIEnvironment* guiScene, irr::s32 id, IInterfaceObj *leftButton,
IInterfaceObj *rightButton, IInterfaceObj *image,
std::vector<irr::io::path> texturesPath, bool userPercentage):
AInterfaceObj(guiScene, id), _driver(driver)
{
    _leftButton = static_cast<UIButton *>(leftButton);
    _rightButton = static_cast<UIButton *>(rightButton);
    _image = static_cast<UIImage *>(image);
    if (texturesPath.size() < 1)
        return;
    for (int i = 0; i < texturesPath.size(); i += 1)
        _textures.push_back(_driver->getTexture(texturesPath[i]));
    _actualTexture = 0;
    _image->setTexture(_textures[_actualTexture]);
}

UILateralMenu::~UILateralMenu()
{
    // std::cout << "~UILateralMenu" << std::endl;
}

void UILateralMenu::nextTextureLeft()
{
    if (_actualTexture - 1 < 0)
        _actualTexture = _textures.size() - 1;
    else
        _actualTexture -= 1;
    _image->setTexture(_textures[_actualTexture]);
}
void UILateralMenu::nextTextureRight()
{
    if (_actualTexture + 1 >= _textures.size())
        _actualTexture = 0;
    else
        _actualTexture += 1;
    _image->setTexture(_textures[_actualTexture]);
}

bool UILateralMenu::setIdx(int idx)
{
    if (idx < 0 || idx >= _textures.size())
        return false;
    _actualTexture = idx;
    _image->setTexture(_textures[_actualTexture]);
    return true;
}

int UILateralMenu::getActualTextureNb(void) const
{
    return (_actualTexture);
}

void UILateralMenu::setVisible(bool visible)
{
    _leftButton->setVisible(visible);
    _rightButton->setVisible(visible);
    _image->setVisible(visible);
}
