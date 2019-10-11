/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/UIEditBox.hpp
*/

#ifndef UI_EDIT_BOX
#define UI_EDIT_BOX

    #include "AInterfaceObj.hpp"
    #include "UIImage.hpp"
    #include "UISmartText.hpp"

    class UIEditBox: public AInterfaceObj
    {
        public:
            UIEditBox(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene,
            irr::s32 id, const irr::io::path &backgroundTextPath, std::string text,
            irr::core::rect<irr::f32> rect, irr::core::position2df textPos, float textSize,
            int maxCharacter, bool usePercentage = true);
            ~UIEditBox();

            void reset() {};
            void setText(std::string &text);
            void setVisible(bool);
            void addCharacter(char c);
            void removeCharacter(void);
            void update(void);
            void setClicked(void);
            void setUnclicked(void);
            bool isClicked(void) const;
            std::string getText(void) const;

        private:
            irr::video::IVideoDriver *_driver;
            UISmartText *_input;
            UIImage *_background;
            irr::core::rect<irr::f32> _rect;
            irr::video::ITexture *_texture;
            std::string _defaultText;
            irr::core::position2df _textPos;
            std::string _inputText;
            int _textSize;
            bool _border;
            bool _wordWrap;
            bool _fillBackground;
            bool _clicked;
            int _clock;
            int _clockTimeSet;
            int _maxCharacter;
    };

#endif