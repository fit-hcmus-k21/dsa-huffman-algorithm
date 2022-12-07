#include "lib.h"



// --------------------------Chức năng 3---------------------------

void HuffmanCoding::handleRequest3 () {
    setColor(15);
    cout << "Nhập đường dẫn file cần nén: ";
    setColor(1);
    string path;
    getline(cin, path);

    clock_t start, end;
    start = clock();

    // tách tên file và path
    init(path);

    // mở file output
    fout.open(encodeFilename, ios::binary);
    if (fout.fail()) {
        cout << "Không thể tạo file" << endl;
        return;
    }

    // mã hóa file
    encode();

    end = clock();
    setColor(3);
    cout << "Đã nén file thành công !" << endl;
    cout << "Thời gian nén: " << (double)1000 * (end - start) / CLOCKS_PER_SEC << "ms" << endl;

}


void HuffmanCoding :: encode () {
    // tạo bảng tần số xuất hiện của các ký tự trong file input
    createFreqTable();

    // in ra bảng tần suất
    // printTable();
    
    // tạo rừng cây
    createForest();


    // hợp nhất các cây thành 1 cây duy nhất
    mergeForest();

    // in cây
    root = forest->front();
    // printTree(root);

    // duyệt cây để tạo bảng mã hóa
    createCodesTable(root);

    // in ra bảng mã hóa
    // printCodesTable(root);

    // chuyển bảng mã hóa từ dạng cây sang dạng mảng
    convertEncodeTable(root);

    // in ra bảng mã hóa
    // for (int i = 0; i < 256; i++) {
    //     if (encodeTable[i].code.size() != 0) {
    //         cout << i << " :" ;
    //         for (auto x : encodeTable[i].code) {
    //             cout << (int)x;
    //         }
    //         cout << endl;
    //     }
    // }

    /* đọc từng byte 
    chuyển theo bộ mã thành xâu nhị phân, ghép với xâu nhị phân còn dư bước trước,
    nếu đủ 8bits thì ghi tệp
    */

}

// ---------------------------------Chức năng 4---------------------------
void HuffmanCoding::handleRequest4 () {
    setColor(15);
    cout << "Nhập đường dẫn file cần giải nén: ";
    setColor(1);
    string path;
    getline(cin, path);
    clock_t start, end;
    start = clock();

    // mở file output
    fout.open(decodeFilename, ios::binary);
    if (fout.fail()) {
        cout << "Không thể tạo file" << endl;
        return;
    }
    // giải mã file
    decode();

    end = clock();

    setColor(3);
    cout << "Đã giải nén file thành công !" << endl;
    cout << "Thời gian giải nén: " << (double)1000 * (end - start) / CLOCKS_PER_SEC << "ms" << endl;

}

void HuffmanCoding::decode() {

}

// --------------------------định nghĩa các hàm class---------------------------

HuffmanCoding::HuffmanCoding() {
    // khởi tạo các biến
    root = NULL;
    forest = new queue <Tree *>;
    memset(freqTable, 0, sizeof(freqTable));
}

HuffmanCoding::~HuffmanCoding() {
    // đóng file input
    fin.close();
    fout.close();

    // giải phóng bộ nhớ
    delete root;
    

}

// khởi tạo đường dẫn và tên file từ đường dẫn nhập vào, mở file input
void HuffmanCoding::init(string originalPath) {
    this->path = originalPath.substr(0, originalPath.find_last_of("\\"));
    this->filename = originalPath.substr(originalPath.find_last_of("\\") + 1);
    this->encodeFilename = path + "\\encode.txt";
    this->decodeFilename = path + "\\decode.txt";

    // mở file input
    fin.open(originalPath, ios::binary);
    if (fin.fail()) {
        cout << "Không thể mở file" << endl;
        return;
    }
}


