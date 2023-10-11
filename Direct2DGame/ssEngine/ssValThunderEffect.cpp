#include "ssValThunderEffect.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssValkyrieScript.h"
#include "ssRenderer.h"
#include "ssValkyrie.h"
#include "ssThunderPiece.h"

namespace ss
{
	ValThunderEffect::ValThunderEffect()
		: mOffset(Vector3::Zero)
	{
		SetName(L"ValThunderEffect");

		mTransform = GetComponent<Transform>();
		
		mLeftPiece = new ThunderPiece(this);
		AddOtherGameObject(mLeftPiece, eLayerType::EnemyProjectile);

		mMiddlePiece = new ThunderPiece(this);
		AddOtherGameObject(mMiddlePiece, eLayerType::EnemyProjectile);

		mRightPiece = new ThunderPiece(this);
		AddOtherGameObject(mRightPiece, eLayerType::EnemyProjectile);

	}

	ValThunderEffect::~ValThunderEffect()
	{
		mLeftPiece->SetState(eState::Dead);
		mMiddlePiece->SetState(eState::Dead);
		mRightPiece->SetState(eState::Dead);
	}
	void ValThunderEffect::Initialize()
	{
		GameObject::Initialize();
	}
	void ValThunderEffect::Update()
	{
		GameObject::Update();

		mValkPos = mValk->GetComponent<Transform>()->GetPosition();
		mValkPos.z -= 0.3f;
		mValkPos += mOffset;
		mTransform->SetPosition(mValkPos);
		mPos = mTransform->GetPosition();

		Vector3 leftPos = mPos + mLeftPiece->GetOffset();
		mLeftPiece->GetComponent<Transform>()->SetPosition(leftPos);

		Vector3 rightPos = mPos + mRightPiece->GetOffset();
		mRightPiece->GetComponent<Transform>()->SetPosition(rightPos);

		Vector3 middlePos = mPos + mMiddlePiece->GetOffset();
		mMiddlePiece->GetComponent<Transform>()->SetPosition(middlePos);

	}
	void ValThunderEffect::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void ValThunderEffect::Render()
	{
		GameObject::Render();
	}

	void ValThunderEffect::SetDead()
	{
		SetState(eState::Dead);
	}

	void ValThunderEffect::SetDown()
	{
		mLeftPiece->SetOffset(Vector3(-0.24f, 0.12f, 0.f));
		mLeftPiece->SetRotation(Vector3(0.8f, 0.0f, -1.2f));

		mMiddlePiece->SetOffset(Vector3(-0.09f, 0.16f, 0.f));
		mMiddlePiece->SetRotation(Vector3(0.8f, 0.f, 1.6f));

		mRightPiece->SetOffset(Vector3(0.11f, 0.12f, 0.f));
		mRightPiece->SetRotation(Vector3(0.8f, 0.f, 1.2f));
	}

	void ValThunderEffect::SetUp()
	{
		mLeftPiece->SetOffset(Vector3(-0.13f, -0.19f, 0.f));
		mLeftPiece->SetRotation(Vector3(0.8f, 0.0f, 1.2f));

		mMiddlePiece->SetOffset(Vector3(0.07f, -0.21f, 0.f));
		mMiddlePiece->SetRotation(Vector3(0.8f, 0.f, 1.6f));

		mRightPiece->SetOffset(Vector3(0.26f, -0.17f, 0.f));
		mRightPiece->SetRotation(Vector3(0.8f, 0.f, 2.f));
	}

	void ValThunderEffect::SetRight()
	{
		mLeftPiece->SetOffset(Vector3(-0.1f, 0.14f, 0.f));
		mLeftPiece->SetRotation(Vector3(0.8f, 0.0f, -0.4f));

		mMiddlePiece->SetOffset(Vector3(-0.14f, -0.05f, 0.f));
		mMiddlePiece->SetRotation(Vector3(0.8f, 0.f, 0.f));

		mRightPiece->SetOffset(Vector3(-0.1f, -0.26f, 0.f));
		mRightPiece->SetRotation(Vector3(0.8f, 0.f, 0.42f));
	}

	void ValThunderEffect::SetLeft()
	{
		mLeftPiece->SetOffset(Vector3(0.09f, 0.15f, 0.f));
		mLeftPiece->SetRotation(Vector3(0.8f, 0.0f, 3.6f));

		mMiddlePiece->SetOffset(Vector3(0.14f, -0.045f, 0.f));
		mMiddlePiece->SetRotation(Vector3(0.8f, 0.f, 3.2f));

		mRightPiece->SetOffset(Vector3(0.11f, -0.245f, 0.f));
		mRightPiece->SetRotation(Vector3(0.8f, 0.f, 2.8f));
	}

	
}



