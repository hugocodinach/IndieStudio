/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/AActor.hpp
*/


#ifndef AACTOR_HPP_
#define AACTOR_HPP_

#include <mutex>
#include <string>
#include <iostream>
#include <irr/irrlicht.h>
#include <queue>
#include "Map.hpp"
#include "Key.hpp"
#include "Particle.hpp"
#include "IActor.hpp"

class AActor: public IActor
{
    public:
        AActor();

        ~AActor();

        virtual void pure(void) = 0;

        void firstAction(void) override;
        void secondAction(void) override;
        void thirdAction(void) override;
        void forthAction(void) override;
        void fifthAction(void) override;
        void sixthAction(void) override;
        void firstActionResolve(void) override;
        void secondActionResolve(void) override;
        void thirdActionResolve(void) override;
        void forthActionResolve(void) override;
        void fifthActionResolve(void) override;
        void sixthActionResolve(void) override;
        void applyBonus(Bonus *bonus) override;
        void pushAction(handleMethodPtr PTR, IActorMethodPtr ptr) final;
        std::queue< std::pair<handleMethodPtr, IActorMethodPtr> >& getActionsToDo() final;
        std::vector< std::pair<KeyHandler, IActorMethodPtr> > getBinds() final;
        coord_t getCoord();
        void setCoord(coord_t coord);
        direction getDirection(void);
        irr::core::vector3df getMoveVector(void);
        virtual void setMoveVector(irr::core::vector3df vect);
        virtual bool getWallPass(void);
        virtual void updateWallPass(void);
        void updateParticles(void);
        int getRange();
        void setInput(int idx, KeyHandler key);
        status_e getStatus(void);
        void updateStatus(void);
        void deleteGameObj();
        virtual void resetLastRecord();
        virtual int getMaxBomb();
        int getBombs();
        void setBombs(int bombs);
        int getId(void);
        bool hasPower();
        void setPower(bool power);
        bool isOnline();
        void setIsOnline(bool neo);
        void unstackAction();
        void stun();
        void setNetwork(NetworkClient *network);
        int getCharacterIDX(void);
        NetworkClient *getNetwork(void);
        void setActualBombs(int);
        void setMaxBombs(int);
        void setRange(int);
        void setStatus(int);
	void setDeath(bool neo);
	bool getDeath(void);

    protected:
    	bool _dead = false;
        int _id = 0;
        std::vector< std::pair<KeyHandler, IActorMethodPtr> > _actions;
        irr::core::vector3df _moveVector;
        std::vector<int> _events;
        std::queue< std::pair<handleMethodPtr, IActorMethodPtr> > _actionsToDo;
        std::mutex _mut;
        coord_t _coord;
        bool _hasPower = false;
        std::vector<Particle *> _particles;
        bool _isOnline = false;
        NetworkClient *_network = nullptr;
};

#endif