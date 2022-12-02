#include <bits/stdc++.h>
#include <windows.h>
#include <direct.h>
#include <dirent.h>
using namespace std;

// ------------Các yêu cầu----------------

// 1. Chức năng 1: nhập vào đường dẫn thư mục, in ra màn hình toàn bộ những thư mục con và tập tin trong thư mục đó.
void listDir(string path) ;

// 2. Chức năng 2: nhập vào đường dẫn thư mục, tên tập tin. In ra đường dẫn tuyệt đối của thư mục
void printPath(string path, string filename) ;

// 3. Chức năng 3: Tạo ra file nén encode.txt
void encode(string path, string filename) ;

// 4. Chức năng 4: Giải nén file encode.txt
void decode(string path, string filename) ;
