/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/actor/Bomberman.cpp
*/

#include "Bomberman.hpp"

Bomberman::Bomberman(irr::scene::ISceneManager *smgr, irr::core::vector3df pos, int x, int y, int id, std::vector<irr::scene::IAnimatedMesh *> vect_mesh, int characterIDX)
{
	_characterIDX = characterIDX;
	std::vector<particleSettings> spellSettings = {WATER_SPELL_PS, FIRE_SPELL_PS, WIND_SPELL_PS};

	_bomberman = smgr->addAnimatedMeshSceneNode(smgr->getMesh((modelsList[_characterIDX].file).c_str()));
	_bomberman->setPosition(pos);
	_maxBomb = modelsList[_characterIDX].bombNbr;
	_range = modelsList[_characterIDX].range;
	_speed = modelsList[_characterIDX].mouseSpeed;
	_type = modelsList[_characterIDX].type;
	_hasPower = false;

	_bomberman->getMaterial(0).NormalizeNormals = true;
	_bomberman->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_coord.x = x;
	_coord.y = y;
	_x = y;
	_y = x;
	_moveVector.Z = 0;
	_moveVector.X = 0;
	_moveVector.Y = 0;
	_bombs = _maxBomb;
	_id = id;
	_particul = new PersoParticule(smgr, pos, _bomberman);
	_particles.push_back(new Particle(smgr, _bomberman, spellSettings[_type]));
	_direction = RIGHT;
	_vect_mesh = vect_mesh;
	_start = std::chrono::system_clock::now();
	_wait = false;
}

Bomberman::~Bomberman()
{
}

bool &Bomberman::getWait()
{
	return _wait;
}

void Bomberman::setCoord(coord_t coord)
{
	_coord = coord;
	_x = coord.y;
	_y = coord.x;
}

void Bomberman::pure(void)
{
}

void Bomberman::play(void)
{
}

void Bomberman::firstAction(void)
{
	if (_status.getStatus() == STUN)
		return;
	if (_actionsToDo.size() == 0)
	{
		if (_network != nullptr && isOnline() == false)
		{
			if (_wait == false) {
				_wait = true;
				_network->action("FIRST");
				return;
			}
			_wait = false;
		}
		_direction = LEFT;
		_moveVector.Z -= TILE_SIZE;
		_bomberman->setRotation(irr::core::vector3df(0, 90, 0));
		pushAction(&ActionHandler::moveActor, static_cast<IActorMethodPtr>(&AActor::firstActionResolve));
	}
}

void Bomberman::secondAction(void)
{
	if (_status.getStatus() == STUN)
		return;
	if (_actionsToDo.size() == 0)
	{
		// std::cout << "DEBBUG" << std::endl;
		if (_network != nullptr && isOnline() == false)
		{
			if (_wait == false) {
				_wait = true;
				_network->action("SECOND");
				return;
			}
			_wait = false;
			// _wait = true;
			// _network->action("SECOND");
			// return;
		}
		_direction = DOWN;
		_moveVector.X += TILE_SIZE;
		_bomberman->setRotation(irr::core::vector3df(0, 0, 0));
		pushAction(&ActionHandler::moveActor, static_cast<IActorMethodPtr>(&AActor::secondActionResolve));
	}
}

void Bomberman::thirdAction(void)
{
	if (_status.getStatus() == STUN)
		return;
	if (_actionsToDo.size() == 0)
	{
		if (_network != nullptr && isOnline() == false)
		{
			if (_wait == false) {
				_wait = true;
				_network->action("THIRD");
				return;
			}
			_wait = false;
			// _wait = true;
			// _network->action("THIRD");
			// return;
		}
		_direction = RIGHT;
		_moveVector.Z += TILE_SIZE;
		_bomberman->setRotation(irr::core::vector3df(0, 270, 0));
		pushAction(&ActionHandler::moveActor, static_cast<IActorMethodPtr>(&AActor::thirdActionResolve));
	}
}

void Bomberman::forthAction(void)
{
	if (_status.getStatus() == STUN)
		return;
	if (_actionsToDo.size() == 0)
	{

		if (_network != nullptr && isOnline() == false)
		{
			if (_wait == false) {
				_wait = true;
				_network->action("FORTH");
				return;
			}
			_wait = false;
			// _wait = true;
			// _network->action("FORTH");
			// return;
		}
		_direction = UP;
		_moveVector.X -= TILE_SIZE;
		_bomberman->setRotation(irr::core::vector3df(0, 180, 0));
		pushAction(&ActionHandler::moveActor, static_cast<IActorMethodPtr>(&AActor::forthActionResolve));
	}
}

