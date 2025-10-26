#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

using namespace std;

// Объявляем типы функций
typedef int (*YesNoFunc)(const char*);
typedef void (*AboutFunc)();
typedef int (*MinFunc)(int, int);

int main() {
    cout << "=== Тест DLL (динамическое подключение) ===" << endl;
    
    void* hDll = nullptr;
    
#ifdef _WIN32
    // Windows загрузка DLL
    hDll = LoadLibrary("DialogLibrary.dll");
#else
    // Linux/macOS загрузка shared library
    hDll = dlopen("./libDialogLibrary.so", RTLD_LAZY);
#endif
    
    if (!hDll) {
#ifdef _WIN32
        cout << "Ошибка: не удалось загрузить DialogLibrary.dll!" << endl;
#else
        cout << "Ошибка: не удалось загрузить libDialogLibrary.so!" << endl;
        cout << "Ошибка: " << dlerror() << endl;
#endif
        return 1;
    }
    
    // Получаем адреса функций
#ifdef _WIN32
    YesNoFunc yesNoDialog = (YesNoFunc)GetProcAddress((HMODULE)hDll, "ShowYesNoDialog");
    AboutFunc aboutDialog = (AboutFunc)GetProcAddress((HMODULE)hDll, "ShowAboutDialog");
    MinFunc findMin = (MinFunc)GetProcAddress((HMODULE)hDll, "FindMinimum");
#else
    YesNoFunc yesNoDialog = (YesNoFunc)dlsym(hDll, "ShowYesNoDialog");
    AboutFunc aboutDialog = (AboutFunc)dlsym(hDll, "ShowAboutDialog");
    MinFunc findMin = (MinFunc)dlsym(hDll, "FindMinimum");
#endif
    
    if (!yesNoDialog || !aboutDialog || !findMin) {
        cout << "Ошибка: не удалось найти функции в библиотеке!" << endl;
#ifdef _WIN32
        FreeLibrary((HMODULE)hDll);
#else
        dlclose(hDll);
#endif
        return 1;
    }
    
    // Используем функции
    cout << "Показать диалог 'О программе'? (y/n): ";
    char choice;
    cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        aboutDialog();
    }
    
    // Тест диалога подтверждения
    if (yesNoDialog("Вы хотите найти минимум двух чисел?")) {
        int x, y;
        cout << "Введите первое число: ";
        cin >> x;
        cout << "Введите второе число: ";
        cin >> y;
        
        int minVal = findMin(x, y);
        cout << "Минимум: " << minVal << endl;
    }
    
    // Выгружаем библиотеку
#ifdef _WIN32
    FreeLibrary((HMODULE)hDll);
#else
    dlclose(hDll);
#endif
    
    cout << "Программа завершена." << endl;
    return 0;
}