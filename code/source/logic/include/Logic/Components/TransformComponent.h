#pragma once
#include "ITransformComponent.h"
#include <vector>

namespace logic
{

static constexpr core::ComponentKey sk_transformComponentKey = "TransformComponent";

class TransformComponent final: public ITransformComponent
{
public:
	TransformComponent();
	void SetPosition(core::Vector2F i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override {};
	void Deregister() override {};

private:
	core::Vector2F m_position;
};

} // namespace logic