#include "GameRequestHandler.h"
#include "Helper.h"

bool GameRequestHandler::isRequestRelevant(const Request& request)
{
	return request._request_code == LEAVE_GAME || request._request_code == GET_QUESTION || request._request_code == SUBMIT_ANSWER || request._request_code == GET_LEADERBOARD;
}

RequestResult GameRequestHandler::handleRequest(const Request& request)
{
	RequestResult r;
	std::string r_msg = std::to_string(SUCCESS);
	try
	{
		json j = json::parse(request._buffer);
		json result_j;
		std::string data;
		switch (request._request_code)
		{
		case LEAVE_GAME:
		{
			leave();
			r._new_handler = _factory->createMenuRequestHandler(_logged_user);
			break;
		}
		case GET_QUESTION:
		{
			Question* question = _game->getQuestionAt(_question);
			result_j["question"] = question->_question;
			result_j["answers"] = question->_answers;
			data = result_j.dump();
			r._new_handler = this;
			break;
		}
		case SUBMIT_ANSWER:
		{
			_game->addScore(_logged_user, _question, j.at("index"));
			result_j["correct_ans"] = _game->getQuestionAt(_question++)->_correct_ans;
			result_j["score"] = _game->getScore(_logged_user);
			data = result_j.dump();
			r._new_handler = this;
			break;
		}
		case GET_LEADERBOARD:
		{
			result_j = _game->getLeaderBoard();
			data = result_j.dump();
			r._new_handler = this;
		}
		}
		r_msg += Helper::getPaddedNumber(data.length(), SIZE_DIGIT_COUNT);
		r_msg += data;
	}
	catch (const std::string& err)
	{
		r_msg = std::to_string(ERROR_MSG) + Helper::getPaddedNumber(err.length(), SIZE_DIGIT_COUNT) + err;
		r._new_handler = nullptr;
	}
	catch (const std::exception& err)
	{
		std::string err_msg = err.what();
		r_msg = std::to_string(ERROR_MSG) + Helper::getPaddedNumber(err_msg.length(), SIZE_DIGIT_COUNT) + err_msg;
	}

	r._buffer = std::vector<std::uint8_t>(r_msg.begin(), r_msg.end());
	return r;
}

void GameRequestHandler::leave()
{
	_game->removePlayer(_logged_user);
	_room_manager->getRoom(_game->getId())->removeUser(_logged_user);
	if (_game->getNumberOfLoggedPlayers() == 0)
	{
		_room_manager->deleteRoom(_game->getId());
		_game_manager->deleteGame(_game->getId());
	}
}

void GameRequestHandler::handleSocketError()
{
	leave();

	MenuRequestHandler* temp = _factory->createMenuRequestHandler(_logged_user); // no need for RoomRequestHandler becuase the game handeles also the room socket error
	temp->handleSocketError();
	delete temp;
}