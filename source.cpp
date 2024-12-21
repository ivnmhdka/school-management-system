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

void delete_siswa(list_siswa &listSiswa, adr_siswa &p, adr_siswa &q) {
    if (listSiswa.first == p && listSiswa.last == p){
        listSiswa.first = nullptr;
        listSiswa.last = nullptr;
    }else if (listSiswa.first == p) {
        listSiswa.first = p->next;
        delete p;
    } else if (listSiswa.last == p){
        listSiswa.last = q;
        q->next = nullptr;
        delete p;
    } else {
        q->next = p->next;
        delete p;
        p = nullptr;
    }
}

void delete_tugas(adr_siswa &siswa, adr_tugas &p, adr_tugas &q) {
    if (siswa->listtugas == nullptr) {
        siswa->listtugas = p->next;
        delete p;
    } else {
        q->next = p->next;
        delete p;
    }
}

void delete_guru(list_guru &listGuru, adr_guru &p) {
    if (listGuru.first == p && listGuru.last == p){
        listGuru.first = nullptr;
        listGuru.last = nullptr;
        delete p;
    } else if (listGuru.first == p){
        listGuru.first = p->next;
        delete p;
    } else if (listGuru.last == p){
        listGuru.last = p->prev;
        listGuru.last->next = nullptr;
        delete p;
    } else {
        adr_guru q = p->prev;
        q->next = p->next;
        delete p;
    }
}

void show_all_siswa(list_siswa listSiswa) {
    cout << "====================================" << endl;
    cout << "        DATA SISWA (List Parent)    " << endl;
    cout << "====================================" << endl;

    adr_siswa current = listSiswa.first;
    int no = 1;
    while (current != nullptr) {
        print_siswa_details(current);
        current = current->next;
    }

    if (listSiswa.first == nullptr) {
        cout << "   Tidak ada data siswa." << endl;
        cout << "------------------------------------" << endl;
    }
}

void show_all_guru(list_guru listGuru) {
    cout << "====================================" << endl;
    cout << "        DATA GURU (List Child)      " << endl;
    cout << "====================================" << endl;

    adr_guru current = listGuru.first;
    int no = 1;
    while (current != nullptr) {
        print_guru_details(current);
        current = current->next;
    }

    if (listGuru.first == nullptr) {
        cout << "   Tidak ada data guru." << endl;
        cout << "------------------------------------" << endl;
    }
}

void show_tugas_siswa_from(adr_siswa x) {
    if (x == nullptr) {
        cout << "Siswa tidak ditemukan." << endl;
        return;
    }
    cout << "====================================" << endl;
    cout << "    TUGAS DARI SISWA: " << x->info.name << endl;
    cout << "====================================" << endl;

    adr_tugas current = x->listtugas;
    int no = 1;
    while (current != nullptr) {
        cout << no++ << ". Subjek : " << current->info.subjek << endl;
        cout << "   Tugas id: " << current->info.id << endl;
        cout << "   Bab     : " << current->info.bab << endl;
        cout << "   Tenggat : " << current->info.tenggat << endl;

        if (current->from != nullptr) {
            cout << "   Guru    : " << current->from->info.nama << endl;
        }
        cout << "------------------------------------" << endl;
        current = current->next;
    }

    if (x->listtugas == nullptr) {
        cout << "   Tidak ada tugas." << endl;
        cout << "------------------------------------" << endl;
    }
}

void show_all_tugas_siswa_from(list_siswa listSiswa) {
    cout << "====================================" << endl;
    cout << "   DATA SISWA DAN TUGAS (Parent-Child) " << endl;
    cout << "====================================" << endl;

    adr_siswa current = listSiswa.first;
    while (current != nullptr) {
        show_tugas_siswa_from(current);
        current = current->next;
    }

    if (listSiswa.first == nullptr) {
        cout << "   Tidak ada data siswa." << endl;
        cout << "------------------------------------" << endl;
    }
}

void show_siswa_from_guru(list_siswa listSiswa, adr_guru x) {
    if (x == nullptr) {
        cout << "Guru tidak ditemukan." << endl;
        return;
    }
    cout << "====================================" << endl;
    cout << " SISWA DARI GURU: " << x->info.nama << endl;
    cout << "====================================" << endl;

    adr_siswa currentSiswa = listSiswa.first;
    int no = 1;
    while (currentSiswa != nullptr) {
        adr_tugas currentTugas = currentSiswa->listtugas;
        while (currentTugas != nullptr) {
            if (currentTugas->from == x) {
                cout << no++ << ". Nama Siswa : " << currentSiswa->info.name << endl;
                cout << "------------------------------------" << endl;
                break;
            }
            currentTugas = currentTugas->next;
        }
        currentSiswa = currentSiswa->next;
    }

    if (no == 1) {
        cout << "   Tidak ada siswa yang memiliki tugas dari guru ini." << endl;
        cout << "------------------------------------" << endl;
    }
}

void show_tugas_siswa_from_guru(list_siswa listSiswa, adr_guru x) {
    if (x == nullptr) {
        cout << "Guru tidak ditemukan." << endl;
        return;
    }

    cout << "====================================" << endl;
    cout << "   SISWA BERELASI DENGAN GURU: " << x->info.nama << endl;
    cout << "====================================" << endl;

    adr_siswa currentSiswa = listSiswa.first;
    while (currentSiswa != nullptr) {
        adr_tugas currentTugas = currentSiswa->listtugas;
        while (currentTugas != nullptr) {
            if (currentTugas->from == x) {
                cout << "- Nama Siswa : " << currentSiswa->info.name << endl;
                break;
            }
            currentTugas = currentTugas->next;
        }
        currentSiswa = currentSiswa->next;
    }
}