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

struct Tree {
    char c;
    int freq;
    vector <char> code;
    Tree *left, *right;
    Tree (char c, int freq) {
        this->c = c;
        this->freq = freq;
        left = right = NULL;
    } 
    Tree (Tree *tree1, Tree *tree2) {
        this->freq = tree1->freq + tree2->freq;
        if (tree1->freq < tree2->freq) {
            this->left = tree1;
            this->right = tree2;
        } else {
            this->left = tree2;
            this->right = tree1;
        }
    }
};

// ------------Các yêu cầu----------------

// 1. Chức năng 1: nhập vào đường dẫn thư mục, in ra màn hình toàn bộ những thư mục con và tập tin trong thư mục đó.
void listDir(string path, Folder *head) ;

void printSubFolder (Folder folder) ;

void handleRequest1() ;


// 2. Chức năng 2: nhập vào đường dẫn thư mục, tên tập tin. In ra đường dẫn tuyệt đối của thư mục
bool printPath(string dir, string filename, string &path) ;

void handleRequest2() ;


// 3. Chức năng 3: Tạo ra file nén encode.txt
void encode(string path, string filename) ;

void handleRequest3() ;

void encodeFile (ifstream &fin, ofstream &fout) ;

int createFreqTable (ifstream &fin, int *table) ;

void printTable (int *table) ;

void createForest (int *table, queue <Tree*> *root) ;

void mergeForest (queue <Tree *> *root) ;

void sortForest_Freq (queue <Tree *> *root) ;

int compareFreq (Tree *tree1, Tree *tree2) ;

void createHuffCodes (Tree *root) ;


// 4. Chức năng 4: Giải nén file encode.txt
void decode(string path, string filename) ;

void handleRequest4() ;



// -----------các hàm bổ trợ--------------
void gotoxy(short x, short y) ;

void setColor(int color) ;
