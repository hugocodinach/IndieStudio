/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/InterfaceKeyBinding.hpp
*/

#ifndef INTERFACE_KEY_BINDING
#define INTERFACE_KEY_BINDING

    #include <vector>
    #include <map>
    #include <string>
    #include <iostream>

    #include "irr/irrlicht.h"

    #include "AInterfaceScene.hpp"
    #include "IInterfaceObj.hpp"
    #include "InterfaceManager.hpp"
	#include "utils.hpp"
    #include "Key.hpp"

	extern irr::core::array<irr::SJoystickInfo> myjoystickInfo;

    class InterfaceKeyBinding: public AInterfaceScene
    {
        public:

            enum KEY_BINDING_OBJ_ID {
                POPUP_BACKGROUND,
                POPUP_TEXT,
                BACK_BUTTON,

                FORWARD_INPUT_J1,
                BACKWARD_INPUT_J1,
                LEFT_INPUT_J1,
                RIGHT_INPUT_J1,
                DROP_BOMB_INPUT_J1,
                INTERACTION_INPUT_J1,

                FORWARD_INPUT_J2,
                BACKWARD_INPUT_J2,
                LEFT_INPUT_J2,
                RIGHT_INPUT_J2,
                DROP_BOMB_INPUT_J2,
                INTERACTION_INPUT_J2,

                FORWARD_INPUT_J3,
                BACKWARD_INPUT_J3,
                LEFT_INPUT_J3,
                RIGHT_INPUT_J3,
                DROP_BOMB_INPUT_J3,
                INTERACTION_INPUT_J3,

                FORWARD_INPUT_J4,
                BACKWARD_INPUT_J4,
                LEFT_INPUT_J4,
                RIGHT_INPUT_J4,
                DROP_BOMB_INPUT_J4,
                INTERACTION_INPUT_J4,

            };

            enum KEY_BINDING_STATU {
                DEFAULT = 1,
                WAIT_INPUT = 2,
            };

            enum PLAY_KEY {
                FORWARD,
                BACKWARD,
                LEFT,
                RIGHT,
                DROP_BOMB,
                INTERACTION,
            };

            typedef struct binding_info_s {
                KeyHandler keyObj;
                const char label[128];
            } binding_info_t;
        
            std::map<const irr::EKEY_CODE, std::string> key_map = {
            {irr::EKEY_CODE::KEY_LBUTTON, "KEY_LBUTTON" },
            {irr::EKEY_CODE::KEY_RBUTTON, "KEY_RBUTTON" },
            {irr::EKEY_CODE::KEY_CANCEL, "KEY_CANCEL" },
            {irr::EKEY_CODE::KEY_MBUTTON, "KEY_MBUTTON" },
            {irr::EKEY_CODE::KEY_XBUTTON1, "KEY_XBUTTON1" },
            {irr::EKEY_CODE::KEY_XBUTTON2, "KEY_XBUTTON2" },
            {irr::EKEY_CODE::KEY_BACK, "KEY_BACK" },
            {irr::EKEY_CODE::KEY_TAB, "KEY_TAB" },
            {irr::EKEY_CODE::KEY_CLEAR, "KEY_CLEAR" },
            {irr::EKEY_CODE::KEY_RETURN, "KEY_RETURN" },
            {irr::EKEY_CODE::KEY_SHIFT, "KEY_SHIFT" },
            {irr::EKEY_CODE::KEY_CONTROL, "KEY_CONTROL" },
            {irr::EKEY_CODE::KEY_MENU, "KEY_MENU" },
            {irr::EKEY_CODE::KEY_PAUSE, "KEY_PAUSE" },
            {irr::EKEY_CODE::KEY_CAPITAL, "KEY_CAPITAL" },
            {irr::EKEY_CODE::KEY_KANA, "KEY_KANA" },
            {irr::EKEY_CODE::KEY_HANGUEL, "KEY_HANGUEL" },
            {irr::EKEY_CODE::KEY_HANGUL, "KEY_HANGUL" },
            {irr::EKEY_CODE::KEY_JUNJA, "KEY_JUNJA" },
            {irr::EKEY_CODE::KEY_FINAL, "KEY_FINAL" },
            {irr::EKEY_CODE::KEY_HANJA, "KEY_HANJA" },
            {irr::EKEY_CODE::KEY_KANJI, "KEY_KANJI" },
            {irr::EKEY_CODE::KEY_ESCAPE, "KEY_ESCAPE" },
            {irr::EKEY_CODE::KEY_CONVERT, "KEY_CONVERT" },
            {irr::EKEY_CODE::KEY_NONCONVERT, "KEY_NONCONVERT" },
            {irr::EKEY_CODE::KEY_ACCEPT, "KEY_ACCEPT" },
            {irr::EKEY_CODE::KEY_MODECHANGE, "KEY_MODECHANGE" },
            {irr::EKEY_CODE::KEY_SPACE, "SPACE" },
            {irr::EKEY_CODE::KEY_PRIOR, "KEY_PRIOR" },
            {irr::EKEY_CODE::KEY_NEXT, "KEY_NEXT" },
            {irr::EKEY_CODE::KEY_END, "KEY_END" },
            {irr::EKEY_CODE::KEY_HOME, "KEY_HOME" },
            {irr::EKEY_CODE::KEY_LEFT, "KEY_LEFT" },
            {irr::EKEY_CODE::KEY_UP, "KEY_UP" },
            {irr::EKEY_CODE::KEY_RIGHT, "KEY_RIGHT" },
            {irr::EKEY_CODE::KEY_DOWN, "KEY_DOWN" },
            {irr::EKEY_CODE::KEY_SELECT, "KEY_SELECT" },
            {irr::EKEY_CODE::KEY_PRINT, "KEY_PRINT" },
            {irr::EKEY_CODE::KEY_EXECUT, "KEY_EXECUT" },
            {irr::EKEY_CODE::KEY_SNAPSHOT, "KEY_SNAPSHOT" },
            {irr::EKEY_CODE::KEY_INSERT, "KEY_INSERT" },
            {irr::EKEY_CODE::KEY_DELETE, "DELETE" },
            {irr::EKEY_CODE::KEY_HELP, "KEY_HELP" },
            {irr::EKEY_CODE::KEY_KEY_0, "0" },
            {irr::EKEY_CODE::KEY_KEY_1, "1" },
            {irr::EKEY_CODE::KEY_KEY_2, "2" },
            {irr::EKEY_CODE::KEY_KEY_3, "3" },
            {irr::EKEY_CODE::KEY_KEY_4, "4" },
            {irr::EKEY_CODE::KEY_KEY_5, "5" },
            {irr::EKEY_CODE::KEY_KEY_6, "6" },
            {irr::EKEY_CODE::KEY_KEY_7, "7" },
            {irr::EKEY_CODE::KEY_KEY_8, "8" },
            {irr::EKEY_CODE::KEY_KEY_9, "9" },
            {irr::EKEY_CODE::KEY_KEY_A, "A" },
            {irr::EKEY_CODE::KEY_KEY_B, "B" },
            {irr::EKEY_CODE::KEY_KEY_C, "C" },
            {irr::EKEY_CODE::KEY_KEY_D, "D" },
            {irr::EKEY_CODE::KEY_KEY_E, "E" },
            {irr::EKEY_CODE::KEY_KEY_F, "F" },
            {irr::EKEY_CODE::KEY_KEY_G, "G" },
            {irr::EKEY_CODE::KEY_KEY_H, "H" },
            {irr::EKEY_CODE::KEY_KEY_I, "I" },
            {irr::EKEY_CODE::KEY_KEY_J, "J" },
            {irr::EKEY_CODE::KEY_KEY_K, "K" },
            {irr::EKEY_CODE::KEY_KEY_L, "L" },
            {irr::EKEY_CODE::KEY_KEY_M, "M" },
            {irr::EKEY_CODE::KEY_KEY_N, "N" },
            {irr::EKEY_CODE::KEY_KEY_O, "O" },
            {irr::EKEY_CODE::KEY_KEY_P, "P" },
            {irr::EKEY_CODE::KEY_KEY_Q, "Q" },
            {irr::EKEY_CODE::KEY_KEY_R, "R" },
            {irr::EKEY_CODE::KEY_KEY_S, "S" },
            {irr::EKEY_CODE::KEY_KEY_T, "T" },
            {irr::EKEY_CODE::KEY_KEY_U, "U" },
            {irr::EKEY_CODE::KEY_KEY_V, "V" },
            {irr::EKEY_CODE::KEY_KEY_W, "W" },
            {irr::EKEY_CODE::KEY_KEY_X, "X" },
            {irr::EKEY_CODE::KEY_KEY_Y, "Y" },
            {irr::EKEY_CODE::KEY_KEY_Z, "Z" },
            {irr::EKEY_CODE::KEY_LWIN, "KEY_LWIN" },
            {irr::EKEY_CODE::KEY_RWIN, "KEY_RWIN" },
            {irr::EKEY_CODE::KEY_APPS, "KEY_APPS" },
            {irr::EKEY_CODE::KEY_SLEEP, "KEY_SLEEP" },
            {irr::EKEY_CODE::KEY_NUMPAD0, "KEY_NUMPAD0" },
            {irr::EKEY_CODE::KEY_NUMPAD1, "KEY_NUMPAD1" },
            {irr::EKEY_CODE::KEY_NUMPAD2, "KEY_NUMPAD2" },
            {irr::EKEY_CODE::KEY_NUMPAD3, "KEY_NUMPAD3" },
            {irr::EKEY_CODE::KEY_NUMPAD4, "KEY_NUMPAD4" },
            {irr::EKEY_CODE::KEY_NUMPAD5, "KEY_NUMPAD5" },
            {irr::EKEY_CODE::KEY_NUMPAD6, "KEY_NUMPAD6" },
            {irr::EKEY_CODE::KEY_NUMPAD7, "KEY_NUMPAD7" },
            {irr::EKEY_CODE::KEY_NUMPAD8, "KEY_NUMPAD8" },
            {irr::EKEY_CODE::KEY_NUMPAD9, "KEY_NUMPAD9" },
            {irr::EKEY_CODE::KEY_MULTIPLY, "KEY_MULTIPLY" },
            {irr::EKEY_CODE::KEY_ADD, "KEY_ADD" },
            {irr::EKEY_CODE::KEY_SEPARATOR, "KEY_SEPARATOR" },
            {irr::EKEY_CODE::KEY_SUBTRACT, "KEY_SUBTRACT" },
            {irr::EKEY_CODE::KEY_DECIMAL, "KEY_DECIMAL" },
            {irr::EKEY_CODE::KEY_DIVIDE, "KEY_DIVIDE" },
            {irr::EKEY_CODE::KEY_F1, "KEY_F1" },
            {irr::EKEY_CODE::KEY_F2, "KEY_F2" },
            {irr::EKEY_CODE::KEY_F3, "KEY_F3" },
            {irr::EKEY_CODE::KEY_F4, "KEY_F4" },
            {irr::EKEY_CODE::KEY_F5, "KEY_F5" },
            {irr::EKEY_CODE::KEY_F6, "KEY_F6" },
            {irr::EKEY_CODE::KEY_F7, "KEY_F7" },
            {irr::EKEY_CODE::KEY_F8, "KEY_F8" },
            {irr::EKEY_CODE::KEY_F9, "KEY_F9" },
            {irr::EKEY_CODE::KEY_F10, "KEY_F10" },
            {irr::EKEY_CODE::KEY_F11, "KEY_F11" },
            {irr::EKEY_CODE::KEY_F12, "KEY_F12" },
            {irr::EKEY_CODE::KEY_F13, "KEY_F13" },
            {irr::EKEY_CODE::KEY_F14, "KEY_F14" },
            {irr::EKEY_CODE::KEY_F15, "KEY_F15" },
            {irr::EKEY_CODE::KEY_F16, "KEY_F16" },
            {irr::EKEY_CODE::KEY_F17, "KEY_F17" },
            {irr::EKEY_CODE::KEY_F18, "KEY_F18" },
            {irr::EKEY_CODE::KEY_F19, "KEY_F19" },
            {irr::EKEY_CODE::KEY_F20, "KEY_F20" },
            {irr::EKEY_CODE::KEY_F21, "KEY_F21" },
            {irr::EKEY_CODE::KEY_F22, "KEY_F22" },
            {irr::EKEY_CODE::KEY_F23, "KEY_F23" },
            {irr::EKEY_CODE::KEY_F24, "KEY_F24" },
            {irr::EKEY_CODE::KEY_NUMLOCK, "KEY_NUMLOCK" },
            {irr::EKEY_CODE::KEY_SCROLL, "KEY_SCROLL" },
            {irr::EKEY_CODE::KEY_LSHIFT, "KEY_LSHIFT" },
            {irr::EKEY_CODE::KEY_RSHIFT, "KEY_RSHIFT" },
            {irr::EKEY_CODE::KEY_LCONTROL, "KEY_LCONTROL" },
            {irr::EKEY_CODE::KEY_RCONTROL, "KEY_RCONTROL" },
            {irr::EKEY_CODE::KEY_LMENU, "KEY_LMENU" },
            {irr::EKEY_CODE::KEY_RMENU, "KEY_RMENU" },
            {irr::EKEY_CODE::KEY_OEM_1, "KEY_OEM_1" },
            {irr::EKEY_CODE::KEY_PLUS, "+/=" },
            {irr::EKEY_CODE::KEY_COMMA, "KEY_COMMA" },
            {irr::EKEY_CODE::KEY_MINUS, "-" },
            {irr::EKEY_CODE::KEY_PERIOD, "KEY_PERIOD" },
            {irr::EKEY_CODE::KEY_OEM_2, "KEY_OEM_2" },
            {irr::EKEY_CODE::KEY_OEM_3, "KEY_OEM_3" },
            {irr::EKEY_CODE::KEY_OEM_4, "KEY_OEM_4" },
            {irr::EKEY_CODE::KEY_OEM_5, "KEY_OEM_5" },
            {irr::EKEY_CODE::KEY_OEM_6, "KEY_OEM_6" },
            {irr::EKEY_CODE::KEY_OEM_7, "KEY_OEM_7" },
            {irr::EKEY_CODE::KEY_OEM_8, "KEY_OEM_8" },
            {irr::EKEY_CODE::KEY_OEM_AX, "KEY_OEM_AX" },
            {irr::EKEY_CODE::KEY_OEM_102, "KEY_OEM_102" },
            {irr::EKEY_CODE::KEY_ATTN, "KEY_ATTN" },
            {irr::EKEY_CODE::KEY_CRSEL, "KEY_CRSEL" },
            {irr::EKEY_CODE::KEY_EXSEL, "KEY_EXSEL" },
            {irr::EKEY_CODE::KEY_EREOF, "KEY_EREOF" },
            {irr::EKEY_CODE::KEY_PLAY, "KEY_PLAY" },
            {irr::EKEY_CODE::KEY_ZOOM, "KEY_ZOOM" },
            {irr::EKEY_CODE::KEY_PA1, "KEY_PA1" },
            {irr::EKEY_CODE::KEY_OEM_CLEAR, "KEY_OEM_CLEAR" },
//X11 keycode
            {static_cast<irr::EKEY_CODE>(10), "&"},
            {static_cast<irr::EKEY_CODE>(11), "é"},
            {static_cast<irr::EKEY_CODE>(12), "\""},
            {static_cast<irr::EKEY_CODE>(14), "("},
            {static_cast<irr::EKEY_CODE>(16), "è"},
            {static_cast<irr::EKEY_CODE>(18), "ç"},
            {static_cast<irr::EKEY_CODE>(19), "à"},
            {static_cast<irr::EKEY_CODE>(20), ")"},
            {static_cast<irr::EKEY_CODE>(34), "^"},
            {static_cast<irr::EKEY_CODE>(35), "$"},
            {static_cast<irr::EKEY_CODE>(48), "ù"},
            {static_cast<irr::EKEY_CODE>(49), "Œ"},
            {static_cast<irr::EKEY_CODE>(51), "*"},
            {static_cast<irr::EKEY_CODE>(60), ":"},
            {static_cast<irr::EKEY_CODE>(61), "!"},
            };

            std::map<const ControllerKey, std::string> controller_map = {
		{A1,"A1"},
    		{B1,"B1"},
    		{X1,"X1"},
    		{Y1,"Y1"},
    		{LB1,"LB1"},
    		{RB1,"RB1"},
    		{SELECT1,"SELECT1"},
    		{START1,"START1"},
    		{HOME1,"HOME1"},
    		{LS1,"LS1"},
    		{RS1,"RS1"},
    		{UD1,"UD1"},
    		{RD1,"RD1"},
    		{DD1,"DD1"},
    		{LD1,"LD1"},
    		{LT1,"LT1"},
    		{RT1,"RT1"},
    		{A2,"A2"},
    		{B2,"B2"},
    		{X2,"X2"},
    		{Y2,"Y2"},
    		{LB2,"LB2"},
    		{RB2,"RB2"},
    		{SELECT2,"SELECT2"},
    		{START2,"START2"},
    		{HOME2,"HOME2"},
    		{LS2,"LS2"},
    		{RS2,"RS2"},
    		{UD2,"UD2"},
    		{RD2,"RD2"},
    		{DD2,"DD2"},
    		{LD2,"LD2"},
    		{LT2,"LT2"},
    		{RT2,"RT2"},
    		{A3,"A3"},
    		{B3,"B3"},
    		{X3,"X3"},
    		{Y3,"Y3"},
    		{LB3,"LB3"},
    		{RB3,"RB3"},
    		{SELECT3,"SELECT3"},
    		{START3,"START3"},
    		{HOME3,"HOME3"},
    		{LS3,"LS3"},
    		{RS3,"RS3"},
    		{UD3,"UD3"},
    		{RD3,"RD3"},
    		{DD3,"DD3"},
    		{LD3,"LD3"},
    		{LT3,"LT3"},
    		{RT3,"RT3"},
    		{A4,"A4"},
    		{B4,"B4"},
    		{X4,"X4"},
    		{Y4,"Y4"},
    		{LB4,"LB4"},
    		{RB4,"RB4"},
    		{SELECT4,"SELECT4"},
    		{START4,"START4"},
    		{HOME4,"HOME4"},
    		{LS4,"LS4"},
    		{RS4,"RS4"},
    		{UD4,"UD4"},
    		{RD4,"RD4"},
    		{DD4,"DD4"},
    		{LD4,"LD4"},
    		{LT4,"LT4"},
    		{RT4,"RT4"},
	    };

            InterfaceKeyBinding(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
            irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId,
            std::map<int, std::pair<std::string, KeyHandler>> &keys, MusicPlayer &musicPlayer);
            ~InterfaceKeyBinding();

            void print(irr::EKEY_CODE key) const;

            void create();
            bool manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene);
            bool update(void);
	int joystick(const irr::SEvent& event);


        private:
            std::map<int, std::pair<std::string, KeyHandler>> &_keys;
            std::map<const irr::EKEY_CODE, std::string *> _key_map;
            int _keyPerPlayer;
            int _idWaitingBind;
    };

#endif