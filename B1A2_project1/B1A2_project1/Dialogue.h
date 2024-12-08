#pragma once
#include "ResourceBase.h"

struct LineInfo
{
	std::wstring speakerName;
	std::wstring speakerID;
	int32 state;
	int32 dir;
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