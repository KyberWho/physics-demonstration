#include "Input.h"
#include "Logger.h"

// -------------------------------------------------------------------------------
// CALLBACK FUNCTIONS
// -------------------------------------------------------------------------------

// Recieves input and notifies all observers of said input
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
int ActionAttributes::GetKey() const { return m_BindedKey; }
void ActionAttributes::SetKey(int currentKey)
{
	m_BindedKey = currentKey;
}

std::string ActionAttributes::GetName() const { return m_ActionName; }
void ActionAttributes::SetName(const std::string& givenName)
{
	m_ActionName = givenName;
}

std::function<void()> ActionAttributes::GetFunction() const { return m_ActionFunction; }
void ActionAttributes::SetFunction(const std::function<void()> currentFunction)
{
	m_ActionFunction = currentFunction;
}

void ActionAttributes::SetToggleable(bool toggleable)
{
	m_Toggleable = toggleable;
}

void ActionAttributes::SetUnavailable(bool unavailable)
{
	m_Unavailable = unavailable;
}

// -------------------------------------------------------------------------------
// ACTION CLASS
// -------------------------------------------------------------------------------

Action::Action()
{
	m_CurrentAttributes = new ActionAttributes();
}

Action::~Action()
{
	delete m_CurrentAttributes;
}

ActionAttributes* Action::AccessAttributes() const { return m_CurrentAttributes; }

void Action::Execute() const
{
	std::function<void()> executableFunction = m_CurrentAttributes->GetFunction();
	executableFunction();
}

// -------------------------------------------------------------------------------
// ACTION-HANDLER CLASS
// -------------------------------------------------------------------------------

// Vector to keep track + store all the action objects inside
std::vector<Action*> ActionHandler::m_AllCreatedActions;

// Creates an action with the given parameters
void ActionHandler::CreateAction(int bindedKey, const std::function<void()> bindedFunction, const std::string& bindedName)
{
	Action* newAction = new Action();
	ActionAttributes* attributes = newAction->AccessAttributes();
	
	attributes->SetKey(bindedKey);
	attributes->SetFunction(bindedFunction);
	attributes->SetName(bindedName);

	ActionHandler::AddAction(newAction);
}

// Adds/removes the action from the main vector
void ActionHandler::AddAction(Action* actionToAdd)
{
	m_AllCreatedActions.push_back(actionToAdd);
}

void ActionHandler::RemoveAction(std::string actionToRemove)
{
	Action* currentAction = ActionHandler::RetrieveAction(actionToRemove);
	if (currentAction == nullptr)
	{
		LOG_WARN("Unable to remove action as it isn't in the list!");
		return;
	}

	for (std::vector<Action*>::iterator it = m_AllCreatedActions.begin(); it != m_AllCreatedActions.end();)
	{
		if (*it == currentAction)
		{
			m_AllCreatedActions.erase(it);
			delete currentAction;
			break;
		}
	}

	m_AllCreatedActions.shrink_to_fit();
}

void ActionHandler::RemoveAllActions()
{
	if (!m_AllCreatedActions.empty()) m_AllCreatedActions.clear();
}

// Retrieves a given action when given the name of the action
// TODO: Will optimise in the future, for now just doing basic linear search
Action* ActionHandler::RetrieveAction(std::string bindedName)
{
	ActionAttributes* attributes;

	for (Action* currentAction : m_AllCreatedActions)
	{
		attributes = currentAction->AccessAttributes();
		if (attributes->GetName().compare(bindedName) == 0)
		{
			return currentAction;
		}
	}

	LOG_WARN("No action was found of name: " << bindedName);
	return nullptr;
}

Action* ActionHandler::RetrieveLastAction()
{
	if (!m_AllCreatedActions.empty()) return m_AllCreatedActions.back();

	return nullptr;
}

// -------------------------------------------------------------------------------
// INPUT CLASS
// -------------------------------------------------------------------------------

// Hashmaps linking the keys to the actions
std::unordered_map<int, const Action*> InputHandler::m_PressedActions;
std::unordered_map<int, const Action*> InputHandler::m_ReleasedActions;

void InputHandler::Init(GLFWwindow* window)
{
    glfwSetKeyCallback(window, KeyCallback);
}

void InputHandler::ReleaseAllActions()
{
	if (!m_PressedActions.empty())
		m_PressedActions.clear();

	if (!m_ReleasedActions.empty())
		m_ReleasedActions.clear();
}

// Attaches the action to the appropriate hash maps
void InputHandler::AttachAction(const Action* currentAction, int type)
{	 
	if (currentAction == nullptr)
	{
		LOG_ERR("Unable to attach given action!");
		return;
	}

	ActionAttributes* currentAttributes = currentAction->AccessAttributes();
	switch (type)
	{
		case GLFW_PRESS:
			m_PressedActions.insert_or_assign(currentAttributes->GetKey(), currentAction);
			break;
		case GLFW_RELEASE:
			m_ReleasedActions.insert_or_assign(currentAttributes->GetKey(), currentAction);
			break;
	}
}	 

// Detaches the action from the appropriate hash map
void InputHandler::DetachAction(const Action* currentAction, int key, int type)
{
	if (currentAction == nullptr)
	{
		LOG_WARN("Passed in a nullptr to DetachAction!");
		return;
	}

	switch (type)
	{
		case GLFW_PRESS:
			for (auto it = m_PressedActions.begin(); it != m_PressedActions.end();)
				it->second == currentAction ? it = m_PressedActions.erase(it) : ++it;
			break;
		case GLFW_RELEASE:
			for (auto it = m_ReleasedActions.begin(); it != m_ReleasedActions.end();)
				it->second == currentAction ? it = m_ReleasedActions.erase(it) : ++it;
			break;
	}

	delete currentAction;
}

// Notifier functions telling all observers listening to execute their function
void InputHandler::NotifyPressed(int currentKey)
{
	for (auto& [key, value] : m_PressedActions)
	{
		if (key == currentKey && value != nullptr)
			value->Execute();
	}
}

void InputHandler::NotifyReleased(int currentKey)
{
	for (auto& [key, value] : m_ReleasedActions)
	{
		if (key == currentKey && value != nullptr)
			value->Execute();
	}
}