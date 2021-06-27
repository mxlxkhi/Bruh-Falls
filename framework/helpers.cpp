// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Helper functions

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <codecvt>
#include "helpers.h"

// Log file location
extern const LPCWSTR LOG_FILE;

// Helper function to get the module base address
uintptr_t il2cppi_get_base_address()
{
	return (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
}

// Helper function to append text to a file
void il2cppi_log_write(std::string text)
{
	HANDLE hfile = CreateFileW(LOG_FILE, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,
	                           NULL);

	if (hfile == INVALID_HANDLE_VALUE)
		MessageBoxW(0, L"Could not open log file", 0, 0);

	DWORD written;
	WriteFile(hfile, text.c_str(), (DWORD)text.length(), &written, NULL);
	WriteFile(hfile, "\r\n", 2, &written, NULL);
	CloseHandle(hfile);
}

// Helper function to open a new console window and redirect stdout there
void il2cppi_new_console()
{
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}

#if _MSC_VER >= 1920
// Helper function to convert Il2CppString to std::string
std::string il2cppi_to_string(Il2CppString* str)
{
	std::u16string u16(reinterpret_cast<const char16_t*>(str->chars));
	return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
}

// Helper function to convert System.String to std::string
std::string il2cppi_to_string(app::String* str)
{
	return il2cppi_to_string(reinterpret_cast<Il2CppString*>(str));
}

//Made by kemo (credit pls)
MethodInfo* il2cppi_get_method(std::string assembly_name, std::string name_space, std::string class_name,
                               std::string prop_name,
                               std::string get_or_set, std::string method_name, int args_count)
{
	auto domain = il2cpp_domain_get();
	auto assembly = il2cpp_domain_assembly_open(domain, assembly_name.c_str());

	if (!assembly)
	{
		printf("[X] Couldn't get assembly %s\n", assembly_name.c_str());
		return nullptr;
	}

	auto image = il2cpp_assembly_get_image(assembly);
	auto _class = il2cpp_class_from_name(image, name_space.c_str(), class_name.c_str());

	if (!_class)
	{
		printf("[X] Couldn't get class %s from namespace %s\n", class_name.c_str(), name_space.c_str());
		return nullptr;
	}

	if (!prop_name.empty())
	{
		auto prop = il2cpp_class_get_property_from_name(_class, prop_name.c_str());

		if (!prop)
		{
			printf("[X] Couldn't get prop %s\n", prop_name.c_str());
			return nullptr;
		}

		if (get_or_set.empty()) get_or_set = "set";

		if (get_or_set == "set")
		{
			return il2cpp_property_get_set_method(prop);
		}
		else
		{
			return il2cpp_property_get_get_method(prop);
		}
	}
	else
	{
		return il2cpp_class_get_method_from_name(_class, method_name.c_str(), args_count);
	}
}

bool IsBadReadPtr(void* p)
{
	MEMORY_BASIC_INFORMATION mbi;
	if (VirtualQuery(p, &mbi, sizeof(mbi)))
	{
		DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
		bool b = !(mbi.Protect & mask);
		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;

		return b;
	}
	return true;
}
#endif
