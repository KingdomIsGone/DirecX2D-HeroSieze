#include "ssGameObject.h"
#include "ssRenderer.h"
#include "ssGraphicDevice_Dx11.h"
#include "ssInput.h"
#include "ssTime.h"

namespace ss
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
		
	}

	void GameObject::Update()
	{
		

	}

	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render()
	{
		//상수버퍼로 위치정보 크기정보, 색깔, 업데이트 해줘야한다.

		
	}
}