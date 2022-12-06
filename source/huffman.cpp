#include "lib.h"

// --------------------------Chức năng 3---------------------------
void encodeFile (ifstream &fin, ofstream &fout) {
    // tạo bảng tần số xuất hiện của các ký tự trong file input
    int *table = new int[256];
    memset(table, 0, 256 * sizeof(int));
    int sumFreq = createFreqTable(fin, table);

    // in ra bảng tần suất
    // printTable(table);
    
    // tạo rừng cây
    queue <Tree *> *root = new queue <Tree *>;
    createForest(table, root);


    // hợp nhất các cây thành 1 cây duy nhất
    mergeForest(root);

    // in cây
    // printTree(root->front());

    // duyệt cây để tạo bảng mã hóa
    createHuffCodes(root->front());

    // in ra bảng mã hóa
    printHuffCodesTable(root->front());



    // giải phóng bộ nhớ
    delete[] table;
    delete root;
}

// đọc file input và tạo bảng các ký tự xuất hiện trong file
int createFreqTable(ifstream &fin, int *table) {
    char c;
    while (fin.read(&c, 1)) {
        table[(int)c]++;
    }

    // đếm tổng số tần suất của các ký tự trong file
    int count = 0;
    for (int i = 0; i < 256; i++) {
        if (table[i] != 0) {
            count += table[i];
        }
    }
    return count;
}

// in ra bảng tần số
void printTable(int *table) {
    cout << "Character   :      Freq      " << endl;
    for (int i = 0; i < 256; i++) {
        if (table[i] != 0) {
            cout << (char) i << "         :         " << table[i] << endl;
        }
    }
}

// tạo rừng n cây, mỗi cây gồm dữ liệu tần số, ký tự, node left và right
void createForest (int *table, queue <Tree*> *root) {

    for (int i = 0; i < 256; i++) {
        if (table[i] != 0) {
            Tree *newTree = new Tree (char (i), table[i]);

            // đẩy vào queue
            root->push(newTree);
        }
    }
}

// hợp nhất các cây thành 1 cây duy nhất
void mergeForest (queue <Tree *> *root) {
    while (root->size() > 1) {
        // sắp xếp cây theo chiều tần số tăng dần
        sortForest_Freq(root ) ;

        // lấy ra hai cây đầu
        Tree *tree1 = root->front();
        root->pop();
        Tree *tree2 = root->front();
        root->pop();

        // hợp nhất hai cây đầu 
        Tree *mergedTree = new Tree (tree1, tree2);

        // đẩy cây đã hợp nhất vào queue
        root->push(mergedTree);
    }

}

int compareFreq (Tree *tree1, Tree *tree2) {
    return tree1->freq < tree2->freq;
}

// sắp xếp danh sách queue theo tần số tăng dần
void sortForest_Freq (queue <Tree *> *root) {
    // chuyển queue thành vector
    vector <Tree *> v;
    while (!root->empty()) {
        v.push_back(root->front());
        root->pop();
    }

    // sắp xếp vector theo tần số tăng dần
    sort(v.begin(), v.end(), compareFreq);

    // chuyển vector thành queue
    for (int i = 0; i < v.size(); i++) {
        root->push(v[i]);
    }
}

// in ra cây sau khi merge về tần số và ký tự
void printTree (Tree *root) {
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
void createHuffCodes (Tree *root) {
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
    createHuffCodes(root->left);
    createHuffCodes(root->right);
}

// in ra bảng mã hóa
void printHuffCodesTable (Tree *root) {
    if (root == NULL) {
        return;
    }
    printHuffCodesTable(root->left);

    if (root->left == NULL && root->right == NULL) {
        cout << "char : " << root->c << "   freq: " << root->freq << "   ";
        cout << "code : " ;
        for (int i = 0; i < root->code.size(); i++) {
            cout << (int) root->code[i] ;
        }   
        cout << endl;
    }

    printHuffCodesTable(root->right);

}

// chuyển theo bộ mã thành xâu nhị phân, ghép với xâu nhị phân còn dư bước trước, nếu đủ 8bits thì ghi tệp
