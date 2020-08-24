#pragma once

#define _INDEX32

#ifdef _INDEX16
// 인덱스에 사용되는 비트를 정의합니다. 16비트시 이 설정을 유지합니다
// _INDEX16 -> 16 bits Indexing (Selected)
// _INDEX32 -> 32 bits Indexing 
#define MeshIndex WORD
#endif

#ifdef _INDEX32

// 인덱싱에 사용되는 비트를 정의합니다. 32비트시 이 설정을 유지합니다
// _INDEX16 -> 16 bits Indexing
// _INDEX32 -> 32 bits Indexing (Seleted)
#define MeshIndex UINT
#endif

// 애플리케이션의 해상도와 종횡비를 설정합니다.
static unsigned int BIWidth = 1280;
static unsigned int BIHeight = 720;
static float BIAspectRatio = (float)BIWidth / (float)BIHeight;

static HINSTANCE BIAppHandleInst;
static HWND BIAppWindowHandle;