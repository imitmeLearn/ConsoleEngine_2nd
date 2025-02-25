#include "Node_RBT.h"

Node_RBT::Node_RBT(int data,Color_RBTNode color)
	:data(data),color(color)
{}

const char * Node_RBT::ColorString() const
{
	return color== Color_RBTNode::Red? "RED":"BLACK";
}