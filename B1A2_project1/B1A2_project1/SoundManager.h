#pragma once
#include <fmod.hpp>
#include "Sound.h"	// SoundType 때문에 어쩔 수 없이 include 함

class SoundManager
{
	DECLARE_SINGLE(SoundManager);

	~SoundManager();

public:
	void Init(HWND hwnd);
	void Play(const std::wstring& key, SoundType type, bool loop = false);
	void Stop(const std::wstring& key);
	void StopAll();

	FMOD::System* GetSystem() const { return _system; }

private:
	FMOD::System* _system = nullptr; // FMOD 시스템 객체
	std::unordered_map<std::wstring, Sound*> _sounds; // 로드된 사운드 저장소
};

