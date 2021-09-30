#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>


#define BUF_SIZE 256
TCHAR* szName=new TCHAR[20];;
TCHAR* szMsg = new TCHAR[20];

int _tmain()
{
   _tprintf(TEXT("Enter mapping name:"));
   std::cin >> szMsg;
   HANDLE hMapFile;
   LPCTSTR pBuf;

   hMapFile = OpenFileMapping(
                   FILE_MAP_ALL_ACCESS,   // read/write access
                   FALSE,                 // do not inherit the name
                   szName);               // name of mapping object
   if (GetLastError() == 2){
   	hMapFile = CreateFileMapping(
                 INVALID_HANDLE_VALUE,    // use paging file
                 NULL,                    // default security
                 PAGE_READWRITE,          // read/write access
                 0,                       // maximum object size (high-order DWORD)
                 BUF_SIZE,                // maximum object size (low-order DWORD)
                 szName);                 // name of mapping object
   }
   
   

   if (hMapFile == NULL)
   {
      _tprintf(TEXT("Could not create file mapping object (%d).\n"),
             GetLastError());
      return 1;
   }
   pBuf = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                        FILE_MAP_ALL_ACCESS, // read/write permission
                        0,
                        0,
                        BUF_SIZE);

   if (pBuf == NULL)
   {
      _tprintf(TEXT("Could not map view of file (%d).\n"),
             GetLastError());

       CloseHandle(hMapFile);

      return 1;
   }
   int a = 4;
   while (a > 0){
   
	   _tprintf(TEXT("Enter 1 for writing, 2 for reading, 3 for exit:"));
	   
	   std::cin >> a;
	   if (a == 1){
	   	_tprintf(TEXT("Enter the message:"));
	   	
		std::cin >> szMsg;
	   	CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
	    _getch();
	   }
	   if (a == 2){
	   	_tprintf(pBuf);
	   	_tprintf("\n");
	   }
	   if (a == 3){
	    a = 0;
	   }
	}

   UnmapViewOfFile(pBuf);

   CloseHandle(hMapFile);

   return 0;
}


