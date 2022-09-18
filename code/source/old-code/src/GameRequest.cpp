#include "GameRequest.h"

std::list<LPGameRequest> CGameRequest::RequestList = std::list<LPGameRequest>();

CGameRequest::CGameRequest(GAME_REQUEST_TYPES t)
{
	Type = t;
}

void CGameRequest::AddRequest(LPGameRequest re)
{
	CGameRequest::RequestList.push_back(re);
}
