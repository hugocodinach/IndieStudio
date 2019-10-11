/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/AInterfaceScene.hpp
*/

#ifndef AINTERFACE_SCENE
#define AINTERFACE_SCENE

    #include <vector>
    #include <map>
    #include <utility>
	// #include <bits/stdc++.h> 
	#include <boost/algorithm/string.hpp> 

    #include "irr/irrlicht.h"

    #include "IInterfaceScene.hpp"
    #include "IInterfaceObj.hpp"
	#include "NetworkClient.hpp"
    #include "Alphabet.hpp"
    #include "PersSelection.hpp"

    class AInterfaceScene: public IInterfaceScene
    {
        public:
            AInterfaceScene(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
            irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId,
            MusicPlayer &musicPlayer);
            ~AInterfaceScene();

            virtual void create() = 0;
            virtual bool manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene) = 0;
            virtual bool update(void) = 0;
            int getId(void) const;
            bool isInAlphabet(char c);
            bool isFromBack(void) const;
            float cptFontSize(float) const;

        protected:
            int computeObjId(int ObjId) const;
            int getSceneFromId(int id);
            int getObjIdFromId(int id);
            IInterfaceObj * getObjbyId(int id) const;
            bool checkObjType(int objId, int type) const;
            int buttonUpdate(const irr::SEvent& event, sceneInfo_t &nextScene,
            int nextSceneId, int buttonId) const;
            void updateVisibleObj(void);
            bool isObjOnStatu(std::pair<std::vector<int>, IInterfaceObj *> &obj, int statu);
            int lateralTextUpdate(int id_left_button, int id_right_button,
                int id_lateral_text, int id_obj_to_check, const irr::SEvent& event);
            MODELS rotatingMeshesUpdate(int id_left_button, int id_right_button,
                int id_meshe_to_mode, int id_obj_to_check, RotatingMeshes &meshesManager,
                const irr::SEvent& event, int status);
            std::vector<std::pair<std::vector<int>, IInterfaceObj *>> _objs;
            irr::gui::IGUIEnvironment *_guiEnv;
            irr::video::IVideoDriver *_driver;
            irr::IrrlichtDevice *_device;
            int _id;
            int _actualStatu;
            int _prevStatu;
            int _allStatu;
            std::vector<int> &_prevSceneId;
            bool _fromBack;
            MusicPlayer &_musicPlayer;
    };

#endif