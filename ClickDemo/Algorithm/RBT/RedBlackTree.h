#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include "Node_RBT.h"

class RedBlackTree
{
public:
	~RedBlackTree();
	RedBlackTree();

	//노드 검색 함수
	bool Find(int data,Node_RBT** outNode);

	//노드 추가 함수
	bool Insert(int data);

	//노드 출력 함수
	void Print(int depth = 0,int blackCount = 0);

	//노드 삭제 함수.
	void Remove(int data);

private:
	//노드 생성함수
	Node_RBT* CreateNode (int data,Color_RBTNode color);

	//노드 검색 재귀 함수.
	bool FindRecursive(Node_RBT* node,Node_RBT** outNode,int data);

	//노드 추가 함수 (새 노드 전달)
	void Insert(Node_RBT* newNode);

	//노드 삭제 함수.
	void RemoveImpl(Node_RBT* node);

	//트리에 노드를 추가하는 재귀 함수.
	void InsertRecursive(Node_RBT* node,Node_RBT* newNode);

	//노드 삽입 후 재정렬을 처리히는 함수.
	void RestructureAfterInsert(Node_RBT* newNode);

	void RestructureAfterRemove(Node_RBT* node);

	//회전함수_좌
	void RotateToLeft(Node_RBT* node);
	void RotateToRight(Node_RBT* node);

	//트리에서 최소 값을 가진 노드를 검색하는 함수.
	Node_RBT* FindMinRecursive(Node_RBT* node);
	//트리에서 최대 값을 가진 노드를 검색하는 함수.
	Node_RBT* FindMaxRecursive(Node_RBT* node);

	//삭제함수
	void DestroyRecursive(Node_RBT* node);

	//출력 재귀 함수
	void PrintRecursive(Node_RBT* node,int depth,int blackCount);

private:
	Node_RBT* root = nullptr;
	static Node_RBT* nil;
};

//콘솔 텍스트 색상 열거형,
enum class TextColor
{
	Red = FOREGROUND_RED
	,Green = FOREGROUND_GREEN
	,Blue=FOREGROUND_BLUE
	,White = Red|Green|Blue|FOREGROUND_INTENSITY
};

void SetTextColor(TextColor color);