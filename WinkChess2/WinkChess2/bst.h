#pragma once

//template<typename K, typename V> class BSTNode {
//public:
//	BSTNode<K, V>* left;
//	BSTNode<K, V>* right;
//	K key;
//	V value;
//
//	BSTNode(K k, V v) {
//		key = k;
//		value = v;
//		left = nullptr;
//		right = nullptr;
//	}
//
//	void Add(BSTNode<K, V> node) {
//		if (node.key < key)
//			if (left) left->Add(node);
//			else left = &node;
//		else
//			if (right) right->Add(node);
//			else right = &node;
//	}
//
//	void Add(K key, V value) {
//		BSTNode<K, V> node(key, value);
//		Add(node);
//	}
//
//	bool Exists(K k) {
//		this;
//		if (key == k) return true;
//		else if (k < key)
//			if (left != nullptr) return left->Exists(k);
//			else return false;
//		else
//			if (right != nullptr) return right->Exists(k);
//			else return false;
//	}
//
//	V Get(K k) {
//		if (key == k) return k;
//		else if (k < key)
//			if (left) return left->Get(k);
//			else return nullptr;
//		else
//			if (right) return right->Get(k);
//			else return nullptr;
//	}
//
//	void Set(K k, V v) {
//		if (key == k) value = v;
//		else if (k < key && left) left->Set(k, v);
//		else if (k >= key && right) right->Set(k, v);
//	}
//};
//
//template<typename K, typename V> class BSTTree {
//public:
//
//protected:
//	BSTNode<K, V>* buckets;
//	int n_buckets;
//};

template<typename K, typename V> class BSTNode {
public:
	K key;
	V value;
	BSTNode<K, V>* left;
	BSTNode<K, V>* right;

	BSTNode(K k, V v) {
		key = k;
		value = v;
		left = nullptr;
		right = nullptr;
	}
};

typedef enum BSTStatus { SUCCESS, KEY_NOT_FOUND, NO_DATA } BSTStatus;

template<typename K, typename V> class BST {
public:
	BSTNode<K, V>* root;

	BST(int prealloc) {
		// make the root node of the tree
		root = new BSTNode<K, V>(0, 0);

		// pre-allocate memory for new tree branches
		_prealloc = (BSTNode<K, V>*)malloc(sizeof(BSTNode<K, V>) * prealloc);
		_n_prealloc = prealloc;
		_prealloc_used = 0;
	}
	
	void Add(K key, V value) {
		BSTNode<K, V>* current = root;

		_done = 0;
		while (_done == 0) {
			if (key < current->key) {
				if (current->left == nullptr) {
					if (_prealloc_used < _n_prealloc) {
						_prealloc[_prealloc_used] = BSTNode<K, V>(key, value);
						current->left = _prealloc + _prealloc_used;
						_prealloc_used++;
						_done = 1;
					}
					else {
						current->left = new BSTNode<K, V>(key, value);
					}
				}
				else current = current->left;
			}
			else {
				if (current->right == nullptr) {
					if (_prealloc_used < _n_prealloc) {
						_prealloc[_prealloc_used] = BSTNode<K, V>(key, value);
						current->right = _prealloc + _prealloc_used;
						_prealloc_used++;
						_done = 1;
					}
					else {
						current->right = new BSTNode<K, V>(key, value);
					}
				}
				else current = current->right;
			}
		}
	}

	bool AddUnique(K key, V value) {
		BSTNode<K, V>* current = root;


	}

	V Get(K key, BSTStatus* status) {
		*status = BSTStatus::SUCCESS;

		// get top node
		BSTNode<K, V>* current;
		if (root->right != nullptr && root->left != nullptr) current = (key < root->key) ? root->left : root->right;
		else if (root->right != nullptr) current = root->right;
		else if (root->left != nullptr) current = root->left;
		else {
			*status = BSTStatus::NO_DATA;
			return (V)NULL;
		}

		while (true) {
			if (current->key == key) return current->value;
			else if (key < current->key) {
				if (current->left == nullptr) {
					*status = BSTStatus::KEY_NOT_FOUND;
					return (V)NULL;
				}
				else current = current->left;
			}
			else {
				if (current->right == nullptr) {
					*status = BSTStatus::KEY_NOT_FOUND;
					return (V)NULL;
				}
				else current = current->right;
			}
		}
	}

	void Set(K key, V value, BSTStatus* status) {
		*status = BSTStatus::SUCCESS;
		
		// get top node
		BSTNode<K, V>* current;
		if (root->right != nullptr && root->left != nullptr) current = (key < root->key) ? root->left : root->right;
		else if (root->right != nullptr) current = root->right;
		else if (root->left != nullptr) current = root->left;
		else {
			*status = BSTStatus::NO_DATA;
			return;
		}

		while (true) {
			if (current->key == key) {
				current->value = value;
				return;
			}
			else if (key < current->key) {
				if (current->left == nullptr) {
					*status = BSTStatus::KEY_NOT_FOUND;
					return;
				}
				else current = current->left;
			}
			else {
				if (current->right == nullptr) {
					*status = BSTStatus::KEY_NOT_FOUND;
					return;
				}
				else current = current->right;
			}
		}
	}

	BSTNode<K, V>* Min(BSTStatus* status) {
		*status = BSTStatus::SUCCESS;

		BSTNode<K, V>* current;
		if (root->left != nullptr) current = root->left;
		else if (root->right != nullptr) current = root->right;
		else {
			*status = BSTStatus::NO_DATA;
			return (BSTNode<K, V>*)NULL;
		}

		while (true) {
			if (current->left != nullptr) current = current->left;
			else return current;
		}
	}

	BSTNode<K, V>* Max(BSTStatus* status) {
		*status = BSTStatus::SUCCESS;

		BSTNode<K, V>* current;
		if (root->right != nullptr) current = root->right;
		else if (root->left != nullptr) current = root->left;
		else {
			*status = BSTStatus::NO_DATA;
			return (BSTNode<K, V>*)NULL;
		}

		while (true) {
			if (current->right != nullptr) current = current->right;
			else return current;
		}
	}

	V operator [](int index) {
		BSTStatus status;
		return Get(index, &status);
	}

private:
	// pre-allocation
	BSTNode<K, V>* _prealloc;
	int _n_prealloc;
	int _prealloc_used;

	char _done;
};