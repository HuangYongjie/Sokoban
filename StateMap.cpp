#include "StateMap.h"

StateMap::state StateMap::whatsThere(int x, int y) {
    for (auto& i : walls) {
        if (i.first == x && i.second == y) {
			return state::wall;
		}
	}
    for (auto& i : chests) {
        if (i.x == x && i.y == y) {
			return state::chest;
		}
	}
	//当坐标超出地图范围时，返回wall
	if (x < 0 || x >= width || y < 0 || y >= height) {
		return state::wall;
	}
	return state::empty;
}

std::pair<int, int> StateMap::getNextBlock(std::pair<int, int> thisBlock, direction dir) {
    switch (dir) {
	case direction::up:
		return std::make_pair(thisBlock.first, thisBlock.second - 1);
	case direction::down:
		return std::make_pair(thisBlock.first, thisBlock.second + 1);
	case direction::left:
		return std::make_pair(thisBlock.first - 1, thisBlock.second);
	case direction::right:
		return std::make_pair(thisBlock.first + 1, thisBlock.second);
	default:
		return std::make_pair(-1, -1);
	}
}

bool StateMap::checkSuccess() {
	//检测所有targets，若所有targets位置都存在chest，则返回1，否则返回0
	bool success(false);
	for (auto& i : targets) {
		bool flag = false;
		for (auto& j : chests) {
			if (i.first == j.x && i.second == j.y) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			success = false;
			break;
		}
		else {
			success = true;
		}
	}
	return success;
}

bool StateMap::move(direction dir) {
	auto playerBlock = std::make_pair(player.first, player.second);
	auto nextBlock = getNextBlock(playerBlock, dir);
	auto nextBlockState = whatsThere(nextBlock.first, nextBlock.second);
	switch (nextBlockState) {
		case state::empty:
			player = nextBlock;
			return false;
		case state::wall:
			return false;
		case state::chest:
			auto nextNextBlock = getNextBlock(nextBlock, dir);
			auto nextNextBlockState = whatsThere(nextNextBlock.first, nextNextBlock.second);
			//若下下个方块为空，则移动箱子，并检查是否已完成目标
			if (nextNextBlockState == state::empty) {
				for (auto& i : chests) {
					if (i.x == nextBlock.first && i.y == nextBlock.second) {
						i.x = nextNextBlock.first;
						i.y = nextNextBlock.second;
						break;
					}
				}
				player = nextBlock;
				return checkSuccess();
			}
			else {
				return false;
			}
	}
    return false;
}

StateMap::StateMap(int width, 
	int height, std::pair<int, int> player,
	std::vector<std::pair<int, int>> walls,
	std::vector<std::pair<int, int>> targets,
	std::vector<std::pair<int, int>> chestsPos) :width(width), height(height){
	this->player = player;
	this->walls = walls;
	this->targets = targets;
	chests = {};
	for (auto& i : chestsPos) {
		chests.push_back(Chest(i.first, i.second));
	}
}
