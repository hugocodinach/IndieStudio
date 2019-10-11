/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/UIImage.hpp
*/

#ifndef UI_IMAGE
#define UI_IMAGE

    #include <string>
    #include <iostream>

    #include "AInterfaceObj.hpp"

    class UIImage: public AInterfaceObj
    {
        public:
            UIImage(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene, irr::s32 id,
            irr::core::rect<irr::f32> rect, irr::video::ITexture *texture, bool usePercentage = true,
            bool setScale = true, irr::gui::IGUIElement *parent=0, bool useAlphaChannel=true,
            const wchar_t *text=0);
            ~UIImage();

            void reset() {};
            void setColor(irr::video::SColor color);
            bool setTexture(irr::video::ITexture *texture);
            void setVisible(bool);
            irr::gui::IGUIElement *getIrrElement(void) const;

        private:
            const wchar_t *_text;
            irr::gui::IGUIElement *_parent;
            bool _useAlphaChannel;
            irr::gui::IGUIImage *_imageObj;
            irr::core::rect<irr::s32> _rect;
            irr::video::ITexture *_texture;
            bool _setScale;
            irr::video::IVideoDriver *_driver;
    };

#endif