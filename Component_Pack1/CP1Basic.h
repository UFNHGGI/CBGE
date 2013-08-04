#ifndef __CP1BASIC_H__
#define __CP1BASIC_H__

#ifdef CP1_BUILDDLL
#define CP1DECL		__declspec(dllexport)
#else
#define CP1DECL		__declspec(dllimport)
#endif

#endif	//__CP1BASIC_H__