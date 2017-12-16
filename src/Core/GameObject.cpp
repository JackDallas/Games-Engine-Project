#include "GameObject.h"

#include <iostream>

GameObject::GameObject() {

}

GameObject::~GameObject() {

}

void GameObject::setParent(std::shared_ptr<GameObject> _parent) {
	parent = _parent;
}