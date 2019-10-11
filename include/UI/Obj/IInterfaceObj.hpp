/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/IInterfaceObj.hpp
*/

#ifndef IINTERFACE_OBJ
#define IINTERFACE_OBJ

    #include <iostream>

    #include "irr/irrlicht.h"

    enum UI_OBJ_TYPE {
        BUTTON = 1,
        IMAGE,
        TEXT,
    };

    class IInterfaceObj
    {
        public:
        virtual ~IInterfaceObj() = default;

        virtual void reset() = 0;
        virtual int getId() const = 0;
        virtual int getType() const = 0;
        virtual void setVisible(bool) = 0;

        private:
    };

#endif