void Bomberman::fifthAction(void)
{
	if (_status.getStatus() == STUN)
		return;
	if (_actionsToDo.size() == 0)
	{

		if (_network != nullptr && isOnline() == false)
		{
			if (_wait == false) {
				_wait = true;
				_network->action("FIFTH");
				return;
			}
			_wait = false;
			// _wait = true;
			// _network->action("FIFTH");
			// return;
		}
		pushAction(&ActionHandler::PutBomb, static_cast<IActorMethodPtr>(&AActor::fifthAction));
	}
}

void Bomberman::sixthAction(void)
{
	if (_hasPower)
	{
		// std::cout << "CALL" << std::endl;
		if (_actionsToDo.size() == 0)
		{
		// std::cout << "CALL 1" << std::endl;


			if (_network != nullptr && isOnline() == false)
			{
				if (_wait == false) {
					_wait = true;
				_network->action("SIXTH");
				return;
			}
			_wait = false;
			// _wait = true;
				// _network->action("SIXTH");
				// return;
			}
		// std::cout << "CALL 2" << std::endl;

			void (ActionHandler::*handleMethodPtr[])(IActor &) = {&ActionHandler::waterSpell, &ActionHandler::fireSpell, &ActionHandler::windSpell};
		// std::cout << "CALL 3" << std::endl;
			pushAction(handleMethodPtr[_type], static_cast<IActorMethodPtr>(&AActor::sixthActionResolve));
		// std::cout << "CALL 4" << std::endl;
			_hasPower = false;
		}
	}
}

void Bomberman::firstActionResolve(void)
{
	if (_status.getStatus() == STUN)
		return;
	_particul->SetVisible(true);
	irr::core::vector3df pos = _bomberman->getPosition();
	float movingSpeed = 1. + ((static_cast<float>(_speed) - 1.) / 4.);
	int movingRange = (_moveVector.Z + movingSpeed) > 0 ? _moveVector.Z : -movingSpeed;


    
	// int result = fibonacci(42);
    _end = std::chrono::system_clock::now();
 
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds> (_end-_start).count();

	if (elapsed_seconds > 15) {
		pos.Z += movingRange;
		_moveVector.Z -= movingRange;
		_bomberman->setPosition(pos);
		_start = std::chrono::system_clock::now();
	}

	if (_moveVector.Z == 0)
	{
		_y -= 1;
		_coord.x = _y;
		_wait = false;
		unstackAction();
	}
}

void Bomberman::secondActionResolve(void)
{
	// std::cout << "DUGdaz" << std::endl;

	if (_status.getStatus() == STUN)
		return;
	_particul->SetVisible(true);
	// std::cout << "DUG" << std::endl;
	irr::core::vector3df pos = _bomberman->getPosition();
	float movingSpeed = 1. + ((static_cast<float>(_speed) - 1.) / 4.);
	int movingRange = (_moveVector.X - movingSpeed) < 0 ? _moveVector.X : movingSpeed;

	_end = std::chrono::system_clock::now();
 
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds> (_end-_start).count();

	if (elapsed_seconds > 15) {
		pos.X += movingRange;
		_moveVector.X -= movingRange;
		_bomberman->setPosition(pos);
		_start = std::chrono::system_clock::now();
	}
	if (_moveVector.X == 0)
	{
		_x += 1;
		_coord.y = _x;
		_wait = false;
		unstackAction();
	}
}

void Bomberman::thirdActionResolve(void)
{
	if (_status.getStatus() == STUN)
		return;
	_particul->SetVisible(true);
	irr::core::vector3df pos = _bomberman->getPosition();
	float movingSpeed = 1. + ((static_cast<float>(_speed) - 1.) / 4.);
	int movingRange = (_moveVector.Z - movingSpeed) < 0 ? _moveVector.Z : movingSpeed;

	_end = std::chrono::system_clock::now();
 
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds> (_end-_start).count();

	if (elapsed_seconds > 15) {
		pos.Z += movingRange;
		_moveVector.Z -= movingRange;
		_bomberman->setPosition(pos);
		_start = std::chrono::system_clock::now();
	}
	if (_moveVector.Z == 0)
	{
		_y += 1;
		_coord.x = _y;
		_wait = false;
		unstackAction();
	}
}

