#include <iostream>
using namespace std;

void and_gate() {
    int x1, x2, w1 = 1, w2 = 1, th = 2, y, out;
    cout << "\n[AND Gate]\n";
    cout << "Masukkan X1: ";
    cin >> x1;
    cout << "Masukkan X2: ";
    cin >> x2;

    y = x1 * w1 + x2 * w2;
    out = (y >= th) ? 1 : 0;
    cout << "Hasil AND Gate: " << out << endl;
}

void or_gate() {
    int x1, x2, w1 = 2, w2 = 2, th = 2, y, out;
    cout << "\n[OR Gate]\n";
    cout << "Masukkan X1: ";
    cin >> x1;
    cout << "Masukkan X2: ";
    cin >> x2;

    y = x1 * w1 + x2 * w2;
    out = (y >= th) ? 1 : 0;
    cout << "Hasil OR Gate: " << out << endl;
}

void xor_gate() {
    int x1, x2, w1 = 2, w2 = -1, w3 = -1, w4 = 2, w5 = 2, w6 = 2;
    int out1, out2, out3, th = 2, z1, z2, y;

    cout << "\n[XOR Gate]\n";
    cout << "Masukkan X1: ";
    cin >> x1;
    cout << "Masukkan X2: ";
    cin >> x2;

    z1 = x1 * w1 + x2 * w2;
    out1 = (z1 >= th) ? 1 : 0;
    cout << "Out1 = " << out1 << endl;

    z2 = x1 * w3 + x2 * w4;
    out2 = (z2 >= th) ? 1 : 0;
    cout << "Out2 = " << out2 << endl;

    y = out1 * w5 + out2 * w6;
    out3 = (y >= th) ? 1 : 0;
    cout << "Hasil XOR Gate: " << out3 << endl;
}

int main() {
    int choice;
    do {
        cout << "\nPilih operasi logika:\n";
        cout << "1. AND Gate\n";
        cout << "2. OR Gate\n";
        cout << "3. XOR Gate\n";
        cout << "4. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1:
                and_gate();
                break;
            case 2:
                or_gate();
                break;
            case 3:
                xor_gate();
                break;
            case 4:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi." << endl;
        }
    } while (choice != 4);

    return 0;
}
