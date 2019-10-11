/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/InterfacePlay.cpp
*/

#include "InterfacePlay.hpp"

InterfacePlay::InterfacePlay(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
                             irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId, std::vector<user_info_t> &users,
                             GameModule *game, MusicPlayer &musicPlayer, NetworkClient* serveclient) : AInterfaceScene(device, guiEnv, driver, id, prevSceneId, musicPlayer), _users(users),
                                                                           _game(game), _timerText(_driver, _guiEnv, -1, "00:00", {2, 48}, cptFontSize(36))
{
    _usersUi.push_back({{1, 1}, {}});
    _usersUi.push_back({{89, 1}, {}});
    _usersUi.push_back({{1, 77}, {}});
    _usersUi.push_back({{89, 77}, {}});
    this->create();
    _prevStatu = -1;
    _actualStatu = PLAY_STATU::DEFAULT;
    _allStatu = PLAY_STATU::DEFAULT;
    _timer = device->getTimer();
    _timerStart = _timer->getTime();
    _frezzTime = false;
    _scoresCreated = false;
	_serveclient = serveclient;
}

InterfacePlay::~InterfacePlay()
{
    // std::cout << "~InterfacePlay" << std::endl;
}

void InterfacePlay::create()
{
    IInterfaceObj *new_obj;

    //NAME PLAYER 1
    for (int i = 0; i < _users.size(); i += 1)
    {
        new_obj = new UISmartText(_driver, _guiEnv, -1,
                                  _users[i].username, _usersUi[i].startPos, cptFontSize(16));
        _objs.push_back(std::make_pair(std::vector<int>{PLAY_STATU::DEFAULT}, new_obj));
    }
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(PLAY_OBJ_ID::SAVE_BUTTON),
                           irr::core::rect<irr::f32>(2, 37, 7, 45),
                           irr::core::rect<irr::s32>(0, 0, 1000, 1000),
                           "sb_back_arrow",
                           "./ressources/UI/play/save_idle.png",
                           "./ressources/UI/play/save_over.png",
                           "./ressources/UI/play/save_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{PLAY_STATU::DEFAULT}, new_obj));
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(PLAY_OBJ_ID::HOME_BUTTON),
                           irr::core::rect<irr::f32>(2, 30, 8, 38),
                           irr::core::rect<irr::s32>(0, 0, 512, 512),
                           "sb_back_arrow",
                           "./ressources/UI/global/farm.png",
                           "./ressources/UI/global/farm_hover.png",
                           "./ressources/UI/global/farm_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{PLAY_STATU::DEFAULT}, new_obj));
}

bool InterfacePlay::manageEvent(const irr::SEvent &event, sceneInfo_t &nextScene)
{
    int idScene = -1;
    int idObj = -1;

    if (event.EventType == irr::EET_GUI_EVENT)
    {
        idScene = this->getSceneFromId(event.GUIEvent.Caller->getID());
        idObj = this->getObjIdFromId(event.GUIEvent.Caller->getID());
    }
    if (idScene == UI_SCENE_ID::PLAY)
    {
        switch (idObj)
        {
        case PLAY_OBJ_ID::SAVE_BUTTON:
            if (buttonUpdate(event, nextScene, UI_SCENE_ID::PLAY, idObj) == BUTTON_STATU::CLICKED)
            {
                _game->getSave()->saveGameModule(_game);
            }
        }
        if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
        {
            if (idObj == PLAY_OBJ_ID::START_BUTTON)
            {
                nextScene.sceneId = UI_SCENE_ID::MENU;
                return true;
            }
            else if (idObj == PLAY_OBJ_ID::QUIT_BUTTON)
            {
				_serveclient->quit();
                nextScene.sceneId = UI_SCENE_ID::QUIT;
                return (true);
            }
            else if (idObj == PLAY_OBJ_ID::HOME_BUTTON)
            {
				if (_serveclient != nullptr) {
					_serveclient->quit();
				}
                _game->reset();
                nextScene.sceneId = UI_SCENE_ID::MENU;
                return true;
            }
        }
    }
    if (idObj == PLAY_OBJ_ID::HOME_BUTTON)
        buttonUpdate(event, nextScene, UI_SCENE_ID::PLAY, idObj);
    return false;
}

