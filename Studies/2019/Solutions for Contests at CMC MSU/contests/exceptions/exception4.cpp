#include <iostream>

bool S_worker (int &i, std::string &s) {
    bool ret = false;
    if (s[i] == '0') {
        i++;
    } else if (s[i] == '1') {
        state = 'A';
        i++;
    } else {
        ret = true;
    }
    return ret;
}

bool A_worker (int &i, std::string &s) {
    bool ret = false;
    if (s[i] == '0') {
        i++;
    } else if (s[i] == '1') {
        state = 'S';
        i++;
    } else if (s[i] == '#') {
        state = 'B';
        i--;
    } else {
        ret = true;
    }
    return ret;
}

bool B_worker (int &i, std::string &s) {
    bool ret = false;
    if (s[i] == '0' || s[i] == '1') {
        i--;
    } else if (s[i] == '#') {
        state = 'C';
        i++;
    } else {
        ret = true;
    }
    return ret;
}

bool C_worker (int &i, std::string &s) {
    bool ret = false;
    if (s[i] == '0') {
        i++;
    } else if (s[i] == '1') {
        state = 'D';
        s[i] = '0';
        ret = true;
    } else {
        ret = true;
    }
    return ret;
}

int main (void) {
    std::string s;
    std::cin >> s;
    char state = 'S';
    unsigned i = 1;
    while (1) {
        if (state == 'S') {
            if (S_worker(i, s)) {
                break;
            }
        } else if (state == 'A') {
            if (A_worker(i, s)) {
                break;
            }
        } else if (state == 'B') {
            if (B_worker(i, s)) {
                break;
            }
        } else if (state == 'C') {
            if (C_worker(i, s)) {
                break;
            }
        } else {
            break;
        }
        if (i >= s.length()) {
            break;
        }
    }
    std::cout << s << std::endl;
    return 0;
}
