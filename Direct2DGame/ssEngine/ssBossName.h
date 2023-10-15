#pragma once
#include "ssGameObject.h"

namespace ss
{
	class BossName : public GameObject
	{
	public:
		BossName();
		~BossName();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetOnOff(bool is) { mbOn = is; }
		
		void SetBossName(const wchar_t name[])
		{
			for (int i = 0; i < 20; i++)
			{
				mBossName[i] = name[i];
			}
		}

		void SetFontPos(float x, float y) { mX = x; mY = y; }

	private:
		Transform* mTransform;
		Vector3 mPos;

		bool mbOn;
		wchar_t mBossName[20];

		class MeshRenderer* mRenderer;

		float mX;
		float mY;

	};
}