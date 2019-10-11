/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/AInterfaceObj.cpp
*/

#include "AInterfaceObj.hpp"

AInterfaceObj::AInterfaceObj(irr::gui::IGUIEnvironment* guiScene, irr::s32 id,
bool display): _guiScene(guiScene), _id(id), _display(display)
{
}

AInterfaceObj::~AInterfaceObj()
{
}

int AInterfaceObj::getId() const
{
    return _id;
}

int AInterfaceObj::getType() const
{
    return (_type);
}

int AInterfaceObj::cptWidth(int percentage)
{
    return (percentage * WINDOW_WIDTH / 100);
}

int AInterfaceObj::cptHeight(int percentage)
{
    return (percentage * WINDOW_HEIGHT / 100);
}

void AInterfaceObj::realPosFromPercentage(irr::core::rect<irr::s32> &rect)
{
    rect.UpperLeftCorner.X = cptWidth(rect.UpperLeftCorner.X);
    rect.UpperLeftCorner.Y = cptHeight(rect.UpperLeftCorner.Y);
    rect.LowerRightCorner.X = cptWidth(rect.LowerRightCorner.X);
    rect.LowerRightCorner.Y = cptHeight(rect.LowerRightCorner.Y);
}

irr::core::rect<irr::s32> AInterfaceObj::posFromPercentage(irr::core::rect<irr::f32> rect,
const irr::core::dimension2du& screenSize)
{
    irr::core::rect<irr::s32> converted;

    converted.UpperLeftCorner.X = rect.UpperLeftCorner.X * screenSize.Width / 100;
    converted.UpperLeftCorner.Y = rect.UpperLeftCorner.Y * screenSize.Height / 100;
    converted.LowerRightCorner.X = rect.LowerRightCorner.X * screenSize.Width / 100;
    converted.LowerRightCorner.Y = rect.LowerRightCorner.Y * screenSize.Height / 100;
    return (converted);
}

irr::core::rect<irr::s32> AInterfaceObj::convertRectfToRecti(irr::core::rect<irr::f32> rect)
{
    irr::core::rect<irr::s32> converted;

    converted.UpperLeftCorner.X = rect.UpperLeftCorner.X;
    converted.UpperLeftCorner.Y = rect.UpperLeftCorner.Y;
    converted.LowerRightCorner.X = rect.LowerRightCorner.X;
    converted.LowerRightCorner.Y = rect.LowerRightCorner.Y;
    return (converted);
}