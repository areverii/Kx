#include "Geometry.h"

namespace KRASKA {

#ifdef WIP

	Geometry::Geometry() {

	}

	Geometry::Geometry(std::vector<Vertex> vertices, std::vector<uint16_t> indices16, std::vector<uint32_t> indices32)
	{
		std::copy(vertices.begin(), vertices.end(), back_inserter(_vertices));
		std::copy(indices16.begin(), indices16.end(), back_inserter(_indices16));
		std::copy(indices32.begin(), indices32.end(), back_inserter(_indices32));
	}

	Geometry Geometry::Icosahedron(bool flat) {
		return Icosphere(0.5f, 0, flat);
	}
	
	Geometry Geometry::Icosphere(float radius, uint32_t subdivisions, bool flat) {
		
		std::vector<glm::vec3> vertices;
		std::vector<TriangleIndices> faces;

		// Vertices
		float t = (1.0f + std::sqrt(5.0f)) / 2.0f;

		// XY plane
		vertices.push_back(glm::normalize(glm::vec3(-1.0f, t, 0.0f)));
		vertices.push_back(glm::normalize(glm::vec3(1.0f, t, 0.0f)));
		vertices.push_back(glm::normalize(glm::vec3(-1.0f, -t, 0.0f)));
		vertices.push_back(glm::normalize(glm::vec3(1.0f, -t, 0.0f)));
		// YZ plane
		vertices.push_back(glm::normalize(glm::vec3(0.0f, -1.0f, t)));
		vertices.push_back(glm::normalize(glm::vec3(0.0f, 1.0f, t)));
		vertices.push_back(glm::normalize(glm::vec3(0.0f, -1.0f, -t)));
		vertices.push_back(glm::normalize(glm::vec3(0.0f, 1.0f, -t)));
		// XZ plane
		vertices.push_back(glm::normalize(glm::vec3(t, 0.0f, -1.0f)));
		vertices.push_back(glm::normalize(glm::vec3(t, 0.0f, 1.0f)));
		vertices.push_back(glm::normalize(glm::vec3(-t, 0.0f, -1.0f)));
		vertices.push_back(glm::normalize(glm::vec3(-t, 0.0f, 1.0f)));

		// Icosahedron faces
		// 5 faces around point 0
		faces.push_back(TriangleIndices{ 0, 5, 11 });
		faces.push_back(TriangleIndices{ 0, 1, 5 });
		faces.push_back(TriangleIndices{ 0, 7, 1 });
		faces.push_back(TriangleIndices{ 0, 10, 7 });
		faces.push_back(TriangleIndices{ 0, 11, 10 });
		// 5 adjacent faces
		faces.push_back(TriangleIndices{ 1, 9, 5 });
		faces.push_back(TriangleIndices{ 5, 4, 11 });
		faces.push_back(TriangleIndices{ 11, 2, 10 });
		faces.push_back(TriangleIndices{ 10, 6, 7 });
		faces.push_back(TriangleIndices{ 7, 8, 1 });
		// 5 faces around point 3
		faces.push_back(TriangleIndices{ 3, 4, 9 });
		faces.push_back(TriangleIndices{ 3, 2, 4 });
		faces.push_back(TriangleIndices{ 3, 6, 2 });
		faces.push_back(TriangleIndices{ 3, 8, 6 });
		faces.push_back(TriangleIndices{ 3, 9, 8 });
		// 5 adjacent faces
		faces.push_back(TriangleIndices{ 4, 5, 9 });
		faces.push_back(TriangleIndices{ 2, 11, 4 });
		faces.push_back(TriangleIndices{ 6, 10, 2 });
		faces.push_back(TriangleIndices{ 8, 7, 6 });
		faces.push_back(TriangleIndices{ 9, 1, 8 });

		for (int i = 0; i < subdivisions; i++)
		{
			std::vector<TriangleIndices> subdividedFaces;
			for (auto &face : faces)
			{
				// Generate midpoints between vertices
				int a = generateSubdividedVertex(face.i1, face.i2, vertices);
				int b = generateSubdividedVertex(face.i2, face.i3, vertices);
				int c = generateSubdividedVertex(face.i3, face.i1, vertices);

				// Subdivide each face with 4 new faces
				subdividedFaces.push_back(TriangleIndices{ face.i1, a, c });
				subdividedFaces.push_back(TriangleIndices{ face.i2, b, a });
				subdividedFaces.push_back(TriangleIndices{ face.i3, c, b });
				subdividedFaces.push_back(TriangleIndices{ a, b, c });
			}
			std::copy(subdividedFaces.begin(), subdividedFaces.end(), back_inserter(faces));
		}
		
		// Scale by radius
		for (int i = 0; i < vertices.size(); i++) {
			vertices.at(i) *= radius;
		}
		std::vector<Vertex> assembledVertices;
		std::vector<uint16_t> indices16;
		std::vector<uint32_t> indices32;

		KR_INFO("about to enter flat check");
		if (flat)
		{
			//Vertex assembledVertices[faces.size() * 3];
			
			//uint16_t indices16[faces.size() * 3];
			//uint32_t indices32[faces.size() * 3];

			for (int i = 0; i < faces.size(); i++)
			{
				glm::vec3 v1 = vertices.at(faces.at(i).i1);
				glm::vec3 v2 = vertices.at(faces.at(i).i2);
				glm::vec3 v3 = vertices.at(faces.at(i).i3);
				glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v2 - v3));

				//assembledVertices[3 * i] = Vertex(v1, normal, Colour.White, UV.Zero);
				//assembledVertices[3 * i + 1] = Vertex(v2, normal, Colour.White, UV.Zero);
				//assembledVertices[3 * i + 2] = Vertex(v3, normal, Colour.White, UV.Zero);
				assembledVertices.at(3 * i) = Vertex{ v1, normal };
				assembledVertices.at(3 * i + 1) = Vertex{ v2, normal };
				assembledVertices.at(3 * i + 2) = Vertex{ v3, normal };

				indices16.at(3 * i) = (uint16_t)(3 * i);
				indices16.at(3 * i + 1) = (uint16_t)(3 * i + 1);
				indices16.at(3 * i + 2) = (uint16_t)(3 * i + 2);

				indices32.at(3 * i) = (uint32_t)(3 * i);
				indices32.at(3 * i + 1) = (uint32_t)(3 * i + 1);
				indices32.at(3 * i + 2) = (uint32_t)(3 * i + 2);
			}

