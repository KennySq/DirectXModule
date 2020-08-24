#pragma once
// VirtualObject�� ��Ÿ�� �̺�Ʈ�� �����ϱ� ���� �𵨸��� Interface �Դϴ�.
// �� �̺�Ʈ�� �������
// Init -> OnInit (���ø����̼� ����, ������ �ڵ�� �ν��Ͻ� �ʱ�ȭ ����)
// Update -> OnUpdate (���ø����̼� ��Ÿ��, �� �����Ӹ��� ȣ��)
// Render -> OnRender (������, Update ���Ŀ� ȣ���)
// Release -> OnRelease (����, �ڿ� ������, ���ø����̼� ���� �Ǵ� �ڿ��� �����Ǵ� ������ �̺�Ʈ �߻� ��)
// *Delta�� ������ �ð����� ��Ÿ���ϴ�.
class VirtualObject
{
protected:
	virtual bool OnInit() = 0;
	virtual void OnUpdate(float Delta) = 0;
	virtual void OnRender(float Delta) = 0;
	virtual void OnRelease() = 0;
public:
	virtual bool Init() { return OnInit();}
	virtual void Update(float Delta) { OnUpdate(Delta); }
	virtual void Render(float Delta) { OnRender(Delta); }
	virtual void Release() { OnRelease(); }
};

