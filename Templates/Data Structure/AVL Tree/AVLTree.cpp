struct Node {
	int val;
	Node* left;
	Node* right;
	int height, subsize;
	Node(int _val) {
		val = _val;
		left = right = NULL;
		height = subsize = 1;
	}
};

struct AVLTree {

	Node* root;

	int height(Node* node) {
		if (node) return node->height;
		return 0;
	}

	int subsize(Node* node) {
		if (node) return node->subsize;
		return 0;
	}

	int bfactor(Node* node) {
		return height(node->right) - height(node->left);
	}

	void fix(Node* node) {
		node->height = max(height(node->right), height(node->left)) + 1;
		node->subsize = subsize(node->right) + subsize(node->left) + 1;
	}

	Node* rotateRight(Node* p) {
		Node* q = p->left;
		p->left = q->right;
		q->right = p;
		fix(p);
		fix(q);
		return q;
	}

	Node* rotateLeft(Node* p) {
		Node* q = p->right;
		p->right = q->left;
		q->left = p;
		fix(p);
		fix(q);
		return q;
	}

	Node* balance(Node* node) {
		fix(node);
		if (bfactor(node) == 2) {	// need rotateLeft
			if (bfactor(node->right) < 0) {
				node->right = rotateRight(node->right);
			}
			return rotateLeft(node);
		}
		else if (bfactor(node) == -2) {	// need rotateRight
			if (bfactor(node->left) > 0) {
				node->left = rotateLeft(node->left);
			}
			return rotateRight(node);
		}
		return node;
	}

	Node* insert(Node* node, int val) {
		if (!node) return new Node(val);
		if (val < node->val) {
			node->left = insert(node->left, val);
		}
		else {
			node->right = insert(node->right, val);
		}
		return balance(node);
	}

	Node* findMin(Node* node) {
		if (node->left) return findMin(node->left);
		return node;
	}

	Node* removeMin(Node* node) {
		if (node->left == NULL) return node->right;
		node->left = removeMin(node->left);
		return balance(node);
	}

	Node* remove(Node* node, int val) {
		if (!node) return NULL;
		if (val < node->val) {
			node->left = remove(node->left, val);
		}
		else if (val > node->val) {
			node->right =remove(node->right, val);
		}
		else{
			Node* nodeLeft = node->left;
			Node* nodeRight = node->right;
			delete node;
			if (!nodeRight) return nodeLeft;
			Node* minn = findMin(nodeRight);
			minn->right = removeMin(nodeRight);
			minn->left = nodeLeft;
			return balance(minn);
		}
		return balance(node);
	}
};

AVLTree avl;

int main() {
	avl.root = avl.insert(avl.root, 1);
	avl.root = avl.remove(avl.root, 1);
}