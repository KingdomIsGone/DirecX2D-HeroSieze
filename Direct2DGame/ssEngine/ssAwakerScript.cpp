#include "ssAwakerScript.h"
#include "ssGameObject.h"
#include "ssValAwaker.h"

namespace ss
{
	AwakerScript::AwakerScript()
	{
	}
	AwakerScript::~AwakerScript()
	{
	}
	void AwakerScript::Initialize()
	{
	}
	void AwakerScript::Update()
	{

	}
	void AwakerScript::OnCollisionEnter(Collider2D* other)
	{
		dynamic_cast<ValAwaker*>(GetOwner())->SetTouched();
	}
	void AwakerScript::OnCollisionStay(Collider2D* other)
	{
		
	}
	void AwakerScript::OnCollisionExit(Collider2D* other)
	{
	}
}
