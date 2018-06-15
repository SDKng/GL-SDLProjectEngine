#include "GameObject.h"
#include "Component.h"

namespace engine {

	GameObject::GameObject() :
		m_position(0.0f, 0.0f, 0.0f, 1.0f),
		m_scale(1.0f, 1.0f, 1.0f, 1.0f),
		m_rotation(0.0f, 0.0f, 0.0f, 0.0f),
		m_transform(1.0f)
	{



	}

	GameObject::~GameObject() {



	}

	bool GameObject::Init() {
	
		return true;
	}

	void GameObject::Update() {

		// make the object move by itself
		/*m_transform = glm::translate(m_transform, glm::vec3(0.0001f, 0.0f, 0.0f));*/
		
		for (Component* c : m_components) {

			c->Update();
		}
		for (GameObject* c : m_children) {

			c->Update();
		}
	}

	void GameObject::Draw() const {

		for (Component* c : m_components) {

			c->Draw();
		}
		for (GameObject* c : m_children) {

			//program doesnt hit here
			c->Draw();
		}
	}

	bool GameObject::Shutdown() {

		return true;
	}

	void GameObject::AddChildObject(GameObject* go) {

		m_children.push_back(go);
	}

	//inline std::vector<GameObject*> GetChildren() const { return m_children; };

	void GameObject::AddConponent(class Component* c) {

		c->SetParent(this);
		m_components.push_back(c);
	}

	void GameObject::Translate(float x, float y, float z) {

		m_transform = glm::translate(m_transform, glm::vec3(x, y, z));
	}

};


