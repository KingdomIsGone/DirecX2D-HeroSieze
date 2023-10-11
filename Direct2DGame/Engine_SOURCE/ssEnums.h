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
		Player = 2,
		Monster,
		OtherObject,
		Summon1,
		Summon2,
		Projectile,
		EnemyProjectile,
		Light,
		MonsterUI,
		UI,
		Item,
		Inventory,
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
		SpecialMonster,
		Projectile,
		Item,
		Sensor,
	};

	enum class eItemGrade
	{
		Normal,
		Magic,
		Legend,
	};
	enum class eItemKind
	{
		Weapon,
		Armor,
		Shield,
		Helmet,
		Belt,
		Shoes,
	};
	enum class e4Direction
	{
		Up,
		Down,
		Right,
		Left,
	};

}