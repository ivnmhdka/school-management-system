#include "header.h"

int main() {
    list_siswa listSiswa = {nullptr, nullptr};
    list_guru listGuru = {nullptr, nullptr};

    generate_dummy_data(listSiswa, listGuru);

    int choice;
    while (true) {
        int tugasCount = count_all_tugas(listSiswa);
        int siswaNoTugas = count_siswa_with_no_tugas(listSiswa);
        cout << "=====================================\n";
        cout << "   SCHOOL MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";
        cout << "Tugas Count: " << tugasCount << " | Siswa with no Tugas: " << siswaNoTugas << "\n";
        cout << "=====================================\n";
        cout << "Menu:\n";
        cout << "1. Insert Siswa\n";
        cout << "2. Insert Tugas\n";
        cout << "3. Insert Guru\n";
        cout << "4. Delete Siswa\n";
        cout << "5. Delete Tugas\n";
        cout << "6. Delete Guru\n";
        cout << "7. Search Siswa\n";
        cout << "8. Search Tugas\n";
        cout << "9. Search Guru\n";
        cout << "10. Show All Siswa\n";
        cout << "11. Show All Guru\n";
        cout << "12. Show Tugas for Siswa\n";
        cout << "13. Show Siswa from Guru\n";
        cout << "14. Show Tugas from Guru\n";
        cout << "15. Count Tugas from Siswa\n";
        cout << "16. Swap Guru from Tugas\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: process_insert_siswa(listSiswa); break;
            case 2: process_insert_tugas(listSiswa, listGuru); break;
            case 3: process_insert_guru(listGuru); break;
            case 4: process_delete_siswa(listSiswa); break;
            case 5: process_delete_tugas(listSiswa); break;
            case 6: process_delete_guru(listGuru); break;
            case 7: process_search_siswa(listSiswa); break;
            case 8: process_search_tugas(listSiswa); break;
            case 9: process_search_guru(listGuru); break;
            case 10: show_all_siswa(listSiswa); break;
            case 11: show_all_guru(listGuru); break;
            case 12: process_show_tugas_siswa_from(listSiswa); break;
            case 13: process_show_siswa_from_guru(listSiswa, listGuru); break;
            case 14: process_show_tugas_siswa_from_guru(listSiswa, listGuru); break;
            case 15: process_count_tugas_from_siswa(listSiswa); break;
            case 16: process_swap_guru_from_tugas(listSiswa, listGuru); break;
            case 0: cout << "Exiting program...\n"; return 0;
            default: cout << "Invalid choice, try again.\n"; break;
        }
    }
    return 0;
}
