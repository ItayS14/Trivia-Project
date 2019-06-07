#include "LoginRequestHandler.h"
#include "json.hpp"
#include "Helper.h"

using json = nlohmann::json;


bool LoginRequestHandler::isRequestRelevant(const Request& request)
{
	return request._request_code == LOGIN || request._request_code == SIGNUP;
}

RequestResult LoginRequestHandler::handleRequest(const Request& request) {
	
	json j = json::parse(request._buffer);
	RequestResult r;
	std::string r_msg;
	try
	{
		switch (request._request_code)
		{
		case LOGIN:
			_login_manager->login(j["username"], j["password"]);
			break;
		case SIGNUP:
			_login_manager->signup(j["username"], j["password"], j["email"]);
			break;
		}
		r_msg = std::to_string(SUCCESS) + Helper::getPaddedNumber(0, SIZE_DIGIT_COUNT);
		r._new_handler = _handler_factory->createMenuRequestHandler(j["username"]); // later will be swapped with menu handler
	}
	catch (const std::string& err)
	{
		r_msg = std::to_string(ERROR_MSG) + Helper::getPaddedNumber(err.length(), SIZE_DIGIT_COUNT) + err;
		r._new_handler = nullptr;
	}
	r._buffer = std::vector<std::uint8_t>(r_msg.begin(), r_msg.end());
	return r;
}