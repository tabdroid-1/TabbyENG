#include "Entity.h"
#include "tbpch.h"

namespace Tabby {

Entity::Entity(entt::entity handle, Scene* scene)
    : m_EntityHandle(handle)
    , m_Scene(scene)
{
}

}
