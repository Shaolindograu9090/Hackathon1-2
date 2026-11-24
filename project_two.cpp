#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, root;
	if (!(cin >> n >> root)) return 0;

	vector<int> leftChild(n + 1), rightChild(n + 1);
	for (int id = 1; id <= n; ++id) {
		cin >> leftChild[id] >> rightChild[id];
	}

	vector<int> preorder, inorder, postorder;
	if (root != 0) {
		// Pre-order: node, left, right.
		stack<int> nodes;
		nodes.push(root);
		while (!nodes.empty()) {
			int node = nodes.top();
			nodes.pop();
			preorder.push_back(node);
			if (rightChild[node] != 0) nodes.push(rightChild[node]);
			if (leftChild[node] != 0) nodes.push(leftChild[node]);
		}

		// In-order: left, node, right.
		int current = root;
		while (current != 0 || !nodes.empty()) {
			while (current != 0) {
				nodes.push(current);
				current = leftChild[current];
			}
			current = nodes.top();
			nodes.pop();
			inorder.push_back(current);
			current = rightChild[current];
		}

		// Post-order: left, right, node.
		stack<pair<int, bool>> pending;
		pending.push({root, false});
		while (!pending.empty()) {
			auto [node, visited] = pending.top();
			pending.pop();
			if (visited) {
				postorder.push_back(node);
			} else {
				pending.push({node, true});
				if (rightChild[node] != 0) pending.push({rightChild[node], false});
				if (leftChild[node] != 0) pending.push({leftChild[node], false});
			}
		}
	}

	auto printTraversal = [](const vector<int>& traversal) {
		for (size_t i = 0; i < traversal.size(); ++i) {
			if (i > 0) cout << ' ';
			cout << traversal[i];
		}
		cout << '\n';
	};

	printTraversal(preorder);
	printTraversal(inorder);
	printTraversal(postorder);
	return 0;
}
