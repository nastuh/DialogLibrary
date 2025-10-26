#ifndef DIALOGLIBRARY_H
#define DIALOGLIBRARY_H

#ifdef _WIN32
    #ifdef DIALOGLIBRARY_EXPORTS
        #define DIALOG_API __declspec(dllexport)
    #else
        #define DIALOG_API __declspec(dllimport)
    #endif
#else
    #define DIALOG_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

    DIALOG_API int ShowYesNoDialog(const char* question);
    DIALOG_API void ShowAboutDialog();
    DIALOG_API int FindMinimum(int x, int y);

#ifdef __cplusplus
}
#endif

#endif