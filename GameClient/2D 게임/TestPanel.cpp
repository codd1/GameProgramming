#include "pch.h"
#include "TestPanel.h"
#include "ResourceManager.h"
#include "Button.h"

TestPanel::TestPanel()
{
	{	// ���������� �Ͼ� �������� �ϳ� ����
		Button* ui = new Button();
		//ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start"), BS_Default);
		ui->SetPos({ 400, 200 });
		ui->SetSize({ 650, 300 });
		AddChild(ui);
	}
	{	// 1��° UI
		Button* ui = new Button();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_On"), BS_Clicked);
		ui->SetPos({ 200, 200 });

		//ui->_onClickMemFunc = &TestPanel::OnClickStartButton;
		// �̷� ������ callback �Լ��� ����ؼ� Click �̺�Ʈ�� �߻����� �� OnClickStartButton �� �Լ��� ȣ��ǰ� ��
		// ��(this)�� ������� OnClickStartButton �� �Լ��� ȣ������.
		ui->AddOnClickDelegate(this, &TestPanel::OnClickStartButton);
		AddChild(ui);
	}
	{	// 2��° UI
		Button* ui = new Button();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Edit_Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Edit_On"), BS_Clicked);
		ui->SetPos({ 400, 200 });
		ui->AddOnClickDelegate(this, &TestPanel::OnClickEditButton);
		AddChild(ui);
	}
	{	// 3��° UI
		Button* ui = new Button();
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Exit_Off"), BS_Default);
		ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Exit_On"), BS_Clicked);
		ui->SetPos({ 600, 200 });
		ui->AddOnClickDelegate(this, &TestPanel::OnClickExitButton);
		AddChild(ui);
	}
}

TestPanel::~TestPanel()
{

}

void TestPanel::BeginPlay()
{
	Super::BeginPlay();
}

void TestPanel::Tick()
{
	Super::Tick();


}

void TestPanel::Render(HDC hdc)
{
	Super::Render(hdc);

	wstring str = std::format(L"Count : {0}", _count);
	Utils::DrawTextW(hdc, { 100, 0 }, str);
}

void TestPanel::OnClickStartButton()
{
	_count++;
}

void TestPanel::OnClickEditButton()
{
	_count--;
}

void TestPanel::OnClickExitButton()
{
	_count = 0;
}
