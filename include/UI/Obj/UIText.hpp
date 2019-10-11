/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/UIText.hpp
*/

#ifndef UI_TEXT
#define UI_TEXT

    #include "AInterfaceObj.hpp"

    class UIText: public AInterfaceObj
    {
        public:
            UIText(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene, wchar_t *text,
            irr::core::rect<irr::f32> rect, irr::s32 id, const irr::io::path &fontPath,
            bool userPercentage = true, bool display = true, bool border = false,
            bool wordWrap = false, bool fillBackground = false, irr::gui::IGUIElement *parent = 0);
            ~UIText();

            void reset() {};
            void setText(wchar_t *text);
            void setVisible(bool);

        private:
            irr::gui::IGUIStaticText *_textObj;
            irr::gui::IGUIFont *_font;
            wchar_t *_text;
            irr::core::rect<irr::s32> _rect;
            bool _border;
            bool _wordWrap;
            bool _fillBackground;
            irr::gui::IGUIElement *_parent;
            irr::video::IVideoDriver *_driver;
    };

#endif