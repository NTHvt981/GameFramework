#include "GameRequest.h"

list<LPGameRequest> CGameRequest::RequestList = list<LPGameRequest>();

CGameRequest::CGameRequest(GAME_REQUEST_TYPES t)
{
	Type = t;
}

void CGameRequest::AddRequest(LPGameRequest re)
{
	CGameRequest::RequestList.push_back(re);
}
