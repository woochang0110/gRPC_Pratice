#ifndef PCH_H
#define PCH_H

// Windows 매크로 충돌 방지 (필수)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "framework.h"

// gRPC와 충돌하는 Windows 매크로 제거
#ifdef Service
#undef Service
#endif

#endif // PCH_H
