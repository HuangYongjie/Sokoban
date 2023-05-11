#include <Windows.h>
#include "StateMap.h"

//创建一个StateMap实例
StateMap map(5, 5,
	std::make_pair(2, 2),
	{ std::make_pair(0, 0), std::make_pair(0, 1), std::make_pair(0, 2) , 
	std::make_pair(0, 4), std::make_pair(2, 0), std::make_pair(3, 0), 
	std::make_pair(4, 0), std::make_pair(0, 4), std::make_pair(1, 4), 
	std::make_pair(2, 4),std::make_pair(4, 2), std::make_pair(4, 3), 
	std::make_pair(4, 4)},
	{ std::make_pair(0, 3), std::make_pair(1, 0), std::make_pair(3, 4), std::make_pair(4, 1) },
	{ std::make_pair(1, 3), std::make_pair(1, 1), std::make_pair(3, 3), std::make_pair(3, 1) }
);

//定义一个函数,使用GDI绘制StateMap，黑色实心方块表示墙，红色实心方块表示箱子，红色空心方块表示目标，红色实心圆表示玩家
void drawStateMap(HWND& hWnd, StateMap& map) {
	PAINTSTRUCT ps;
	//获取设备上下文
	HDC hdc = BeginPaint(hWnd, &ps);
	//获取窗口大小
	RECT rect;
	GetClientRect(WindowFromDC(hdc), &rect);
	//计算每个格子的大小
	int width = (rect.right - rect.left) / map.getWidth();
	int height = (rect.bottom - rect.top) / map.getHeight();
	//创建画刷
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	//选择画刷
	SelectObject(hdc, hBrush);
	//绘制墙
	auto wallsPos = map.getWalls();
	for (auto& p : wallsPos) {
		Rectangle(hdc, p.first * width, p.second * height, (p.first + 1) * width, (p.second + 1) * height);
	}
	//创建画刷
	HBRUSH hBrush2 = CreateSolidBrush(RGB(255, 0, 0));
	//选择画刷
	SelectObject(hdc, hBrush2);
	//绘制目标
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	auto targetsPos = map.getTargets();
	for (auto& p : targetsPos) {
		Rectangle(hdc, p.first * width, p.second * height, (p.first + 1) * width, (p.second + 1) * height);
	}
	SelectObject(hdc, hBrush2);
	//绘制箱子
	auto chestsPos = map.getChests();
	for (auto& p : chestsPos) {
		Rectangle(hdc, p.first * width, p.second * height, (p.first + 1) * width, (p.second + 1) * height);
	}
	//绘制玩家
	Ellipse(hdc, map.getPlayer().first * width, map.getPlayer().second * height, (map.getPlayer().first + 1) * width, (map.getPlayer().second + 1) * height);
	//删除画笔
	EndPaint(hWnd, &ps);
}


//窗口过程
LRESULT CALLBACK dealMessage(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_UP:
			if (map.move(StateMap::direction::up)) {
				MessageBox(hWnd, L"挑战成功！", L"提示", MB_OK);
			}
			break;
		case VK_DOWN:
			if (map.move(StateMap::direction::down)) {
				MessageBox(hWnd, L"挑战成功！", L"提示", MB_OK);
			}
			break;
		case VK_LEFT:
			if (map.move(StateMap::direction::left)) {
				MessageBox(hWnd, L"挑战成功！", L"提示", MB_OK);
			}
			break;
		case VK_RIGHT:
			if (map.move(StateMap::direction::right)) {
				MessageBox(hWnd, L"挑战成功！", L"提示", MB_OK);
			}
			break;
		}
		//重新绘制窗口
		drawStateMap(hWnd, map);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		drawStateMap(hWnd, map);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	//注册窗口类
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = dealMessage;
	wndClass.lpszClassName = TEXT("Sokoban");
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);

	//创建窗口
	HWND hWnd = CreateWindow(
		TEXT("Sokoban"),
		TEXT("Sokoban"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		500,
		500,
		NULL,
		NULL,
		hInstance,
		NULL
	);
		
	//在此窗口中绘制StateMap
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	//消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		//翻译消息
		TranslateMessage(&msg);
		//分发消息
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
