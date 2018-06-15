#pragma once

#include "Resource.h"
#include <vector>

namespace engine {

	class MeshData : Resource {
		
		std::vector<float> m_vertices;
		std::vector<int> m_indices;

	public:
		MeshData(const std::vector<float> vertices, const std::vector<int>& indices);
		~MeshData();

		bool Init() override;
		bool Shutdown() override;

		inline std::vector<float> GetVertices() const { return m_vertices; }
		inline std::vector<int> GetIndices() const { return m_indices; }
	};
}