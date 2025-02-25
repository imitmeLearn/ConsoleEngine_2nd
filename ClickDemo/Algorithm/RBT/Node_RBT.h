#pragma once

#include <iostream>
#include <string>

//메모리 삭제 함수
template<typename T>
void SafeDelete(T*& t)
{
	if(t)
	{
		delete t;
		t = nullptr;
	}
}
enum class Color_RBTNode
{
	Red,
	Black,
};
//노드 색상 열거형 //트리안에서 넣는게 의미상 맞지만, 코드 작성 시 가독성 차원에서 밖으로 뺌.

class Node_RBT
{
public:
	~Node_RBT() = default;
	Node_RBT(int data =0,Color_RBTNode color = Color_RBTNode::Red);

	//Getter /Seetter
	inline	const int Data() const {
		return data;
	}
	inline	void SetData(int newData){
		data = newData;
	}
	inline	const Color_RBTNode GetColor() const{
		return color;
	}

	inline	void SetColor(Color_RBTNode newColor){
		color = newColor;
	}
	const char* ColorString() const;

	inline	Node_RBT* Parent() const {
		return parent;
	}

	inline	void SetParent(Node_RBT* newParent)  {
		parent = newParent;
	}

	inline	Node_RBT* Left() const {
		return left;
	}
	inline void SetLeft(Node_RBT* newleft)  {
		left = newleft;
	}

	inline	Node_RBT* Right() const {
		return right;
	}
	inline void SetRight(Node_RBT* newright)  {
		right = newright;
	}

private:
	int data = 0;	//데이터
	Color_RBTNode color = Color_RBTNode::Red;	//색상

	Node_RBT* parent = nullptr;	//부모노드
	Node_RBT* left = nullptr;	//왼쪽 자식 노드.
	Node_RBT* right = nullptr;	//자식 노드 _오른쪽
};
