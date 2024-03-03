#pragma once

#include "Types.h"
#include "Defines.h"
#include "Enums.h"

#include <windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

#include <format>

#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#include "Utils.h"

// 메모리 누수 체크를 위한 부분 - _CrtDumpMemoryLeaks()를 호출하면 확인 가능
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif