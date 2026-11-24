#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	if (!(cin >> n)) return 0;
	if (n == 0) {
		cout << "-1 0\n";
		return 0;
	}

	
	vector<pair<int, int>> children(n + 1);
	vector<int> indegree(n + 1, 0);
	for (int id = 1; id <= n; ++id) {
		cin >> children[id].first >> children[id].second;
		for (int child : {children[id].first, children[id].second}) {
			if (child >= 1 && child <= n) ++indegree[child];
		}
	}

	int root = 1;
	for (int id = 1; id <= n; ++id) {
		if (indegree[id] == 0) {
			root = id;
			break;
		}
	}

	queue<int> q;
	vector<bool> visited(n + 1, false);
	q.push(root);
	visited[root] = true;
	int height = 0;
	int maxWidth = 0;

	while (!q.empty()) {
		int levelSize = static_cast<int>(q.size());
		maxWidth = max(maxWidth, levelSize);
		++height;

		while (levelSize-- > 0) {
			int id = q.front();
			q.pop();
			for (int child : {children[id].first, children[id].second}) {
				if (child >= 1 && child <= n && !visited[child]) {
					visited[child] = true;
					q.push(child);
				}
			}
		}
	}

	cout << height << ' ' << maxWidth << '\n';
	return 0;
}
