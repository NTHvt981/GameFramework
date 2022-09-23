#pragma once
#include "GraphicSystem/Database/IGraphicDatabaseAPI.h"

namespace database
{

class IDatabase: public graphics::database::IGraphicDatabaseAPI
{
public:
	virtual void LoadResource() = 0;

};

} // namespace database