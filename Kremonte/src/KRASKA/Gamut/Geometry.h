#pragma once

#include "Kremonte/krpch.h"
#include <glm/glm.hpp>
#include <cstdint>
#include <cmath>
#include <vector>

namespace KRASKA {

#ifdef WIP

	class Geometry {

	public:
		struct Vertex {

			glm::vec3 position;
			glm::vec3 normal;
			glm::vec3 tangent;
			glm::vec3 bittangent;

		};

		Geometry();
		Geometry(std::vector<Vertex> vertices, std::vector<uint16_t> indices16, std::vector<uint32_t> indices32);
		Geometry Icosahedron(bool flat);
		Geometry Icosphere(float radius, uint32_t subdivisions, bool flat);

	private:
		std::vector<Vertex> _vertices;
		std::vector<uint16_t> _indices16;
		std::vector<uint32_t> _indices32;

		struct TriangleIndices {
			const int i1;
			const int i2;
			const int i3;
		};

		int generateSubdividedVertex(int index1, int index2, std::vector<glm::vec3>& vertices);

	};

#endif
}