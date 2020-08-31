// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "libfbxsdk-mt.lib")
#pragma comment(lib, "libxml2-mt.lib")
#pragma comment(lib, "libfbxsdk.lib")
#pragma comment(lib, "zlib-mt.lib")


#include "framework.h"

// STL Headers
#include<functional>
#include<iostream>
#include<map>
#include<memory>
#include<string>
#include<vector>
#include<wrl.h>

#include<atlbase.h>


// D3D Headers
#include<d3d11.h>
#include<d3dcompiler.h>
#include<dxgi.h>

#include<dinput.h>
#include<DirectXColors.h>
#include<DirectXMath.h>

// FBX SDK Headers
#include<fbxsdk.h>

#include"Built-In-Variables.h"
#include"ModuleDebugger.h"

#include"VirtualObject.h"

#include"Device.h"
#include"Texture.h"

#include"RenderResources.h"

#include"FBXLoader.h"

#include"Camera.h"
#include"D3DRSBuffer.h"

#include"IRenderer.h"
#include"Instance.h"

#include"Scene.h"

#include"Renderer.h"

