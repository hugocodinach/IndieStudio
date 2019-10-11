/*
** EPITECH PROJECT, 2018
** key.cpp
** File description:
** src/keyHandler/key.cpp
*/

#include "Key.hpp"

KeyHandler::KeyHandler(ControllerKey key)
{
    _key = key;
    _type = CONTROLLER;
}

KeyHandler::KeyHandler(irr::EKEY_CODE key)
{
    _key = key;
    _irrKeyValue = key;
    _type = KEYBOARD;
}

KeyHandler::KeyHandler(int key, int type)
{
    _key = key;
    _irrKeyValue = static_cast<irr::EKEY_CODE>(key);
    _type = static_cast<KeyType>(type);
}

KeyHandler::~KeyHandler()
{
}

void KeyHandler::setKey(irr::EKEY_CODE key)
{
    _key = key;
    _irrKeyValue = key;
    _type = KEYBOARD;
}

void KeyHandler::setKey(ControllerKey key)
{
    _key = key;
    _type = CONTROLLER;
}


int KeyHandler::getKey(void) const
{
    return _key;
}

KeyType KeyHandler::getType(void) const
{
    return _type;
}

irr::EKEY_CODE KeyHandler::getIrrKey(void) const
{
    return _irrKeyValue;
}

bool KeyHandler::operator==(const KeyHandler &other) const
{
    return (_type == other.getType() && static_cast<int>(_key) == static_cast<int>(other.getKey()));
}