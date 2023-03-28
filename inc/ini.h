#ifndef INI_H 
#define INI_H 

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static inline DWORD ini_get_string(
    LPCSTR section, LPCSTR key, LPCSTR default_value, LPSTR out_string, DWORD out_size, LPCSTR file_name)
{
    return GetPrivateProfileStringA(section, key, default_value, out_string, out_size, file_name);
}

static inline BOOL ini_get_bool(LPCSTR section, LPCSTR key, BOOL default_value, LPCSTR file_name)
{
    char value[8];
    ini_get_string(section, key, default_value ? "Yes" : "No", value, sizeof(value), file_name);

    return (_stricmp(value, "yes") == 0 || _stricmp(value, "true") == 0 || _stricmp(value, "1") == 0);
}

static inline int ini_get_int(LPCSTR section, LPCSTR key, int default_value, LPCSTR file_name)
{
    char def_value[16];
    _snprintf(def_value, sizeof(def_value), "%d", default_value);

    char value[16];
    ini_get_string(section, key, def_value, value, sizeof(value), file_name);

    return atoi(value);
}

static inline float ini_get_float(LPCSTR section, LPCSTR key, float default_value, LPCSTR file_name)
{
    char def_value[16];
    _snprintf(def_value, sizeof(def_value), "%.1f", default_value);

    char value[16];
    ini_get_string(section, key, def_value, value, sizeof(value), file_name);

    return (float)atof(value);
}

#endif
