#pragma once

#include "../Engine/glm/glm.hpp"
#include "../Engine/glm/gtc/matrix_transform.hpp"
#include "../Engine/glm/gtc/type_ptr.hpp"

#include <vector>

namespace engine {

	class GameObject {

		glm::vec4 m_position;
		glm::vec4 m_scale;
		glm::vec4 m_rotation;

		glm::mat4 m_transform;
		
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
		inline const glm::mat4& GetTransform() const { return m_transform; }

		void Translate(float x, float y, float z);
	};


}