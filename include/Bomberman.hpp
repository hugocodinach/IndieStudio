/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/Bomberman.hpp
*/

#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

#include <string>
#include <iostream>
#include <mutex>
#include "AActor.hpp"
#include "WallPass.hpp"
#include "Status.hpp"
#include "PersoParticles.hpp"

enum ParticlesOrder {
    SPELL,
};

enum MODELS {
    PENGUIN,
    PIG,
    CAT,
    CHICKEN,
    HOOTY,
    LAMA,
    SHEEP,
    SNAKE,
    SQUIRREL
};

enum TYPE {
    EAU,
    FEU,
    AIR
};

#define MODELS_SIZE 9

#define WIND_SPELL_PS {\
    irr::core::aabbox3d<irr::f32>(-5,0,-5,5,1,5),\
    irr::core::vector3df(0.0f,0.0f,0.0f),\
    {160, 200},\
    irr::video::SColor(0,0,0,0),\
    irr::video::SColor(0,100,221,23),\
    100,\
    300,\
    0,\
    irr::core::dimension2df(0.5,0.5),\
    irr::core::dimension2df(0.5,0.5),\
    irr::core::vector3df(0, 0, 0),\
	true\
}\

#define FIRE_SPELL_PS {\
    irr::core::aabbox3d<irr::f32>(-5,0,-5,5,1,5),\
    irr::core::vector3df(0.0f,0.0f,0.0f),\
    {160, 200},\
    irr::video::SColor(0,0,0,0),\
    irr::video::SColor(0,198,40,40),\
    100,\
    300,\
    0,\
    irr::core::dimension2df(0.5,0.5),\
    irr::core::dimension2df(0.5,0.5),\
    irr::core::vector3df(0, 0, 0),\
	true\
}\

#define WATER_SPELL_PS {\
    irr::core::aabbox3d<irr::f32>(-5,0,-5,5,1,5),\
    irr::core::vector3df(0.0f,0.0f,0.0f),\
    {160, 200},\
    irr::video::SColor(0,0,0,0),\
    irr::video::SColor(0,33,150,243),\
    100,\
    300,\
    0,\
    irr::core::dimension2df(0.5,0.5),\
    irr::core::dimension2df(0.5,0.5),\
    irr::core::vector3df(0, 0, 0),\
	true\
}\

#define IS_NOT_A_CALLBACK _actionsToDo.front().second != static_cast<IActorMethodPtr>(&AActor::firstAction) &&	\
		    _actionsToDo.front().second != static_cast<IActorMethodPtr>(&AActor::secondAction) &&	\
		    _actionsToDo.front().second != static_cast<IActorMethodPtr>(&AActor::thirdAction) &&	\
		    _actionsToDo.front().second != static_cast<IActorMethodPtr>(&AActor::forthAction) &&	\
		    _actionsToDo.front().second != static_cast<IActorMethodPtr>(&AActor::fifthAction) &&	\
		    _actionsToDo.front().second != static_cast<IActorMethodPtr>(&AActor::sixthAction)

typedef struct models_s {
            MODELS idx;
            TYPE type;
            std::string file;
            int range;
            int bombNbr;
            int mouseSpeed;
} models_t;

const std::vector<models_t> modelsList =
    {{PENGUIN, EAU, "./ressources/models/Penguin/penguin.3ds", 3, 1, 4 - 1},
    {PIG, FEU, "./ressources/models/Pig/pig.3ds", 1, 4, 2 - 1},
    {CAT, EAU, "./ressources/models/Cat/cat.3ds", 4, 1, 2 - 1},
    {CHICKEN, AIR, "./ressources/models/Chicken/Chicken1.3ds", 2, 2, 4 - 1},
    {HOOTY, AIR, "./ressources/models/Hooty/hooty.3ds", 1, 1, 8 - 1},
    {LAMA, FEU, "./ressources/models/Lama/lama.3ds", 2, 3, 2 - 1},
    {SHEEP, FEU, "./ressources/models/Sheep/sheep.3ds", 2, 2, 3 - 1},
    {SNAKE, EAU, "./ressources/models/Snake/snake.3ds", 2, 2, 3 - 1},
    {SQUIRREL, AIR, "./ressources/models/Squirrel/squirrel.3ds", 1, 2, 6 - 1}
};

class Bomberman : public AActor
{
    public:
        Bomberman(irr::scene::ISceneManager* smgr, irr::core::vector3df pos, int x, int y, int id, std::vector<irr::scene::IAnimatedMesh *> vect_mesh, int characterIDX);
        ~Bomberman();

        void setCoord(coord_t coord);
        void pure(void);
        void play(void);

        void firstAction(void) override;
        void secondAction(void) override;
        void thirdAction(void) override;
        void forthAction(void) override;
        void fifthAction(void) final;
        void sixthAction(void) final;

        void firstActionResolve(void) override;
        void secondActionResolve(void) override;
        void thirdActionResolve(void) override;
        void forthActionResolve(void) override;
        void sixthActionResolve(void) final;

        void waterSpellResolve(void);
        void fireSpellResolve(void);
        void windSpellResolve(void);

        bool getWallPass(void) final;
        void updateWallPass(void) final;
        void deleteGameObj();
        void stun(void);
        status_e getStatus(void);
        void updateStatus(void);
        void applyBonus(Bonus *bonus) final;
        direction getDirection(void);
        int getRange();
        std::chrono::system_clock::time_point &getLastRecord(void);
        void resetLastRecord();
        float &cd();
        float &cd(float neo);
        int getMaxBomb();
        int getBombs();
        void setBombs(int bombs);
        TYPE getType(void);
        int getCharacterIDX();
        void setRange(int);
        void setActualBombs(int);
        void setMaxBombs(int);
        void setStatus(int);
		bool &getWait();

    private:
        irr::scene::IAnimatedMeshSceneNode* _bomberman;
        float _cd = 0;
        std::chrono::system_clock::time_point _lastRecord;
        std::vector<std::vector<int>> _map;
        std::mutex _mut;
        Status _status;
        int _x;
        int _y;
        int _bombs;
        int _maxBomb = 3;
        int _range = 1;

		std::chrono::time_point<std::chrono::system_clock> _start;
		std::chrono::time_point<std::chrono::system_clock> _end;

        TYPE _type;
        WallPass _wallPass;
        PersoParticule* _particul;
        direction _direction;
        std::vector<irr::scene::IAnimatedMesh *> _vect_mesh;
        int _characterIDX;
		bool _wait = false;
};

#endif