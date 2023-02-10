#include "ecs/component_family_base.hpp"

namespace rythe::core::ecs
{
	//void* component_family_base::createComponent(entity& ent, pointer<void> src)
	//{
	//	//m_componentData.emplace(ent.m_id, std::make_any<void*>());
	//	m_componentData.try_emplace(ent.m_id, src);
	//	return m_componentData[ent.m_id].ptr;
	//}

	//void* component_family_base::createComponent(entityId id, pointer<void> src)
	//{
	//	//m_componentData.emplace(id, std::make_any<void*>());
	//	m_componentData.try_emplace(id, src);
	//	return m_componentData[id].ptr;
	//}

	//void* component_family_base::getComponent(entity& ent)
	//{
	//	return m_componentData[ent.m_id].ptr;
	//}

	//void* component_family_base::getComponent(entityId id)
	//{
	//	return m_componentData[id].ptr;
	//}

	//void component_family_base::destroyComponent(entityId id)
	//{
	//	m_componentData.erase(id);
	//}
}