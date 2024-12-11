#include "pch.h"
#include "Dialogue.h"
#include <fstream>
#include <iostream>
#include <string>

Dialogue::Dialogue()
{
}

Dialogue::~Dialogue()
{
}

void Dialogue::LoadFile(const std::wstring& path)
{
	std::wifstream ifs;

	// 한글 인코딩 설정
	ifs.imbue(std::locale("ko_KR.UTF-8"));

	ifs.open(path);

	// 이벤트 저장을 위한 키, 값 변수
	std::wstring key;
	std::vector<LineInfo> infos;

	std::wstring str;

	while (std::getline(ifs, str))
	{
		// 문자열 스트림 생성
		std::wistringstream wiss(str);

		std::wstring eventName;
		std::getline(wiss, eventName, L',');

		if (eventName == L"end")
		{
			_lines[key] = infos;
			continue;
		}
		else if (!eventName.empty())
		{
			key = eventName;
			continue;
		}
		
		LineInfo info;

		std::getline(wiss, info.speakerName, L',');

		// 문자열 정수로 변환
		std::wstring id;
		std::getline(wiss, id, L',');
		info.speakerID = std::stoi(id);

		// 문자열 정수로 변환
		std::wstring state;
		std::getline(wiss, state, L',');
		info.state = std::stoi(state);

		std::wstring dir;
		std::getline(wiss, dir, L',');
		info.dir = std::stoi(dir);

		std::getline(wiss, info.speech, L',');
		// 개행문자 처리
		int32 start = 0;
		while ((start = info.speech.find(L"\\n", start))!= std::wstring::npos)
		{
			info.speech.replace(start, 2, L"\n");
			start += 1;
		}

		infos.push_back(info);
	}

	ifs.close();
}