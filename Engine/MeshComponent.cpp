
#include "MeshComponent.h"
#include "ShaderProgram.h"
#include "MeshData.h"
#include "GL/glew.h"
#include "GameObject.h"
#include "..\Engine\stbimage\Texture.h"

#include "../Engine/glm/glm.hpp"
#include "../Engine/glm/gtc/matrix_transform.hpp"
#include "../Engine/glm/gtc/type_ptr.hpp"

namespace engine {

	MeshComponent::MeshComponent(MeshData* md, ShaderProgram* sp, class Texture* tex) :
		m_meshdata(md), m_shaderprogram(sp), m_texture(tex)
	{


	}

	MeshComponent::~MeshComponent() {

		glDeleteVertexArrays(1, &VAO);
		glDeleteVertexArrays(1, &VBO);
		glDeleteVertexArrays(1, &EBO);


	}

	bool MeshComponent::Init()  {

		//creating buffers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_meshdata->GetVertices()[0]) * m_meshdata->GetVertices().size(),
											m_meshdata->GetVertices().data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_meshdata->GetIndices()[0]) * m_meshdata->GetIndices().size(),
											m_meshdata->GetIndices().data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 *sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		
		m_texture->Init();
		glUniform1i(glGetUniformLocation(m_shaderprogram->GetID(), "texture1"), 0);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return true;
	}
	void MeshComponent::Update()  {

		unsigned int transformLoc = glGetUniformLocation(m_shaderprogram->GetID(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(m_parent->GetTransform()));

	}
	void MeshComponent::Draw() const {


		m_shaderprogram->Use();
		m_texture->Use();
	
		/*glBindTexture(GL_TEXTURE_2D, m_texture->GetID());*/
		
		//draw some triangles

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}
	bool MeshComponent::Shutdown()  {


		return true;
	};
}