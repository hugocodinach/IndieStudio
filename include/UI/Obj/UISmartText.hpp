/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/UISmartText.hpp
*/

#ifndef UI_SMART_TEXT
#define UI_SMART_TEXT

    #include <string>
    #include <vector>
    #include <algorithm>

    #include "AInterfaceObj.hpp"
    #include "UIImage.hpp"

    class UISmartText: public AInterfaceObj
    {
        public:
            UISmartText(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene,
            irr::s32 id, std::string text, irr::core::position2df pos, float fontSize,
            bool userPercentage = true, bool clickable = false);
            ~UISmartText();

            void reset() {};

            void setText(std::string text);
            void setFont(int size);
            void setPos(irr::core::position2di &pos);
            void setVisible(bool);
            void setHover(void);
            void setIdle(void);
            void setClicked(void);

            std::string getText(void) const;
            irr::core::position2di getPos(void) const;

            void setParent(irr::gui::IGUIElement *);

        private:

            void updateText(void);
            void createCollisionBox(void);
            irr::video::IVideoDriver *_driver;
            std::string _text;
            irr::core::position2di _pos;
            int _fontSize;
            std::vector<std::pair<int, UIImage *>> _images;
            bool _clickable;
            irr::core::rect<irr::s32> _rect;
            irr::gui::IGUIButton *_collisionBox;
    };

#endif