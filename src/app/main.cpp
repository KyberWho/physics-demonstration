#include <Application.h>

// Entry point of the application
int main()
{
	std::cout << "Application Name: " << APP_NAME << '\n';
	std::cout << "Application Version: v" << APP_VERSION_MAJOR << "." <<
		APP_VERSION_MINOR << "\n\n";

	bool windowCreated = Application::CreateWindow();

	if (!windowCreated)
	{
		LOG_ERR("Failed to start application instance\n");
		return -1;
	}

	if (!Application::UpdateWindow())
	{
		Application::TerminateWindow();
		return 0;
	}

	Application::TerminateWindow();
	return -1;
}