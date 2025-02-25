﻿#include "RedBlackTree.h"

Node* RedBlackTree::nil = nullptr;
Node * RedBlackTree::CreateNode(int data,Node::Color color)
{
	Node* newNode = new Node(data,color);
	newNode -> SetLeft(nil);
	newNode -> SetRight(nil);
	return newNode;
}

RedBlackTree::~RedBlackTree()
{
	DestroyRecursive(root);
	SafeDelete(nil);
}

RedBlackTree::RedBlackTree()
{
	if(nil == nullptr)
	{
		nil = new Node(0,Node::Color::Black);
	}
	root = nil;
}

bool RedBlackTree::Find(int data,Node** outNode)
{
	//트리가 비었다면, 검색 실패
	if(root == nil)
	{
		return false;
	}

	//재귀적으로 검색 진행.
	return FindRecursive(root,outNode,data);
}

bool RedBlackTree::FindRecursive(Node* node,Node** outNode,int data)
{
	//재귀 탈출 조건(검색 실패)
	if(node == nil)
	{
		return false;
	}

	//검색에 성공했으면, true 및 outNode 반환
	if(node->Data() == data)
	{
		*outNode = node;
		return true;
	}

	//검색할 데이터가 현재 노드 값 보다 작으면 왼쪽으로 검색 진행.
	if(node->Data() > data)
	{
		return FindRecursive(node->Left(),outNode,data);
	}

	else
	{
		return FindRecursive(node->Right(),outNode,data);
	}
	return false;
}
bool RedBlackTree::Insert(int data)
{
	Node* node = nullptr;
	if(Find(data,&node))
	{
		std::cout <<"오류 - 노드 추가 실패 : 이미 같은 값이 있다. 입력값 : "
			<<data<<" \n";
		return false;
	}

	Insert(CreateNode(data,Node::Color::Red));	//노드 생성 후 결과 반환.
	return true;	//중복 안되면, 성공!
}

void RedBlackTree::Print(int depth,int blackCount)
{
	PrintRecursive(root,depth,blackCount);
}

void RedBlackTree::Insert(Node * newNode)
{
	//트리가 비어있는 경우, 루트로 설정
	if(root == nil)
	{
		root = newNode;
		root->SetColor(Node::Color::Black);
		return ;
	}

	//비어있지 않은 경우, 재귀적으로 위치 검색 후 삽입. 이진트리와 같아.
	InsertRecursive(root,newNode);

	//삽입 된 노드 값 정리.
	newNode->SetColor(Node::Color::Red);
	newNode->SetLeft(nil);
	newNode->SetRight(nil);

	//	케이스에 따라서, 재정렬-삽입 후 재정랼
	RestructureAfterInsert(newNode);
}

void RedBlackTree::Remove(int data)
{
	Node* deleted = nullptr;
	if(!Find(data,&deleted))
	{
		std::cout
			<< "오류 : "
			<<data
			<<"\n";

		return;
	}

	RemoveImpl(deleted);
}
void RedBlackTree::RemoveImpl(Node * node)
{
	// 삭제 대상 노드.
	Node* removed = nullptr;

	// 삭제할 위치의 대체 노드.
	Node* trail = nil;

	Node* target = node;

	// 자손이 하나 이하인 경우.
	if(target->Left() == nil || target->Right() == nil)
	{
		removed = target;
	}

	// 자손이 모두 있는 경우.
	else
	{
		// 대체할 노드 검색.
		// (왼쪽 하위 트리에서 가장 큰값을 대체 노드로 설정).
		removed = FindMaxRecursive(target->Left());

		// 대체 노드가 존재하면 해당 데이터 설정.
		//if (removed != nullptr && removed != nil)
		//{
		//    // 현재 노드의 값을 대상 노드의 값으로 변경.
		//    target->SetData(removed->Data());
		//}

		// 현재 노드의 값을 대상 노드의 값으로 변경.
		target->SetData(removed->Data());
	}

	// 자손이 하나만 있을 때.
	if(node->Left() != nil && node->Right() == nil)
	{
		trail = node->Left();
	} else if(node->Right() != nil && node->Left() == nil)
	{
		trail = node->Right();
	}

	// 대상 노드가 있는 경우.
	if(trail != nil /*&& trail != nullptr*/)
	{
		trail->SetParent(removed->Parent());
	}

	// removed 노드가 root인 경우.
	if(removed->Parent() == nullptr)
	{
		root = trail;
	}
	// root가 아닐 때.
	else
	{
		// trail 노드를 removed의 원래 위치로 설정.
		if(removed == removed->Parent()->Left())
		{
			removed->Parent()->SetLeft(trail);
		} else
		{
			removed->Parent()->SetRight(trail);
		}
	}

	// 재정렬 여부 확인후 진행.
	if(removed->GetColor() == Node::Color::Black && trail != nil)
	{
		// 재정렬 진행.
		RestructureAfterRemove(trail);
	}

	// 노드 삭제.
	SafeDelete(removed);
}

