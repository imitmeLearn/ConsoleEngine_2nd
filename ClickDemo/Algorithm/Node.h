#pragma once

#include "Math/Vector2.h"

class Node
{
	friend class AStar;

public:
	Node(const Vector2& position = Vector2(),Node* parent = nullptr)
		: position(position),parent(parent)
	{}

	~Node() = default;

	Vector2 operator-(const Node& other)
	{
		return position - other.position;
	}

	bool operator==(const Node& other)
	{
		return position == other.position;
	}
	const Vector2& Position()
	{
		return position;
	}

	void SetPosition(const Vector2& position)
	{
		this-> position = position;
	}
	bool isParent()
	{
		if(parent)
		{
			return true;
		}
		return false;
	}
private:
	Vector2 position;
	Node* parent = nullptr;
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
};