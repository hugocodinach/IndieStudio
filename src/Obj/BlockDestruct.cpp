/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/Obj/BlockDestruct.cpp
*/

#include "BlockDestruct.hpp"

BlockDestruct::BlockDestruct(irr::scene::ISceneManager* smgr, irr::core::vector3df pos, int x, int y, std::string str)
{
    _block = smgr->addCubeSceneNode();
    _block->setPosition({pos.X,pos.Y + 2, pos.Z});
    _block->getMaterial(0).NormalizeNormals = true;
    _block->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    if (str == "./ressources/feu.jpg") {
        _block->setMaterialTexture(0, smgr->getVideoDriver()->getTexture(str.c_str()));
        _explo = new ExplosionParticule(smgr, pos, _block);
    } else {
        _block->setMaterialTexture(0, smgr->getVideoDriver()->getTexture(str.c_str()));
    }
    _block->setScale(irr::core::vector3df(0.3));
    _x = x;
    _y = y;
}

BlockDestruct::BlockDestruct(irr::scene::ISceneManager* smgr, irr::core::vector3df pos, int x, int y, int b)
{
    _block = smgr->addMeshSceneNode(smgr->getMesh("./ressources/models/Walls/haystack.3ds"),0);
    _block->setPosition({pos.X,pos.Y + 2, pos.Z});
    _block->getMaterial(0).NormalizeNormals = true;
    _block->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _x = x;
    _y = y;
}

BlockDestruct::~BlockDestruct()
{
    if (_block != nullptr)
        _block->remove();
}

bool BlockDestruct::BlockIsDestruct(int y, int x)
{
    if (_x == x && _y == y) {
        _block->remove();
        _block = nullptr;
        return true;
    }
    return false;
}

void BlockDestruct::pure()
{
}