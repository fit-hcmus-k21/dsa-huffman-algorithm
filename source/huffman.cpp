#include "lib.h"

// --------------------------Chức năng 3---------------------------
void encodeFile (ifstream &fin, ofstream &fout) {
    // tạo bảng tần số xuất hiện của các ký tự trong file input
    int *table = new int[256];
    int sumFreq = createFreqTable(fin, table);

    printTable(table);

    // tạo rừng cây
    queue <Tree *> *root;
    createForest(table, root);

    // hợp nhất các cây thành 1 cây duy nhất






    // giải phóng bộ nhớ
    delete[] table;

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
        Tree *tree2 = root->front();

        // hợp nhất hai cây đầu 
        Tree *mergedTree = new Tree (tree1, tree2);

        // đẩy cây đã hợp nhất vào queue
        root->push(mergedTree);
    }

}

// sắp xếp danh sách queue theo tần số tăng dần
void sortForest_Freq (queue <Tree *> *root) {

}


// tạo bảng mã hóa

// chuyển theo bộ mã thành xâu nhị phân, ghép với xâu nhị phân còn dư bước trước, nếu đủ 8bits thì ghi tệp
