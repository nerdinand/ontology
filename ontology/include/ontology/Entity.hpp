//----------------------------------------------------------------------------
//Entity.hpp
//----------------------------------------------------------------------------

#ifndef __ONTOLOGY_ENTITY_HPP__
#define __ONTOLOGY_ENTITY_HPP__

//----------------------------------------------------------------------------
// include files

#include <ontology/Entity.hxx>
#include <ontology/EntityManager.hpp>
#include <ontology/Component.hpp>

namespace Ontology {

//----------------------------------------------------------------------------
template<class T, class... Args>
Entity& Entity::addComponent(Args&&... args)
{
    assert(m_ComponentMap.find(&typeid(T)) == m_ComponentMap.end());
    Component* component = new T(args...);
    m_ComponentMap[&typeid(T)] = std::unique_ptr<Component>(component);
    m_Creator->informAddComponent(*this, component);
    return *this;
}

//----------------------------------------------------------------------------
template<class T>
void Entity::removeComponent()
{
    const auto it = m_ComponentMap.find(&typeid(T));
    assert(it != m_ComponentMap.end());
    m_Creator->informRemoveComponent(*this, it->second.get());
    m_ComponentMap.erase(it);
}

//----------------------------------------------------------------------------
template<class T>
T& Entity::getComponent()
{
    const auto it = m_ComponentMap.find(&typeid(T));
    assert(it != m_ComponentMap.end());
    return *static_cast<T*>(it->second.get());
}

//----------------------------------------------------------------------------
template<class T>
const T& Entity::getComponent() const
{
    const auto it = m_ComponentMap.find(&typeid(T));
    assert(it != m_ComponentMap.end());
    return *static_cast<T*>(it->second.get());
}

} // namespace Ontology

#endif // __ONTOLOGY_ENTITY_HPP__
