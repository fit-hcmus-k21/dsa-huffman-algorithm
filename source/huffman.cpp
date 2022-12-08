#include "lib.h"



// --------------------------Chức năng 3---------------------------

void HuffmanCoding::handleRequest3 () {
    setColor(15);
    cout << "Nhập đường dẫn file cần nén: ";
    setColor(6);
    string path;
    getline(cin, path);

    setColor(3);
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

    // đóng file
    fin.close();
    fout.close();

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
    //         int n = encodeTable[i].code.size();
    //         for (int j = 0; j < n; j++) {
    //             unsigned char code = encodeTable[i].code.front();
    //             cout << (int) code;
    //             encodeTable[i].code.pop();
    //             encodeTable[i].code.push(code);
    //         }
    //         cout << endl;
    //     }
    // }

    /* đọc từng byte 
    chuyển theo bộ mã thành xâu nhị phân, ghép với xâu nhị phân còn dư bước trước,
    nếu đủ 8bits thì ghi tệp
    */
    buffer = 0;
    numBitFilled = 0;
    codeLen = 0;

    // đếm số byte mã hóa
    int numByteEncoded = 0;

    char ch;
    // di chuyển về đầu tệp
    fin.clear();
    fin.seekg(0);

    while (fin.get(ch)) {
        // cout << "ki tu da doc: " << ch << endl;
        unsigned char c = ch;
        codeLen = encodeTable[c].code.size();

        while (codeLen > 0) {
            
            if (numBitFilled == 8) {
                fout.put(buffer);
                numBitFilled = 0;
                buffer = 0;
                numByteEncoded++;
            }
            
            unsigned char code = encodeTable[c].code.front();
            encodeTable[c].code.pop();
            encodeTable[c].code.push(code);
            buffer = (buffer << 1) | code;
            codeLen--;
            numBitFilled++;
            
        }

    }

    // ghi ký tự EOF
    codeLen = encodeTable[26].code.size();
    while (codeLen > 0) {
        if (numBitFilled == 8) {
            fout.put(buffer);
            numBitFilled = 0;
            buffer = 0;
            numByteEncoded++;
        } 

        unsigned char code = encodeTable[26].code.front();
        encodeTable[26].code.pop();
        encodeTable[26].code.push(code);
        buffer = (buffer << 1) | code;
        codeLen --;
        numBitFilled ++;
        
    }

    // nếu còn trong buffer chưa ghi file
    if (numBitFilled > 0) {
        while (numBitFilled != 8) {
            buffer = (buffer << 1) | 0;
            numBitFilled ++;
        }
        fout.put(buffer);
        numBitFilled = 0;
        buffer = 0;
        numByteEncoded++;
    }
    cout << "Số byte trước khi mã hóa: " << countBytes << endl;
    cout << "Số byte sau khi mã hóa: " << numByteEncoded << endl;
    // printf("Tỷ lệ nén: %.2f%%\n", (float)numByteEncoded / countBytes * 100);
}

// ---------------------------------Chức năng 4---------------------------
void HuffmanCoding::handleRequest4 () {
    setColor(15);
    cout << "Nhập đường dẫn file cần giải nén: ";
    setColor(6);
    string path;
    getline(cin, path);

    // tách tên file, đường dẫn, mở file input
    init(path);

    setColor(1);
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

    // đóng file
    fin.close();
    fout.close();

}

void HuffmanCoding::decode() {
    // đọc file input và duyệt cây huffman, nếu là lá thì ghi vào file output
    char ch;
    int numBytesDecode = 0;
    int numBytesRead = 0;
    Tree *cur = root;

    while (fin.get(ch)) {
        numBytesRead++;
        unsigned char c = ch;
        for (int i = 7; i >= 0; i--) {
            unsigned char code = (c >> i) & 1;  // lấy bit thứ i
            if (cur->left == NULL && cur->right == NULL) {
                if (cur->c == 26) { // EOF
                    break;
                }
                char buffer = cur->c;
                fout.put(buffer);
                cur = root;
                numBytesDecode++;
            }

            if (code == 0) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
    }

    cout << "Số byte trước khi giải nén: " << numBytesRead << endl;
    cout << "Số byte sau khi giải nén: " << numBytesDecode << endl;
}

// --------------------------định nghĩa các hàm class---------------------------

HuffmanCoding::HuffmanCoding() {
    // khởi tạo các biến
    root = NULL;
    forest = new queue <Tree *>;
    memset(freqTable, 0, sizeof(freqTable));
}

HuffmanCoding::~HuffmanCoding() {
    // giải phóng bộ nhớ
    delete root;
    delete forest;
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
    countBytes = 0;
    for (int i = 0; i < 256; i++) {
        if (freqTable[i] != 0) {
            countBytes += freqTable[i];
        }
    }

    freqTable[26] ++; // vị trí ký tự EOF

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
        root->left->code.push(0);
    }

    // qua phải thì là 1
    if (root->right != NULL) {
        root->right->code = root->code;
        root->right->code.push(1);
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
        int n = root->code.size();
        for (int i = 0; i < n; i++ ) {
            unsigned char c = root->code.front();
            cout << c;
            root->code.pop();
            root->code.push(c);
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




