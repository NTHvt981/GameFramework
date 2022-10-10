#pragma once
#include "Core/DataTypes/Iterator.h"
#include <cstdint>

namespace core
{

enum class SoundId : uint64_t
{
	SoundTrack,
	BlasterMasterSFX1,
	BlasterMasterSFX2,
	BlasterMasterSFX3,
	BlasterMasterSFX4,
	BlasterMasterSFX5,
	BlasterMasterSFX6,
	BlasterMasterSFX7,
	BlasterMasterSFX8,
	BlasterMasterSFX9,
	BlasterMasterSFX10,
	BlasterMasterSFX11,
	BlasterMasterSFX12,
	BlasterMasterSFX13,
	BlasterMasterSFX14,
	BlasterMasterSFX15,
	BlasterMasterSFX16,
	BlasterMasterSFX17,
	BlasterMasterSFX18,
	BlasterMasterSFX19,
	BlasterMasterSFX20,
	BlasterMasterSFX21,
	BlasterMasterSFX22,
	BlasterMasterSFX23,
	BlasterMasterSFX24,
	BlasterMasterSFX25,
	BlasterMasterSFX26,
	BlasterMasterSFX27,
	BlasterMasterSFX28,
	BlasterMasterSFX29,
	BlasterMasterSFX30,
	BlasterMasterSFX31,
	BlasterMasterSFX32,
	BlasterMasterSFX33,
	BlasterMasterSFX34,
	BlasterMasterSFX35,
	BlasterMasterSFX36,
	BlasterMasterSFX37
};

using SoundIdIterators = Iterator<SoundId, SoundId::SoundTrack, SoundId::BlasterMasterSFX37>;

} // namespace core