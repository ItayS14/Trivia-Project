#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(const Request& request)
{
	return request._request_code == LOGIN || request._request_code == SIGNUP;
}

RequestResult LoginRequestHandler::handleRequest(const Request& request) {
	switch (request._request_code)
	{
	case LOGIN:
		login(request);
		break;
	case SIGNUP:
		signup(request);
		break;
	}
}