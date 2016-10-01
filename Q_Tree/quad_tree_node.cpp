#include "quad_tree_node.h"
#include "object.h"

template <typename T>
QuadTreeNode<T>::QuadTreeNode 
(float x, float y, float w, float h, int level, int maxlevel, QuadType quadtype, QuadTreeNode* parent) {
	x_ = x;
	y_ = y;
	w_ = w;
	h_ = h;
	level_ = level;
	maxlevel_ = maxlevel;
	quad_type_ = quadtype;
	parent_ = parent;
}

template <typename T>
QuadTreeNode<T>::~QuadTreeNode() {
	if (level_ == maxlevel_) {
		return;
	}
	parent_ = nullptr;
}

template <typename T>
bool QuadTreeNode<T>::contains(float px, float py, float w, float h, T* object) const {
	if (object -> x_ >= px && object -> x_ + object -> w_ <= px + w && object->y_ >= py && object -> y_ + object -> h_ <= py + h) {
		return true;
	}
	return false;
}

template <typename T>
void QuadTreeNode<T>::insert_object(T* object) {
	if (level_ == maxlevel_) {
		objects_.push_back(object);
		return;	
	}
// recursively insert a new QuadTreeNode to either of four quads
	if (contains(x_ + w_/2, y_, w_/2, h_/2, object)) {
		if (!up_right_node_) {
			up_right_node_ = new QuadTreeNode(x_, y_, w_/2, h_/2, level_ + 1, maxlevel_, BOTTOM_LEFT, this); 
		} 
		up_right_node_->insert_object(object);
	} 
//	else if (contains()) {
//		up_left_node_
//	
// }  
 
// if not completely belong to one quad, insert a new node to current node
	if (contains(x_, y_, w_, h_, object)) {
			objects_.push_back(object);
			}
}


