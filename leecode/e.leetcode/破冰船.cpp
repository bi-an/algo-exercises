/*
 * @Author: bi_an:desktop 2608120872@qq.com
 * @Date: 2022-05-25 20:46:00
 * @LastEditors: bi_an:desktop 2608120872@qq.com
 * @LastEditTime: 2022-05-25 21:33:51
 * @FilePath: \practice\leecode\e.leetcode\破冰船.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <limits.h>
#include <memory>
using namespace std;

/// 广度优先搜索 + 双端队列
/// 每次 dis 变化则加到双端队列的尾部，如果不变则加到双端队列的头部，每次读取 dis 都从队列头部，
/// 这样可以保证，在当前层没有遍历完的情况下，绝对不会进入下一层。因为只要当前层没有遍历完，那么就
/// 会往头部追加元素。
class Solution {
	const int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0,1} }; // 方向

	deque<pair<int, int>> q; // 双端队列，保证头部元素小于尾部
	int dis[505][505]; // 从起始点到达当前位置破冰的数量

public:
	int icebreaker(vector<string>& grid) {
		int m = grid.size(), n = grid[0].size();
		memset(dis, 0x3f, sizeof dis); // 初始化为无穷大
		int inf;
		memset(&inf, 0x3f, sizeof inf);

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (grid[i][j] == 'S') {
					dis[i][j] = 0;
					q.emplace_back(i, j); // 找到破冰船初始位置，并追加到双端队列尾部
				}
			}
		}

		// 广度优先搜索
		while (!q.empty()) {
			int x = q.front().first, y = q.front().second;
			q.pop_front();

			// 遍历上下左右
			for (int i = 0; i < 4; ++i) {
				int cx = x + dirs[i][0], cy = y + dirs[i][1]; // 当前坐标
				if (cx < 0 || cx >= m || cy < 0 || cy >= n)
					continue;// 越界
				
				if (grid[cx][cy] == '#' || dis[cx][cy] < inf) // 遇到障碍物或已经访问过
					continue; // 遇到障碍无需更新 dis ，因为判断障碍物的时间和判断是否访问过的时间相同，且可以一次同时判断

				if (grid[cx][cy] == '.') // 遇到可通行水域，权值不变，追加到队列头：可以理解为可通行水域可视为遍历的同一层（深度）
				{
					dis[cx][cy] = dis[x][y];
					q.emplace_front(cx, cy);
				}
				else if (grid[cx][cy] == '*') { // 遇到冰层，权值加1，追加位置信息到队列尾
					dis[cx][cy] = dis[x][y] + 1;
					q.emplace_back(cx, cy);
				}
			}
		}

		int ans = inf;
		// 遍历所有边界，找出答案
		for (int i = 0; i < m; ++i)
			ans = min(ans, min(dis[i][0], dis[i][n - 1]));
		for (int j = 0; j < n; ++j)
			ans = min(ans, min(dis[0][j], dis[m - 1][j]));

		return ans;
	}
};