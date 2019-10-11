/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/UILateralText.hpp
*/

#ifndef UI_LATERAL_TEXT
#define UI_LATERAL_TEXT

    #include <vector>

    #include "AInterfaceObj.hpp"
    #include "UIButton.hpp"
    #include "UISmartText.hpp"

    class UILateralText: public AInterfaceObj
    {
        public:
            UILateralText(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene, int id,
            IInterfaceObj *leftButton, IInterfaceObj *rightButton, std::vector<std::string> texts,
            irr::core::position2df pos, float fontSize, bool userPercentage = true);
            ~UILateralText();

            void reset() {};

            void nextTextLeft();
            void nextTextRight();
            void setVisible(bool);

            int getIdx(void) const;
            bool setIdx(int idx);

        private:
            irr::video::IVideoDriver *_driver;
            UIButton *_leftButton;
            UIButton *_rightButton;
            UISmartText *_textZone;
            std::vector<std::string> _texts;
            irr::core::position2df _pos;
            float _fontSize;
            int _actualIdx;
    };

#endif