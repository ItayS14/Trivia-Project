#include "LoginRequestHandler.h"
#include "json.hpp"
#include "Helper.h"

using json = nlohmann::json;


bool LoginRequestHandler::isRequestRelevant(const Request& request)
{
	return request._request_code == LOGIN || request._request_code == SIGNUP;
}

RequestResult LoginRequestHandler::handleRequest(const Request& request) {
	
	RequestResult r;
	std::string r_msg;
	try
	{
		json j = request._buffer.size() == 0 ? nullptr : json::parse(request._buffer);
		switch (request._request_code)
		{
		case LOGIN:
			_login_manager->login(j.at("username"), j.at("password"));
			r._new_handler = _handler_factory->createMenuRequestHandler(j["username"]);
			break;
		case SIGNUP:
			_login_manager->signup(j.at("username"), j.at("password"), j.at("email"));
			r._new_handler = this;
			break;
		}
		r_msg = std::to_string(SUCCESS) + Helper::getPaddedNumber(0, SIZE_DIGIT_COUNT);
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