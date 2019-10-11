/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/UISmartListBox.hpp
*/

#ifndef UI_SMART_LIST_BOX
#define UI_SMART_LIST_BOX

    #include <string>
    #include <vector>
    #include <iostream>

    #include "AInterfaceObj.hpp"
    #include "UISmartText.hpp"

    class UISmartListBox: public AInterfaceObj
    {
        public:
            UISmartListBox(irr::video::IVideoDriver *driver,
            irr::gui::IGUIEnvironment* guiScene, irr::core::rect<irr::f32> rect,
            irr::s32 id, std::vector<std::string> _array, float fontSize,
            int maxRow, bool userPercentage = true);
            ~UISmartListBox();

            void reset() {};

            void showNextPage();
            void showPrevPage();
            void setVisible(bool);

            bool setRowHover(int rowSelected);
            bool setRowClicked(int rowSelected);
            void setArray(std::vector<std::string> array);
			std::vector<std::string> getArray();
            void clearArrayObj(void);
            void unhover(void);

            int getRowSelected(void) const;
            std::string getRowSelectedText(void) const;

            bool OnEvent(const irr::SEvent &event);

        private:

            void updateArray(int idx_to_start);
            void loadArray(void);

            irr::video::IVideoDriver *_driver;
            irr::s32 _idButtonPrev;
            irr::s32 _idButtonNext;
            irr::gui::IGUIButton *_prevButton;
            irr::gui::IGUIButton *_nextButton;
            std::vector<std::string> _array;
            std::vector<std::pair<int, UISmartText *>> _arrayObj;
            float _fontSize;
            int _maxRow;
            int _actualRow;
            int _prevStartIdx;
            irr::core::rect<irr::s32> _rect;
            int _rowSelected;
            int _lastUsedId;
            int _lastHovered;
            int _lastClicked;
    };

#endif