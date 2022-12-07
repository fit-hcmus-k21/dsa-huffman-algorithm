// #undef _WIN32_WINNT
// #define _WIN32_WINNT 0x0501 
// #define WIN32_LEAN_AND_MEAN


#include <bits/stdc++.h>
// #include <algorithm>
// #include <queue>
#include <windows.h>
#include <dirent.h>


using namespace std;


// ------------Các yêu cầu----------------


struct Folder {
    string name;
    vector<string> files;
    vector<Folder *> subFolders;
};

// 1. Chức năng 1: nhập vào đường dẫn thư mục, in ra màn hình toàn bộ những thư mục con và tập tin trong thư mục đó.
void listDir(string path, Folder *head) ;

void printSubFolder (Folder folder) ;

void handleRequest1() ;


// 2. Chức năng 2: nhập vào đường dẫn thư mục, tên tập tin. In ra đường dẫn tuyệt đối của thư mục
bool printPath(string dir, string filename, string &path) ;

void handleRequest2() ;



// ----------------------------------------Struct, Class cho chức năng 3 và 4----------------------------------------------

struct Tree {
    unsigned char c;
    int freq;
    queue <unsigned char> code;
    Tree *left, *right;

    Tree();

    Tree (unsigned char c, int freq) {
        this->c = c;
        this->freq = freq;
        left = right = NULL;
    } 
    Tree (Tree *tree1, Tree *tree2) {
        this->c = '\0';
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

struct EncodeTable {
    unsigned char c ;
    queue <unsigned char> code;
};


class HuffmanCoding {

    public:

        HuffmanCoding()  ;
        ~HuffmanCoding() ;

        // -------------các hàm chức năng---------------

        // khởi tạo đường dẫn và tên file
        void init(string originalPath);
        // mã hóa file
        void encode() ;
        // giải mã file
        void decode() ;

        // ------------các hàm xử lý-----------------
        
        // 3. Chức năng 3: Tạo ra file nén encode.txt
        void handleRequest3() ;

        // 4. Chức năng 4: Giải nén file encode.txt
        void handleRequest4() ;


        // ------------các hàm bổ trợ-----------------

        // hàm tạo bảng tần số
        void createFreqTable() ;

        // hàm in bảng tần số (debug)
        void printTable() ;

        // hàm tạo rừng các cây huffman
        void createForest() ;

        // hàm sắp xếp lại cây trong rừng theo tần số xuất hiện từ thấp đến cao 
        void sortForest_Freq() ;

        // hàm hợp mỗi hai cây thành 1 cho đến khi chỉ còn 1 cây
        void mergeForest() ;

        // hàm in cây huffman sau khi hợp nhất (debug)
        void printTree(Tree *root) ;

        // hàm tạo bảng mã huffman
        void createCodesTable(Tree *root) ;

        // hàm in bảng mã hóa (debug)
        void printCodesTable(Tree *root) ;

        void convertEncodeTable(Tree *root) ;


    private:
        // tên file và đường dẫn
        string path;
        string filename;
        string encodeFilename;
        string decodeFilename;

        // các file stream
        ifstream fin;
        ofstream fout;

        // biến đếm tổng số Bytes file input và bảng tần số
        int countBytes;
        int freqTable[256];


        // rừng các cây huffman
        queue <Tree *> *forest; 

        // cây huffman sau khi hợp nhất
        Tree *root; 

        // tạo bảng mã hóa chỉ gồm ký tự và mã hóa của ký tự dạng mảng để dễ truy cập
        EncodeTable encodeTable[256];

        // bộ đệm ghi file
        unsigned char buffer;
        
        // biến đếm số bit trong bộ đệm
        int numBitFilled;

        // độ dài của kí tự mã hóa
        int codeLen;


};


// -----------các hàm bổ trợ--------------
void gotoxy(short x, short y) ;

void setColor(int color) ;


// hàm hỗ trợ sắp xếp theo tần số trong vector
bool compareFreq(Tree *tree1, Tree *tree2) ;
