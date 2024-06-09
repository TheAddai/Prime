
#include "pch.h"
#include "engine/platform/platform.h"
#include "engine/utils/timer.h"
#include "engine/utils/file_dialog.h"
#include "engine/engine.h"

#ifdef PPLATFORM_WINDOWS
#include <Windows.h>
#include <ShlObj.h>
#include <atlbase.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#endif // PPLATFORM_WINDOWS

namespace prime {

	float Timer::GetTime()
	{
		return (float)glfwGetTime();
	}

	std::string FileDialog::OpenFile(const char* filter)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Engine::GetWindow().GetHandle());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();

	}

	std::string FileDialog::SaveFile(const char* filter)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Engine::GetWindow().GetHandle());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		// Sets the default extension by extracting it from the filter
		ofn.lpstrDefExt = strchr(filter, '\0') + 1;

		if (GetSaveFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();
	}

	std::string FileDialog::GetFilePath()
	{
		BROWSEINFO  bi;
		ZeroMemory(&bi, sizeof(bi));
		char buffer[MAX_PATH] = "";
		auto init = OleInitialize(nullptr);

		bi.hwndOwner = glfwGetWin32Window((GLFWwindow*)Engine::GetWindow().GetHandle());
		bi.lpszTitle = "";
		bi.pidlRoot = 0;
		bi.pszDisplayName = buffer;
		bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI | BIF_VALIDATE;

		LPITEMIDLIST item = SHBrowseForFolder(&bi);
		if (item != NULL) { SHGetPathFromIDList(item, buffer); }
		
		return std::string(buffer);
	}
}