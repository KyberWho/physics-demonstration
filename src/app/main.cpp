#include <Application.h>

// Entry point of the application
int main()
{
	bool windowCreated = Application::CreateWindow();

	if (!windowCreated)
	{
		std::cerr << "Failed to create application instance\n";
		return -1;
	}

	std::cout << "Application Name: " << APP_NAME << '\n';
	std::cout << "Application Version: v" << APP_VERSION_MAJOR << "." <<
		APP_VERSION_MINOR << '\n';

	if (!Application::UpdateWindow())
	{
		Application::TerminateWindow();
		return 0;
	}

	return -1;
}