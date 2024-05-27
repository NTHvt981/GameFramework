#pragma once
#include "Core/APIs/INativeInputAPI.h"
#include <array>
#include <Windows.h>
#include <dinput.h>
#include <wrl/client.h>

namespace logic
{

class DirectInputAPI final : public core::INativeInputAPI
{
public:
	DirectInputAPI(const HWND i_hwnd, const HINSTANCE i_hInstance);
	~DirectInputAPI();

	// Inherited via INativeInputAPI
	void Initialize() override;
	void UpdateInput() override;
	void Shutdown() override;
	void Pause() override;
	void Resume() override;

	// Inherited via INativeInputAPI
	bool IsKeyDown(const core::KeyboardKey i_key) override;
	bool IsKeyUp(const core::KeyboardKey i_key) override;
	bool IsKeyPressed(const core::KeyboardKey i_key) override;
	bool IsKeyRelease(const core::KeyboardKey i_key) override;
	bool IsKeyHold(const core::KeyboardKey i_key) override;

private:
	const HWND m_hwnd;
	const HINSTANCE m_hInstance;

	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	ComPtr<IDirectInput8> m_directInput = nullptr;
	ComPtr<IDirectInputDevice8> m_directInputDevice = nullptr;

	bool m_currentKeys[256];
	bool m_previousKeys[256];
};

} // namespace logic