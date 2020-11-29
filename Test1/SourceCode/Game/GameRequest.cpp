#include "GameRequest.h"

list<LPRequest> CGameRequest::RequestList = list<LPRequest>();

CGameRequest::CGameRequest(REQUEST_TYPES t)
{
	type = t;
}

void CGameRequest::AddRequest(LPRequest re)
{
	CGameRequest::RequestList.push_back(re);
}
