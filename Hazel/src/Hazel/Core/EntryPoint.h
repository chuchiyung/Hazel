#pragma once

#include "Hazel/Core/Application.h"

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_INFO("Initialized Core Log!");
	int a = 5;
	HZ_TRACE("Client Log : Var = {0}", a);
	
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif