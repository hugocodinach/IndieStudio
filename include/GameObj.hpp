/*
** EPITECH PROJECT, 2018
** GameObj.hpp
** File description:
** include/GameObj.hpp
*/

#ifndef GAME_OBJ
#define GAME_OBJ

#include "IGameObj.hpp"

class GameObj : public IGameObj
{
    public:
        virtual void pure() = 0;

        template<typename T>
        void setPosition(irr::core::vector3df pos, T node) {
            node->setPosition(pos);
        };

        void setVisibility(bool visibility) final;
        void toggleVisibility(void) final;
        irr::core::vector3df getPosition(void);
        bool isVisible(void) final;

    protected:
          irr::core::vector3df _pos;
          bool _visible;
};

#endif