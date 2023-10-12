#pragma once
#include "ssMeshRenderer.h"
#include "ssStructedBuffer.h"
#include "ssParticleShader.h"

namespace ss
{
	class ParticleSystem : public MeshRenderer
	{
	public:
		ParticleSystem();
		~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetTexture(std::shared_ptr<Texture> tex);
		void BindCB();

	private:
		graphics::StructedBuffer* mParticleStructBuffer;
		graphics::StructedBuffer* mSharedBuffer;

		std::shared_ptr<ParticleShader> mParticleShader;
		std::shared_ptr<Texture>mParticleTexture;

		UINT    mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float   mLifeTime;
		float	mFrequency;

		float mTime;

		float mAlpha;
	};
}