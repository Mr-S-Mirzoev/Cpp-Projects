#include <iostream>

using std::cin;
using std::cout;
using std::endl;

bool check (bool &st, unsigned &nuls_k, unsigned &nuls,  unsigned &eins_k, unsigned &eins, bool &flag) {
    if (st) {
        if (nuls_k || (eins_k && eins_k != eins)) {
            flag = false;
        }
        if ((!eins) || (!nuls)) {
            flag = false;
        }
        cout << flag << endl;
    }
}

int main () {
    char prev = ' ';
    int x;
    unsigned nuls = 0, eins = 0, nuls_k = 0, eins_k = 0;
    bool st = false, flag = true, first = true;
    while ((x = cin.get()) && x != EOF) {
        if (isspace(x)) {
            if (st) {
                if (nuls_k || (eins_k && eins_k != eins)) {
                    flag = false;
                }
                if ((!eins) || (!nuls)) {
                    flag = false;
                }
                cout << flag << endl;
                prev = ' ';
                nuls = 0;
                eins = 0; 
                nuls_k = 0; 
                eins_k = 0;
                flag = true;
                st = false;
                first = true;
            } else {
                continue;
            }
        } else {
            if (!st) {
                st = true;
            }
            if (!flag) {
                continue;
            } else {
                if (x != '0' && x != '1') {
                    flag = false;
                    prev = ' ';
                    continue;
                } else {
                    if (first) {
                        if (x == '0') {
                            if (prev == '1') {
                                first = false;
                                nuls_k ++;
                            } else {
                                nuls ++;
                            }
                            prev = x;
                        } else {
                            prev = x;
                            if  (nuls == 0) {
                                flag = false;
                                continue;
                            }
                            eins++;
                        }
                    } else {
                        if (x == '0') {
                            if (prev == '1') {
                                if (eins_k != eins) {
                                    prev = ' ';
                                    flag = false;
                                    continue;
                                } else {
                                    eins_k = 0;
                                    nuls_k ++;
                                }
                            } else {
                                nuls_k ++;
                            }
                            prev = x;
                        } else {
                            if (prev == '1') {
                                eins_k ++;
                            } else {
                                if (nuls_k != nuls) {
                                    flag = false;
                                    prev = ' ';
                                    continue;
                                } else {
                                    nuls_k = 0;
                                    eins_k ++;
                                }
                            }
                            prev = x;
                        }
                    }
                }
            }
        }
    }
    check(st, nuls_k, nuls, eins_k, eins, flag);
    return 0;
}
