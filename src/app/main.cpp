#include <Application.h>

// Entry point of the application
int main()
{
	std::cout << "\nApplication Name: " << APP_NAME << '\n';
	std::cout << "Application Version: v" << APP_VERSION_MAJOR << "." <<
		APP_VERSION_MINOR << "\n\n";

	if (!Application::CreateWindow())
	{
		LOG_ERR("Failed to start application instance\n");
		return -1;
	}

	Application::Run();

	// Should never reach here
	return -1;
}