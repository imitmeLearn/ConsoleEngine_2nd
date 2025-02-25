#include "NodeRBTActor.h"

//NodeRBTActor::NodeRBTActor(Node_RBT * node)
//	:node(node)
//{}
//
NodeRBTActor::NodeRBTActor(const Vector2 & position)
	:DrawableActor("------\nI0000ⓒI\n------")
	//	:DrawableActor("┌────┐\n│0000│\n└────┘")
{
	this->position = position;	//위치 설정
}

NodeRBTActor::NodeRBTActor(const Vector2 & position,Node_RBT * node)
	: DrawableActor("┌────┐\n│0000│\n└────┘")

{
	this->node = node;
	this->position = position;	//위치 설정
}