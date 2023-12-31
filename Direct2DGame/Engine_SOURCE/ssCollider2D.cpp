#include "ssCollider2D.h"
#include "ssGameObject.h"
#include "ssRenderer.h"
#include "..\\ssEngine\ssPlayerScript.h"

namespace ss
{
	bool Collider2D::mIsCollide = false;
	UINT Collider2D::mColliderNumber = 0;
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
		, mTopColCount(0)
		, mBottomColCount(0)
		, mRightColCount(0)
		, mLeftColCount(0)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
	}
	Collider2D::~Collider2D()
	{
	}
	void Collider2D::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
	}

	void Collider2D::Update()
	{

	}
	void Collider2D::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 scale = tr->GetScale();
		scale.x *= mSize.x;
		scale.y *= mSize.y;

		Vector3 pos = tr->GetPosition();
		pos.x += mCenter.x;
		pos.y += mCenter.y;

		mPosition = pos;

		graphics::DebugMesh mesh = {};
		mesh.position = pos;
		mesh.scale = scale;
		mesh.rotation = tr->GetRotation();
		mesh.type = eColliderType::Rect;

		renderer::PushDebugMeshAttribute(mesh);
	}

	void Collider2D::Render()
	{
	}

	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionEnter(other);
		}

		GameObject* gameObject = GetOwner();
		gameObject->OnCollisionEnter(other);

		mIsCollide = true;
	}
	void Collider2D::OnCollisionStay(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionStay(other);
		}

		GameObject* gameObject = GetOwner();
		gameObject->OnCollisionStay(other);
	}
	void Collider2D::OnCollisionExit(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionExit(other);
		}

		GameObject* gameObject = GetOwner();
		gameObject->OnCollisionExit(other);

		mIsCollide = false;
	}
	void Collider2D::SetDirCountPlus(e4Direction dir)
	{
		switch (dir)
		{
		case ss::enums::e4Direction::Up:
			mTopColCount++;
			break;
		case ss::enums::e4Direction::Down:
			mBottomColCount++;
			break;
		case ss::enums::e4Direction::Right:
			mRightColCount++;
			break;
		case ss::enums::e4Direction::Left:
			mLeftColCount++;
			break;
		default:
			break;
		}
	}
	void Collider2D::SetDirCountMinus(e4Direction dir)
	{
		switch (dir)
		{
		case ss::enums::e4Direction::Up:
			mTopColCount--;
			break;
		case ss::enums::e4Direction::Down:
			mBottomColCount--;
			break;
		case ss::enums::e4Direction::Right:
			mRightColCount--;
			break;
		case ss::enums::e4Direction::Left:
			mLeftColCount--;
			break;
		default:
			break;
		}
	}
	UINT Collider2D::GetDirCount(e4Direction dir)
	{
		switch (dir)
		{
		case ss::enums::e4Direction::Up:
			return mTopColCount;
			break;
		case ss::enums::e4Direction::Down:
			return mBottomColCount;
			break;
		case ss::enums::e4Direction::Right:
			return mRightColCount;
			break;
		case ss::enums::e4Direction::Left:
			return mLeftColCount;
			break;
		default:
			break;
		}
		
	}
}
