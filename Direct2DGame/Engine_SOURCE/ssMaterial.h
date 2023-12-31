#pragma once
#include "ssResource.h"
#include "ssShader.h"
#include "ssTexture.h"

namespace ss::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void Binds();
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		void SetRenderingMode(eRenderingMode mode) { mMode = mode; }
		eRenderingMode GetRenderingMode() { return mMode; }


	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture;

		eRenderingMode mMode;
	};
}