bool InterfacePlay::addBonus(int player, int bonus)
{
    float start_y = 0.0;
    float start_x = 0.0;
    int idx_texture = 0;

    for (; idx_texture < bonusesPath.size() && bonusesPath[idx_texture].first != bonus; idx_texture += 1)
        ;
    if (bonusesPath[idx_texture].first == -1)
        return false;
    start_y = (_usersUi[player].startPos.Y + 2) + bonus * (BONUS_IMG_HEIGHT + BONUS_IMG_HEIGT_OFFSET);
    start_x = (_usersUi[player].startPos.X) + getNbOfBonus(player, bonus) * 1;
    UIImage *new_obj = new UIImage(_driver, _guiEnv, -1,
    irr::core::rect<irr::f32>(start_x, start_y, start_x + BONUS_IMG_WIDTH, start_y + BONUS_IMG_HEIGHT),
    _driver->getTexture(bonusesPath[bonus].second));
    _usersUi[player].bonuses.push_back(std::make_pair(bonus, new_obj));
    return (true);
}

int InterfacePlay::getNbOfBonus(int player, int bonus)
{
    int nb_bonus = 0;

    if (player >= 4)
        return -1;
    for (int i = 0; i < _usersUi[player].bonuses.size(); i += 1)
    {
        if (_usersUi[player].bonuses[i].first == bonus)
            nb_bonus += 1;
    }
    return (nb_bonus);
}

void InterfacePlay::updateTime(int time)
{
    double seconds = time / 1000;
    float minutes = seconds / 60.0;

    seconds = seconds - (static_cast<int>(minutes) * 60.0);
    std::string new_minutes = std::to_string(static_cast<int>(minutes));
    if (minutes < 10)
        new_minutes = "0" + new_minutes;
    std::string new_seconds = std::to_string(static_cast<int>(seconds));
    if (seconds < 10)
        new_seconds = "0" + new_seconds;
    std::string new_time = new_minutes + ":" + new_seconds;
    _timerText.setText(new_time);
}

void InterfacePlay::frezzClock(void)
{
    _frezzTime = true;
}

void InterfacePlay::unfrezzClock(void)
{
    _frezzTime = false;
}

bool InterfacePlay::update()
{
    if (_game->isOnPodium() && !_scoresCreated)
    {
        int tmp;
        std::vector<GameModule::character_t> charac = _game->getPlayerInfo();
        std::vector<int> scores = _game->getScore();
        std::vector<MODELS> models;

        for (size_t i = 0; i != charac.size(); i += 1)
            models.push_back(static_cast<MODELS>(charac[i].characterIDX));

        for (size_t i = 0; i < scores.size() - 1; i += 1) {
            if (scores[i] < scores[i + 1]) {
                tmp = scores[i];
                scores[i] = scores[i + 1];
                scores[i + 1] = tmp;
                tmp = static_cast<int>(models[i]);
                models[i] = models[i + 1];
                models[i + 1] = static_cast<MODELS>(tmp);
                i = -1;
            }
        }
        std::vector<irr::core::position2df> pos{
            {50, (models.size() > 0) ? scoresPodiumPos[models[0]] : -20},
            {37, (models.size() > 1) ? scoresPodiumPos[models[1]] + 6 : -20},
            {60, (models.size() > 2) ? scoresPodiumPos[models[2]] + 10 : -20},
            {20, (models.size() > 3) ? scoresPodiumPos[models[3]] + 20 : -20}};
        for (size_t i = 0; i != scores.size(); i += 1)
        {
            _objs.push_back(std::make_pair(std::vector<int>{PLAY_STATU::DEFAULT},
                                           new UISmartText(_driver, _guiEnv, -1,
                                                           std::to_string(scores[i]), pos[i], cptFontSize(25))));
        }
        _scoresCreated = true;
    }
    if (_frezzTime == false)
        updateTime(_timer->getTime() - _timerStart);
    return true;
}