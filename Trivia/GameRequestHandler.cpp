#include "GameRequestHandler.h"
#include "Helper.h"
bool GameRequestHandler::isRequestRelevant(const Request& request)
{
	return request._request_code == LEAVE_GAME || request._request_code == GET_QUESTION || request._request_code == SUBMIT_ANSWER || request._request_code == GET_STATISTICS;
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
			leave();
			r._new_handler = _factory->createMenuRequestHandler(_logged_user);
			break;
		case GET_QUESTION:
			Question* question = _game->getQuestionAt(j.at("number"));
			result_j["question"] = question->_question;
			result_j["answers"] = question->_answers;
			data = result_j.dump();
			r._new_handler = this;
		case SUBMIT_ANSWER:
			//add points
			result_j["correct_ans"] = _game->getQuestionAt(j.at("index"))->_correct_ans;
			result_j["score"] = _game->getScore(_logged_user);
			data = result_j.dump();
			r._new_handler = this;
		case GET_STATISTICS:
			break;
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
