#pragma once

#include <glm/glm.hpp>
#include <cstdint>

namespace KRASKA {

	class Geometry {

	public:
		struct Vertex {

			glm::vec3 position;
			glm::vec3 normal;
			glm::vec3 tangent;
			glm::vec3 bittangent;

		};

		void Icosphere(float radius, uint32_t subdivisions, bool flat);



	};
}