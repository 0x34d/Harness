#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <wimgapi.h>

#define IN
#define OUT
#define INOUT

//ADK 

DWORD
WINAPI
SampleCallback(
	IN	DWORD msgId, //message ID
	IN	WPARAM param1,   //usually file name
	INOUT   LPARAM param2,   //usually error code
	IN	void* unused
)
{
	//First parameter: message string
	TCHAR* message = (TCHAR*)param1;

	//Second parameter: error code
	DWORD errorCode = param2;

	switch (msgId)
	{
	case WIM_MSG_ERROR:

		//This message is sent upon failure error case.
		//
		printf("ERROR: %s [err = %d]\n", message, errorCode);
		break;

	case WIM_MSG_RETRY:

		//This message is sent when file is being reapplied because of a
		//network timeout. Retry is done up to five times.
		//
		printf("RETRY: %s [err = %d]\n", message, errorCode);
		break;

	case WIM_MSG_INFO:

		//This message is sent when informational message is available.
		//
		printf("INFO: %s [err = %d]\n", message, errorCode);
		break;

	case WIM_MSG_WARNING:

		//This message is sent when warning message is available.
		//
		printf("WARNING: %s [err = %d]\n", message, errorCode);
		break;
	}

	return WIM_MSG_SUCCESS;
}


void
SampleCleanup(HANDLE hWim, FARPROC callback)
{
	WIMCloseHandle(hWim);
	WIMUnregisterMessageCallback(NULL, callback);
}

//
//Main Function:
//
DWORD __declspec(noinline) WimImage(DWORD argc, TCHAR* argv[])
{
	HANDLE hWim = NULL;
	DWORD  created = 0;
	FARPROC callback = (FARPROC)SampleCallback;

	//TCHAR* wimFile = TEXT("C:\\capture.wim");  //source .wim file
	TCHAR* tmpDir = TEXT("D:\\Temp"); 	//temporary directory

	DWORD imgIndex = 0;
	WIM_INFO hWimInfo = { 0 };

	//Register callback
	//
	if (WIMRegisterMessageCallback(NULL,
		callback,
		NULL) == INVALID_CALLBACK_VALUE) {
		printf("Cannot set callback\n");
		return 2;
	}

	hWim = WIMCreateFile(argv[1],  // existing .wim file to append to
		WIM_GENERIC_READ,  //access mode
		WIM_OPEN_EXISTING, 				 //open flag
		0, // or WIM_FLAG_VERIFY flag for file corruption check
		0,
		&created);

	//Serch OP
	if (!hWim) {
		printf("Cannot open WIM file\n");

		SampleCleanup(hWim, callback);
		return 2;
	}

	if (hWimInfo.ImageCount < 1) {
		printf("Only one image in the .wim file. Cannot delete it\n");

		SampleCleanup(hWim, callback);
		//SetLastError(ERROR_INVALID_PARAMETER);
		return 0;
	}

	SampleCleanup(hWim, callback);

	return 0;
}

DWORD __cdecl wmain(DWORD argc, TCHAR* argv[])
{
	DWORD dwError = ERROR_SUCCESS;
	if (argc < 2) {
		printf("Usage: %s <input file>\n", argv[0]);
		return dwError;
	}
	dwError = WimImage(argc, argv);
	if (ERROR_SUCCESS != dwError)
	{
		return dwError;
	}
	return dwError;
}