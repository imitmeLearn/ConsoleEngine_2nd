#include "Start.h"
#include "Engine/Engine.h"

Start::Start()
	: DrawableActor("s")
{
	color = Color::Blue;
}

Start::Start(DemoLevel* level)
	: DrawableActor("s")
{
	color = Color::Blue;
	position = Vector2(1,1);
	refLevel = level;
}

void Start::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if(Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		//if(!refLevel->isDraw) false;
		//
		//이미SE 생성된 위치에,재 생성 못하도록

		if(refLevel->IsClickedOutofMap()) return;

		//애니메이션을 위한 노드 초기화
		refLevel->StopAnimation();

		position = Engine::Get().MousePosition();
		refLevel->DrawPath();
	}

	//노드가 있지 않고,
	// 목표지점
	// 목표도착하지 않았다면,
	//계속이동
	//if(!refLevel->IsEmpty_curr_path_node())
	//if(refLevel->curr_paths.size() >0)
	if(refLevel->add_path_node_smart.size() >0)
	{
		PlayAnimation(deltaTime);
	}
}

//void Start::PlayAnimation(float deltaTime){
//
//	//direction= refLevel->NextNodeDirection(this->position);
//	//direction= refLevel->GetNextNodeDir(this->Position());
//	//direction= refLevel->GetNextPathDir(this->Position());
//
//	//tempPos = Position();
//	//tempPos.x += direction.x ;//* speed * deltaTime;
//	//tempPos.y += direction.y ;//* speed * deltaTime;
//
//	//if(tempPos.y < 0 || tempPos.y > refLevel->origin_grid.size()-1)
//	//{
//	//	return;
//	//}
//
//	////if(position.x < 0)
//	//if(tempPos.x < 0|| tempPos.x > refLevel->origin_grid[0].size()-1)
//	//{
//	//	return;
//	//}
//	//SetPosition(Vector2(
//	//	static_cast<int>(std::round(tempPos.x))
//	//	,static_cast<int>(std::round(tempPos.y))
//	//));
//
//	/*	int delay = static_cast<int>(0.05f * 1000);
//		Sleep(delay);*/
//		//if(refLevel->NodePointer()==-1)
//		//{
//		//	PlayAnimation();
//		//}
//		//if(!isArrived())
//		//{
//		//	//도착하지 않았다면, 이동
//		///*	yPosition -= speed * deltaTime;
//		//	position.y = (int)yPosition;*/
//		//	tempPos = position;
//		//	tempPos.x += direction.x * speed * deltaTime;
//		//	tempPos.y += direction.y * speed * deltaTime;
//
//		//	position.x = static_cast<int>(std::round(tempPos.x));
//		//	position.y = static_cast<int>(std::round(tempPos.y));
//		//} else
//		//{
//		//	refLevel->DrawPath();
//		//}
//}
//노드 기반
void Start::PlayAnimation(float deltaTime)
{
	//auto node = refLevel->curr_path_node;

	//direction = Vector2(1,1);

	//다음노드가 목표노드 이거나
	if(refLevel-> CheckNextNode(this->Position()) == refLevel->goal->Position())
	{
		return;
	}

	/*if(
		isArrived(this->Position(),refLevel-> CheckNextNode(this->Position()))
	)*/
	{
		direction= refLevel->GetNextNodeDir(this->Position());
		//다음 노드 위치랑, 같음
	}

	tempPos = Position();
	tempPos.x += direction.x ;// * speed * deltaTime;
	tempPos.y += direction.y ;// * speed * deltaTime;

	if(tempPos.y < 0 || tempPos.y > refLevel->origin_grid.size()-1)
	{
		//tempPos.y -= direction.y ;
	}

	//if(position.x < 0)
	if(tempPos.x < 0|| tempPos.x > refLevel->origin_grid[0].size()-1)
	{
		//tempPos.x -= direction.x ;
	}

	SetPosition(tempPos);

	//refLevel->DrawPath();
	//SetPosition(Vector2(
	//	static_cast<int>(std::round(tempPos.x))
	//	,static_cast<int>(std::round(tempPos.y))
	//));

	//direction= refLevel->NextNodeDirection(this->position);
	//refLevel->NextNode();
	//auto next = refLevel->GetGaolNodePosition();
	//direction=	refLevel->GetDirection(this->position,next);
	/*if(refLevel)
	{
		animation = new Animation(refLevel->Curr_path_node());
	}*/
}

bool Start::isArrived(Vector2 start,Vector2 next)
{
	if(start == next)
	{
		refLevel->SetNextPointer();
		return true;
	}

	else
	{
		return false;
	}
}
bool Start::isArrived()
{
	//도착했다면, 다음 목적지 가져와, 단위벡터 set하기
	//if(this->Position() == refLevel->GetGaolNodePosition())
	//if(this->Position() == refLevel->GetGaolNodePosition())
	{
		//direction=	refLevel->NextNodeDirection(this->position);

		/*	refLevel->NextNode();
			auto next = refLevel->GetGaolNodePosition();
			direction=	refLevel->GetDirection(this->position,next);*/
		return true;
	}
	return false;
}