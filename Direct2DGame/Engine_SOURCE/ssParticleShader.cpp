#include "ssParticleShader.h"
#include "ssRenderer.h"
#include "ssConstantBuffer.h"
#include "ssTime.h"

namespace ss::graphics
{
	ParticleShader::ParticleShader()
		: ComputeShader(128, 1, 1)
		, mParticleBuffer(nullptr)
	{
	}

	ParticleShader::~ParticleShader()
	{
	}

	void ParticleShader::Binds()
	{
		mParticleBuffer->BindUAV(0);

		mGroupX = mParticleBuffer->GetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}

	void ParticleShader::Clear()
	{
		mParticleBuffer->Clear();
	}

	void ParticleShader::SetParticleBuffer(StructedBuffer* particleBuffer)
	{
		mParticleBuffer = particleBuffer;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Particle];

		static float elapsedTime = 0.0f;
		elapsedTime += Time::DeltaTime();

		renderer::ParticleCB data = {};
		data.elementCount = mParticleBuffer->GetStride();
		data.elpasedTime = Time::DeltaTime();

		cb->SetData(&data);
		cb->Bind(eShaderStage::CS);
	}

}