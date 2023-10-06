#pragma once
#include <vector>

#include <assimp/scene.h>

#include "core/math/math.hpp"
#include "core/logging/logging.hpp"

#include "rendering/data/vertex.hpp"


namespace rythe::rendering
{
	struct sub_mesh
	{
		std::string name;
		rsl::size_type count;
		rsl::size_type offset;
		rsl::int32 materialIdx;
	};

	struct mesh
	{
		std::vector<math::vec4> vertices;
		std::vector<math::vec4> colors;
		std::vector<math::vec3> normals;
		std::vector<math::vec2> texCoords;
		std::vector<unsigned int> indices;
		//std::vecotr<material_data> materials;
		std::vector<sub_mesh> submeshes;

		mesh() = default;
		mesh(const mesh& msh) : vertices(msh.vertices), colors(msh.colors), normals(msh.normals), texCoords(msh.texCoords), indices(msh.indices), submeshes(msh.submeshes) {}
		mesh(const aiScene* scene)
		{
			initialize(scene);
		}

		void initialize(const aiScene* scene)
		{
			if (!scene->HasMeshes())
			{
				log::error("The scene we tried to load did not contain any meshes, curious");
				return;
			}
			//Currently only supporting single meshes, i'll figure out how to do submeshes later
			auto mesh = scene->mMeshes[0];
			log::debug("Mesh Count:{}", scene->mNumMeshes);

			if (mesh->HasPositions())
			{
				auto s_vertices = mesh->mVertices;
				auto posCount = mesh->mNumVertices;

				for (int i = 0; i < posCount; i++)
				{
					vertices.push_back(math::vec4(s_vertices[i].x, s_vertices[i].y, s_vertices[i].z, 1.0f));
				}
			}
			else
				log::error("The mesh we tried to load does not contain any vertices, curious");

			if (mesh->HasVertexColors(0))
			{
				auto s_colors = mesh->mColors[0];
				auto posCount = mesh->mNumVertices;


				for (int i = 0; i < posCount; i++)
				{
					colors.push_back(math::vec4(s_colors[i].r, s_colors[i].g, s_colors[i].b, s_colors[i].a));
				}
			}


			if (mesh->HasFaces())
			{

				auto numFaces = mesh->mNumFaces;

				for (int i = 0; i < numFaces; i++)
				{
					auto indexCount = mesh->mFaces[i].mNumIndices;
					auto s_indices = mesh->mFaces[i].mIndices;
					for (int j = 0; j < indexCount; j++)
					{
						indices.push_back(s_indices[j]);
					}
				}
			}


		}
	};
}