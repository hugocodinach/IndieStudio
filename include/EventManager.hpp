/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/EventManager.hpp
*/

#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <iostream>
#include <vector>
#include <irr/irrlicht.h>
#include "Key.hpp"
#include "AI.hpp"
#include "InterfaceManager.hpp"
#include "utils.hpp"

extern irr::core::array<irr::SJoystickInfo> myjoystickInfo;

class EventManager : public irr::IEventReceiver
{
    public:
        EventManager(InterfaceManager *elManagor);
        ~EventManager();
        bool OnEvent(const irr::SEvent &event);
        virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
        std::vector<KeyHandler> &getKeyVect();
        std::vector<KeyHandler> &getKeyVect(std::vector<AI*> &AIVect, std::vector<IActor*> &actorVect);
        const irr::SEvent::SJoystickEvent & GetJoystickState(void) const;

    private:
        InterfaceManager *_elManagor;
        std::vector<KeyHandler> _keyvect;
        bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
        bool ControllerKeyIsDown[68];
        irr::SEvent::SJoystickEvent JoystickState;
};
#endif
