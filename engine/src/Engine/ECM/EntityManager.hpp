#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "ECM.hpp"

#include <map>

namespace Engine { namespace ECM {

	// A very simple, kinda like holder/storage class for entity objects
	class EntityManager final
	{
		public:
			EntityManager() = default;
			~EntityManager() = default;			

			std::map<std::string, std::shared_ptr<Entity>> GetEntsDictionary()
			{
				return m_entities;
			}

			void PopulateEntsDictionary(std::map<std::string, std::shared_ptr<Entity>> t_ents)
			{
				for (const auto& ent : t_ents)
					Save(ent.first, ent.second);
			}
			
			template<class T>
			T* GetComponent(const std::string t_name)
			{
				static_assert(std::is_base_of<Component, T>::value, "must be a component");
				// ... checks
				return dynamic_cast<T*>(m_components[t_name]->GetType());
			}

			template<class T>
			T* Find(const std::string& t_name)
			{
				static_assert(std::is_base_of<Entity, T>::value, "must be an entity");

				if (m_entities.find(t_name) == m_entities.end())
				{
					throw("The entity you are trying to access does not exist! ");
				}
				else
				{
					if (m_entities[t_name] == nullptr)
						throw("The entity you are trying to access is not initialised! ");
					else
						return dynamic_cast<T*>(m_entities[t_name]->GetType());
				}
			}

			void Save(const std::string& t_name, std::shared_ptr<Entity> t_entity)
			{
				if (m_entities.find(t_name) == m_entities.end())
				{
					if (t_entity == nullptr)
						throw("The entity you are trying to access is not initialised! ");
					else
						m_entities[t_name] = t_entity;
				}
			}
			
			bool Exists(const std::string& t_name)
			{
				return (m_entities.find(t_name) == m_entities.end());
			}

			void Remove(const std::string& t_name)
			{
				if (m_entities.find(t_name) == m_entities.end())
				{
					throw("The entity you are trying to access does not exist! ");
				}
				else
				{
					if (m_entities[t_name] == nullptr)
						throw("There's an error with this entity! ");
					else
						m_entities.erase(t_name);
				}
			}

			void Render()
			{
				// Reversed traversal!!! (had issues with how they were rendered before)
				// This is more like C++03/11 style, but does the job very well at the moment.
				// TODO: Possibly.., optimize and clean to look neater, using more modern C++!
				
				auto entities = m_entities;
				for (auto it1 = entities.rbegin(); it1 != entities.rend(); ++it1)
				{
					auto& entityName = it1->first;
					auto& components = it1->second->GetCompsDictionary();
					for (auto it2 = components.rbegin(); it2 != components.rend(); ++it2)
					{
						if (it2->second == nullptr)
							throw("There's an error with this entity! ");
						else
						{
							auto& componentName = it2->first;
							auto& componentType = it2->second;
							componentType->Render();
						}
					}
				}
			}

			void Update(float t_deltaTime)
			{
				for (const auto& ent : m_entities)
				{
					if (ent.second == nullptr)
						throw("There's an error with this entity! ");
					else
						ent.second->Update(t_deltaTime);
				}
			}

		private:
			std::map<std::string, std::shared_ptr<Entity>> m_entities;
	};

} }

#endif // !ENTITY_MANAGER_H