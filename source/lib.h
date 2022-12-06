#include <bits/stdc++.h>
#include <windows.h>
#include <direct.h>
#include <dirent.h>
using namespace std;

struct Folder {
    string name;
    vector<string> files;
    vector<Folder *> subFolders;
};

// ------------Các yêu cầu----------------

// 1. Chức năng 1: nhập vào đường dẫn thư mục, in ra màn hình toàn bộ những thư mục con và tập tin trong thư mục đó.
void listDir(string path, Folder *head) ;

void printSubFolder (Folder folder) ;

// 2. Chức năng 2: nhập vào đường dẫn thư mục, tên tập tin. In ra đường dẫn tuyệt đối của thư mục
void printPath(string path, string filename) ;

// 3. Chức năng 3: Tạo ra file nén encode.txt
void encode(string path, string filename) ;

// 4. Chức năng 4: Giải nén file encode.txt
void decode(string path, string filename) ;

void handleRequest1() ;

void handleRequest2() ;

void handleRequest3() ;

void handleRequest4() ;



// -----------các hàm bổ trợ--------------
void gotoxy(short x, short y) ;

void setColor(int color) ;
