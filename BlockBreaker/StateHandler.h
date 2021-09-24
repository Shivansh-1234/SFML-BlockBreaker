#pragma once

#include <memory>
#include <stack>

#include "State.h"

typedef std::unique_ptr<State> StateRef;

class StateHandler
{
private:
	std::stack<StateRef> _state;
	StateRef _newState;

	bool _isRemoving, _isAdding, _isReplacing;
public:
	StateHandler() {}
	~StateHandler() {}

	void AddState(StateRef newState, bool isReplacing = true);
	void RemoveState();

	void ProcessChanges();

	StateRef& GetActiveState();
};

