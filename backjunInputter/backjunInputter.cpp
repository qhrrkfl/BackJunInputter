// backjunInputter.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <Windows.h>
#include <processthreadsapi.h>
#include <iostream>
#include <tchar.h>

// reading a text file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;




int main()
{

	string path = "C:\\Users\\JS\\source\\repos\\backjunInputter\\Debug\\";
	SECURITY_ATTRIBUTES saAttr;
	// Set the bInheritHandle flag so pipe handles are inherited. 

	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	


	HANDLE hChildStd_OUT_Rd;
	HANDLE hChildStd_OUT_Wr;
	HANDLE hChildStd_IN_Rd;
	HANDLE hChildStd_IN_Wr;

	//child process's STDOUT is the program output or data that child process returns
	// Create a pipe for the child process's STDOUT. 
	if (!CreatePipe(&hChildStd_OUT_Rd, &hChildStd_OUT_Wr, &saAttr, 0))
		cout << "cannot create out pipe" << endl;

	// Ensure the read handle to the pipe for STDOUT is not inherited.
	if (!SetHandleInformation(hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
		cout << "cannot set out pipe info" << endl;

	//child process's STDIN is the user input or data that you enter into the child process
	// Create a pipe for the child process's STDIN. 
	if (!CreatePipe(&hChildStd_IN_Rd, &hChildStd_IN_Wr, &saAttr, 0))
		cout << "cannot Create In Pipe" << endl;

	// Ensure the write handle to the pipe for STDIN is not inherited. 
	if (!SetHandleInformation(hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0))
		cout << "cannot set in pipe info" << endl;

	// Create the child process. 


	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	BOOL bSuccess = FALSE;

	// Set up members of the PROCESS_INFORMATION structure. 

	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

	// Set up members of the STARTUPINFO structure. 
	// This structure specifies the STDIN and STDOUT handles for redirection.
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	//siStartInfo.hStdError = hChildStd_OUT_Wr;
	//siStartInfo.hStdOutput = hChildStd_OUT_Wr;
	siStartInfo.hStdInput = hChildStd_IN_Rd;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	// Create the child process. 
	TCHAR prcsName[] = _T("C:\\Users\\JS\\source\\repos\\backjunInputter\\Debug\\testChilProcess.exe");
	bSuccess = CreateProcess(
		prcsName,
		NULL,     // command line 
		NULL,          // process security attributes 
		NULL,          // primary thread security attributes 
		TRUE,          // handles are inherited 
		CREATE_NEW_CONSOLE,             // creation flags 
		NULL,          // use parent's environment 
		NULL,          // use parent's current directory 
		&siStartInfo,  // STARTUPINFO pointer 
		&piProcInfo);  // receives PROCESS_INFORMATION 

	// If an error occurs, exit the application. 
	if (!bSuccess) {
		char* error;
		DWORD dw = GetLastError();
		cout << "Cannot Create Process" << "   error code : " << dw << endl;
	}
	else
	{
		// Close handles to the child process and its primary thread.
		// Some applications might keep these handles to monitor the status
		// of the child process, for example. 
		// 자식은 지가 뒤지면 알아서 클린하는데
		// 부모는 알아서 지워야한다. 아예 첨부터 지워줘도 상관없는듯하다..
		//CloseHandle(piProcInfo.hProcess);
		//CloseHandle(piProcInfo.hThread);
	}

	char testStr[] = "아버지가 송신";
	DWORD dwWrittend;
	BOOL bWriteSuc;
	/// =====================================================================================================

	/// 입력 포멧 마지막 구분자는 \n으로 마무리한다.
	// 입력 버퍼의 길이는 \n까지만 센다
	// 그이상으로 입력하면 \n이후의 문자열도 입력으로 본다.
	// 그 이후 동작은 잘 모르겠다. 잘안된다. \n을 꼭 지키자.
	///=====================================================================================================
	string line;
	ifstream myfile(path + "1931.txt");
	if (myfile.is_open())
	{
		char buff[1024];

		int inputlogTest = 0;
		int iInputCnt = 0;
		char* next_Token;
		while (getline(myfile, line))
		{
			ZeroMemory(buff, 1024);
			line += "\n";
			strcpy_s(buff, strlen(line.c_str())+1, line.c_str());
			if (iInputCnt > 0)
			{
				char* tok;
				tok = strtok_s(buff, " ", &next_Token);
				while (tok)
				{

					int idx = 0;

					while (tok[idx] != '\0') 
					{
						idx++;
					}

					char inputBuff[1024];
					ZeroMemory(inputBuff, 1024);
					strcpy_s(inputBuff, idx + 1, tok);
					inputBuff[idx] = '\n';
					idx++;
					cout << "input : " << tok  << "   ";
					bWriteSuc = WriteFile(hChildStd_IN_Wr, inputBuff, idx, &dwWrittend, NULL);
					tok = strtok_s(NULL, " ", &next_Token);

				}
				continue;

			}
			

			bWriteSuc = WriteFile(hChildStd_IN_Wr, buff, line.length(), &dwWrittend, NULL);
			cout << buff << endl;
			if (bWriteSuc == FALSE)
			{
				cout << "write fail" << endl;
			}
			iInputCnt++;
		}
		myfile.close();
	}




	DWORD dwRead, dwWritten;
	CHAR chBuf[1024];
	ZeroMemory(chBuf, sizeof(chBuf));
	BOOL bReadSuc = FALSE;
	HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wResult = 0;
	//bReadSuc = ReadFile(hChildStd_OUT_Rd, chBuf, 1024, &dwRead, NULL);

	cout << "ends" << endl;
	int wait;
	CloseHandle(hChildStd_OUT_Rd);
	CloseHandle(hChildStd_OUT_Wr);
	CloseHandle(hChildStd_IN_Rd);
	CloseHandle(hChildStd_IN_Wr);

}
