// CalculatorWithUndo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CalculatorWithUndo.h"
#include <string>



TCHAR szWindowClass[] = _T("CALCULATOR");
TCHAR szTitle[] = _T("Calculator");
void updateValueText(const double value);
void updateCounter();
bool isKeyDown(int vKey);


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);\
WNDCLASSEX* registration();
HINSTANCE hInst;
HWND hWnd;
Calculation* worker = new Calculation();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Calculator Creation"),
			NULL);
		return 1;
	}

	hInst = hInstance;
	hWnd = CreateWindow(szWindowClass, szTitle, WS_DLGFRAME, CW_USEDEFAULT, CW_USEDEFAULT, 250, 350,(HWND)NULL, (HMENU)NULL, hInst, (LPVOID)NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

WNDCLASSEX* registration() {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Calculator Fail"),
			NULL);
	}
	return &wcex;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HGDIOBJ hfDefault = GetStockObject(DEFAULT_GUI_FONT);
	HWND btn;
    switch (message)
    {
	case WM_CREATE:
		
		btn = CreateWindowEx(NULL, L"BUTTON", L"=", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 118, 205, 36, 28, hWnd, (HMENU)IDOK, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"QUIT", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 118, 255, 36, 28, hWnd, (HMENU)IDCANCEL, GetModuleHandle(NULL), NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"7", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 14, 55, 36, 28, hWnd, (HMENU)IDC_btn7, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"8", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 66, 55, 36, 28, hWnd, (HMENU)IDC_btn8, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"9", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 118, 55, 36, 28, hWnd, (HMENU)IDC_btn9, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"4", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 14, 105, 36, 28, hWnd, (HMENU)IDC_btn4, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"5", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 66, 105, 36, 28, hWnd, (HMENU)IDC_btn5, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"6", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 118, 105, 36, 28, hWnd, (HMENU)IDC_btn6, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"1", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 14, 155, 36, 28, hWnd, (HMENU)IDC_btn1, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"2", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 66, 155, 36, 28, hWnd, (HMENU)IDC_btn2, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"3", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 118, 155, 36, 28, hWnd, (HMENU)IDC_btn3, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"+", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 170, 55, 36, 28, hWnd, (HMENU)IDC_btnAdd, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"-", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 170, 105, 36, 28, hWnd, (HMENU)IDC_btnSub, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"*", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 170, 155, 36, 28, hWnd, (HMENU)IDC_btnMul, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"/", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 170, 205, 36, 28, hWnd, (HMENU)IDC_btnDiv, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"UNDO", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 14, 255, 36, 28, hWnd, (HMENU)IDC_btnUndo, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"CLEAR", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 66, 255, 36, 28, hWnd, (HMENU)IDC_btnClear, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L"0", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 14, 205, 36, 28, hWnd, (HMENU)IDC_btn0, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"BUTTON", L".", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 66, 205, 36, 28, hWnd, (HMENU)IDC_btnDecPt, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"STATIC", L"0", WS_VISIBLE | WS_CHILD, 14, 34, 210, 16, hWnd, (HMENU)IDC_VALUE, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"STATIC", L"0", WS_VISIBLE | WS_CHILD, 104, 14, 104, 16, hWnd, (HMENU)IDC_TRACKER, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		btn = CreateWindowEx(NULL, L"STATIC", L"Operations:", WS_VISIBLE | WS_CHILD, 14, 14, 75, 16, hWnd, (HMENU)IDC_STATIC, hInst, NULL);
		SendMessage(btn, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		break;
    case WM_COMMAND:
        {
			double returnVal;
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case IDC_btn0:
				returnVal = worker->digit(0);
				updateValueText(returnVal);
				//updateCounter();
				break;
			case IDC_btn1:
				returnVal = worker->digit(1);
				updateValueText(returnVal);
				//updateCounter();
				break;
			case IDC_btn2:
				returnVal = worker->digit(2);
				updateValueText(returnVal);
				//updateCounter();
				break;
			case IDC_btn3:
				returnVal = worker->digit(3);
				updateValueText(returnVal);
				//updateCounter();
				break;
			case IDC_btn4:
				returnVal = worker->digit(4);
				updateValueText(returnVal);
				//updateCounter();
				break;
			case IDC_btn5:
				returnVal = worker->digit(5);
				updateValueText(returnVal);
				//updateCounter();
				break;
			case IDC_btn6:
				returnVal = worker->digit(6);
				updateValueText(returnVal);
				//updateCounter();
				break;
			case IDC_btn7:
				returnVal = worker->digit(7);
				updateValueText(returnVal);
				//updateCounter();
				break;
			case IDC_btn8:
				returnVal = worker->digit(8);
				updateValueText(returnVal);
				//updateCounter();
				break;
			case IDC_btn9:
				returnVal = worker->digit(9);
				updateValueText(returnVal);
				//updateCounter();
				break;
			case IDC_btnAdd:
				returnVal = worker->add();
				updateValueText(returnVal);
				updateCounter();
				break;
			case IDC_btnSub:
				returnVal = worker->sub();
				updateValueText(returnVal);
				updateCounter();
				break;
			case IDC_btnMul:
				returnVal = worker->mul();
				updateValueText(returnVal);
				updateCounter();
				break;
			case IDC_btnDiv:
				returnVal = worker->div();
				updateValueText(returnVal);
				updateCounter();
				break;
			case IDC_btnDecPt:
				returnVal = worker->decimal();
				updateValueText(returnVal);
				updateCounter();
				break;
			case IDOK:
				returnVal = worker->equal();
				updateValueText(returnVal);
				updateCounter();
				break;
			case IDC_btnClear:
				returnVal = worker->clear();
				updateValueText(returnVal);
				updateCounter();
				break;
			case IDC_btnUndo:
				returnVal = worker->undo();
				updateValueText(returnVal);
				updateCounter();
				break;
			case IDCANCEL:
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_DELETE:
		case VK_CLEAR:
			SendMessage(hWnd, WM_COMMAND, IDC_btnClear, NULL);
			break;
		case VK_RETURN:
			SendMessage(hWnd, WM_COMMAND, IDOK, NULL);
			break;
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		case VK_NUMPAD0:
		case 0x30:
			SendMessage(hWnd, WM_COMMAND, IDC_btn0, NULL);
			break;
		case VK_NUMPAD1:
		case 0x31:
			SendMessage(hWnd, WM_COMMAND, IDC_btn1, NULL);
			break;
		case VK_NUMPAD2:
		case 0x32:
			SendMessage(hWnd, WM_COMMAND, IDC_btn2, NULL);
			break;
		case VK_NUMPAD3:
		case 0x33:
			SendMessage(hWnd, WM_COMMAND, IDC_btn3, NULL);
			break;
		case VK_NUMPAD4:
		case 0x34:
			SendMessage(hWnd, WM_COMMAND, IDC_btn4, NULL);
			break;
		case VK_NUMPAD5:
		case 0x35:
			SendMessage(hWnd, WM_COMMAND, IDC_btn5, NULL);
			break;
		case VK_NUMPAD6:
		case 0x36:
			SendMessage(hWnd, WM_COMMAND, IDC_btn6, NULL);
			break;
		case VK_NUMPAD7:
		case 0x37:
			SendMessage(hWnd, WM_COMMAND, IDC_btn7, NULL);
			break;
		case VK_NUMPAD8:
		case 0x38:
			SendMessage(hWnd, WM_COMMAND, IDC_btn8, NULL);
			break;
		case VK_NUMPAD9:
		case 0x39:
			SendMessage(hWnd, WM_COMMAND, IDC_btn9, NULL);
			break;
		case VK_DECIMAL:
			SendMessage(hWnd, WM_COMMAND, IDC_btnDecPt, NULL);
			break;
		case VK_ADD:
			SendMessage(hWnd, WM_COMMAND, IDC_btnAdd, NULL);
			break;
		case VK_MULTIPLY:
			SendMessage(hWnd, WM_COMMAND, IDC_btnMul, NULL);
			break;
		case VK_SUBTRACT:
			SendMessage(hWnd, WM_COMMAND, IDC_btnSub, NULL);
			break;
		case VK_DIVIDE:
			SendMessage(hWnd, WM_COMMAND, IDC_btnDiv, NULL);
			break;
		case 0x5a:
			if (isKeyDown(0x11)) {
				SendMessage(hWnd, WM_COMMAND, IDC_btnUndo, NULL);
			}
			break;
		}
		break;
	/*case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;*/
    case WM_DESTROY:
        PostQuitMessage(0);
		delete worker;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
	SetFocus(hWnd);
    return 0;
}

void updateValueText(double val) {
	string s = std::to_string(val);
	TCHAR* buffer;
    buffer = new TCHAR [s.length()+1];
	swprintf (buffer, (s.length() + 1), L"%f", val);
	SetDlgItemText(hWnd, IDC_VALUE, buffer);
}

void updateCounter() {
	
	SetDlgItemInt(hWnd, IDC_TRACKER, (worker->getOperations()), false);
}

bool isKeyDown(int vKey) {
	SHORT value = GetKeyState(vKey);
	char lowBit = value & 1;
	char hiBits = value & 0x8000;
	if (hiBits) {
		return true;
	}
	if (lowBit) {
		return true;
	}
	return false;
}