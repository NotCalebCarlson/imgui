#pragma once
#include "imgui.h"

inline ImFont* g_FontRegular = nullptr;
inline ImFont* g_FontLarge = nullptr;

void RenderUI();
void CleanupUI();
