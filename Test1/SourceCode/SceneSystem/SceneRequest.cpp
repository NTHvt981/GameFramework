#include "SceneRequest.h"

list<LPSceneRequest> CSceneRequest::RequestList = list<LPSceneRequest>();

CSceneRequest::CSceneRequest(SCENE_REQUEST_TYPES t)
{
	Type = t;
}

void CSceneRequest::AddRequest(LPSceneRequest re)
{
	CSceneRequest::RequestList.push_back(re);
}