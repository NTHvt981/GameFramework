#pragma once
#include "ITransformComponent.h"
#include <memory>
#include <vector>

namespace logic
{

class TransformComponent final: public ITransformComponent
{
public:
	TransformComponent(const core::Vector2F i_position = core::Vector2F());
	void SetPosition(core::Vector2F i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override {};
	void Deregister() override {};

private:
	core::Vector2F m_position;
};

} // namespace logic