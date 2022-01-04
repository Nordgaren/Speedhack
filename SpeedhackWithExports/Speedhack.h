#pragma once
#ifdef SPEEDHACKWITHEXPORTS_EXPORTS
#define SPEEDHACKWITHEXPORTS_API __declspec(dllexport)
#else
#define SPEEDHACKWITHEXPORTS_API __declspec(dllimport)
#endif

#include <Windows.h>
#include <detours.h>

namespace Speedhack
{
	extern float speed;
	extern bool attatched;

	typedef DWORD(WINAPI* _tGetTickCount)(void);
	extern _tGetTickCount _GTC;
	extern DWORD _GTC_BaseTime;

	typedef ULONGLONG(WINAPI* _tGetTickCount64)(void);
	extern _tGetTickCount64 _GTC64;
	extern DWORD _GTC64_BaseTime;

	typedef BOOL(WINAPI* _tQueryPerformanceCounter)(LARGE_INTEGER*);
	extern _tQueryPerformanceCounter _QPC;
	extern LARGE_INTEGER _QPC_BaseTime;


	DWORD WINAPI _hGetTickCount();

	DWORD WINAPI _hGetTickCount64();

	DWORD WINAPI _hQueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);


	extern "C" SPEEDHACKWITHEXPORTS_API void Setup();
	
	extern "C" SPEEDHACKWITHEXPORTS_API void Detach();

	extern "C" SPEEDHACKWITHEXPORTS_API void SetSpeed(float* relSpeed);

	void SetSpeed(float* relSpeed);
}
