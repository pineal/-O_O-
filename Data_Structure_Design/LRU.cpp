// doubly-linked list node
template <class K, class V>
class Node {
	public:
		Node* next;
		Node* prev;
		K key;
		V value;
		Node(K key, V value) {
			this -> key = key;
			this -> value = value;
			next = nullptr;
			prev = nullptr;
		}

		void update(K key, V value) {
			this -> key = key;
			this -> value = value;
		}
};

template <class K, class V>
class LRU {
	public:
		int size;
		int limit;
		Node<K, V>* head;
		Node<K, V>* tail;
		unordered_map<K, Node<K,V>*>* ma;

		LRU(int limit) {
			this -> limit = limit;
			this -> size = 0;
			ma = new map<K, Node<K,V>*>();
			head = tail = nullptr;
		}

		void set(K key, V value) {
			Node<K, V>* node = nullptr;
			if (ma->find(key) != ma -> end()) {
				//if the key exists in the cache, 
				//we need to update its value
				//and move it to head
				node = (*ma)[key];
				node -> value = value;
				remove(node);
			} else if (map.size() < limit) {
				//if the key is not in the cache and
				//we still have space,
				//we can append a new node to head
				node = new Node<K, V>(key, value);
			} else {
				//if the key is not in the cache and
				//we don't have space, we need to evict 
				//the tail and reuse the node let it 
				//maintain the new key, value and put it
				//to head
				node = tail;
				remove(node);
				node->update(key, value);
			}
			append(node);
		}

		bool get(K key, V & value) {
			if (ma -> find(key) == ma -> end()) {
				return false;
			}		
			//we need to move the node to the head
			Node<K, V>* node = (*ma)[key];
			remove(node);
			append(node);
			value = node -> value;
			return true;
		}

		Node<K,V>* remove(Node<K, V>* node) {
			ma->erase(node->key);
			size--;
			if (node -> prev != nullptr) {
				node -> prev -> next = node -> next;
			}
			if (node -> next != nullptr) {
				node -> next -> prev = node -> prev;
			}
			if (node == head) {
				head = head -> next;
			}
			if (node == tail) {
				tail = tail -> prev;
			}
			node -> next = node -> prev = nullptr;
			return node;
		}

		Node<K, V>* append(Node<K, V>* node) {
			(*ma)[node -> key] = node;
			size++;
			if (head == nullptr) {
				head = tail = node;
			} else {
				node -> next = head;
				head -> prev = node;
				head = node;
			}
			return node;
		}
};
