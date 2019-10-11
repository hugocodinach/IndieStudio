/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/UIImage.cpp
*/

#include "UIImage.hpp"

UIImage::UIImage(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene, irr::s32 id,
irr::core::rect<irr::f32> rect, irr::video::ITexture *texture, bool usePercentage,
bool setScale, irr::gui::IGUIElement *parent, bool useAlphaChannel, const wchar_t *text):
AInterfaceObj(guiScene, id), _driver(driver), _texture(texture), _setScale(setScale),
_useAlphaChannel(useAlphaChannel), _parent(parent), _text(text)
{
    _type = UI_OBJ_TYPE::IMAGE;
    _imageObj = nullptr;
    if (!_texture) {
        // std::cout << "Can't load texture" << std::endl;
        return;
    }
    if (usePercentage == true)
        _rect = posFromPercentage(rect, _driver->getScreenSize());
    else
        _rect = convertRectfToRecti(rect);
    _imageObj = guiScene->addImage(_rect, _parent, _id, _text, _useAlphaChannel);
    _imageObj->setScaleImage(_setScale);
    _imageObj->setImage(_texture);
}

UIImage::~UIImage()
{
    if (_imageObj)
        _imageObj->setVisible(false);
}

bool UIImage::setTexture(irr::video::ITexture *texture)
{
    _texture = texture;
    _imageObj->setImage(_texture);
    return true;
}

void UIImage::setColor(irr::video::SColor color)
{
    _imageObj->setColor(color);
}

void UIImage::setVisible(bool visible)
{
    _imageObj->setVisible(visible);
}

irr::gui::IGUIElement *UIImage::getIrrElement(void) const
{
    return _imageObj;
}