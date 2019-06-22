#include "GameManager.h"

Game* GameManager::createGame(Room room)
{
	std::vector<std::string> players = room.getAllUsers();
	std::map<std::string, double> players_map;
	for (auto player : players)
		players_map[player] = 0;
	return new Game(_db->getQuestions(room._question_count, room._questions_type), players_map);
}
