#include "lib.h"

// --------------------------Chức năng 3---------------------------
void encodeFile (ifstream &fin, ofstream &fout) {
    // tạo bảng tần số xuất hiện của các ký tự trong file input
    int *table = new int[256];
    int sumFreq = readFile(fin, table);





    // giải phóng bộ nhớ
    delete[] table;

}

// đọc file input và tạo bảng các ký tự xuất hiện trong file
int readFile(ifstream &fin, int *table) {
    char c;
    while (fin.read(&c, 1)) {
        table[(int)c]++;
    }

    // đếm số ký tự xuất hiện trong file
    int count = 0;
    for (int i = 0; i < 256; i++) {
        if (table[i] != 0) {
            count++;
        }
    }
    return count;
}

// tạo rừng n cây, mỗi cây gồm gốc là tần số và lá là kí tự

// hợp nhất các cây thành 1 cây duy nhất

// sắp xếp các cây theo thứ tự tần số tăng dần

// tạo bảng mã hóa

// chuyển theo bộ mã thành xâu nhị phân, ghép với xâu nhị phân còn dư bước trước, nếu đủ 8bits thì ghi tệp