void RedBlackTree::InsertRecursive(Node * node,Node * newNode)
{
	//새 노드의 데이터가 현재 노드보다 작으면, 외쪽하위 느==느===트리로 삽입 진행
	if(node->Data() > newNode ->Data())
	{
		if(node->Left() == nil)
		{
			node->SetLeft(newNode);
			newNode->SetParent(node);
			return;
		}

		InsertRecursive(node->Left(),newNode);
	}

	else
	{
		if(node->Right() == nil)
		{
			node->SetRight(newNode);
			newNode->SetParent(node);
			return;
		}

		InsertRecursive(node->Right(),newNode);
	}
}

void RedBlackTree::RotateToLeft(Node * node)
{
	Node* right = node->Right();

	//오늘쪽 자식 노드의 왼쪽 자식 노드를 부모의 오른쪽 자식 으로 등록
	node ->SetRight(right->Left());

	if(right -> Left() != nil)
	{
		right->Left()->SetParent(node);
	}

	right->SetParent(node->Parent());	//오늘쪽 자식 노드의 부모를 부모의 부모(조부모)로 설정

	if(right-> Parent() == nullptr) //부모가 root인 경우
	{
		root=right;
	}

	else
	{
		//조부모 기준 원원래의 자식 위치로 복구
		if(node == node -> Parent()->Left())
		{
			node ->Parent() ->SetLeft(right);
		}

		else
		{
			node ->Parent() ->SetRight(right);
		}
	}
	right->SetLeft(node);
	node->SetParent(right);
}

void RedBlackTree::RotateToRight(Node * node)
{
	//RotateToLeft 의 반대방얗으로 변경

	Node* left = node->Left();

	node ->SetLeft(left->Right());

	if(left -> Right() != nil)
	{
		left->Right()->SetParent(node);
	}

	left->SetParent(node->Parent());	//왼쪽 자식 노드의 부모를 부모의 부모(조부모)로 설정

	if(left-> Parent() == nullptr) //부모가 root인 경우
	{
		root=left;
	}

	else
	{
		//조부모 기준 원원래의 자식 위치로 복구S
		if(node == node -> Parent()->Left())
		{
			node ->Parent() ->SetLeft(left);
		}

		else
		{
			node ->Parent() ->SetRight(left);
		}
	}

	left->SetRight(node);
	node->SetParent(left);
}

Node * RedBlackTree::FindMinRecursive(Node * node)
{
	//탈출조건
	if(node == nil)
	{
		return nullptr;
	}

	//왼쪽 하위 노드가 더 이상 없으면 현재 노드 반환
	if(node->Left() == nil)
	{
		return node;
	}

	return FindMinRecursive(node->Left());
}

Node * RedBlackTree::FindMaxRecursive(Node * node)
{
	//탈출조건
	if(node == nil)
	{
		return nullptr;
	}

	//오른쪽 하위 노드가 더 이상 없으면 현재 노드 반환
	if(node->Right() == nil)
	{
		return node;
	}

	return FindMaxRecursive(node->Right());
}

void RedBlackTree::DestroyRecursive(Node * node)
{
	if(node == nil)	//재귀 탈출 조건.
	{
		return;
	}

	//자식
	Node* left = node->Left();
	Node* right = node->Right();

	//자식 없는 경우
	/*if(left == nil && right == nil)
	{
		SafeDelete(node);
		return;
	}*/ //위에서, 검색하니 없어도 될듯.

	//자식 있는 경우
	DestroyRecursive(left);
	DestroyRecursive(right);

	//노드삭제
	SafeDelete(node);
}

