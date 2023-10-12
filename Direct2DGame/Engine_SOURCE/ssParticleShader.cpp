#include "ssParticleShader.h"
#include "ssRenderer.h"
#include "ssConstantBuffer.h"
#include "ssTime.h"

namespace ss::graphics
{
	ParticleShader::ParticleShader()
		: ComputeShader(128, 1, 1)
		, mParticleBuffer(nullptr)
		, mInitialAlpha(1.f)
	{
	}

	ParticleShader::~ParticleShader()
	{
	}

	void ParticleShader::Binds()
	{
		mParticleBuffer->BindUAV(0);
		mSharedBuffer->BindUAV(1);

		mGroupX = mParticleBuffer->GetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}

	void ParticleShader::Clear()
	{
		mParticleBuffer->Clear();
		mSharedBuffer->Clear();
	}

	void ParticleShader::SetParticleBuffer(StructedBuffer* particleBuffer)
	{
		mParticleBuffer = particleBuffer;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Particle];

		static float elapsedTime = 0.0f;
		elapsedTime += Time::DeltaTime();

		mInitialAlpha -= 0.05f * Time::DeltaTime();
		if (mInitialAlpha < 0)
			mInitialAlpha = 0;

		renderer::ParticleCB data = {};
		data.elementCount = mParticleBuffer->GetStride();
		data.elpasedTime = elapsedTime;
		data.deltaTime = Time::DeltaTime();
		data.ParticleAlpha = mInitialAlpha;

		cb->SetData(&data);
		cb->Bind(eShaderStage::CS);
		cb->Bind(eShaderStage::PS);
	}

}