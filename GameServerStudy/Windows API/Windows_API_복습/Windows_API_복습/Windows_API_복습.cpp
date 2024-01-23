﻿// Windows_API_복습.cpp : 애플리케이션에 대한 진입점을 정의합니다.
// 1. 메인(기본 cpp 파일) 정리

#include "pch.h"
#include "framework.h"
#include "Windows_API_복습.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;        // 현재 인스턴스입니다.
HWND g_hWnd;            // InitInstance 함수 내의 hWnd를 다른 클래스로 넘겨주기 위한 전역 변수 (핸들 번호)

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
// About 함수 삭제 (불필요)

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    // TODO: 여기에 코드를 입력합니다.
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg = {};
    uint64 prevTick = 0;

    // 기본 메시지 루프입니다:
    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, NULL, 0,0,PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        else {
            uint64 now = ::GetTickCount64();    // 시스템이 시작된 후 경과된 시간(밀리초)

            // 1) 현재 시간과 2)이전 틱에서 경과된 시간 이 얼마인지 확인하고
            // 특정 시간이 되면 if문에 들어가게 함으로써 프레임이 무한으로 늘어나지 않게 조절 가능
            
            // 즉, 지정된 시간 간격(여기서는 10 밀리초)마다 특정 작업을 수행하도록 조건을 설정
            if (now - prevTick >= 10) {
                prevTick = now;
            }
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSAPI);
    wcex.lpszClassName  = L"Windows API";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 겹치는 팝업 또는 자식 창을 만듭니다. 창 클래스, 창 제목, 창 스타일 및 창의 초기 위치 및 크기(선택 사항)를 지정합니다.
   HWND hWnd = CreateWindowW(L"Windows API", L"Client", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_EXIT:
                ::DestroyWindow(hWnd);
                break;
            default:
                return ::DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = ::BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            ::EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        break;
    default:
        return ::DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}