void RedBlackTree::PrintRecursive(Node * node,int depth,int blackCount)
{
	//탈출조건
	if(node == nil)
	{
		return;
	}
	//노드 색상이 검정이면 blackCount 증가.
	if(node -> GetColor() == Node::Color::Black)
	{
		++blackCount;
	}
	//부모 표기 문자열 설정.
	int parentData = 0;
	const char* position = "Root";

	//부모 노드가 있는지 확인.
	if(node -> Parent())
	{
		//부모 노드의 데이터 저장.
		parentData = node->Parent()->Data();

		//부모 노드로부터 현재 노드의 위치 설정
		if(node==node->Parent()->Left())
		{
			position = "Left";
		}

		else
		{
			position = "Right";
		}
	}

	//검은색 수 출력을 위한 문자열.
	char blackCountString[50] = {};

	//자손이 없으면, 현재까지의 검은색 노드 수 설정.
	if(node->Left() == nil && node -> Right() == nil)
	{
		sprintf_s(blackCountString,"------%d",blackCount);
	}

	// Depth 출력.
	for(int ix = 0; ix < depth; ix++)
	{
		std::cout << " ";
	}

	// 노드 색상에 따른 콘솔 설정.
	if(node->GetColor() == Node::Color::Red)
	{
		SetTextColor(TextColor::Red);
	}

	else
	{
		SetTextColor(TextColor::White);
	}

	// 현재 노드 값 출력.
	std::cout
		<< node->Data() << " "
		<< node->ColorString() << " ["
		<< position << ", "
		<< parentData << "] "
		<< blackCountString << "\n";

	// 노드를 출력한 뒤에는 콘솔 원래대로.
	SetTextColor(TextColor::White);

	// 하위 노드 출력.
	PrintRecursive(node->Left(),depth + 1,blackCount);
	PrintRecursive(node->Right(),depth + 1,blackCount);
}
void SetTextColor(TextColor color)
{
	static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console,(int)color);
}
void RedBlackTree::RestructureAfterInsert(Node* newNode)
{
	//부모가 빨간색인 경우, (Red-Red Conflict)
	while(newNode != root && newNode ->Parent() ->GetColor() == Node::Color::Red)
	{
		//삼촌구하기 - 왼쪽인 경우
		if(newNode->Parent() ==newNode->Parent()->Parent()->Left())
		{
			//삼촌
			Node* uncle = newNode-> Parent() ->Parent()->Right();

			//삼촌노드가 빨간색 일 때 - Case1.
			//해결 : 부모와 삼촌을 Black,할아버지를 Red로 변경 후,할아버지 기준으로 다시 검사
			if(uncle -> GetColor() == Node::Color::Red())
			{
				newNode -> Parent() ->SetColor(Node::Color::Black);
				uncle->SetColor(Node::Color::Black);
				newNode->Parent()->Parent()->SetColor(Node::Color::Red);

				newNode=newNode->Parent()->Parent();
				continue;
			}

			//위에서, continue; 했으니, else안함.
			//삼촌이 검정색 일 때 : case2,3
			//해결 2: 지그재그 형태: 부모위치와나의위치가 반대 : 일직으로ㅡ 변경 후 case3 처리.

			if(newNode == newNode->Parent()->Right())
			{
				//부모를 중심으로 회전 처리(일직선으로 만들기 위해)
				newNode = newNode->Parent();
				RotateToLeft(newNode);
			}

			//해결 3:부모와 일치할때 -일직선 일 떄,
			newNode -> Parent()->SetColor(Node::Color::Black);
			newNode ->Parent()->Parent()->SetColor(Node::Color::Red);

			RotateToRight(newNode->Parent()->Parent());
		}
		//삼촌구하기 -부모가 조부모 기준으로 오른쪽 자손일 때
		else
		{
			//삼촌
			Node* uncle = newNode-> Parent() ->Parent()->Left();

			//삼촌노드가 빨간색 일 때 - Case1.
			//해결 : 부모와 삼촌을 Black,할아버지를 Red로 변경 후,할아버지 기준으로 다시 검사
			if(uncle -> GetColor() == Node::Color::Red())
			{
				newNode -> Parent() ->SetColor(Node::Color::Black);
				uncle->SetColor(Node::Color::Black);
				newNode->Parent()->Parent()->SetColor(Node::Color::Red);

				newNode=newNode->Parent()->Parent();
				continue;
			}

			//위에서, continue; 했으니, else안함.
			//삼촌이 검정색 일 때 : case2,3
			//해결 2: 지그재그 형태: 부모위치와나의위치가 반대 : 일직으로ㅡ 변경 후 case3 처리.

			if(newNode == newNode->Parent()->Left())
			{
				//부모를 중심으로 회전 처리(일직선으로 만들기 위해)
				newNode = newNode->Parent();
				RotateToRight(newNode);
			}

			//해결 3:부모와 일치할때 -일직선 일 떄,
			newNode -> Parent()->SetColor(Node::Color::Black);
			newNode ->Parent()->Parent()->SetColor(Node::Color::Red);

			RotateToLeft(newNode->Parent()->Parent());
		}
	}

	//루트노드는 블랙
	root->SetColor(Node::Color::Black);
}

