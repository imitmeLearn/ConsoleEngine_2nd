#pragma once
#include <Actor/DrawableActor.h>

class Node_RBT;
class NodeRBTActor: public DrawableActor
{
	RTTI_DECLARATIONS(NodeRBTActor,DrawableActor)

public:
	//NodeRBTActor(Node_RBT* node);
	NodeRBTActor(const Vector2& position);
	NodeRBTActor(const Vector2& position,Node_RBT* node);

private:
	Node_RBT* node;
};
