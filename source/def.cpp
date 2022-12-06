#include "lib.h"



// --------------------------Chức năng 1---------------------------

// 1. Chức năng 1: nhập vào đường dẫn thư mục, in ra màn hình toàn bộ những thư mục con và tập tin trong thư mục đó.
void listDir(string path, Folder *head) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            int type = ent->d_type;
            switch (type) {
                case DT_DIR: {
                    if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                        continue;
                    }
                    Folder *folder = new Folder();
                    folder->name = ent->d_name;
                    head->subFolders.push_back(folder);
                    listDir(path + "/" + ent->d_name, folder);
                    break;
                }
                case DT_REG: {
                    head->files.push_back(ent->d_name);
                    break;
                }
                default:
                    break;
            }
        }
        closedir(dir);
    } else {
        setColor(12);
        perror("Không thể mở thư mục");
    }
}

void printDir (Folder *head, int level) {
    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    if (head->name != "") {
        cout << head->name << endl;
    }

    for (int i = 0; i < head->subFolders.size(); i++) {
        printDir(head->subFolders[i], level + 1);
    }

    for (int i = 0; i < head->files.size(); i++) {
        for (int j = 0; j < level + 1 ; j++) {
            cout << "    ";
        }
        cout << head->files[i] << endl;
    }
    
}

void handleRequest1() {
    setColor(15);
    string path;
    cout << "\nNhập đường dẫn thư mục: ";
    setColor(1);
    getline(cin, path);
    Folder *head = new Folder();
    listDir(path, head);
    setColor(3);
    printDir(head, 0);
}


// --------------------------Chức năng 2---------------------------

// 2. Chức năng 2: nhập vào đường dẫn thư mục, tên tập tin. In ra đường dẫn tuyệt đối của thư mục
void printPath(string path, string filename) {

}





// --------------------------Chức năng 3---------------------------

// 3. Chức năng 3: Tạo ra file nén encode.txt
void encode(string path, string filename) {

}


// --------------------------Chức năng 4---------------------------


// 4. Chức năng 4: Giải nén file encode.txt
void decode(string path, string filename) {
  
}

void handleRequest2() {
    cout << "cau 2" << endl;
}

void handleRequest3() {
    cout << "cau 3" << endl;
}

void handleRequest4() {
    cout << "cau 4" << endl;
}


// -----------các hàm bổ trợ--------------
void gotoxy(short x, short y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}