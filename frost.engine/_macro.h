#pragma once
#define FROST_DLL
#ifdef FROST_DLL
	#ifdef FROST_BUILD
		#define FROST_API __declspec(dllexport)
	#else
		#define FROST_API __declspec(dllimport)
	#endif
#else
	// if not dll - no need for __declspec
	#define FROST_API
#endif
