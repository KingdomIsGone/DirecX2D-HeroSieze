#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ITemlistSelectEffect : public GameObject
	{
	public:
		ITemlistSelectEffect(GameObject* parent);
		~ITemlistSelectEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetBlank();
		void SetMater();

		void SetItemIn(bool is) { mItemIn = is; }
		void SetSelected(bool is) { mSelected = is; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;

		class MeshRenderer* mRenderer;

		bool mItemIn;
		bool mSelected;
	};
}