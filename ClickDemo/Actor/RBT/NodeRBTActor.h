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

	void SetReImage(const char* image)
	{
		if(this->image)
		{
			delete[] this->image;
		}

		auto length = strlen(image) + 1;
		this->image = new char[length];
		strcpy_s(this->image,length,image);

		//너비 설정
		width = (int)strlen(image);

		//여러줄인경우
		 // 가장 긴 줄의 길이를 찾아서 width 설정
		int max_width = 0,current_width = 0,max_height=1;
		for(int i = 0; i < length; i++) {
			if(image[i] == '\n') {
				max_width = (max_width > current_width) ? max_width : current_width;
				current_width = 0;
				++max_height;
			} else {
				current_width++;
			}
		}
		max_width = (max_width > current_width) ? max_width : current_width;

		/*width_check = current_width;
		width_recheck = width;
		length_recheck = length;
		image_check=	this->image;*/

		width = max_width;
		height = max_height;
	}

private:
	Node_RBT* node;
	/*char* image_check;

	int width_check = 0;
	int width_recheck = 0;
	int length_recheck = 0;*/
};
