#include "lib.h"

// 1. Chức năng 1: nhập vào đường dẫn thư mục, in ra màn hình toàn bộ những thư mục con và tập tin trong thư mục đó.
void listDir(string path) {
    DIR *dir;
    struct dirent *ent; // ent is a pointer to dirent structure, a shorthand for struct dirent
    if ((dir = opendir (path.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            int type = ent->d_type;
            switch (type) {
                case DT_REG:    // regular file
                    cout << "File: " << ent->d_name << endl;
                    break;
                case DT_DIR:    // directory
                    cout << "Directory: " << ent->d_name << endl;
                    break;
                case DT_LNK:    // symbolic link
                    cout << "Symbolic link: " << ent->d_name << endl;
                    break;
                default:
                    cout << "Unknown: " << ent->d_name << endl;
                    break;
            }
        }
        closedir (dir);
    } else {
        cout << "Cannot open directory" << endl;   
    }
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
