#include "GameObject.h"
#include "Component.h"

namespace engine {

	GameObject::GameObject() {



	}

	GameObject::~GameObject() {



	}

	bool GameObject::Init() {
	
		return true;
	}

	void GameObject::Update() {

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

		m_components.push_back(c);
	}

};


