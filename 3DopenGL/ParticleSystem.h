#pragma once
#include "Libs.h"

struct ParticleProps
{
	glm::vec3 Position;
	glm::vec3 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 5.0f;
};

class ParticleSystem
{
public:
	ParticleSystem();

	void OnUpdate(float dt);
	void OnRender(float dt);

	void Emit(const ParticleProps& particleProps);
private:
	struct Particle
	{
		//Pyramid pyramid = Pyramid();

		Model* model;

		glm::vec3 Position;
		glm::vec3 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 5.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 39;
};