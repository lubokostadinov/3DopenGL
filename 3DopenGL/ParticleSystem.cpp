#include "ParticleSystem.h"
#include "Libs.h"
#include "Game.h"
#include "Random.h"

#include <gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/compatibility.hpp>

ParticleSystem::ParticleSystem()
{
	m_ParticlePool.resize(40);
	
}

void ParticleSystem::OnUpdate(float dt)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= dt;
		particle.Position += particle.Velocity * (float)dt;
		particle.Rotation += 0.01f * dt;

	}
}

void ParticleSystem::OnRender(float dt)
{

	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		// Fade away particles
		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
		//color.a = color.a * life;

		float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);

			std::vector<Mesh*> meshes;
			Quad pyramid = Quad();
			meshes.push_back(
				new Mesh(
					&pyramid,
					particle.Position,
					glm::vec3(0.f),
					glm::vec3(particle.Rotation, particle.Rotation, particle.Rotation),
					glm::vec3(0.1f)
				)
			);

			particle.model = new Model(
				particle.Position,
				Game::Get().materials[0],
				Game::Get().textures[TEX_STONE],
				Game::Get().textures[TEX_STONE_SPECULAR],
				meshes);

			for (auto*& i : meshes)
				delete i;


		// Render
		particle.model->render(Game::Get().shaders[SHADER_CORE_PROGRAM]);
	
	}
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * (Random::Float() - 0.5f);
	particle.Velocity.y += particleProps.VelocityVariation.y * (Random::Float() - 0.5f);

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}
