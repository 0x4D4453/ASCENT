#ifndef ENTITYLIST_H
#define ENTITYLIST_H

/* Program Defined */
#include "Utility/List.h"

/* Forward Declaration */
namespace Entities { class Entity; }

class EntityList {
  private:
    List<Entities::Entity*> m_entities;
  
  public:
    EntityList();
    ~EntityList();
    void include(Entities::Entity* pEntity);
    List<Entities::Entity*>::Iterator first();
    List<Entities::Entity*>::Iterator last();
};

#endif