#include "guiEditor.h"
#include "..\\Engine_SOURCE\\ssMesh.h"
#include "..\\Engine_SOURCE\\ssResources.h"
#include "..\\Engine_SOURCE\\ssTransform.h"
#include "..\\Engine_SOURCE\\ssMeshRenderer.h"
#include "..\\Engine_SOURCE\\ssMaterial.h"
#include "..\\Engine_SOURCE\\ssRenderer.h"

#include "ssEngine/ssGridScript.h"

namespace gui
{
	using namespace ss::enums;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugObjects = {};

	void Editor::Initialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<ss::Mesh> mesh
			= ss::Resources::Find<ss::Mesh>(L"DebugRect");
		std::shared_ptr<ss::Material> material
			= ss::Resources::Find<ss::Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<ss::Transform>();
		ss::MeshRenderer* mr
			= mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<ss::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);


		EditorObject* grid = new EditorObject();
		grid->SetName(L"Grid");

		mr = grid->AddComponent<ss::MeshRenderer>();
		mr->SetMesh(ss::Resources::Find<ss::Mesh>(L"RectMesh"));
		mr->SetMaterial(ss::Resources::Find<ss::Material>(L"GridMaterial"));
		ss::GridScript* gridSc = grid->AddComponent<ss::GridScript>();
		gridSc->SetCamera(renderer::cameras[0]);

		mEditorObjects.push_back(grid);

	}
	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void Editor::Update()
	{


		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}
	void Editor::LateUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}
	void Editor::Render()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const ss::graphics::DebugMesh& mesh
			: renderer::debugMeshs)
		{
			DebugRender(mesh);
		}

		renderer::debugMeshs.clear();
	}
	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}
	}

	void Editor::DebugRender(const ss::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.

		ss::Transform* tr = debugObj->GetComponent<ss::Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);

		tr->LateUpdate();

		/*ss::MeshRenderer * mr
			= debugObj->GetComponent<ss::MeshRenderer>();*/
			// main camera
		ss::Camera* mainCamara = renderer::mainCamera;

		ss::Camera::SetGpuViewMatrix(mainCamara->GetViewMatrix());
		ss::Camera::SetGpuProjectionMatrix(mainCamara->GetProjectionMatrix());

		debugObj->Render();
	}
}