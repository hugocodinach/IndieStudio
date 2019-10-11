/*
** EPITECH PROJECT, 2018
** Key.hpp
** File description:
** include/Key.hpp
*/

#ifndef KEY
#define KEY

#include <irr/irrlicht.h>

enum ControllerKey {
    A1,
    B1,
    X1,
    Y1,
    LB1,
    RB1,
    SELECT1,
    START1,
    HOME1,
    LS1,
    RS1,
    UD1,
    RD1,
    DD1,
    LD1,
    LT1,
    RT1,
    A2,
    B2,
    X2,
    Y2,
    LB2,
    RB2,
    SELECT2,
    START2,
    HOME2,
    LS2,
    RS2,
    UD2,
    RD2,
    DD2,
    LD2,
    LT2,
    RT2,
    A3,
    B3,
    X3,
    Y3,
    LB3,
    RB3,
    SELECT3,
    START3,
    HOME3,
    LS3,
    RS3,
    UD3,
    RD3,
    DD3,
    LD3,
    LT3,
    RT3,
    A4,
    B4,
    X4,
    Y4,
    LB4,
    RB4,
    SELECT4,
    START4,
    HOME4,
    LS4,
    RS4,
    UD4,
    RD4,
    DD4,
    LD4,
    LT4,
    RT4,
};

enum KeyType {
    KEYBOARD,
    CONTROLLER,
};

class KeyHandler
{
    public:
        KeyHandler(irr::EKEY_CODE key);
        KeyHandler(ControllerKey key);
        KeyHandler(const KeyHandler &oldKey) {
		_key = oldKey._key;
		_irrKeyValue = oldKey._irrKeyValue;
		_type = oldKey._type;
	};
        KeyHandler(int key, int type);
        ~KeyHandler();

        bool operator==(const KeyHandler &other) const;

        void setKey(irr::EKEY_CODE key);
        void setKey(ControllerKey key);
        int getKey(void) const;
        KeyType getType(void) const;
        irr::EKEY_CODE getIrrKey(void) const;

    private:
        int _key;
        irr::EKEY_CODE _irrKeyValue;
        KeyType _type;
};

#endif