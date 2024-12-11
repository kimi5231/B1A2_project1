#include "pch.h"
#include "Item.h"
#include <fstream>
#include <iostream>
#include <string>

Item::Item()
{
}

Item::~Item()
{
}

void Item::LoadFile(const std::wstring& path)
{
	std::wifstream ifs;
	ifs.imbue(std::locale("ko_KR.UTF-8"));
	ifs.open(path);

    std::wstring line;

    // 한 줄씩 읽어서 처리
    while (std::getline(ifs, line))
    {
        if (line.empty())
            continue;

        std::wstringstream wiss(line);
        auto* info = new ItemInfo(); // 동적 할당

        std::getline(wiss, info->ID, L',');

        std::getline(wiss, info->name, L',');
        
        std::getline(wiss, info->explain);
        // 개행 문자
        int32 start = 0;
        while ((start = info->explain.find(L"\\n", start)) != std::wstring::npos)
        {
            info->explain.replace(start, 2, L"\n");
            start += 1;
        }

        // 메모리 누수 방지용 - 근데 지금은 필요없어서 보류...
        //if (!std::getline(wiss, info->ID, L',')) { delete info; continue; }
        //if (!std::getline(wiss, info->name, L',')) { delete info; continue; }
        //if (!std::getline(wiss, info->explain)) { delete info; continue; }

        _items[info->ID] = info;
    }

    ifs.close();
}
