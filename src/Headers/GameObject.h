#pragma once
//std
#include <vector>
#include <memory>
//int
#include "Logger.h"
class Component;

class GameObject : public std::enable_shared_from_this<GameObject> {

public:
	GameObject();
	~GameObject();
	/**
	setParent sets this gameObjects Parent
	*/
	void setParent(std::shared_ptr<GameObject>);

	/**
	addComponent adds a new component to the gameObject

	The Template class passed through must inherit from Component
	*/
	template <class T>
	std::shared_ptr<T> addComponent() {
		std::shared_ptr<T> newComponent = std::make_shared<T>();

		newComponent->gameObject = shared_from_this(); // should it be weak_from_this()

		Components.push_back(newComponent);

		newComponent->onAwake();

		return newComponent;
	}

	/**
	getComponent adds a new component to the gameObject

	The Template class passed through must inherit from Component
	@return returns a reference to the component
	*/
	template <class T>
	std::shared_ptr<T> getComponent() {
		if (Components.size() > 0) { 
			for (size_t i = 0; i < Components.size(); i++) {
				std::shared_ptr<T> comp = std::dynamic_pointer_cast<T>(Components.at(i));

				if (comp) return comp;
			}
		}
		Logger::Error("no Components Found");

		return std::shared_ptr<T>(); //error
	}
	/**
	refernce to this objects parent
	*/
	std::weak_ptr<GameObject> parent;
	/**
	vector of components on this gameObject
	*/ 
	std::vector<std::shared_ptr<Component>> Components;
};