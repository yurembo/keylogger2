 wchar_t prevProg[256] = L"\0";
wchar_t *curProg = new wchar_t[BUFFER_SIZE];
        GetWindowText(foreground, curProg, BUFFER_SIZE);
if (wcscmp(curProg, prevProg) != 0) {
            wcscpy_s(prevProg, curProg);
            wstring ws = curProg;
            __time64_t longtime;
            struct tm newtime;
            _time64(&longtime);
            _localtime64_s(&newtime, &longtime);
            wchar_t str_time[64];
            _wasctime_s(str_time, &newtime);
            file << "\n[Program: " << wchar_t(curProg) << " DateTime: " << wchar_t(str_time) << "]\n";
        }