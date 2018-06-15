
#include "MeshData.h"

namespace engine {

	
	MeshData::MeshData(const std::vector<float> vertices, const std::vector<int> &indices) :
		m_vertices(vertices), m_indices(indices)
	{
	
		
	
	}

	MeshData::~MeshData() {
		
		m_vertices.clear();
		m_indices.clear();
	}

	bool MeshData::Init() {
	
	
		return true;
	}

	bool MeshData::Shutdown() {
	
	
		return true;
	}
}