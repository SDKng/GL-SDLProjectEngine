
#include "MeshComponent.h"
#include "ShaderProgram.h"
#include "MeshData.h"
#include "GL/glew.h"

namespace engine {

	MeshComponent::MeshComponent(MeshData* md, ShaderProgram* sp) :
		m_meshdata(md), m_shaderprogram(sp)
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return true;
	}
	void MeshComponent::Update()  {



	}
	void MeshComponent::Draw() const  {

		//draw some triangles
		m_shaderprogram->Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}
	bool MeshComponent::Shutdown()  {


		return true;
	};
}