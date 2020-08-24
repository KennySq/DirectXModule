#pragma once

#define _INDEX32

#ifdef _INDEX16
// �ε����� ���Ǵ� ��Ʈ�� �����մϴ�. 16��Ʈ�� �� ������ �����մϴ�
// _INDEX16 -> 16 bits Indexing (Selected)
// _INDEX32 -> 32 bits Indexing 
#define MeshIndex WORD
#endif

#ifdef _INDEX32

// �ε��̿� ���Ǵ� ��Ʈ�� �����մϴ�. 32��Ʈ�� �� ������ �����մϴ�
// _INDEX16 -> 16 bits Indexing
// _INDEX32 -> 32 bits Indexing (Seleted)
#define MeshIndex UINT
#endif

// ���ø����̼��� �ػ󵵿� ��Ⱦ�� �����մϴ�.
static unsigned int BIWidth = 1280;
static unsigned int BIHeight = 720;
static float BIAspectRatio = (float)BIWidth / (float)BIHeight;

static HINSTANCE BIAppHandleInst;
static HWND BIAppWindowHandle;