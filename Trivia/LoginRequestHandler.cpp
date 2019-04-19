#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(const Request& request)
{
	return request._request_code == LOGIN || request._request_code == SIGNUP;
}
