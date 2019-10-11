/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/BlockDestruct.hpp
*/

#ifndef BLOCKDESTRUCT_HPP_
#define BLOCKDESTRUCT_HPP_

#include <string>
#include <iostream>
#include "GameObj.hpp"
#include "ExplosionParticles.hpp"

typedef struct innerBonus_s {
	int x;
	int y;
	int type;
} innerBonus_t;

class BlockDestruct : public GameObj
{
    public:
        BlockDestruct(irr::scene::ISceneManager* smgr, irr::core::vector3df pos, int x, int y, std::string str);
        BlockDestruct(irr::scene::ISceneManager* smgr, irr::core::vector3df pos, int x, int y, int b);
        ~BlockDestruct();

        bool BlockIsDestruct(int y, int x);
        void pure();

        int _x;
        int _y;

    private:
        irr::scene::IMeshSceneNode* _block;
        ExplosionParticule* _explo;
};

#endif