#pragma once

#include <GLFW/glfw3.h>

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

// Callback function used with recieving input and notifying all observers of said input
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// -------------------------------------------------------------------------------
// ACTION ATTRIBUTES CLASS
// -------------------------------------------------------------------------------

// Class designed to hold all the attributes (key bindings, actions, etc.) for a specified action
class ActionAttributes
{
	private:
		std::string actionName;

		int bindedKey = NULL;
		std::function<void()> actionFunction = nullptr;

		bool toggleableAction = false;
		bool actionUnavailable = false;
	public:
		int& GetKey();
		std::function<void()> GetFunction();
		std::string GetName();

		void SetKey(int currentKey);
		void SetFunction(std::function<void()> currentFunction);
		void SetName(std::string givenName);

		void SetToggleable(bool toggleable);
		void SetUnavailable(bool unavailable);
};

// -------------------------------------------------------------------------------
// ACTION CLASS
// -------------------------------------------------------------------------------

// Class which handles everything to do with the usage of an action
class Action
{
private:
	ActionAttributes* currentAttributes;
public:
	Action();
	~Action();

	ActionAttributes* accessAttributes();

	void Execute();
};

// -------------------------------------------------------------------------------
// ACTION-HANDLER CLASS
// -------------------------------------------------------------------------------

// Handles the memory management + retrieval of created actions
class ActionHandler
{
	private:
		static std::vector<Action*> allCreatedActions;
	public:
		ActionHandler() = delete;
	
		static void CreateAction(int bindedKey, std::function<void()> bindedFunction, std::string bindedName);

		static void AddAction(Action* actionToAdd);
		static void RemoveAction(std::string actionToRemove);

		static void RemoveAllActions();

		static Action* RetrieveAction(std::string bindedName);
};

// -------------------------------------------------------------------------------
// INPUT CLASS
// -------------------------------------------------------------------------------

// Handles how the keyboard events are connected to specific actions (following the observer pattern)
class InputHandler
{
	private:
		static std::unordered_map<int, Action*> pressedActions;
		static std::unordered_map<int, Action*> releasedActions;
	public:
		InputHandler() = delete;

		static void Init(GLFWwindow* window);
		static void ReleaseAllActions();

		static void AttachAction(Action* currentAction, int type);
		static void DetachAction(Action* currentAction, int key, int type);

		// find all actions linked to current key; we will iterate through bindedActions finding all possible keys
		static void NotifyPressed(int currentKey);
		static void NotifyReleased(int currentKey);
};