#pragma once

#ifdef BR_PLATFORM_WINDOWS

extern Brio::Application* Brio::CreateApplication();

int main(int argc, char** argv)
{
	Brio::Log::Init();

	auto application = Brio::CreateApplication();
	application->Run();
	delete application;
}

#else
#error Brio only support Windows!
#endif
