 #include <iostream>

struct Node {
	int key;
	Node* left;
	Node* right;
	explicit Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int key) {
	if (!root) return new Node(key);
	if (key < root->key) root->left = insert(root->left, key);
	else if (key > root->key) root->right = insert(root->right, key);
	return root;
}

Node* removeMinimum(Node* root) {
	if (!root->left) {
		Node* right = root->right;
		delete root;
		return right;
	}
	root->left = removeMinimum(root->left);
	return root;
}

Node* removeKey(Node* root, int key) {
	if (!root) return nullptr;
	if (key < root->key) {
		root->left = removeKey(root->left, key);
	} else if (key > root->key) {
		root->right = removeKey(root->right, key);
	} else if (!root->left) {
		Node* right = root->right;
		delete root;
		return right;
	} else if (!root->right) {
		Node* left = root->left;
		delete root;
		return left;
	} else {
		Node* successor = root->right;
		while (successor->left) successor = successor->left;
		root->key = successor->key;
		root->right = removeMinimum(root->right);
	}
	return root;
}

void printPreorder(const Node* root, bool& first) {
	if (!root) return;
	if (!first) std::cout << ' ';
	std::cout << root->key;
	first = false;
	printPreorder(root->left, first);
	printPreorder(root->right, first);
}

void destroy(Node* root) {
	if (!root) return;
	destroy(root->left);
	destroy(root->right);
	delete root;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	if (!(std::cin >> n)) return 0;
	Node* root = nullptr;
	for (int i = 0, key; i < n; ++i) {
		std::cin >> key;
		root = insert(root, key);
	}

	int q;
	std::cin >> q;
	for (int i = 0, key; i < q; ++i) {
		std::cin >> key;
		root = removeKey(root, key);
	}

	bool first = true;
	printPreorder(root, first);
	std::cout << '\n';
	destroy(root);
	return 0;
}
