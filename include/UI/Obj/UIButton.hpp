/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/UIButton.hpp
*/

#ifndef UI_BUTTON
#define UI_BUTTON

    #include "AInterfaceObj.hpp"
    #include "UISmartText.hpp"
    #include "musicPlayer.hpp"

    enum BUTTON_STATU {
        IDLE = 0,
        HOVER = 1,
        CLICKED = 2,
    };

    enum BUTTON_TYPE {
        BASIC,
        SPRITED,
        TEXTED,
    };

    class UIButton: public AInterfaceObj
    {
        public:
            UIButton(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene,
                irr::s32 id, irr::core::rect<irr::f32> rect, const wchar_t *text, const wchar_t *tooltipText,
                MusicPlayer &musicPlayer, bool userPercentage = true);
            UIButton(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene,
            irr::s32 id, irr::core::rect<irr::f32> rect, irr::core::rect<irr::s32> textureRect,
            const irr::io::path &sbName, const irr::io::path &idleTexturePath,
            const irr::io::path &overTexturePath, const irr::io::path &clickedTexturePath,
            MusicPlayer &musicPlayer, bool userPercentage = true);
            UIButton(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene,
            irr::s32 id, irr::core::rect<irr::f32> rect, irr::core::rect<irr::s32> textureRect,
            const irr::io::path &texturePath, std::string text, irr::core::position2df pos,
            float fontSize, MusicPlayer &musicPlayer, bool userPercentage = true);
            ~UIButton();

            void reset() {};
            bool setButtonClicked(void);
            bool setOver(void);
            bool setIdle(void);
            bool setClicked(void);
            void setVisible(bool);
            bool setLabelText(std::string &text);

        private:

            void addSmartTextChild(UISmartText *text);

            int _type;
            const wchar_t *_text;
            const wchar_t *_tooltipText;
            irr::gui::IGUIButton *_buttonObj;
            irr::core::rect<irr::s32> _textureRect;
            irr::core::rect<irr::s32> _rect;
            irr::video::IVideoDriver *_driver;
            const irr::io::path _sbName;
            irr::gui::IGUISpriteBank *_sb;
            irr::video::ITexture *_texture_idle;
            irr::video::ITexture *_texture_over;
            irr::video::ITexture *_texture_clicked;
            UISmartText *_labelText;
            UIImage *_imageText;
            MusicPlayer &_musicPlayer;
    };

#endif