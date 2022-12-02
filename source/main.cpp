#include "lib.h"

int main() {
    SetConsoleOutputCP(65001);

    cout << "Nhập đường dẫn thư mục: ";
    string path;
    getline(cin, path);
    listDir(path);
 
    return 0;

}

