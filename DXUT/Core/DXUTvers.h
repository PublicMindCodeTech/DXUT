//--------------------------------------------------------------------------------------
// File: DXUTvers.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=320437
//--------------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma once
#endif

#define DXUTLIB_VERSION_DATE "2013.12.30"

#define DXUTLIB_VERSION "11.0.4"
#define DXUTLIB_VERNUM 0x2B20
#define DXUTLIB_VER_MAJOR 11
#define DXUTLIB_VER_MINOR 0
#define DXUTLIB_VER_REVISION 4
#define DXUTLIB_VER_SUBREVISION 0

#define DXUTLIB_VERSION_STR DXUTLIB_VER_MAJOR, DXUTLIB_VER_MINOR, DXUTLIB_VER_REVISION, DXUTLIB_VER_SUBREVISION

#ifdef _DEBUG
#define DXUTLIB_BUILD_ "_d"
#else
#define DXUTLIB_BUILD_ ""
#endif
