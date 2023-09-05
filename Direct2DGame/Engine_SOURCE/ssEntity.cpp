#include "ssEntity.h"


namespace ss
{
	Entity::Entity()
		: mName(L"")
		, mColliderID((UINT64)this)
	{

	}

	Entity::~Entity()
	{
	}

}

namespace gui
{
	Entity::Entity()
		: mName("")
		, mColliderID((UINT64)this)
	{

	}

	Entity::~Entity()
	{
	}
}