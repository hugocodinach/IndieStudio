/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/UISmartListBox.cpp
*/

#include "UISmartListBox.hpp"

UISmartListBox::UISmartListBox(irr::video::IVideoDriver *driver,
irr::gui::IGUIEnvironment* guiScene, irr::core::rect<irr::f32> rect, irr::s32 id,
std::vector<std::string> array, float fontSize, int maxRow, bool userPercentage):
AInterfaceObj(guiScene, id), _driver(driver),
_array(array), _fontSize(fontSize), _maxRow(maxRow)
{
    _actualRow = 0;
    _prevStartIdx = 0;
    _lastClicked = -1;
    _lastHovered = -1;
    _lastUsedId = _id;
    if (userPercentage == true) {
        _fontSize = _fontSize * static_cast<float>(_driver->getScreenSize().Width) / 100;
        _rect = posFromPercentage(rect, _driver->getScreenSize());
    } else {
        _rect = convertRectfToRecti(rect);
    }
    loadArray();
    updateArray(0);
}

UISmartListBox::~UISmartListBox()
{
    
}

void UISmartListBox::loadArray(void)
{
    for (int i = 0, k = 0; i < _array.size(); i += 1, k += 1) {
        if (k >= _maxRow)
            k = 0;
        _arrayObj.push_back(std::make_pair(_lastUsedId,
        new UISmartText(_driver, _guiScene, _lastUsedId, _array[i],
        irr::core::position2df(_rect.UpperLeftCorner.X,
        _rect.UpperLeftCorner.Y + k * _fontSize + k * 10),
        _fontSize, false, false)));
        _lastUsedId += 1;
    }
}

void UISmartListBox::updateArray(int idx_to_start)
{
    int idx = idx_to_start;
    int k = 0;

    _lastUsedId = _id;
    if (idx_to_start < 0)
        return;
    for (int i = 0; i < _arrayObj.size(); i += 1)
        _arrayObj[i].second->setVisible(false);
    for (; idx < _arrayObj.size() && idx < idx_to_start + _maxRow; idx += 1)
        _arrayObj[idx].second->setVisible(true);
    _actualRow = idx;
}

void UISmartListBox::showNextPage()
{
    int next_begin_row = _actualRow;

    if (_prevStartIdx != next_begin_row && next_begin_row < _array.size()) {
        _prevStartIdx = next_begin_row;
        updateArray(next_begin_row);
    }
}

void UISmartListBox::showPrevPage()
{
    int next_begin_row = (_actualRow - 2 * _maxRow) < 0 ? 0 : (_actualRow - 2 * _maxRow);

    if (_prevStartIdx != next_begin_row && next_begin_row < _array.size()) {
        _prevStartIdx = next_begin_row;
        updateArray(next_begin_row);
    }
}

bool UISmartListBox::setRowHover(int rowSelected)
{
    if (rowSelected < 0 || rowSelected >= _arrayObj.size() || _lastHovered == rowSelected) {
        return false;
    }
    if (_lastHovered >= 0 && _lastHovered != _lastClicked)
        _arrayObj[_lastHovered].second->setIdle();
    else if (_lastHovered >= 0 && _lastHovered == _lastClicked)
        _arrayObj[_lastHovered].second->setClicked();
    _lastHovered = rowSelected;
    _arrayObj[rowSelected].second->setHover();
    return true;
}

bool UISmartListBox::setRowClicked(int rowSelected)
{
    if (rowSelected < 0 || rowSelected >= _arrayObj.size() || _lastHovered != rowSelected)
        return false;
    if (_lastClicked >= 0)
        _arrayObj[_lastClicked].second->setIdle();
    _lastClicked = rowSelected;
    _arrayObj[rowSelected].second->setClicked();
    return true;
}

void UISmartListBox::unhover(void)
{
    // std::cout << "UISmartListBox::unhover" << std::endl;

    if (_lastHovered >= 0 && _lastHovered != _lastClicked) {
        _arrayObj[_lastHovered].second->setIdle();
        _lastHovered = -1;
    }
}


void UISmartListBox::setVisible(bool visible)
{
    if (visible == false) {
        for (int i = 0; i < _arrayObj.size(); i += 1)
            _arrayObj[i].second->setVisible(visible);
    } else {
    for (int idx = _prevStartIdx; idx < _arrayObj.size() && idx < _prevStartIdx + _maxRow; idx += 1)
        _arrayObj[idx].second->setVisible(true);
    }
}

void UISmartListBox::clearArrayObj(void)
{
    for (int i = 0; i < _arrayObj.size(); i += 1)
        delete _arrayObj[i].second;
    _arrayObj.clear();
}

void UISmartListBox::setArray(std::vector<std::string> array)
{
    _array = array;
    clearArrayObj();
    loadArray();
    updateArray(0);
}

std::vector<std::string> UISmartListBox::getArray()
{
    return _array;
}

int UISmartListBox::getRowSelected(void) const
{
    return (_lastClicked);
}

std::string UISmartListBox::getRowSelectedText(void) const
{
    if (_lastClicked < 0 || _lastClicked >= _array.size())
        return ("");
    return (_arrayObj[_lastClicked].second->getText());
}
