#pragma once


namespace ss::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Collider2D,
		Particle,
		MeshRenderer,
		Animator,
		Script,
		Light,
		Camera,
		AudioListener,
		AudioSource,
		End,
	};

	enum class eLayerType
	{
		Map,
		Grid,
		Player,
		Monster,
		Summon1,
		Summon2,
		Projectile,
		EnemyProjectile,
		Light,
		MonsterUI,
		UI,
		Cursor,
		End = 16,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		ComputeShader,
		AudioClip,
		End,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};


	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};

	enum class eCollideType
	{
		Player,
		NormalMonster,
		Projectile,
	};
}