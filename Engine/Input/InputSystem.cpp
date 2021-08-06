#include "InputSystem.h"

#include <SDL.h>

namespace nh
{
	void InputSystem::Startup()
	{
		const uint8_t* keyboardStateSDL = SDL_GetKeyboardState(&numKeys);
		keyboardState.resize(numKeys);
		std::copy(keyboardStateSDL + 0, keyboardStateSDL + numKeys, keyboardState.begin());
		prevKeyboardState = keyboardState;
	}

	void InputSystem::Shutdown()
	{

	}

	void InputSystem::Update(float dt)
	{
		prevKeyboardState = keyboardState;
		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardStateSDL + 0, keyboardStateSDL + numKeys, keyboardState.begin());
	}

	InputSystem::eKeyState InputSystem::GetKeyState(int id)
	{
		eKeyState state = eKeyState::Idle;
		bool keyDown = IsKeyDown(id);
		bool prevKeyDown = IsPreviousKeyDown(id);

		if (keyDown) { state = (prevKeyDown) ? eKeyState::Held : eKeyState::Pressed; }
		else { state = (prevKeyDown) ? eKeyState::Release : eKeyState::Idle; }

		return state;
	}

	bool InputSystem::IsKeyDown(int id)
	{
		return keyboardState[id];
	}

	bool InputSystem::IsPreviousKeyDown(int id)
	{
		return prevKeyboardState[id];
	}
}