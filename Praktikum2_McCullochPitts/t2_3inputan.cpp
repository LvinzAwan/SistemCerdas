#include <iostream>
using namespace std;

void and_gate() {
    int x1, x2, x3;
    int w1 = 2, w2 = 2, w3 = 2, th = 6, y, out;

    cout << "\n[AND Gate]\n";
    cout << "Masukkan X1: "; cin >> x1;
    cout << "Masukkan X2: "; cin >> x2;
    cout << "Masukkan X3: "; cin >> x3;

    y = x1 * w1 + x2 * w2 + x3 * w3;
    out = (y >= th) ? 1 : 0;

    cout << "Hasil AND Gate: " << out << endl;
}

void or_gate() {
    int x1, x2, x3;
    int w1 = 4, w2 = 4, w3 = 4, th = 4, y, out;

    cout << "\n[OR Gate]\n";
    cout << "Masukkan X1: "; cin >> x1;
    cout << "Masukkan X2: "; cin >> x2;
    cout << "Masukkan X3: "; cin >> x3;

    y = x1 * w1 + x2 * w2 + x3 * w3;
    out = (y >= th) ? 1 : 0;

    cout << "Hasil OR Gate: " << out << endl;
}

void xor_gate() {
    int x1, x2, x3;
    int w1 = 2, w2 = -1, w3 = -1, w4 = 2, w5 = -1, w6 = 2;
    int w7 = 2, w8 = 2, w9 = 2;
    int out1, out2, out3, final_out;
    int th = 2;
    int z1, z2, z3, y;

    cout << "\n[XOR Gate - 3 Input]\n";
    cout << "Masukkan X1: "; cin >> x1;
    cout << "Masukkan X2: "; cin >> x2;
    cout << "Masukkan X3: "; cin >> x3;

    // Layer 1
    z1 = x1 * w1 + x2 * w2;
    out1 = (z1 >= th) ? 1 : 0;
    cout << "Out1 = " << out1 << endl;

    z2 = x1 * w3 + x2 * w4;
    out2 = (z2 >= th) ? 1 : 0;
    cout << "Out2 = " << out2 << endl;

    z3 = x2 * w5 + x3 * w6;
    out3 = (z3 >= th) ? 1 : 0;
    cout << "Out3 = " << out3 << endl;

    // Layer 2
    y = out1 * w7 + out2 * w8 + out3 * w9;
    final_out = (y >= th) ? 1 : 0;

    cout << "Hasil XOR Gate : " << final_out << endl;
}

int main() {
    int choice;
    do {
        cout << "\nPilih operasi logika 3 inputan:\n";
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
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (choice != 4);

    return 0;
}
