#pragma once
#include "Logic/Databases/IGraphicDatabaseAPI.h"
#include "AudioSystem/Database/IAudioDatabaseAPI.h"

namespace database
{

class IDatabase:	public graphics::database::IGraphicDatabaseAPI,
					public audios::database::IAudioDatabaseAPI
{
public:
	virtual void LoadResource() = 0;
};

} // namespace database