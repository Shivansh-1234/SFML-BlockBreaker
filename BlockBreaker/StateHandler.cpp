#include "StateHandler.h"

void StateHandler::AddState(StateRef newState, bool isReplacing)
{
	this->_isAdding = true;
	this->_isReplacing = isReplacing;

	this->_newState = std::move(newState);
}

void StateHandler::RemoveState()
{
	this->_isRemoving = true;
}

void StateHandler::ProcessChanges()
{
	if (this->_isRemoving && !this->_state.empty())
	{
		this->_state.pop();

		if (!this->_state.empty())
		{
			this->_state.top()->Resume();
		}
		this->_isRemoving = false;
	}

	

	if (this->_isAdding)
	{
		if (!this->_state.empty())
		{
			if (this->_isReplacing)
			{
				this->_state.pop();
			}

			else
			{
				this->_state.top()->Pause();
			}
		}

		this->_state.push(std::move(this->_newState));
		this->_state.top()->Init();
		this->_isAdding = false;
	}
}

StateRef& StateHandler::GetActiveState()
{
	return this->_state.top();
}
