//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Server
//

#pragma once

#include <memory>
#include <algorithm>
#include <vector2d.h>
#include "Socket.hpp"
#include "Bomb.hpp"
#include "Astar.hpp"

namespace Indie {
	enum GameState {
		NOTCONNECTED,
		WAITING,
		PLAYING
	};

	class Client {
		public:
			Client(int id, int fd, const std::string &name) : _id(id), _fd(fd), _name(name), _state(WAITING), _alive(true) {}
			int _id;
			int _fd;
			std::string _name;
			GameState _state;
			irr::core::vector2di pos2d;
			bool _alive;
	};

	enum BotMode {
		ATTACK,
		DEFENSE
	};
	class Bot {
		public:
			Bot(int id) : _id(id), _state(WAITING), _alive(true), _speed(1.5f), _power(1), _bombNumber(1), _wallUp(false), rotation(0), _direction(0) {}
			void move(std::vector<std::vector<int>> &map);
			int get2dy(std::vector<std::vector<int>> &map);
			int get2dx(std::vector<std::vector<int>> &map);
			void roadToTake(std::vector<std::vector<int>> &map);
			void findDefensiveRoad(std::vector<std::vector<int>> &map);
			int lookAround(std::vector<std::vector<int>> &map);
			void findWay(std::vector<std::vector<int>> &map);
			std::vector<Pos> findGoal(std::vector<std::vector<int>> &map);

			int _id;
			GameState _state;
			irr::core::vector2di pos2d;
			irr::core::vector3df pos3d;
			bool _alive;
			irr::f32 _speed;
			std::size_t _power;
			std::size_t _bombNumber;
			bool _wallUp;
			irr::f32 rotation;
			int _direction;
			std::vector<int> road {0};
			bool t = false;
			BotMode _mode = DEFENSE;
			int xd = 0;
	};

	bool operator==(std::unique_ptr<Client> &, std::unique_ptr<Client> &);
	bool operator!=(std::unique_ptr<Client> &, std::unique_ptr<Client> &);

	class Server {
		public:
			Server();
			void start();
			void setClientsFds();
			void readOnFds();
			int maxFd() const;
			void addClient();
			int readClient(std::unique_ptr<Client> &);
			GameState checkIfStartGame();
			static void runServer();
			void destroyEntities(std::unique_ptr<Indie::Bomb> &bomb);
			bool hitPlayer(const irr::core::vector2di &target, const int &id);
			void manageBomb();
			void replaceByBonus(const irr::core::vector2di &pos);
			bool wallMove(std::unique_ptr<Client> &client, irr::core::vector3df &pos3d, irr::core::vector2di &pos2d, irr::f32 &rotation);
			bool validMove(const int &block);
			void comPlayer(const ObjectsEvents &event, std::vector<std::string> &, std::unique_ptr<Client> &);
			void comBomb(const ObjectsEvents &event, std::vector<std::string> &, std::unique_ptr<Client> &);
			void comGameInfos(const ObjectsEvents &event, std::vector<std::string> &, std::unique_ptr<Client> &);
			void comMap(const ObjectsEvents &event, std::vector<std::string> &, std::unique_ptr<Client> &);
			std::vector<std::vector<int>> buildMap(const std::string &msg);
			int getBlock(irr::core::vector2di &pos) const { return _map[pos.Y][pos.X]; }
			void setBlock(irr::core::vector2di &pos, int value) { _map[pos.Y][pos.X] = value; }
			void sendInfoToClient();
			void createBomb(int, irr::core::vector2di pos2d, irr::core::vector3df pos3d, std::size_t power, std::size_t limit);
			void manageBot();

		private:
			fd_set _fdRead;
			Socket _socket;
			int _hostFd;
			GameState _state;
			std::vector<std::unique_ptr<Client>> _clients;
			std::vector<std::unique_ptr<Bot>> _bots;
			std::vector<std::unique_ptr<Indie::Bomb>> _bombs;
			std::vector<std::vector<int>> _map;
			std::vector<std::vector<int>> _spawn;
			std::string _mapMsg;
			std::string _lastCmd;
			std::vector<void (Indie::Server::*)(const ObjectsEvents &event, std::vector<std::string> &, std::unique_ptr<Client> &)> _objectsFct;
			int _lastId;
			bool _continue;
	};

}

