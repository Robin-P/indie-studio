/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** AI
*/

#include <random>
#include "AI.hpp"
#include "Server.hpp"
#include "Clock.hpp"

void Indie::Server::manageBot()
{
	static Clock tm;
	static int status = 0;
	if (status == 0) {
		for (auto &bot : _bots) {
			bot->pos2d.X = bot->get2dy(_map);
			bot->pos2d.Y = bot->get2dx(_map);
		}
		status = 1;
	}
	for (auto &bot : _bots) {
		if (tm.getElapsedTime() > 50) {
			bot->move(_map);
			bot->xd = 0;
			_lastCmd = "";
			_lastCmd = std::to_string(BOMB) + ':' +
			std::to_string(CREATEBOMB) + ':' +
			std::to_string(bot->_id) + ':' +
			std::to_string(bot->pos2d.X) + ':' +
			std::to_string( bot->pos2d.Y) + ':' +
			std::to_string(bot->pos3d.X) + ':' +
			std::to_string(bot->pos3d.Y) + ':' +
			std::to_string(bot->pos3d.Z) + ':' +
			std::to_string(bot->_power) + ':' +
			std::to_string(bot->_bombNumber);
			createBomb(bot->_id, bot->pos2d, bot->pos3d, bot->_power, bot->_bombNumber);
			for (auto &i : _clients)
				dprintf(i->_fd, "%d:%d:%d:%d:%d:%f:%f:%f:%f:%i\n", PLAYER, MOVE, bot->_id, bot->pos2d.X, bot->pos2d.Y, bot->pos3d.X, bot->pos3d.Y, bot->pos3d.Z, bot->rotation, bot->_wallUp);
			tm.reset();
		}
	}
}

int Indie::Bot::get2dy(std::vector<std::vector<int>> &map)
{
	int size = map.size() * 20 / 2;
	return ((pos3d.X - size) * -1 / 20);
}

int Indie::Bot::get2dx(std::vector<std::vector<int>> &map)
{
	int size = map.size() * 20 / 2;
	return ((pos3d.Z - size) * -1 / 20);
}

int Indie::Bot::lookAround(std::vector<std::vector<int>> &map)
{
	if (map[pos2d.X][pos2d.Y] == 3)
		return 1;
	else if (pos2d.X > 0 && map[pos2d.X - 1][pos2d.Y] == 3)
		return 1;
	else if (pos2d.Y < 24 && map[pos2d.X][pos2d.Y + 1] == 3)
		return 2;
	else if (pos2d.X < 24 && map[pos2d.X + 1][pos2d.Y] == 3)
		return 3;
	else if (pos2d.Y > 0 && map[pos2d.X][pos2d.Y - 1] == 3)
		return 4;
	if (pos2d.X > 0 && map[pos2d.X - 1][pos2d.Y] == 1)
		return 5;
	else if (pos2d.Y < 24 && map[pos2d.X][pos2d.Y + 1] == 1)
		return 6;
	else if (pos2d.X < 24 && map[pos2d.X + 1][pos2d.Y] == 1)
		return 7;
	else if (pos2d.Y > 0 && map[pos2d.X][pos2d.Y - 1] == 1)
		return 8;
	return 0;
}

void Indie::Bot::findWay(std::vector<std::vector<int>> &map)
{
	if (pos2d.X > 0 && map[pos2d.X - 1][pos2d.Y] == 0)
		road.push_back(1);
	else if (pos2d.Y < 24 && map[pos2d.X][pos2d.Y + 1] == 0)
		road.push_back(2);
	else if (pos2d.X < 24 && map[pos2d.X + 1][pos2d.Y] == 0)
		road.push_back(3);
	else if (pos2d.Y > 0 && map[pos2d.X][pos2d.Y - 1] == 0)
		road.push_back(4);
	else
		road.push_back(0);
}

std::vector<Pos> Indie::Bot::findGoal(std::vector<std::vector<int>> &map)
{
	Astar a(map);
	Pos goal;

	for (int round = 0; round < 5; round++) {
		for (int i = pos2d.X - round; i <= pos2d.X + round; i++) {
			for (int j = pos2d.Y - round; j <= pos2d.Y + round; j++) {
				if (i >= 0 && j >= 0 && i <= 24 && j <= 24)
					if (map[i][j] == 1) {
						goal = {i, j};
						break;
					}
			}
		}
	}
	return a.findPath({pos2d.Y, pos2d.X}, goal);
}

void Indie::Bot::findDefensiveRoad(std::vector<std::vector<int>> &map)
{
	int look = lookAround(map);
	// map[pos2d.X][pos2d.Y] = 0;
	// for (int i = 0; i < map.size(); ++i) {
	// 	for (int j = 0; j < map.size(); ++j) {
	// 		std::cout << map[i][j] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	// map[pos2d.X][pos2d.Y] = 0;
	// std::cout << "pos:" << pos2d.X << " " << pos2d.Y << std::endl;
	if (look == 0) {
		_mode = ATTACK;
		auto path = findGoal(map);
		if (path.size() <= 0) {
			road.push_back(1);
			return;
		}
		Pos tmp;
		path.pop_back();
		std::reverse(path.begin(), path.end());
		for (auto &pos : path)
			std::cout << pos.y << " " << pos.x << std::endl;
		tmp = Pos(pos2d.Y, pos2d.X);
		for (auto &pos : path) {
			if (tmp.x > pos.x)
				road.push_back(4);
			else if (tmp.x < pos.x)
				road.push_back(2);
			else if (tmp.y < pos.y)
				road.push_back(3);
			else if (tmp.y > pos.y)
				road.push_back(1);
			tmp = pos;
		}
	}
	else if (look > 4) {
		xd = 1;
		road.push_back(0);
		_mode = ATTACK;
	}
	else {
		_mode = DEFENSE;
		findWay(map);
	}
}

void Indie::Bot::roadToTake(std::vector<std::vector<int>> &map)
{
	if (road.size() <= 0) {
		findDefensiveRoad(map);
	}
	_direction = road[0];
	road.erase(road.begin());
	if ((_direction == 1 && pos2d.X == 0) ||
	(_direction == 3 && static_cast<std::size_t>(pos2d.X) == map.size()) ||
	(_direction == 2 && static_cast<std::size_t>(pos2d.Y) == map.size()) ||
	(_direction == 4 && pos2d.Y == 0))
		_direction = 0;
}

void Indie::Bot::move(std::vector<std::vector<int>> &map)
{
	int y = get2dy(map);
	int x = get2dx(map);

	// Passe d'un carré à l'autre
	 if (pos2d.X == y && pos2d.Y == x) {
		roadToTake(map);
		switch (_direction) {
			case 1:
				pos2d.X -= 1;
				rotation = 0;
				break;
			case 2:
				pos2d.Y += 1;
				rotation = 90;
				break;
			case 3:
				pos2d.X += 1;
				rotation = 180;
				break;
			case 4:
				pos2d.Y -= 1;
				rotation = 270;
				break;
		}
	}

	// Dans un carré
	switch (_direction) {
		case 1:
			pos3d.X += _speed;
			break;
		case 2:
			pos3d.Z -= _speed;
			break;
		case 3:
			pos3d.X -= _speed;
			break;
		case 4:
			pos3d.Z += _speed;
			break;
	}
}