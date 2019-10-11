/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/AInterfaceObj.hpp
*/

#ifndef AINTERFACE_OBJ
#define AINTERFACE_OBJ

    #include "IInterfaceObj.hpp"

    #define WINDOW_WIDTH    (float)1920.0
    #define WINDOW_HEIGHT   (float)1080.0

    class AInterfaceObj: public IInterfaceObj
    {
        public:
            AInterfaceObj(irr::gui::IGUIEnvironment* guiScene, irr::s32 id = -1, bool display = true);
            ~AInterfaceObj();

            virtual void reset() = 0;
            virtual void setVisible(bool) = 0;

            int getId() const;
            int getType() const;

            void display(bool);

        protected:
            int cptWidth(int percentage);
            int cptHeight(int percentage);
            void realPosFromPercentage(irr::core::rect<irr::s32> &rect);
            irr::core::rect<irr::s32> posFromPercentage(irr::core::rect<irr::f32> rect,
            const irr::core::dimension2du& screenSize);
            irr::core::rect<irr::s32> convertRectfToRecti(irr::core::rect<irr::f32> rect);

            irr::gui::IGUIEnvironment* _guiScene;
            irr::s32 _id;
            int _type;
            bool _display;
    };

#endif