			return Geometry(assembledVertices, indices16, indices32);
		}
		else
		{
			//Vertex assembledVertices[vertices.Count];
			//uint16_t indices16[faces.Count * 3];
			//uint32_t indices32[faces.Count * 3];

			for (int i = 0; i < faces.size(); i++)
			{
				indices16.at(3 * i) = (uint16_t)faces.at(i).i1;
				indices16.at(3 * i + 1) = (uint16_t)faces.at(i).i2;
				indices16.at(3 * i + 2) = (uint16_t)faces.at(i).i3;

				indices32.at(3 * i) = (uint32_t)faces.at(i).i1;
				indices32.at(3 * i + 1) = (uint32_t)faces.at(i).i2;
				indices32.at(3 * i + 2) = (uint32_t)faces.at(i).i3;
			}

			for (int i = 0; i < assembledVertices.size(); i++)
				//assembledVertices[i] = Vertex{ vertices[i], vertices[i].Normalized, Colour.White, UV.Zero };
				assembledVertices.at(i) = Vertex{ vertices.at(i), glm::normalize(vertices.at(i)) };

			return Geometry(assembledVertices, indices16, indices32);
		}
	}

	// HELPER: subdivide by faces
	int Geometry::generateSubdividedVertex(int index1, int index2, std::vector<glm::vec3>& vertices) {
		vertices.push_back((glm::normalize((vertices.at(index1) + vertices.at(index2)) * 0.5f)));

		return vertices.size() - 1;
	}


#endif

}