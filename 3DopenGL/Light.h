#pragma once

#include "Libs.h"

class Light
{
protected:
	float intensity;
	glm::vec3 color;

public:
	Light(float intensity, glm::vec3 color)
	{
		this->intensity = intensity;
		this->color = color;
	}

	~Light()
	{

	}

	//Functions
	virtual void sendToShader(Shader& program) = 0;
};


class PointLight : public Light
{
protected:
	//glm::vec3 position[4] = { glm::vec3(0.f,0.f,0.f), glm::vec3(4.f,0.f,4.f), glm::vec3(-4.f,0.f,-4.f), glm::vec3(2.f,3.f,2.f)};
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;

public:
	PointLight(glm::vec3 position, float intensity = 1.f, glm::vec3 color = glm::vec3(1.f,0.f,0.f),
		float constant = 1.f, float linear = 0.045f, float quadratic = 0.0075f)
		: Light(intensity, color)
	{
		this->position = position;
		
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}

	~PointLight()
	{
	  
	}

	void setPosition(glm::vec3 position)
	{
		this->position = position;
	}

	void sendToShader(Shader& program)
	{
		program.setVec3f(this->position, "pointLight[0].position");
		program.set1f(this->intensity, "pointLight[0].intensity");
		program.setVec3f(this->color, "pointLight[0].color");
		program.set1f(this->constant, "pointLight[0].constant");
		program.set1f(this->linear, "pointLight[0].linear");
		program.set1f(this->quadratic, "pointLight[0].quadratic");

		program.setVec3f(glm::vec3(4.f, 0.f, 4.f), "pointLight[1].position");
		program.set1f(this->intensity, "pointLight[1].intensity");
		program.setVec3f(this->color, "pointLight[1].color");
		program.set1f(this->constant, "pointLight[1].constant");
		program.set1f(this->linear, "pointLight[1].linear");
		program.set1f(this->quadratic, "pointLight[1].quadratic");
	}
};