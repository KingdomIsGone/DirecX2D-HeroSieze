#include "ssCollisionManager.h"
#include "ssGameObject.h"
#include "ssScene.h"
#include "ssSceneManager.h"
#include "ssLayer.h"
#include "ssCollider2D.h"


namespace ss
{
	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		for (UINT column = 0; column < (UINT)eLayerType::End; column++)
		{
			for (UINT row = 0; row < (UINT)eLayerType::End; row++)
			{
				if (mMatrix[column][row] == true)
				{
					LayerCollision((eLayerType)column, (eLayerType)row);
				}
			}
		}
	}

	void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
	{
		Scene* activeScene = SceneManager::GetActiveScene();

		const std::vector<GameObject*>& lefts
			= activeScene->GetLayer(left).GetGameObjects();
		const std::vector<GameObject*>& rights
			= activeScene->GetLayer(right).GetGameObjects();

		for (GameObject* leftObj : lefts)
		{
			Collider2D* leftCol = leftObj->GetComponent<Collider2D>();
			if (leftCol == nullptr)
				continue;
			if (leftObj->GetState()
				!= GameObject::eState::Active)
				continue;

			for (GameObject* rightObj : rights)
			{
				Collider2D* rightCol = rightObj->GetComponent<Collider2D>();
				if (rightCol == nullptr)
					continue;
				if (leftObj == rightObj)
					continue;
				if (rightObj->GetState()
					!= GameObject::eState::Active)
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// 두 충돌체의 ID bool값을 확인
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		// 충돌정보를 가져온다
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect4(left, right))
		{
			// 충돌
			if (iter->second == false)
			{
				//최초 충돌
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);

				iter->second = true;
			}
			else
			{
				// 충돌 중
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// 충돌 X
			if (iter->second == true)
			{
				// 충돌하고 있다가 나갈떄
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);

				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		// Rect vs Rect 
		// 0 --- 1
		// |     |
		// 3 --- 2
		Vector3 arrLocalPos[4] =
		{
		   Vector3{-0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, -0.5f, 0.0f}
		   ,Vector3{-0.5f, -0.5f, 0.0f}
		};

		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		//custom
		Vector3 leftTempPos = leftTr->GetPosition();
		leftTempPos.x += left->GetCenter().x;
		leftTempPos.y += left->GetCenter().y;
		Vector3 rightTempPos = rightTr->GetPosition();
		rightTempPos.x += right->GetCenter().x;
		rightTempPos.y += right->GetCenter().y;

		Matrix leftMatrix = leftTr->GetCenterAppliedMatrix(leftTempPos);
		Matrix rightMatrix = rightTr->GetCenterAppliedMatrix(rightTempPos);

		//Matrix leftMatrix = leftTr->GetMatrix();
		//Matrix rightMatrix = rightTr->GetMatrix();

		Vector3 Axis[4] = {};

		Vector3 leftScale = Vector3(left->GetSize().x, left->GetSize().y, 1.0f);
		Matrix finalLeft = Matrix::CreateScale(leftScale);
		finalLeft *= leftMatrix;  //콜라이더의 월드매트릭스에 스케일 곱한것 

		Vector3 rightScale = Vector3(right->GetSize().x, right->GetSize().y, 1.0f);
		Matrix finalRight = Matrix::CreateScale(rightScale);
		finalRight *= rightMatrix;

		//Vector3::Tranform 함수 : 벡터에 변환행렬을 곱해 벡터로 반환
		Axis[0] = Vector3::Transform(arrLocalPos[1], finalLeft);
		Axis[1] = Vector3::Transform(arrLocalPos[3], finalLeft);
		Axis[2] = Vector3::Transform(arrLocalPos[1], finalRight);
		Axis[3] = Vector3::Transform(arrLocalPos[3], finalRight);

		Axis[0] -= Vector3::Transform(arrLocalPos[0], finalLeft);  //left 콜라이더의 사각형 윗변 벡터=가로벡터
		Axis[1] -= Vector3::Transform(arrLocalPos[0], finalLeft);   //사각형 세로 벡터
		Axis[2] -= Vector3::Transform(arrLocalPos[0], finalRight);
		Axis[3] -= Vector3::Transform(arrLocalPos[0], finalRight);

		for (size_t i = 0; i < 4; i++)
			Axis[i].z = 0.0f;

		//Vector3 vc = leftTr->GetPosition() - rightTr->GetPosition();
		//cutsom
		Vector3 vc = leftTempPos - rightTempPos;
		vc.z = 0.0f;

		Vector3 centerDir = vc;
		for (size_t i = 0; i < 4; i++)
		{
			Vector3 vA = Axis[i];

			float projDistance = 0.0f;
			//한축을 기준으로 다른 축을 내적후 이등분. 
			//이등분하여 변의 길이의 반만 구함
			//네개의 축을 모두 for문 돌리면 직교하는 변은 내적의 길이가 0이 나옴(cos90). 
			//따라서 따로 어떤 변을 사영해야하는지 변별하지 않고 포문 돌리고 이분의 일 하면됨.
			for (size_t j = 0; j < 4; j++)
			{
				projDistance += fabsf(Axis[j].Dot(vA) / 2.0f);
			}

			//두 사각형의 한 변의 반을 각각 사영한 길이의 합이 두 사각형의 중심점을 잇는 벡터의 사영보다 크면 충돌
			//하나라도 작은게 있으면 충돌x projDistance가 합 centerDir.Dot이 중심점을 잇는 벡터의 사영
			if (projDistance < fabsf(centerDir.Dot(vA))) 
				return false;
		}

		return true;
	}

	bool CollisionManager::Intersect4(Collider2D* left, Collider2D* right)
	{
		// Rect vs Rect 
		// 0 --- 1
		// |     |
		// 3 --- 2
		Vector3 arrLocalPos[4] =
		{
		   Vector3{-0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, -0.5f, 0.0f}
		   ,Vector3{-0.5f, -0.5f, 0.0f}
		};
		Vector3 upLocalPos[4] = 
		{
			Vector3{-0.45f, 0.5f, 0.0f}
			,Vector3{0.45f, 0.5f, 0.0f}
			,Vector3{0.45f, 0.46f, 0.0f}
			,Vector3{-0.45f, 0.46f, 0.0f}
		};
		Vector3 downLocalPos[4] =  
		{
			Vector3{-0.45f, -0.46f, 0.0f}
			,Vector3{0.45f, -0.46f, 0.0f}
			,Vector3{0.45f, -0.5f, 0.0f}
			,Vector3{-0.45f, -0.5f, 0.0f}
		};
		Vector3 rightLocalPos[4] =
		{
			Vector3{0.45f, 0.45f, 0.0f}
			,Vector3{0.5f, 0.45f, 0.0f}
			,Vector3{0.5f, -0.45f, 0.0f}
			,Vector3{0.45f, -0.45f, 0.0f}
		};
		Vector3 leftLocalPos[4] = 
		{
			Vector3{-0.5f, 0.45f, 0.0f}
			,Vector3{-0.45f, 0.45f, 0.0f}
			,Vector3{-0.45f, -0.45f, 0.0f}
			,Vector3{-0.5f, -0.45f, 0.0f}
		};
		Vector3 CenterLocalPos[4] //상하좌우
		{
			Vector3(0.0f, 0.48f, 0.0f)
			, Vector3(0.0f, -0.48f, 0.0f)
			, Vector3(-0.475f, 0.0f, 0.0f)
			, Vector3(0.475f, 0.0f, 0.0f)
		};

		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		//custom
		Vector3 leftTempPos = leftTr->GetPosition();
		leftTempPos.x += left->GetCenter().x;
		leftTempPos.y += left->GetCenter().y;
		Vector3 rightTempPos = rightTr->GetPosition();
		rightTempPos.x += right->GetCenter().x;
		rightTempPos.y += right->GetCenter().y;

		Matrix leftMatrix = leftTr->GetCenterAppliedMatrix(leftTempPos);
		Matrix rightMatrix = rightTr->GetCenterAppliedMatrix(rightTempPos);

		Vector3 leftScale = Vector3(left->GetSize().x, left->GetSize().y, 1.0f);
		Matrix finalLeft = Matrix::CreateScale(leftScale);
		finalLeft *= leftMatrix;  //콜라이더의 월드매트릭스에 스케일 곱한것 

		Vector3 rightScale = Vector3(right->GetSize().x, right->GetSize().y, 1.0f);
		Matrix finalRight = Matrix::CreateScale(rightScale);
		finalRight *= rightMatrix;


		leftTempPos = Vector3::Transform(CenterLocalPos[0], finalLeft);
		Vector3 vc = leftTempPos - rightTempPos;
		vc.z = 0.0f;
		Vector3 centerDir = vc;

		bool TopCol = Intersect4_Sub(&finalLeft, &finalRight, upLocalPos, centerDir);
		
		if (TopCol)
		{
			left->SetColDir(1);
			right->SetColDir(2);
		}

		leftTempPos = Vector3::Transform(CenterLocalPos[1], finalLeft);
		vc = leftTempPos - rightTempPos;
		vc.z = 0.0f;
		centerDir = vc;

		bool BottomCol = Intersect4_Sub(&finalLeft, &finalRight, downLocalPos, centerDir);

		if (BottomCol)
		{
			left->SetColDir(2);
			right->SetColDir(1);
		}

		leftTempPos = Vector3::Transform(CenterLocalPos[2], finalLeft);
		vc = leftTempPos - rightTempPos;
		vc.z = 0.0f;
		centerDir = vc;

		bool LeftCol = Intersect4_Sub(&finalLeft, &finalRight, leftLocalPos, centerDir);

		if (LeftCol)
		{
			left->SetColDir(3);
			right->SetColDir(4);
		}

		leftTempPos = Vector3::Transform(CenterLocalPos[3], finalLeft);
		vc = leftTempPos - rightTempPos;
		vc.z = 0.0f;
		centerDir = vc;

		bool RightCol = Intersect4_Sub(&finalLeft, &finalRight, rightLocalPos, centerDir);

		if (RightCol)
		{
			left->SetColDir(4);
			right->SetColDir(3);
		}

		if (RightCol || LeftCol || BottomCol || TopCol)
			return true;

		return false;
	}

	bool CollisionManager::Intersect4_Sub(Matrix* finalLeft, Matrix* finalRight, Vector3 PosArr[4], Vector3 centerDir)
	{
		Vector3 arrLocalPos[4] =
		{
		   Vector3{-0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, -0.5f, 0.0f}
		   ,Vector3{-0.5f, -0.5f, 0.0f}
		};

		Vector3 Axis[4] = {};

		Axis[0] = Vector3::Transform(PosArr[1], *finalLeft);
		Axis[1] = Vector3::Transform(PosArr[3], *finalLeft);
		Axis[2] = Vector3::Transform(arrLocalPos[1], *finalRight);
		Axis[3] = Vector3::Transform(arrLocalPos[3], *finalRight);

		Axis[0] -= Vector3::Transform(PosArr[0], *finalLeft);  //left 콜라이더의 사각형 윗변 벡터=가로벡터
		Axis[1] -= Vector3::Transform(PosArr[0], *finalLeft);   //사각형 세로 벡터
		Axis[2] -= Vector3::Transform(arrLocalPos[0], *finalRight);
		Axis[3] -= Vector3::Transform(arrLocalPos[0], *finalRight);

		for (size_t i = 0; i < 4; i++)
			Axis[i].z = 0.0f;
		
		for (size_t i = 0; i < 4; i++)
		{
			Vector3 vA = Axis[i];

			float projDistance = 0.0f;
			
			for (size_t j = 0; j < 4; j++)
			{
				projDistance += fabsf(Axis[j].Dot(vA) / 2.0f);
			}

			if (projDistance < fabsf(centerDir.Dot(vA)))
				return false;
		}

		return true;
	}




	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		mMatrix[col][row] = enable;
	}

	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}
}