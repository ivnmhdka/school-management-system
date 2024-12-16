#include "header.h"

void create_list_siswa(list_siswa &listSiswa) {
    listSiswa.first = nullptr;
    listSiswa.last = nullptr;
}

void create_list_guru(list_guru &listGuru) {
    listGuru.first = nullptr;
    listGuru.last = nullptr;
}

adr_siswa create_elm_siswa(infotype_siswa x) {
    adr_siswa newSiswa = new elm_siswa;
    newSiswa->info = x;
    newSiswa->next = nullptr;
    newSiswa->listtugas = nullptr;
    return newSiswa;
}

adr_guru create_elm_guru(infotype_guru x) {
    adr_guru newGuru = new elm_guru;
    newGuru->info = x;
    newGuru->next = nullptr;
    newGuru->prev = nullptr;
    return newGuru;
}

adr_tugas create_elm_tugas(infotype_tugas x) {
    adr_tugas newTugas = new elm_tugas;
    newTugas->info = x;
    newTugas->next = nullptr;
    newTugas->from = nullptr;
    return newTugas;
}