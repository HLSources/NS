//========= Copyright � 1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#ifndef VGUI_LOADTGA_H
#define VGUI_LOADTGA_H
#ifdef _WIN32
#pragma once
#endif


#include "vgui_bitmaptga.h"

vgui::BitmapTGA* vgui_LoadTGA(char const *pFilename, bool bInvertAlpha = true);
vgui::BitmapTGA* vgui_LoadTGANoInvertAlpha(char const *pFilename);

#endif // VGUI_LOADTGA_H