void Bomberman::forthActionResolve(void)
{
	if (_status.getStatus() == STUN)
		return;
	_particul->SetVisible(true);
	irr::core::vector3df pos = _bomberman->getPosition();
	float movingSpeed = 1. + ((static_cast<float>(_speed) - 1.) / 4.);
	int movingRange = (_moveVector.X + movingSpeed) > 0 ? _moveVector.X : -movingSpeed;

	_end = std::chrono::system_clock::now();
 
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds> (_end-_start).count();

	if (elapsed_seconds > 15) {
		pos.X += movingRange;
		_moveVector.X -= movingRange;
		_bomberman->setPosition(pos);
		_start = std::chrono::system_clock::now();
	}
	if (_moveVector.X == 0)
	{
		_x -= 1;
		_coord.y = _x;
		_wait = false;
		unstackAction();
	}
}

void Bomberman::sixthActionResolve(void)
{
		// std::cout << "CALL 5" << std::endl;

	void (Bomberman::*ptr[])(void) = {&Bomberman::waterSpellResolve, &Bomberman::fireSpellResolve, &Bomberman::windSpellResolve};
		// std::cout << "CALL 6" << std::endl;

	_particles[SPELL]->playParticleFor(1);
		// std::cout << "CALL 7" << std::endl;

	(this->*ptr[_type])();
		// std::cout << "CALL 8" << std::endl;

}

void Bomberman::waterSpellResolve(void)
{
}

void Bomberman::fireSpellResolve(void)
{
}

void Bomberman::windSpellResolve(void)
{
	irr::core::vector3df pos = _bomberman->getPosition();
	switch (_direction)
	{
	case UP:
		_bomberman->setPosition({pos.X - (TILE_SIZE * 2), pos.Y, pos.Z});
		_x -= 2;
		_coord.y = _x;
		break;
	case RIGHT:
		_bomberman->setPosition({pos.X, pos.Y, pos.Z + (TILE_SIZE * 2)});
		_y += 2;
		_coord.x = _y;
		break;
	case DOWN:
		_bomberman->setPosition({pos.X + (TILE_SIZE * 2), pos.Y, pos.Z});
		_x += 2;
		_coord.y = _x;
		break;
	case LEFT:
		_bomberman->setPosition({pos.X, pos.Y, pos.Z - (TILE_SIZE * 2)});
		_y -= 2;
		_coord.x = _y;
		break;
	default:
		break;
	}
}

bool Bomberman::getWallPass(void)
{
	return _wallPass.isActivated();
}

void Bomberman::updateWallPass(void)
{
	_wallPass.update();
}

void Bomberman::deleteGameObj()
{
	_bomberman->remove();
}

void Bomberman::stun(void)
{
	_status.setStatus(STUN);
}

status_e Bomberman::getStatus(void)
{
	return _status.getStatus();
}

void Bomberman::updateStatus(void)
{
	_status.updateStatus();
}

void Bomberman::applyBonus(Bonus *bonus)
{
	Bonus::bonus_t type = bonus->getType();

	if (type == Bonus::SPEED_UP)
	{
		_speed += 1;
	}
	else if (type == Bonus::BOMB_UP)
	{
		_maxBomb += 1;
		_bombs += 1;
	}
	else if (type == Bonus::FIRE_UP && _range < 5)
	{
		_range += 1;
	}
	else if (type == Bonus::WALL_PASS)
	{
		_wallPass.reset();
	}
	else if (type == Bonus::POWER_UP)
	{
		_hasPower = true;
	}
}

direction Bomberman::getDirection(void)
{
	return _direction;
}

void Bomberman::setRange(int ran)
{
	_range = ran;
}

int Bomberman::getRange()
{
	std::unique_lock<std::mutex> lock(_mut);
	return (_range);
}

std::chrono::system_clock::time_point &Bomberman::getLastRecord(void)
{
	return (_lastRecord);
}

void Bomberman::resetLastRecord()
{
	_lastRecord = std::chrono::system_clock::now();
}
float &Bomberman::cd()
{
	return (_cd);
}

float &Bomberman::cd(float neo)
{
	_cd = neo;
	return (_cd);
}

int Bomberman::getMaxBomb()
{
	return (_maxBomb);
}

int Bomberman::getBombs()
{
	return (_bombs);
}

void Bomberman::setBombs(int bombs)
{
	_bombs += bombs;
}

TYPE Bomberman::getType(void)
{
	return _type;
}

int Bomberman::getCharacterIDX()
{
	return (_characterIDX);
}

void Bomberman::setActualBombs(int bombs)
{
    _bombs = bombs;
}

void Bomberman::setMaxBombs(int maxBomb)
{
    _maxBomb = maxBomb;
}

void Bomberman::setStatus(int status)
{
    if (status == 1)
        this->stun();
}
