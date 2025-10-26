#include "DialogLibrary.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

// Точка входа для Windows DLL
#ifdef _WIN32
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}
#endif

DIALOG_API int ShowYesNoDialog(const char* question) {
#ifdef _WIN32
    // Windows версия
    int result = MessageBoxA(NULL, question, "Подтверждение", 
                           MB_YESNO | MB_ICONQUESTION);
    return (result == IDYES);
#else
    // Linux/macOS версия
    std::cout << "=== " << question << " ===" << std::endl;
    std::cout << "1. Да" << std::endl;
    std::cout << "2. Нет" << std::endl;
    std::cout << "Выберите вариант (1/2): ";
    
    int choice;
    std::cin >> choice;
    return (choice == 1);
#endif
}

DIALOG_API void ShowAboutDialog() {
#ifdef _WIN32
    // Windows версия
    MessageBoxA(NULL, 
        "Разработчик: Раевская Анастасия\n"
        "Группа: 4К9391\n"
        "Лабораторная работа: 4\n"
        "Год: 2025", 
        "О программе", MB_OK | MB_ICONINFORMATION);
#else
    // Linux/macOS версия
    std::cout << "=== О ПРОГРАММЕ ===" << std::endl;
    std::cout << "Разработчик: Иванов Иван" << std::endl;
    std::cout << "Группа: ПИ-123" << std::endl;
    std::cout << "Лабораторная работа: 9" << std::endl;
    std::cout << "Год: 2024" << std::endl;
    std::cout << "====================" << std::endl;
#endif
}

DIALOG_API int FindMinimum(int x, int y) {
    return (x < y) ? x : y;
}