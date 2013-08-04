#ifndef __CP2BASIC_H__
#define __CP2BASIC_H__

#ifdef CP1_BUILDDLL
#define CP2DECL		__declspec(dllexport)
#else
#define CP2DECL		__declspec(dllimport)
#endif

#endif	//__CP1BASIC_H__