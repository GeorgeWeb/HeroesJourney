#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "ECM.hpp"

#include <map>

namespace Engine { namespace ECM {

	// A very simple, kinda like holder/storage class for entity objects
	class EntityManager final
	{
		/** IMPORTANT !!!
		 ** If an entity existing in the global container but not in the scene's local one, needs to be rendered or updated
		 ** inisde a particular scene, then access it using Find and add it to the local container using AddEntity (in the Init func)
		**/

		public:
			EntityManager() = default;
			~EntityManager() = default;

			bool Exists(const std::string& t_name)
			{
				return m_entities.find(t_name) != m_entities.end();
			}

			std::shared_ptr<Entity> GetSharedEntity(const std::string& t_name)
			{
				if (!Exists(t_name))
				{
					throw("The entity you are trying to access does not exist! ");
				}
				else
				{
					return m_entities[t_name];
				}
			}

			template<class T>
			T* Find(const std::string& t_name)
			{
				static_assert(std::is_base_of<Entity, T>::value, "must be an entity");

				if (!Exists(t_name))
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
				if (t_entity == nullptr)
					throw("The entity you are trying to access is not initialised! ");
				else ///> assigns new value to the mapped object or construct a new one
					m_entities.insert_or_assign(t_name, t_entity);
			}

			void Remove(const std::string& t_name)
			{
				if (!Exists(t_name))
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

			void Render(std::map<std::string, std::shared_ptr<Entity>> t_entities)
			{
				// Reversed traversal!!! (fixes past issues with how layers were rendered)
				// [!] This is more like C++03/11 style, but does the job... well at the moment.
				// TODO: Possibly.., optimize and clean to look neater, using more modern C++!

				auto entities = m_entities;
				for (auto it1 = entities.rbegin(); it1 != entities.rend(); ++it1)
				{
					auto& entityName = it1->first;
					auto& entityObject = it1->second;
					
					// Check if the entity is contained in the scene's local container
					// and decide it's visibility based on the return value of the check.
					entityObject->SetVisible(
						t_entities.find(entityName) != t_entities.end()
						&& t_entities[entityName]->IsVisible()
					);
					
					auto& entityComponents = entityObject->GetComponents();
					// Render those that are visible
					for (auto it2 = entityComponents.rbegin(); it2 != entityComponents.rend(); ++it2)
					{
						auto& componentName = it2->first;
						auto& componentObject = it2->second;
						componentObject->Render();
					}
				}
			}

			void Update(std::map<std::string, std::shared_ptr<Entity>> t_entities, float t_deltaTime)
			{
				for (auto& ent : m_entities)
				{
					auto& entityName = ent.first;
					auto& entityObject = ent.second;
					
					// Check if the entity is contained in the scene's local container
					// and decide it's visibility based on the return value of the check.
					entityObject->SetAlive(
						t_entities.find(entityName) != t_entities.end()
						&& t_entities[entityName]->IsAlive()
					);

					// Update those that are alive
					entityObject->Update(t_deltaTime);
				}
			}

		private:
			std::map<std::string, std::shared_ptr<Entity>> m_entities;
	};

} }

#endif // !ENTITY_MANAGER_H