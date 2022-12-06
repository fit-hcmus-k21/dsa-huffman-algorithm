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
bool printPath(string dir, string filename, string &path) {
    DIR *folder;
    struct dirent *ent;
    if ((folder = opendir(dir.c_str())) != NULL) {
        while ((ent = readdir(folder)) != NULL) {
            int type = ent->d_type;
            switch (type ) {
                case DT_DIR:
                    if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0 ) {
                       if ( printPath(dir + "\\" + ent->d_name, filename, path) == true ) {
                        closedir(folder);
                        return true;
                       }
                    }
                    break;
                case DT_REG:
                    if (filename == ent->d_name) {
                        path = dir + "\\" + filename;
                        closedir(folder);
                        return true;
                    }
                    break;
                default:
                    break;
            }
        }
        closedir(folder);

    } else {
        perror("Không thể mở thư mục");
    }
}

void handleRequest2() {
    setColor(15);
    cout << "Nhập đường dẫn thư mục: ";
    setColor(1);
    string dir;
    getline(cin, dir);
    setColor(15);
    cout << "Nhập tên tập tin: ";
    setColor(1);
    string filename;
    getline(cin, filename);
    setColor(3);
    
    // xử lý
    string path ;
    printPath(dir, filename, path);
    if (path != "") {
        setColor(15);
        cout << "     Path: " ;
        setColor(3);
        cout << path << endl;
    } else {
        setColor(12);
        cout << "Không tồn tại " << filename << " trong " << dir << endl;
    }
}



// --------------------------Chức năng 3---------------------------

// 3. Chức năng 3: Tạo ra file nén encode.txt
void encode(string path) {
    ifstream fin(path, ios::binary);
    if (fin.fail()) {
        cout << "Không thể mở file" << endl;
        return;
    }
    
    // tách đường dẫn thành tên file và đường dẫn
    string filename = path.substr(path.find_last_of("\\") + 1);
    string dir = path.substr(0, path.find_last_of("\\"));

    cout << "Tên file: " << filename << endl;
    cout << "Đường dẫn: " << dir << endl;

    // ghép tên fout = dir + encode.txt
    string fileOut = dir + "\\encode.txt";

    ofstream fout(fileOut, ios::binary);
    if (fout.fail()) {
        cout << "Không thể tạo file" << endl;
        return;
    }

    // xử lý mã hóa file
    encodeFile(fin, fout);

    // đóng file
    fin.close();
    fout.close();
}


void handleRequest3() {
    setColor(15);
    cout << "Nhập đường dẫn file cần nén: ";
    setColor(1);
    string path;
    getline(cin, path);
    clock_t start, end;
    setColor(3);
    start = clock();
    encode(path);
    end = clock();
    cout << "Đã nén file thành công !" << endl;
    cout << "Thời gian nén: " << (double)1000 * (end - start) / CLOCKS_PER_SEC << "ms" << endl;
}


// --------------------------Chức năng 4---------------------------


// 4. Chức năng 4: Giải nén file encode.txt
void decode(string path, string filename) {
  
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