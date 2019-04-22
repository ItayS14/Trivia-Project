#include "LoginRequestHandler.h"
#include "json.hpp"

using json = nlohmann::json;

bool LoginRequestHandler::isRequestRelevant(const Request& request)
{
	return request._request_code == LOGIN || request._request_code == SIGNUP;
}

RequestResult LoginRequestHandler::handleRequest(const Request& request) {
	
	json j = json::from_msgpack(request._buffer);
	RequestResult r;
	std::string r_msg;
	//check invalid request parameters
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
		r_msg = std::to_string(SUCCESS) + "0";
		r._new_handler = _handler_factory->createLoginRequestHandler(); // later will be swapped with menu handler
	}
	catch (const std::string& err)
	{
		r_msg = std::to_string(ERROR) + std::to_string(err.length()) + err;
		r._new_handler = nullptr;
	}
	r._buffer = std::vector<std::uint8_t>(r_msg.begin(), r_msg.end());
	return r;
}