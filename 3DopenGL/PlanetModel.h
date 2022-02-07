#pragma once

#include "PlanetMesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "OBJloader.h"

class PlanetModel
{
public:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	std::vector<PlanetMesh*> meshes;
	glm::vec3 position;

	void updateUniforms()
	{

	}

public:
	PlanetModel(glm::vec3 position, Material* material,
		Texture* orTexDif, Texture* orTexSpec,
		std::vector<PlanetMesh*>& meshes)
	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = orTexDif;
		this->overrideTextureSpecular = orTexSpec;

		for (auto* i : meshes)
		{
			this->meshes.push_back(new PlanetMesh(*i));
		}

		for (auto& i : this->meshes)
		{
			i->move(this->position);
			i->setOrigin(this->position);
		}
	}

	//OBJ file loaded model 
	PlanetModel(glm::vec3 position, Material* material,
		Texture* orTexDif, Texture* orTexSpec,
		const char* objFile)
	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = orTexDif;
		this->overrideTextureSpecular = orTexSpec;

		std::vector<Vertex> mesh = loadOBJ(objFile);
		this->meshes.push_back(new PlanetMesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)));


		for (auto& i : this->meshes)
		{
			i->move(this->position);
			i->setOrigin(this->position);
			i->rotate(glm::vec3(0.f, 180.f, 0.f));
		}
	}

	~PlanetModel()
	{
		for (auto*& i : this->meshes)
			delete i;
	}

	//Functions
	void rotate(glm::vec3 rotation)
	{
		for (auto& i : this->meshes)
			i->rotate(rotation);
	}

	void move(glm::vec3 direction)
	{
		for (auto& i : this->meshes)
			i->move(direction);
	}

	void update()
	{

	}

	void render(Shader* shader)
	{
		//Update the uniforms
		this->updateUniforms();

		//Sent uniforms to shader
		this->material->sendToShader(*shader);

		//Use a program (BECAUSE SHADER CLASS LAST UNIFORM UPDATE UNUSES IT)
		shader->use();

		//DRAW
		for (auto& i : this->meshes)
		{
			//Activate texture
			this->overrideTextureDiffuse->bind(0);
			this->overrideTextureSpecular->bind(1);

			i->render(shader); // Also activates the shader
		}
	}
};