#include "lib.h"

// 1. Chức năng 1: nhập vào đường dẫn thư mục, in ra màn hình toàn bộ những thư mục con và tập tin trong thư mục đó.
void listDir(string path) {
    DIR *dir;
    vector <string> listFileName;
    Folder listFolderName;
    struct dirent *ent; // ent is a pointer to dirent structure, a shorthand for struct dirent
    if ((dir = opendir (path.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            int type = ent->d_type;
            switch (type) {
                case DT_REG:    // regular file
                    listFileName.push_back(ent->d_name);
                    break;
                case DT_DIR:    // directory
                    if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
                        Folder folder;
                        folder.name = ent->d_name;
                        listFolderName.subFolders.push_back(folder);
                    }
                    break;
                default:
                    break;
            }
        }
        closedir (dir);
    } else {
        cout << "Cannot open directory" << endl;   
    }

    // duyệt qua các thư mục con
    for (int i = 0; i < listFolderName.subFolders.size(); i++) {
        string subPath = path + "/" + listFolderName.subFolders[i].name;
        listDir(subPath);
    }

}

void printSubFolder (Folder folder) {
    cout << "----";
    cout << folder.name << " : " << endl;
    for (int i = 0; i < folder.subFolders.size(); i++) {
        printSubFolder(folder.subFolders[i]);
        // in ra các file
        for (int j = 0; j < folder.files.size(); j++) {
            cout << "----------" << folder.files[j] << endl;
        }
    }
    // 
}

// 2. Chức năng 2: nhập vào đường dẫn thư mục, tên tập tin. In ra đường dẫn tuyệt đối của thư mục
void printPath(string path, string filename) {

}

// 3. Chức năng 3: Tạo ra file nén encode.txt
void encode(string path, string filename) {

}

// 4. Chức năng 4: Giải nén file encode.txt
void decode(string path, string filename) {
  
}


void handleRequest1() {
    setColor(2);
    string path;
    cout << "\nNhập đường dẫn thư mục: ";
    getline(cin, path);
    vector <string> listFileName;
    Folder listFolderName;
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