#ifndef TEXTCODECONVERT_H_INCLUDED
#define TEXTCODECONVERT_H_INCLUDED

#include <gtk/gtk.h>
#include <locale.h>
#include <windows.h>
#define BUFF_SIZE 1024

char *_T(const char *str);
char* _U(const char* str);

wchar_t * ANSIToUnicode( const char* str );
char * UnicodeToANSI( const wchar_t* str );
wchar_t * UTF8ToUnicode( const char* str );
char * UnicodeToUTF8( const wchar_t* str );
char* w2m(const wchar_t* wcs);
wchar_t* m2w(const char* mbs);
char* ANSIToUTF8(const char* str);

#endif // TEXTCODECONVERT_H_INCLUDED
