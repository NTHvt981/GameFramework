#pragma once
#include "ITransformComponent.h"
#include <memory>
#include <vector>
#include <list>

namespace logic
{

/// <summary>
/// Contain multiple components
/// </summary>
class TransformCompositionComponent final: public ITransformComponent
{
public:
	TransformCompositionComponent(std::initializer_list<std::shared_ptr<ITransformComponent>> i_children);

	// Inherited via Component
	void SetPosition(core::Vector2F i_position) override;
	virtual core::Vector2F GetPosition() const override;
	void Register() override {};
	void Deregister() override {};

	void InsertComponent(std::shared_ptr<ITransformComponent> i_component);
	void RemoveComponent(std::shared_ptr<ITransformComponent> i_component);

private:
	std::list<std::shared_ptr<ITransformComponent>> m_children;
};


} // namespace logic