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
	std::ifstream ifs;
	ifs.imbue(std::locale("ko_KR.UTF-8"));
	ifs.open(path);

	std::string line;

	while (std::getline(ifs, line))
	{
		std::istringstream lineStream(line);
		std::string cell;
		int column = 0;

		while (std::getline(lineStream, cell, ','))
		{
			switch (column)
			{
			case 0: 
				int32 ID = std::stoi(cell);

			}
		}
	}

}
