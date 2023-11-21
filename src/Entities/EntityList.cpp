/* Main Include */
#include "Entities/EntityList.h"

/* Program Defined */
#include "Entities/Entity.h"

/* Standard Library */
#include <iostream>

EntityList::EntityList()
  : m_entities()
{

}

EntityList::~EntityList() {

}

void EntityList::include(Entities::Entity* pEntity) {
  if (!pEntity) {
    std::cerr << "Error adding entity to the list!\n";
    return;
  }

  m_entities.pushBack(pEntity);
}

void EntityList::remove(Entities::Entity* pEntity) {
  m_entities.remove(pEntity);
}

List<Entities::Entity*>::Iterator EntityList::first() {
  return m_entities.getHead();
}

List<Entities::Entity*>::Iterator EntityList::last() {
  return NULL;
}