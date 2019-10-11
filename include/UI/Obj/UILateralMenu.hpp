/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/UILateralMenu.hpp
*/

#ifndef UI_LATERAL_MENU
#define UI_LATERAL_MENU

    #include <vector>

    #include "AInterfaceObj.hpp"
    #include "UIButton.hpp"
    #include "UIImage.hpp"

    class UILateralMenu: public AInterfaceObj
    {
        public:
            UILateralMenu(irr::video::IVideoDriver *driver, irr::gui::IGUIEnvironment* guiScene,
            irr::s32 id, IInterfaceObj *leftButton, IInterfaceObj *rightButton, IInterfaceObj *image,
            std::vector<irr::io::path> texturesPath, bool userPercentage = true);
            ~UILateralMenu();

            void reset() {};

            void nextTextureLeft();
            void nextTextureRight();
            void setVisible(bool);
            bool setIdx(int idx);

            int getActualTextureNb(void) const;

        private:
            irr::video::IVideoDriver *_driver;
            UIButton *_leftButton;
            UIButton *_rightButton;
            UIImage *_image;
            std::vector<irr::video::ITexture *> _textures;
            int _actualTexture;
    };

#endif