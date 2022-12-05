#include "lib.h"

int main() {
    //------------------------- Thiết kế giao diện -------------------------
    SetConsoleOutputCP(65001);

    // lấy chiều dài, chiều rộng console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // đến giữa màn hình
    system("cls");

    // đặt màu nền cho heading
    char *heading = new char[100];
    strcpy(heading, "BÀI TẬP LỚN MÔN CƠ SỞ DỮ LIỆU VÀ GIẢI THUẬT");
    setColor(11);
    gotoxy(0, 1);
    int i;
    for (i = 0; i < (consoleWidth - strlen(heading))/2 + 13 ; i++) {
        cout << "-";
    }
    cout << heading;
    for (; i < consoleWidth - 43 ; i++) {
        cout << "-";
    }
    free(heading);
    // hiển thị menu
    setColor(14);
    gotoxy(10, 3);
    cout << "-----------------------------------------------------MENU-----------------------------------------------------" << endl;
    setColor(10);
    gotoxy(10, 4);
    cout << "   1. Nhập vào đường dẫn thư mục, in ra màn hình toàn bộ những thư mục con và tập tin trong thư mục đó." << endl;
    gotoxy(10, 5);
    cout << "   2. Nhập vào đường dẫn thư mục, tên tập tin. In ra đường dẫn tuyệt đối của thư mục" << endl;
    gotoxy(10, 6);
    cout << "   3. Tạo ra file nén encode.txt" << endl;
    gotoxy(10, 7);
    cout << "   4. Giải nén file encode.txt" << endl;
    gotoxy(10, 8);
    cout << "   5. Thoát chương trình" << endl;
    gotoxy(10, 9);
    setColor(14);
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    
    // set border
    setColor(14);
    for (int i = 4; i < 9; i++) {
        gotoxy(10, i);
        cout << "|";
        gotoxy(10 + 109, i);
        cout << "|";
    }

    //------------------------- Xử lý chức năng -------------------------
    int cont = 1;
    string choose;
    int choice;
    gotoxy(0, 11);
    while (cont) {
        setColor(7);
        cout << "Chọn chức năng: ";
        setColor(9);
        getline(cin, choose);
        choice = atoi(choose.c_str());
        switch (choice) {
            case 1: {
                handleRequest1();
                break;
            }
            case 2: {
                handleRequest2();
                break;
            }
            case 3: {
                handleRequest3();
                break;
            }
            case 4: {
                handleRequest4();
                break;
            }
            case 5: {
                cont = 0;
                // thoát chương trình
                setColor(11);
                gotoxy(0, consoleHeight - 1);
                for (int i = 0; i < consoleWidth; i++) {
                    cout << "-";
                }
                break;
            }
            default: {
                setColor(12);
                cout << "Chức năng không tồn tại!" << endl;
                setColor(15);
                break;
            }
        }
    }  
    setColor(15);
 
    return 225;

}

