#pragma once
#include "Logic/Databases/IGraphicDatabaseAPI.h"
#include "AudioSystem/Database/IAudioDatabaseAPI.h"

namespace logic
{

class IDatabase:	public IGraphicDatabaseAPI,
					public audios::database::IAudioDatabaseAPI
{
public:
	virtual void LoadResource() = 0;
};

} // namespace logic