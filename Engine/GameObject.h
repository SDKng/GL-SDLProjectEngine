#pragma once

#include <vector>

namespace engine {

	class GameObject {

		std::vector<GameObject*> m_children;
		
		// change this to ECS
		std::vector<class Component*> m_components;


	public:
		GameObject();
		virtual ~GameObject();

		virtual bool Init();
		virtual void Update();
		virtual void Draw() const;
		virtual bool Shutdown();

		void AddChildObject(GameObject* go);

		inline std::vector<GameObject*> GetChildren() const { return m_children; };

		void AddConponent(class Component* c);
		
		template <class T>
		T* GetComponent() const {

			for (class Componnent* c : m_components) {

				T8 comp - dynamic_cast<T*>(c);

				if (comp) return comp;

			}

			return nullptr;
		}
	
		inline std::vector<class Component*> GetComponents() const { return m_components; }
	
	};

}