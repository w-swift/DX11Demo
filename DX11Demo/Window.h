#pragma once
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

class Window
{
public:
	explicit Window(const int width, const int height);
	~Window();

	bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, bool windowed);
	
	inline int GetWindowWidth() const
	{
		return width;
	}

	inline int GetWindowHeight() const
	{
		return height;
	}

public:
	LPCTSTR WndClassName = L"firstwindow";
	HWND hwnd = NULL;

private:
	int width;
	int height;
};