void RedBlackTree::RestructureAfterRemove(Node * node)
{
	//더블 블랙 문제 해결.
	while(node->Parent() != nullptr
		&& node->GetColor() == Node::Color::Black)
	{
		//형제 노드 구하기.
		if(node == node->Parent() ->Left())
		{
			Node* sibling = node->Parent() ->Right();
			if(sibling == nil)
			{
				break;
			}

			//case1 -> 형제 노드가 빨간색 일 때.
			// //해결 : 형제 노드를 black - 부모를 red 로 바꿔, 부모 기준 좌 또는 우 회전.
			if(sibling -> GetColor() == Node::Color::Red)
			{
				sibling -> SetColor(Node::Color::Black);
				node->Parent()->SetColor(Node::Color::Red);

				//좌회전
				RotateToLeft(node->Parent());
				continue;
			}

			//case2 : 형제 노드 검정색 - 자식들 다 검정색 일때
			//형제 노드 red , 부모를 새로운 노드로 설중 후, 다시 검사
			if(sibling ->Left() -> GetColor() == Node::Color::Black
				&& sibling ->Right() -> GetColor() ==Node:: Color::Black
				)
			{
				sibling -> SetColor(Node::Color::Red);
				node = node -> Parent();
				continue;
			}

			//case3 : 형제 노드 검정색 - 형제 왼쪽 자식 빨강색
			//해결 : 형제 왼쪽자식 black - 형제 red 로 변경 후, 형제 기준 우 회전.
			if(sibling -> Left()->GetColor() ==Node:: Color:: Red)
			{
				sibling->Left()->SetColor(Node::Color::Black);
				sibling->SetColor(Node::Color::Red);

				RotateToRight(sibling);

				//회전 후 형제 위치 업데이트.
				sibling = node -> Parent()->Right();
			}

			//case4 : 형제 노드 검정색 - 형제 오늘쪽 자식 빨강색
			//해결 : 형제 부모와 같은 색 - 부모를 black - 형제 오른쪽 자식을 BlacK  으로 변경 후, 부모기준 좌회전.
			if(sibling->Right()->GetColor () == Node::Color::Red)
			{
				sibling ->SetColor(sibling->Parent()->GetColor());
				sibling ->Parent()->SetColor(Node::Color::Black);
				sibling->Right()->SetColor(Node::Color::Black);
				RotateToLeft(node->Parent());
			}

			continue;
		}

		Node* sibling = node->Parent() ->Left();
		if(sibling == nil)
		{
			break;
		}

		//case1 -> 형제 노드가 빨간색 일 때.
		// //해결 : 형제 노드를 black - 부모를 red 로 바꿔, 부모 기준 좌 또는 우 회전.
		if(sibling -> GetColor() == Node::Color::Red)
		{
			sibling -> SetColor(Node::Color::Black);
			node->Parent()->SetColor(Node::Color::Red);

			//좌회전
			RotateToRight(node->Parent());
			continue;
		}

		//case2 : 형제 노드 검정색 - 자식들 다 검정색 일때
		//형제 노드 red , 부모를 새로운 노드로 설중 후, 다시 검사
		if(sibling ->Right() -> GetColor() == Node::Color::Black
			&& sibling ->Left() -> GetColor() == Node::Color::Black
			)
		{
			sibling -> SetColor(Node::Color::Red);
			node = node -> Parent();
			continue;
		}

		//case3 : 형제 노드 검정색 - 형제 오른쪽 자식 빨강색
		//해결 : 형제 오늘쪽자식 black - 형제 red 로 변경 후, 형제 기준 좌 회전.
		if(sibling -> Right()->GetColor() == Node::Color:: Red)
		{
			sibling->Right()->SetColor(Node::Color::Black);
			sibling->SetColor(Node::Color::Red);

			RotateToLeft(sibling);

			//회전 후 형제 위치 업데이트.
			sibling = node -> Parent()->Left();
		}

		//case4 : 형제 노드 검정색 - 형제 왼쪽 자식 빨강색
		//해결 : 형제 부모와 같은 색 - 부모를 black - 형제 왼쪽 자식을 BlacK  으로 변경 후, 부모기준 우 회전.
		if(sibling->Left()->GetColor () == Node::Color::Red)
		{
			sibling ->SetColor(sibling->Parent()->GetColor());
			sibling ->Parent()->SetColor(Node::Color::Black);
			sibling->Left()->SetColor(Node::Color::Black);
			RotateToRight(node->Parent());

			node=root;
		}
	}
	node->SetColor(Node::Color::Black);
}