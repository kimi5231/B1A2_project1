#pragma once
#include "ResourceBase.h"

struct LineInfo
{
	std::wstring speakerName;
	int32 speakerID;
	int32 state;
	int32 dir;
	std::wstring type;
	std::wstring cutScene;
	float posX;
	float posY;
	std::wstring speech;
};

class Dialogue : public ResourceBase
{
public:
	Dialogue();
	virtual ~Dialogue() override;

public:
	virtual void LoadFile(const std::wstring& path) override;

public:
	std::vector<LineInfo>& GetEvent(const std::wstring& key) { return _lines[key]; }

private:
	std::unordered_map<std::wstring, std::vector<LineInfo>> _lines;
};