#pragma once
#include <vector>

class StateMap {
public:
	enum class direction {
		up,
		down,
		right,
		left
	};
private:
	enum class state {
		empty,
		wall,
		chest
	};

	class Chest {
	public:
		int x, y;
		Chest(int x, int y) :x(x), y(y) {};

	};
	int width, height;
	std::pair<int, int> player;
	std::vector<std::pair<int, int>> walls, targets;
	std::vector<Chest> chests;

	state whatsThere(int x, int y);
	std::pair<int, int> getNextBlock(std::pair<int, int>, direction);
	bool checkSuccess();

public:
	bool move(direction dir);
	StateMap(int width, int height,
		std::pair<int, int> player,
		std::vector<std::pair<int, int>> walls,
		std::vector<std::pair<int, int>> targets,
		std::vector<std::pair<int, int>> chestsPos);

	//获取地图宽度
	int getWidth() { return width; };
	//获取地图高度
	int getHeight() { return height; };
	//获取玩家位置
	std::pair<int, int> getPlayer() { return player; };
	//获取墙壁位置
	std::vector<std::pair<int, int>> getWalls() { return walls; };
	//获取目标位置
	std::vector<std::pair<int, int>> getTargets() { return targets; };
	//获取箱子位置
	std::vector<std::pair<int, int>> getChests() {
		std::vector<std::pair<int, int>> chestsPos;
		for (auto& i : chests) {
			chestsPos.push_back(std::make_pair(i.x, i.y));
		}
		return chestsPos;
	};
};
