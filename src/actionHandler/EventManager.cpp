/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/actionHandler/EventManager.cpp
*/

#include "EventManager.hpp"

EventManager::EventManager(InterfaceManager *elManagor)
{
	_elManagor = elManagor;
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
	for (int i = 0; i < 68; i++) {
		ControllerKeyIsDown[i] = false;
	}
}

EventManager::~EventManager()
{
}

bool EventManager::OnEvent(const irr::SEvent &event)
{
	int joy = 0;
	if (event.EventType == irr::EET_GUI_EVENT || event.EventType == irr::EET_JOYSTICK_INPUT_EVENT || event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		// // std::cout << "OnEvent" << std::endl;
		_elManagor->onUIEvent(event);
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT)
	{
		for (irr::u32 joystick = 0; joystick < myjoystickInfo.size(); ++joystick)
		{
			joy = joystick;
			const irr::SEvent::SJoystickEvent & joystickData = event.JoystickEvent;
			if (myjoystickInfo.size() <= (int)joystickData.Joystick || myjoystickInfo[joystickData.Joystick].Name != myjoystickInfo[joystick].Name)
				continue;
			if (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_V] > 0) {
				ControllerKeyIsDown[RT1 + (joy * 17)] = true;
			} else {
				ControllerKeyIsDown[RT1 + (joy * 17)] = false;
			}
			if (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Z] > 0) {
				ControllerKeyIsDown[LT1 + (joy * 17)] = true;
			} else {
				ControllerKeyIsDown[LT1 + (joy * 17)] = false;
			}
			if (floatAbs(joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X]) > floatAbs(joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y])) {
				if (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X] > 25000) {
					ControllerKeyIsDown[RD1 + (joy * 17)] = true;
					ControllerKeyIsDown[UD1 + (joy * 17)] = false;
					ControllerKeyIsDown[LD1 + (joy * 17)] = false;
					ControllerKeyIsDown[DD1 + (joy * 17)] = false;
				}
				else if (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X] < - 25000) {
					ControllerKeyIsDown[LD1 + (joy * 17)] = true;
					ControllerKeyIsDown[UD1 + (joy * 17)] = false;
					ControllerKeyIsDown[RD1 + (joy * 17)] = false;
					ControllerKeyIsDown[DD1 + (joy * 17)] = false;
				} else {
					ControllerKeyIsDown[RD1 + (joy * 17)] = false;
					ControllerKeyIsDown[LD1 + (joy * 17)] = false;
				}						
			} else if (floatAbs(joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X]) < floatAbs(joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y])) {
				if (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] > 25000) {
					ControllerKeyIsDown[DD1 + (joy * 17)] = true;
					ControllerKeyIsDown[UD1 + (joy * 17)] = false;
					ControllerKeyIsDown[LD1 + (joy * 17)] = false;
					ControllerKeyIsDown[RD1 + (joy * 17)] = false;
				}
				else if (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] < - 25000) {
					ControllerKeyIsDown[UD1 + (joy * 17)] = true;
					ControllerKeyIsDown[RD1 + (joy * 17)] = false;
					ControllerKeyIsDown[LD1 + (joy * 17)] = false;
					ControllerKeyIsDown[DD1 + (joy * 17)] = false;
				} else {
					ControllerKeyIsDown[UD1 + (joy * 17)] = false;
					ControllerKeyIsDown[DD1 + (joy * 17)] = false;
				}
			}
			else {
					ControllerKeyIsDown[UD1 + (joy * 17)] = false;
					ControllerKeyIsDown[LD1 + (joy * 17)] = false;
					ControllerKeyIsDown[DD1 + (joy * 17)] = false;
					ControllerKeyIsDown[RD1 + (joy * 17)] = false;
			}
			for (int i = 0; i < 9; i++) {
				ControllerKeyIsDown[A1 + i + (joy * 17)] = joystickData.IsButtonPressed((irr::u32)i);
			}
		}
	}
	return false;
};

bool EventManager::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
};

std::vector<KeyHandler> &EventManager::getKeyVect()
{
	_keyvect.clear();
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
	{
		if (KeyIsDown[i] == true)
		{
			_keyvect.push_back(KeyHandler(static_cast<irr::EKEY_CODE> (i)));
		}
	}
	for (int i = 0; i < 68; i++) {
		if (ControllerKeyIsDown[i] == true)
		{
			_keyvect.push_back(KeyHandler(static_cast<ControllerKey> (i)));
		}
	}
	return (_keyvect);
};

std::vector<KeyHandler> &EventManager::getKeyVect(std::vector<AI*> &AIVect, std::vector<IActor*> &actorVect)
{
	bool val = true;
	_keyvect.clear();
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
	{
		val = true;
		for (IActor *act: actorVect) {
			val = true;
			for (int j = 0; j < 6; j++) {
				if (KeyIsDown[i] == true && act->isOnline() && act->getBinds()[j].first == KeyHandler(static_cast<irr::EKEY_CODE> (i))) {
					val = false;
				}
				if (val == false) {
					break;
				}
			}
			if (val == false) {
				continue;
			}
		}
		if (val == false) {
			continue;
		}
		val = true;
		for (AI *ai: AIVect) {
			for (int j = 0; j < 6; j++) {
				if ((ai->getBomberman()->getBinds()[j].first) == KeyHandler(static_cast<irr::EKEY_CODE> (i))) {
					val = false;
				}
				if (val == false) {
					break;
				}
			}
			if (val == false) {
				break;
			}
		}
		if (val == false) {
			continue;
		}
		if (KeyIsDown[i] == true)
		{
			_keyvect.push_back(KeyHandler(static_cast<irr::EKEY_CODE> (i)));
		}
	}
	for (int i = 0; i < 68; i++) {
		val = true;
		for (IActor *act: actorVect) {
			for (int j = 0; j < 6; j++) {
				if (act->isOnline() && act->getBinds()[j].first == KeyHandler(static_cast<ControllerKey> (i))) {
					val = false;
				}
				if (val == false) {
					break;
				}
			}
			if (val == false) {
				break;
			}
		}
		if (val == false) {
			continue;
		}
		val = true;
		for (AI *ai: AIVect) {
			for (int j = 0; j < 6; j++) {
				if (((ai->getBomberman()->getBinds()[j]).first) == KeyHandler(static_cast<ControllerKey> (i))) {
					val = false;
				}
				if (val == false) {
					break;
				}
			}
			if (val == false) {
				break;
			}
		}
		if (val == false) {
			continue;
		}
		if (ControllerKeyIsDown[i] == true)
		{
			_keyvect.push_back(KeyHandler(static_cast<ControllerKey> (i)));
		}
	}
	return (_keyvect);
};

const irr::SEvent::SJoystickEvent & EventManager::GetJoystickState(void) const
{
	return JoystickState;
}