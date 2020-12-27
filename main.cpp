#include <iostream>
#include <windows.h>
#include <winuser.h>

using namespace std;

int main()
{
    system("CLS");

    string windowName;
    cout << "Please enter a active window name: ";
    getline(std::cin >> std::ws, windowName);

    HWND hWnd = FindWindow(0, windowName.c_str());

    if(hWnd == 0)
    {
        MessageBox(0, "Error cannot find window.", "Error", MB_OK|MB_ICONERROR);
    }
    else
    {
        cout << ">> The window found." << endl;

        DWORD proccessID;
        GetWindowThreadProcessId(hWnd, &proccessID);
        HANDLE iProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proccessID);
        if(!iProcess)
        {
            MessageBox(0, "Could not open the process!", "Error!", MB_OK|MB_ICONERROR);
        }
        else
        {
            string memoryAddress;

            cout << "Please enter memory address: ";
            cin >> memoryAddress;

            int newData = 0;

            cout << "Please enter the new value: ";
            cin >> newData;

            DWORD dataSize = sizeof(newData);

            if(WriteProcessMemory(iProcess, (LPVOID)memoryAddress.c_str(), &newData, dataSize, NULL))
            {
                MessageBox(NULL, "WriteProcessMemory worked successfully.", "Success", MB_OK + MB_ICONINFORMATION);
            }
            else
            {
                MessageBox(NULL, "Error while running WriteProcessMemory. Please check the memory address!", "Error", MB_OK + MB_ICONERROR);
            }
            CloseHandle(iProcess);
        }
    }

    return 0;
}
