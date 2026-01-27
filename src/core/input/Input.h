#pragma once

#include <GLFW/glfw3.h>

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

// TODO: Need to add in a factory design pattern for creating actions + action attributes (to do in future iterations)

// -------------------------------------------------------------------------------
// CALLBACK FUNCTIONS
// -------------------------------------------------------------------------------

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// -------------------------------------------------------------------------------
// ACTION ATTRIBUTES CLASS
// -------------------------------------------------------------------------------

// Class designed to hold all the attributes (key bindings, actions, etc.) for a specified action
class ActionAttributes
{
	private:
		std::string m_ActionName;

		int m_BindedKey = NULL;
		std::function<void()> m_ActionFunction = nullptr;

		bool m_Toggleable = false;
		bool m_Unavailable = false;
	public:
		int GetKey() const;
		std::function<void()> GetFunction() const;
		std::string GetName() const;

		void SetKey(const int currentKey);
		void SetFunction(const std::function<void()> currentFunction);
		void SetName(const std::string& givenName);

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
	ActionAttributes* m_CurrentAttributes;
public:
	Action();
	~Action();

	ActionAttributes* AccessAttributes() const;

	void Execute() const;
};

// -------------------------------------------------------------------------------
// ACTION-HANDLER CLASS
// -------------------------------------------------------------------------------

// Handles the memory management + retrieval of created actions
class ActionHandler
{
	private:
		static std::vector<Action*> m_AllCreatedActions;
	public:
		ActionHandler() = delete;
	
		static void CreateAction(int bindedKey, const std::function<void()> bindedFunction, const std::string& bindedName);

		// This handles the ability to create non-returning actions for specific objects
		template<typename T>
		static void CreateAction(int bindedKey, void (T::*bindedFunction)(), T* instance, const std::string& bindedName)
		{
			std::function<void()> func = [bindedFunction, instance]()
				{
					(instance->*bindedFunction)();
				};

			CreateAction(bindedKey, func, bindedName);
		}

		static void AddAction(Action* actionToAdd);
		static void RemoveAction(std::string actionToRemove);

		static void RemoveAllActions();

		static Action* RetrieveAction(std::string bindedName);
		static Action* RetrieveLastAction();
};

// -------------------------------------------------------------------------------
// INPUT CLASS
// -------------------------------------------------------------------------------

// Handles how the keyboard events are connected to specific actions (following the observer pattern)
class InputHandler
{
	private:
		// Made const to avoid accidental modification of actions
		static std::unordered_map<int, const Action*> m_PressedActions;
		static std::unordered_map<int, const Action*> m_ReleasedActions;
	public:
		InputHandler() = delete;

		static void Init(GLFWwindow* window);
		static void ReleaseAllActions();

		static void AttachAction(const Action* currentAction, int type);
		static void DetachAction(const Action* currentAction, int key, int type);

		// find all actions linked to current key; we will iterate through bindedActions finding all possible keys
		static void NotifyPressed(int currentKey);
		static void NotifyReleased(int currentKey);
};