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

void insert_siswa(list_siswa &listSiswa, adr_siswa x) {
    if (listSiswa.first == nullptr) {
        listSiswa.first = x;
        listSiswa.last = x;
    } else {
        listSiswa.last->next = x;
        listSiswa.last = x;
    }
}

void insert_tugas(adr_siswa &xs, adr_guru xg, adr_tugas x) {
    if (xs->listtugas == nullptr) { 
        xs->listtugas = x;
    } else { 
        adr_tugas temp = xs->listtugas;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = x;
    }
    x->from = xg;
}

void insert_guru(list_guru &listGuru, adr_guru x) {
    if (listGuru.first == nullptr) {
        listGuru.first = x;
        listGuru.last = x;
    } else { 
        listGuru.last->next = x;
        x->prev = listGuru.last;
        listGuru.last = x;
    }
}

adr_siswa search_siswa(list_siswa listSiswa, string id, adr_siswa &prec) {
    prec = nullptr;
    adr_siswa current = listSiswa.first;
    while (current != nullptr && current->info.id != id) {
        prec = current;
        current = current->next;
    }
    return current;
}

adr_guru search_guru(list_guru listGuru, string id, adr_guru &prec) {
    prec = nullptr;
    adr_guru current = listGuru.first;
    while (current != nullptr && current->info.id != id) {
        prec = current;
        current = current->next;
    }
    return current; 
}


adr_tugas search_tugas(list_siswa listSiswa, string id, adr_tugas &prec, adr_siswa &siswa) {
    prec = nullptr;
    adr_tugas current = nullptr;
    siswa = listSiswa.first;

    while (siswa != nullptr) {
        current = siswa->listtugas;
        prec = nullptr;
        while (current != nullptr && current->info.id != id) {
            prec = current;
            current = current->next;
        }
        if (current != nullptr) break;
        siswa = siswa->next;
    }

    if (current == nullptr) { 
        siswa = nullptr;
    }

    return current;
}