// tạo bảng các ký tự xuất hiện trong file
void HuffmanCoding::createFreqTable() {
    char c;
    while (fin.read(&c, 1)) {
        unsigned char b = c;
        freqTable[(int) b]++;
    }

    // đếm tổng số tần suất của các ký tự trong file (không tính EOF)
    count = 0;
    for (int i = 0; i < 256; i++) {
        if (freqTable[i] != 0) {
            count += freqTable[i];
        }
    }
}

// in ra bảng tần số
void HuffmanCoding::printTable() {
    cout << "Ascii   :      Freq    " << endl;
    for (int i = 0; i < 256; i++) {
        if (freqTable[i] != 0) {
            cout <<  i << " :  " << freqTable[i] << endl;
        }
    }
}

// tạo rừng n cây, mỗi cây gồm dữ liệu tần số, ký tự, node left và right = NULL
void HuffmanCoding :: createForest () {

    for (int i = 0; i < 256; i++) {
        if (freqTable[i] != 0) {

            Tree *newTree = new Tree ((unsigned char) i, freqTable[i]);

            // đẩy vào queue
            forest->push(newTree);
        }
    }
}

// hợp nhất các cây thành 1 cây duy nhất
void HuffmanCoding::mergeForest () {
    while (forest->size() > 1) {
        // sắp xếp cây theo chiều tần số tăng dần
        sortForest_Freq( ) ;

        // lấy ra hai cây đầu
        Tree *tree1 = forest->front();
        forest->pop();
        Tree *tree2 = forest->front();
        forest->pop();

        // hợp nhất hai cây đầu 
        Tree *mergedTree = new Tree (tree1, tree2);

        // đẩy cây đã hợp nhất vào queue
        forest->push(mergedTree);
    }

}

// sắp xếp danh sách queue theo tần số tăng dần
void HuffmanCoding::sortForest_Freq () {
    // chuyển queue thành vector
    vector <Tree *> v;
    while (!forest->empty()) {
        v.push_back(forest->front());
        forest->pop();
    }

    // sắp xếp vector theo tần số tăng dần
    sort(v.begin(), v.end(), compareFreq);

    // chuyển vector thành queue
    for (int i = 0; i < v.size(); i++) {
        forest->push(v[i]);
    }
}

// in ra cây sau khi merge về tần số và ký tự
void HuffmanCoding::printTree (Tree *root) {
    if (root != NULL) {
        cout << "freq: " << root->freq << endl;
        if (root->c != '\0') {
            cout << "char: " << root->c << endl;
        }
        printTree(root->left);
        printTree(root->right);

    }
}

// tạo bảng mã hóa
void HuffmanCoding :: createCodesTable (Tree *root) {
    if (root == NULL) {
        return;
    }

    // qua trái thì là 0
    if (root->left != NULL) {
        root->left->code = root->code;
        root->left->code.push_back(0);
    }

    // qua phải thì là 1
    if (root->right != NULL) {
        root->right->code = root->code;
        root->right->code.push_back(1);
    }

    // duyệt xuống cây trái và cây phải
    createCodesTable(root->left);
    createCodesTable(root->right);
}

// in ra bảng mã hóa
void HuffmanCoding :: printCodesTable (Tree *root) {
    if (root == NULL) {
        return;
    }
    printCodesTable(root->left);

    if (root->left == NULL && root->right == NULL) {
        cout << "freq: " << root->freq << "   ";
        cout << "code : " ;
        for (int i = 0; i < root->code.size(); i++) {
            cout << (int) root->code[i] ;
        }   
        cout << endl;
    }

    printCodesTable(root->right);

}

// hàm chuyển bảng mã hóa từ dạng cây sang dạng mảng cấu trúc
void HuffmanCoding::convertEncodeTable (Tree *root) {
    if (root == NULL) {
        return;
    }
    convertEncodeTable(root->left);

    if (root->left == NULL && root->right == NULL) {
        encodeTable[(int) root->c].c = root->c;
        encodeTable[(int) root->c].code = root->code;
    }

    convertEncodeTable(root->right);
}




