#include "pch.h"
#include "StructureStage.h"

StructureStage::StructureStage()
{
}

StructureStage::~StructureStage()
{
}

void StructureStage::LoadFile(const std::wstring& path)
{
	std::ifstream ifs;
	ifs.open(path);

	std::string line;

	while (std::getline(ifs, line))
	{
		std::istringstream lineStream(line);
		std::string cell;
		int column = 0;

		StructureStageInfo info;

		while (std::getline(lineStream, cell, ','))
		{
			std::wstring cellWstr(cell.begin(), cell.end());

			switch (column)
			{
            case 0: info.name = cellWstr; break;
            case 1: info.spawnPos.x = std::stof(std::string(cell.begin(), cell.end())); break;
            case 2: info.spawnPos.y = std::stof(std::string(cell.begin(), cell.end())); break;
            case 3: info.keyPos.x = std::stof(std::string(cell.begin(), cell.end())); break;
            case 4: info.keyPos.y = std::stof(std::string(cell.begin(), cell.end())); break;
            case 5: info.wallType = std::stoi(std::string(cell.begin(), cell.end())); break;
            case 6: info.zipLineType = std::stoi(std::string(cell.begin(), cell.end())); break;
            case 7: info.zipLineStartPos.x = std::stof(std::string(cell.begin(), cell.end())); break;
            case 8: info.zipLineStartPos.y = std::stof(std::string(cell.begin(), cell.end())); break;
            case 9: info.zipLineEndPos.x = std::stof(std::string(cell.begin(), cell.end())); break;
            case 10: info.zipLineEndPos.y = std::stof(std::string(cell.begin(), cell.end())); break;
            case 11: info.windowFlickeringCycle = std::stof(std::string(cell.begin(), cell.end())); break;
            case 12: info.windowFlickeringDuration = std::stof(std::string(cell.begin(), cell.end())); break;
			}
			++column;
		}

		_infos.push_back(info);
	}

	ifs.close();
}
