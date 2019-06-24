#include "GameManager.h"


GameManager::~GameManager()
{
	for (auto& pair : _games)
		delete pair.second;
}

void GameManager::createGame(Room* room)
{
	std::vector<std::string> players = room->getAllUsers();
	std::map<std::string, double> players_map;
	for (auto player : players)
		players_map[player] = 0;
	std::lock_guard<std::mutex> lck(_mtx);
	_games[room->_id] =  new Game(_db->getQuestions(room->_question_count, room->_questions_type), players_map, room->_id);
}

void GameManager::deleteGame(unsigned int id)
{
	std::lock_guard<std::mutex> lck(_mtx);
	auto iterator = _games.find(id);
	if (iterator == _games.end())
		throw std::string("Game not found");
	delete (*iterator).second;
	_games.erase(iterator);
}

Game* GameManager::getGame(unsigned int id)
{
	std::lock_guard<std::mutex> lck(_mtx);
	if (_games.find(id) == _games.end())
		throw std::string("Room not found");
	return _games[id];
}