#pragma once

#include "Component.h"


namespace engine {

	class MeshComponent : public Component {

		//should be in meshdata with sp info
		unsigned int VAO, VBO, EBO;

		class MeshData* m_meshdata;
		class ShaderProgram* m_shaderprogram;

	public:

		MeshComponent(class MeshData* md, class ShaderProgram* sp);
		~MeshComponent();
	
		
		bool Init() override;
		void Update() override;
		void Draw() const override;
		bool Shutdown() override;




	};
}
