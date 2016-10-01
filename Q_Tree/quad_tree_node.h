#pragma once
#include <list>
using namespace std;

enum QuadType {
	ROOT,
	UP_RIGHT,
	UP_LEFT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT
};

template <typename T>
class QuadTreeNode {
	private:
		list<T*> objects_;
		QuadTreeNode* parent_;
		QuadTreeNode* up_right_node_;
		QuadTreeNode* up_left_node_;
		QuadTreeNode* bottom_right_node_;
		QuadTreeNode* bottom_left_node_;
		QuadType quad_type_;
		float x_, y_, w_, h_;
		int level_, maxlevel_;
	public:
		bool contains(float px, float py, float w, float h, T* object) const; 
		bool contains(float px, float py, float w, float h, QuadTreeNode<T>* node) const; 
		QuadTreeNode(float x, float y, float w, float h, int level, int maxlevel, QuadType quadtype, QuadTreeNode* parent);
		~QuadTreeNode();
		void insert_object(T* object);
		list<T*> get_object_at(float px, float py, float w, float h);
		void remove_object_at(float px, float py, float w, float h);
};
