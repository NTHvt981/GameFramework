#include "SceneRequest.h"

std::list<LPSceneRequest> CSceneRequest::RequestList = std::list<LPSceneRequest>();

CSceneRequest::CSceneRequest(SCENE_REQUEST_TYPES t)
{
	Type = t;
}

void CSceneRequest::AddRequest(LPSceneRequest re)
{
	CSceneRequest::RequestList.push_back(re);
}