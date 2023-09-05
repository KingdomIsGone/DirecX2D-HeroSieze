#pragma once
#include "..\\Engine_SOURCE\\CommonInclude.h"
#include "..\\Engine_SOURCE\\ssEngine.h"
#include "..\\Engine_SOURCE\\ssGraphics.h"

#include "guiWidget.h"
#include "guiEditorObject.h"
#include "guiDebugObject.h"

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

namespace gui
{
	class Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const ss::graphics::DebugMesh& mesh);

	private:
		static void imguiInit();
		static void imguiRender();
		static void imguiRelease();

	private:
		static std::map<std::wstring, Widget*> mWidgets;
		static std::vector<EditorObject*> mEditorObjects;
		static std::vector<DebugObject*> mDebugObjects;
		static ImGuiIO mIO;

		static class Dockspace* mDockSpace;
	};
}
