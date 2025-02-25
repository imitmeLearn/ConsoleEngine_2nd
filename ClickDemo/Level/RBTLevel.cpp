#include "RBTLevel.h"

RBTLevel::RBTLevel()
{
	//레드블랙 트리 생성
	Initialization("../Assets/InitData.txt",&tree);

	//노드 생성할때, 액터 생성하고,
	//위치변경할때 마다, 애니메이션준다,

	Init();
}

void RBTLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if(Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}
}

void RBTLevel::Draw()
{
	for(auto* actor : actors)
	{
		actor->Draw();
	}
}
void RBTLevel::Init()
{
	NodeRBTActor* node = new NodeRBTActor(Vector2(5,5));

	AddActor(node);
	nodeRBTs.PushBack(node);

	node->SetReImage("┌────┐\n│0000│\n└────┘");
	node->SetPosition(Vector2(10,20));
}
void RBTLevel::Initialization(const char * path,RedBlackTree * tree)
{
	if(tree == nullptr)
	{
		std::cout << "오류: 전달된 트리가 null 입니다.\n";
		return;
	}

	FILE* file = nullptr;
	fopen_s(&file,path,"r");
	if(file == nullptr)
	{
		std::cout << "오류: 파일 읽기 실패.\n";
		return;
	}

	char line[1024] = {};
	if(!fgets(line,1024,file))
	{
		std::cout << "오류: 파일 읽기 실패.\n";
		fclose(file);
		return;
	}

	fclose(file);

	std::vector<int> datas;

	// 첫 토근 읽기.
	char* context = nullptr;
	char* splitString = strtok_s(line,",",&context);
	if(splitString)
	{
		if(int parsed = atoi(splitString))
		{
			datas.emplace_back(parsed);
		}
	}

	// 나머지 토근 읽기.
	while(context)
	{
		splitString = strtok_s(nullptr,",",&context);
		if(!splitString)
		{
			break;
		}

		if(int parsed = atoi(splitString))
		{
			datas.emplace_back(parsed);
		}
	}

	// 트리에 데이터 추가.
	for(auto data : datas)
	{
		tree->Insert(data);
		//Insert(tree,data);
	}

	// 초기 데이터를 설정한 후의 데이터 출력.
	std::cout << "초기 데이터가 적용되었습니다.\n";
	tree->Print();
	Print(tree);
	std::cout << "\n";
}

void RBTLevel::Insert(RedBlackTree * tree,std::vector<int> datas)
{
	//	if(Find(data,))
}
void RBTLevel::Print(RedBlackTree * tree)
{
	//tree.root
	//	PrintRecursive(root,depth,blackCount);
}