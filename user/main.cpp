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
static PlayerSetup* MyPlayer;

//Since the game is badly optimized old players doesn't get freed so you have to update the local player often
auto hkPlayerSetup_GrabRPC(PlayerSetup* __this, int32_t _GrabID, Vector3 _GrabPoint, PhotonMessageInfo info,
                           MethodInfo* method)
{
	//removed check so you can qual everyone even you are dead lmao
	CurrentPlayer = __this;
	if (__this->fields.isMine == true)
	{
		MyPlayer = __this;
	}
}

auto hkPlayerSetup_HitPlayerRPC(PlayerSetup* __this, Vector3 force, int32_t ownerID, PhotonMessageInfo info,
                                MethodInfo* method)
{
	CurrentPlayer = __this;
	if (__this->fields.isMine == true)
	{
		MyPlayer = __this;
	}
}

auto hkPlayerSetup_DamageRPC(PlayerSetup* __this, int32_t _killerID, PhotonMessageInfo info, MethodInfo* method)
{
	CurrentPlayer = __this;
	if (__this->fields.isMine == true)
	{
		MyPlayer = __this;
	}
}

auto hkPlayerSetup_AttackRPC(PlayerSetup* __this, PhotonMessageInfo info, MethodInfo* method)
{
	CurrentPlayer = __this;
	if (__this->fields.isMine == true)
	{
		MyPlayer = __this;
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
		if (MyPlayer && !IsBadReadPtr(MyPlayer))
		{
			if (GetAsyncKeyState(VK_OEM_PLUS) && MyPlayer->fields.isMine)
			{
				MyPlayer->fields.jumpHeight += 100;
				MyPlayer->fields.speed += 100;

				printf("Current speed: %f\n", MyPlayer->fields.speed);
				printf("Current jumpHeight: %f\n", MyPlayer->fields.jumpHeight);

				Sleep(300);
			}

			else if (GetAsyncKeyState(VK_OEM_MINUS) && MyPlayer->fields.isMine)
			{
				MyPlayer->fields.jumpHeight -= 100;
				MyPlayer->fields.speed -= 100;

				printf("Current speed: %f\n", MyPlayer->fields.speed);
				printf("Current jumpHeight: %f\n", MyPlayer->fields.jumpHeight);

				Sleep(300);
			}

			else if (GetAsyncKeyState(0x30) && MyPlayer->fields.isMine) //0 key
			{
				static MethodInfo* FinishMethod;

				if (!FinishMethod)
					FinishMethod = il2cppi_get_method("Assembly-CSharp", "", "PlayerSetup", "", "",
					                                  "Finish", 0);

				//Preventing a possible crash.
				if (FinishMethod)
				{
					printf("Welcome to the finish line!\n");
					PlayerSetup_Finish(MyPlayer, FinishMethod);
				}

				Sleep(300);
			}

			else if (GetAsyncKeyState(0x39)) //9 key
			{
				static MethodInfo* FinishMethod;

				if (!FinishMethod)
					FinishMethod = il2cppi_get_method("Assembly-CSharp", "", "PlayerSetup", "", "",
					                                  "Finish", 0);

				//Preventing a possible crash.
				if (FinishMethod)
				{
					//Being greedy and always win before everyone c:
					if (MyPlayer) PlayerSetup_Finish(MyPlayer, FinishMethod);
					Sleep(10);

					auto NetworkManager = CurrentPlayer->fields.networkManager;

					if (NetworkManager)
					{
						auto PlayerNets = NetworkManager->fields.playerNets;
						if (PlayerNets)
						{
							auto PlayersArray = PlayerNets->fields._items;

							for (auto i = 0; i < 60; i++)
							{
								const auto Player = PlayersArray->vector[i];
								if (Player) PlayerSetup_Finish(Player, FinishMethod);
							}

							printf("This game is so broken lmao\n");
						}
					}
				}

				Sleep(300);
			}

			else if (GetAsyncKeyState(0x38)) //8
			{
				MyPlayer->fields.knifeMode = !MyPlayer->fields.knifeMode;
				printf("Hammer mode: %s\n", MyPlayer->fields.knifeMode ? "true" : "false");

				Sleep(300);
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

	printf(
		"[BRUH FALLS] Made by kemo and mix!\nGrab someone in each match to update your local player in the cheat\nPress + or - to in/decrease speed and jump height.\nPress 0 to qualify (alone), Press 9 to qualify (everyone lmao, can cause crashes)\nPrees 8 to switch to hammer mode (BONK)\n\n");

	//Hooking some funnies
	DetoursEasy(PlayerSetup_GrabRPC, hkPlayerSetup_GrabRPC);

	DetoursEasy(PlayerSetup_RagdollRPC, hkPlayerSetup_RagdollRPC);

	DetoursEasy(PlayerSetup_HitPlayerRPC, hkPlayerSetup_HitPlayerRPC);

	DetoursEasy(PlayerSetup_AttackRPC, hkPlayerSetup_AttackRPC);


	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)pThread, nullptr, 0, nullptr);
}
