// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>
#include <iostream>
#include "il2cpp-appdata.h"
#include "helpers.h"

using namespace app;

extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

/*
 * Author: @kemo#1337, (kem0x on github | xkem0x on twitter)
 */

static PlayerSetup* CurrentPlayer;

auto hkPlayerSetup_GrabRPC(PlayerSetup* __this, int32_t _GrabID, Vector3 _GrabPoint, PhotonMessageInfo info,
                           MethodInfo* method)
{
	//Since the game is badly optimized old players doesn't get freed so you have to update the local player often
	//In this case we update he local player whenever you press left click (grab)
	if (__this->fields.isMine == true)
	{
		CurrentPlayer = __this;
	}
}

auto hkPlayerSetup_RagdollRPC(PlayerSetup* __this, KillType__Enum killType, PhotonMessageInfo info, MethodInfo* method)
{
	//No Death from map shit
}


auto pThread()
{
	//Rushed af DUH
	while (true)
	{
		if (CurrentPlayer)
		{
			if (GetAsyncKeyState(VK_OEM_PLUS))
			{
				CurrentPlayer->fields.jumpHeight += 100;
				CurrentPlayer->fields.speed += 100;

				system("cls");
				printf("Current speed: %f\n", CurrentPlayer->fields.speed);
				printf("Current jumpHeight: %f\n", CurrentPlayer->fields.jumpHeight);

				Sleep(50);
			}
			else if (GetAsyncKeyState(VK_OEM_MINUS))
			{
				CurrentPlayer->fields.jumpHeight -= 100;
				CurrentPlayer->fields.speed -= 100;

				system("cls");
				printf("Current speed: %f\n", CurrentPlayer->fields.speed);
				printf("Current jumpHeight: %f\n", CurrentPlayer->fields.jumpHeight);

				Sleep(50);
			}
		}
		Sleep(60 / 1000);
	}
}

// Custom injected code entry point
void Run()
{
	// Initialize thread data - DO NOT REMOVE
	il2cpp_thread_attach(il2cpp_domain_get());

	il2cppi_new_console();

	printf("[BRUH FALLS] Made by kemo!\nPress left click a couple of time in each match to update your local player in the cheat\nPress + or to in/decrease speed and jump height.\n\n");

	//Hooking some funnies
	DetoursEasy(PlayerSetup_GrabRPC, hkPlayerSetup_GrabRPC);

	DetoursEasy(PlayerSetup_RagdollRPC, hkPlayerSetup_RagdollRPC);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)pThread, nullptr, 0, nullptr);
}
