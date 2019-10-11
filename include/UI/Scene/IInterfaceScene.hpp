/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/IInterfaceScene.hpp
*/

#ifndef IINTERFACE_SCENE
#define IINTERFACE_SCENE

    #include "irr/irrlicht.h"

    #include "IInterfaceObj.hpp"
    #include "UIButton.hpp"
    #include "UIText.hpp"
    #include "UIImage.hpp"
    #include "UILateralMenu.hpp"
    #include "UILateralText.hpp"
    #include "UISmartText.hpp"
    #include "UISmartListBox.hpp"
    #include "UIEditBox.hpp"

    #define TITLE_TEXT_SIZE 50

    enum UI_SCENE_ID {
        MENU = 1,
        PLAY,
        SERVER_ROOM,
        SERVER_LOBBY,
        LOCAL_LOBBY,
        KEY_BINDING,
        OPTION,
        SERVER_CONNECT,
        HELP,
        QUIT,
    };

    enum USER_STATU {
        ONLINE = 3,
        LOCAL = 0,
        AI_PLAYER = 1,
        NOT_PLAYING = 2,
    };

    typedef struct user_info_s {
        std::string username;
        int characterId;
        bool isReady;
        int statu;
    } user_info_t;

    typedef struct sceneInfo_s {
        int sceneId;
        bool isOnline;
        int idxLocalUser;       //For online only.
        int loadGame = false;
		bool autotrigger = false;
        std::vector<user_info_t> users;
    } sceneInfo_t;

    typedef struct option_s {
        int soundVolume;
        int musicVolume;
        bool useCoinMode;
    } option_t;

    class IInterfaceScene
    {
        public:
        virtual ~IInterfaceScene() = default;

        virtual void create() = 0;
        virtual bool manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene) = 0;
        virtual bool update(void) = 0;
        virtual int getId(void) const = 0;
        virtual bool isFromBack(void) const = 0;
        virtual IInterfaceObj *getObjbyId(int id) const = 0;

        private:
    };

#endif