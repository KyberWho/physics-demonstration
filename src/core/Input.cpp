#include "Input.h"
#include "Logger.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (action)
    {
        case GLFW_PRESS:
            InputHandler::NotifyPressed(key);
            break;
        case GLFW_RELEASE:
            InputHandler::NotifyReleased(key);
            break;
    }
}

// -------------------------------------------------------------------------------
// ACTION-ATTRIBUTES CLASS
// -------------------------------------------------------------------------------

// Just a whole bunch of getter-setter functions for each attribute
int& ActionAttributes::GetKey() { return bindedKey; }
void ActionAttributes::SetKey(int currentKey)
{
	bindedKey = currentKey;
}

std::string ActionAttributes::GetName() { return actionName; }
void ActionAttributes::SetName(std::string givenName)
{
	actionName = givenName;
}

std::function<void()> ActionAttributes::GetFunction() { return actionFunction; }
void ActionAttributes::SetFunction(std::function<void()> currentFunction)
{
	actionFunction = currentFunction;
}

void ActionAttributes::SetToggleable(bool toggleable)
{
	toggleableAction = toggleable;
}

void ActionAttributes::SetUnavailable(bool unavailable)
{
	actionUnavailable = unavailable;
}

// -------------------------------------------------------------------------------
// ACTION CLASS
// -------------------------------------------------------------------------------

Action::Action()
{
	currentAttributes = new ActionAttributes();
}

Action::~Action()
{
	delete currentAttributes;
}

ActionAttributes* Action::accessAttributes() { return currentAttributes; }

void Action::Execute()
{
	std::function<void()> executableFunction = currentAttributes->GetFunction();
	executableFunction();
}

// -------------------------------------------------------------------------------
// ACTION-HANDLER CLASS
// -------------------------------------------------------------------------------

// Vector to keep track + store all the action objects inside
std::vector<Action*> ActionHandler::allCreatedActions;

// Creates an action with the given parameters
void ActionHandler::CreateAction(int bindedKey, std::function<void()> bindedFunction, std::string bindedName)
{
	Action* newAction = new Action();
	ActionAttributes* attributes = newAction->accessAttributes();
	
	attributes->SetKey(bindedKey);
	attributes->SetFunction(bindedFunction);
	attributes->SetName(bindedName);

	ActionHandler::AddAction(newAction);
}

// Adds/removes the action from the main vector
void ActionHandler::AddAction(Action* actionToAdd)
{
	allCreatedActions.push_back(actionToAdd);
}

void ActionHandler::RemoveAction(std::string actionToRemove)
{
	Action* currentAction = ActionHandler::RetrieveAction(actionToRemove);
	if (currentAction == nullptr)
	{
		LOG_WARN("Unable to remove action as it isn't in the list!");
		return;
	}

	for (std::vector<Action*>::iterator it = allCreatedActions.begin(); it != allCreatedActions.end();)
	{
		if (*it == currentAction)
		{
			allCreatedActions.erase(it);
			delete currentAction;
			break;
		}
	}

	allCreatedActions.shrink_to_fit();
}

void ActionHandler::RemoveAllActions()
{
	if (!allCreatedActions.empty()) allCreatedActions.clear();
}

// Retrieves a given action when given the name of the action
// TODO: Will optimise in the future, for now just doing basic linear search
Action* ActionHandler::RetrieveAction(std::string bindedName)
{
	ActionAttributes* attributes;

	for (Action* currentAction : allCreatedActions)
	{
		attributes = currentAction->accessAttributes();
		if (attributes->GetName().compare(bindedName) == 0)
		{
			return currentAction;
		}
	}

	LOG_WARN("No action was found of name: " << bindedName);
	return nullptr;
}

// -------------------------------------------------------------------------------
// INPUT CLASS
// -------------------------------------------------------------------------------

// Hashmaps linking the keys to the actions
std::unordered_map<int, Action*> InputHandler::pressedActions;
std::unordered_map<int, Action*> InputHandler::releasedActions;

void InputHandler::Init(GLFWwindow* window)
{
    glfwSetKeyCallback(window, KeyCallback);
}

void InputHandler::ReleaseAllActions()
{
	if (!pressedActions.empty())
		pressedActions.clear();

	if (!releasedActions.empty())
		releasedActions.clear();
}

// Attaches the action to the appropriate hash maps
void InputHandler::AttachAction(Action* currentAction, int type)
{	 
	ActionAttributes* currentAttributes = currentAction->accessAttributes();
	switch (type)
	{
		case GLFW_PRESS:
			pressedActions.insert_or_assign(currentAttributes->GetKey(), currentAction);
			break;
		case GLFW_RELEASE:
			releasedActions.insert_or_assign(currentAttributes->GetKey(), currentAction);
			break;
	}
}	 

// Detaches the action from the appropriate hash map
void InputHandler::DetachAction(Action* currentAction, int key, int type)
{
	switch (type)
	{
		case GLFW_PRESS:
			for (auto it = pressedActions.begin(); it != pressedActions.end();)
				it->second == currentAction ? it = pressedActions.erase(it) : ++it;
			break;
		case GLFW_RELEASE:
			for (auto it = releasedActions.begin(); it != releasedActions.end();)
				it->second == currentAction ? it = releasedActions.erase(it) : ++it;
			break;
	}

	delete currentAction;
}

// Notifier functions telling all observers listening to execute their function
void InputHandler::NotifyPressed(int currentKey)
{
	for (auto& [key, value] : pressedActions)
	{
		if (key == currentKey && value != nullptr)
			value->Execute();
	}
}

void InputHandler::NotifyReleased(int currentKey)
{
	for (auto& [key, value] : releasedActions)
	{
		if (key == currentKey && value != nullptr)
			value->Execute();
	}
}