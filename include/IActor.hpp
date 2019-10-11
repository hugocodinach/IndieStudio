/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/IActor.hpp
*/

#ifndef IACTOR
#define IACTOR

#include <map>
#include "DynamicObj.hpp"
#include "Key.hpp"
#include "ActionHandler.hpp"
#include "Bonus.hpp"
#include "Status.hpp"
#include "NetworkClient.hpp"
extern int MUSIC;

enum direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

class IActor : public DynamicObj
{
    public:
        virtual ~IActor() = default;

        virtual void play(void) = 0;

        virtual void firstAction(void) = 0;
        virtual void secondAction(void) = 0;
        virtual void thirdAction(void) = 0;
        virtual void forthAction(void) = 0;
        virtual void fifthAction(void) = 0;
        virtual void sixthAction(void) = 0;

        virtual void firstActionResolve(void) = 0;
        virtual void secondActionResolve(void) = 0;
        virtual void thirdActionResolve(void) = 0;
        virtual void forthActionResolve(void) = 0;
        virtual void fifthActionResolve(void) = 0;
        virtual void sixthActionResolve(void) = 0;

        virtual void applyBonus(Bonus *bonus) = 0;

        virtual void pushAction(void (ActionHandler::*)(IActor&), void (IActor::*)(void)) = 0;
        virtual void unstackAction() = 0;
        virtual coord_t getCoord() = 0;
        virtual void setCoord(coord_t coord) = 0;
        virtual irr::core::vector3df getMoveVector(void) = 0;
        virtual void setMoveVector(irr::core::vector3df) = 0;
        virtual bool getWallPass(void) = 0;
        virtual direction getDirection(void) = 0;
        virtual void updateWallPass(void) = 0;
        virtual int getCharacterIDX(void) = 0;

        virtual void setActualBombs(int) = 0;
        virtual void setMaxBombs(int) = 0;
        virtual void setRange(int) = 0;
        virtual void setStatus(int) = 0;

        virtual void stun(void) = 0;
        virtual status_e getStatus(void) = 0;
        virtual void updateStatus(void) = 0;
        virtual void updateParticles(void) = 0;

        virtual std::queue< std::pair<void (ActionHandler::*)(IActor&), void (IActor::*)(void)> >& getActionsToDo() = 0;
        virtual std::vector< std::pair<KeyHandler, void (IActor::*)(void)> > getBinds() = 0;
        virtual int getRange() = 0;
        virtual void setInput(int idx, KeyHandler) = 0;
        virtual void deleteGameObj() = 0;
        virtual std::chrono::system_clock::time_point &getLastRecord(void) = 0;
        virtual void resetLastRecord() = 0;
        virtual float &cd() = 0;
        virtual int getMaxBomb() = 0;
        virtual float &cd(float neo) = 0;
        virtual int getBombs() = 0;
        virtual void setBombs(int bombs) = 0;
        virtual int getId(void) = 0;
        virtual bool hasPower() = 0;
        virtual void setPower(bool power) = 0;
        virtual bool isOnline() = 0;
        virtual void setIsOnline(bool neo) = 0;
        virtual void setNetwork(NetworkClient *network) = 0;
        virtual NetworkClient *getNetwork(void) = 0;
	virtual void setDeath(bool) = 0; 
	virtual bool getDeath(void) = 0; 
		virtual bool &getWait() = 0;

};

typedef void (IActor::*IActorMethodPtr)(void);
typedef void (ActionHandler::*handleMethodPtr)(IActor&);

#endif