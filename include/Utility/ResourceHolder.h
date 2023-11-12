#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Standard Library */
#include <iostream>
#include <map>
#include <string>

template <typename Identifier, typename Resource>
class ResourceHolder {
  private:
    std::map<Identifier, Resource*> m_resourceMap;

  public:
    ResourceHolder() 
      : m_resourceMap()
    {

    }

    ~ResourceHolder() {
      typename std::map<Identifier, Resource*>::iterator it;
      for (it = m_resourceMap.begin(); it != m_resourceMap.end(); ++it)
        delete it->second;
    }

    void load(Identifier id, const std::string& filename) {
      Resource* resource_ptr = new Resource();

      if (!resource_ptr->loadFromFile(filename))
        std::cerr << "Error loading resource " << filename << std::endl;

      m_resourceMap.insert(std::make_pair(id, resource_ptr));
    }

    const Resource& getResource(Identifier id) const {
      return *(m_resourceMap.find(id))->second;
    }

    Resource& getResource(Identifier id) {
      return *(m_resourceMap.find(id))->second;
    }
};

#endif
