#pragma once
// VirtualObject는 런타임 이벤트를 관리하기 위해 모델링된 Interface 입니다.
// 각 이벤트는 순서대로
// Init -> OnInit (애플리케이션 시작, 윈도우 핸들과 인스턴스 초기화 직후)
// Update -> OnUpdate (애플리케이션 런타임, 매 프레임마다 호출)
// Render -> OnRender (렌더시, Update 직후에 호출됨)
// Release -> OnRelease (종료, 자원 해제시, 애플리케이션 종료 또는 자원이 해제되는 임의의 이벤트 발생 시)
// *Delta는 프레임 시간차를 나타냅니다.
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

