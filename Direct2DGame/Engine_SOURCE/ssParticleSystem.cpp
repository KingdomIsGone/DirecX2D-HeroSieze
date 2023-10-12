#include "ssParticleSystem.h"
#include "ssTime.h"
#include "ssMesh.h"
#include "ssMaterial.h"
#include "ssResources.h"
#include "ssTransform.h"
#include "ssGameObject.h"
#include "ssConstantBuffer.h"
#include "ssRenderer.h"

namespace ss
{
	ParticleSystem::ParticleSystem()
		: mCount(0)
		, mStartSize(Vector4::One)
		, mEndSize(Vector4::One)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mLifeTime(0.0f)
		, mTime(0.0f)
		, mAlpha(1.f)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);

		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		mParticleShader = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		Particle particles[1000] = {};
		for (size_t i = 0; i < 1000; i++)
		{
			Vector4 pos = Vector4::Zero;

			particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)1000))
					, sinf((float)i * (XM_2PI / 100.f))
					, 0.0f, 1.0f);

			particles[i].position = pos;
			particles[i].speed = 1.0f;
			particles[i].active = 0;
			particles[i].time = 0;

			particles[i].direction.x = 1.0f;
			particles[i].direction.y = (rand() % 3) +1;
		}

		mParticleStructBuffer = new graphics::StructedBuffer();
		mParticleStructBuffer->Create(sizeof(Particle), 1000, eViewType::UAV, particles);

		mSharedBuffer = new graphics::StructedBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);

		SetTexture(Resources::Find<Texture>(L"..\\Resources\\particle\\CartoonSmoke.png"));
	}
	ParticleSystem::~ParticleSystem()
	{
		delete mSharedBuffer;
		delete mParticleStructBuffer;
	}
	void ParticleSystem::Initialize()
	{
	}
	void ParticleSystem::Update()
	{
	}
	void ParticleSystem::LateUpdate()
	{
		float AliveTime = 0.2f / 1.0f;
		mTime += Time::DeltaTime();

		mAlpha -= 0.6f * Time::DeltaTime();

		if (mTime > AliveTime)
		{
			float f = (mTime / AliveTime);
			//UINT AliveCount = (UINT)f;
			mTime = f - floor(f);

			ParticleShared shareData = {};
			shareData.sharedActiveCount = 2;
			mSharedBuffer->SetData(&shareData, 1);

			mAlpha = 1.f;
		}
		else
		{
			ParticleShared shareData = {};
			shareData.sharedActiveCount = 0;
			mSharedBuffer->SetData(&shareData, 1);
		}

		BindCB();

		mParticleShader->SetParticleBuffer(mParticleStructBuffer);
		mParticleShader->SetSharedBuffer(mSharedBuffer);
		mParticleShader->OnExcute();
	}
	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mParticleStructBuffer->BindSRV(eShaderStage::VS, 14);
		mParticleStructBuffer->BindSRV(eShaderStage::GS, 14);
		mParticleStructBuffer->BindSRV(eShaderStage::PS, 14);

		GetMaterial()->SetTexture(mParticleTexture);
		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(1000);

		mParticleStructBuffer->Clear();
		GetMaterial()->Clear();
	}

	void ParticleSystem::SetTexture(std::shared_ptr<Texture> tex)
	{
		mParticleTexture = tex;
		GetMaterial()->SetTexture(tex);
	}
	void ParticleSystem::BindCB()
	{
		ConstantBuffer* cb = renderer::constantBuffer[(int)eCBType::Particle];

		renderer::ParticleCB data = {};

		//data.ParticleAlpha = mAlpha;
		data.ParticleAlpha = 1.f;

		cb->Bind(eShaderStage::PS);
	}
}