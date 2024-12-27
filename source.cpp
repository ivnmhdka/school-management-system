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

int count_all_tugas(list_siswa listSiswa) {
    int total = 0;
    adr_siswa currentSiswa = listSiswa.first;

    while (currentSiswa != nullptr) {
        adr_tugas currentTugas = currentSiswa->listtugas;
        while (currentTugas != nullptr) {
            total++;
            currentTugas = currentTugas->next;
        }
        currentSiswa = currentSiswa->next;
    }

    return total;
}

int count_tugas_from_siswa(adr_siswa x) {
    int total = 0;
    adr_tugas currentTugas = x->listtugas;

    while (currentTugas != nullptr) {
        total++;
        currentTugas = currentTugas->next;
    }

    return total;
}

int count_siswa_with_no_tugas(list_siswa listSiswa) {
    int count = 0;
    adr_siswa currentSiswa = listSiswa.first;

    while (currentSiswa != nullptr) {
        if (currentSiswa->listtugas == nullptr) {
            count++;
        }
        currentSiswa = currentSiswa->next;
    }

    return count;
}

void swap_guru_from_tugas(adr_tugas &xt, adr_guru xg) {
    if (xt != nullptr && xg != nullptr) {
        xt->from = xg;
    }
}

void print_siswa_details(adr_siswa siswa) {
    if (siswa != nullptr) {
        cout << "----------------------------\n";
        cout << "Detail Siswa:\n";
        cout << "Nama     : " << siswa->info.name << "\n";
        cout << "ID       : " << siswa->info.id << "\n";
        cout << "Asal     : " << siswa->info.asal << "\n";
        cout << "Kelas    : " << siswa->info.kelas << "\n";
        cout << "Usia     : " << siswa->info.usia << "\n";
        cout << "----------------------------\n";
    } else {
        cout << "Siswa tidak ditemukan!\n";
    }
}

void print_tugas_details(adr_tugas tugas) {
    if (tugas != nullptr) {
        cout << "----------------------------\n";
        cout << "Detail Tugas:\n";
        cout << "ID       : " << tugas->info.id << "\n";
        cout << "Subjek   : " << tugas->info.subjek << "\n";
        cout << "Bab      : " << tugas->info.bab << "\n";
        cout << "Tenggat  : " << tugas->info.tenggat << "\n";
        cout << "----------------------------\n";
    } else {
        cout << "Tugas tidak ditemukan!\n";
    }
}

void print_guru_details(adr_guru guru) {
    if (guru != nullptr) {
        cout << "----------------------------\n";
        cout << "Detail Guru:\n";
        cout << "Nama     : " << guru->info.nama << "\n";
        cout << "ID       : " << guru->info.id << "\n";
        cout << "Asal     : " << guru->info.asal << "\n";
        cout << "Gelar    : " << guru->info.gelar << "\n";
        cout << "Subjek   : " << guru->info.guruSubjek << "\n";
        cout << "Usia     : " << guru->info.usia << "\n";
        cout << "----------------------------\n";
    } else {
        cout << "Guru tidak ditemukan!\n";
    }
}

void process_insert_siswa(list_siswa &listSiswa) {
    infotype_siswa newSiswa;
    cout << "Masukkan Nama Siswa: ";
    cin >> newSiswa.name;
    cout << "Masukkan ID Siswa: ";
    cin >> newSiswa.id;
    cout << "Masukkan Asal Siswa: ";
    cin >> newSiswa.asal;
    cout << "Masukkan Kelas Siswa: ";
    cin >> newSiswa.kelas;
    cout << "Masukkan Usia Siswa: ";
    cin >> newSiswa.usia;

    adr_siswa newElm = create_elm_siswa(newSiswa);
    insert_siswa(listSiswa, newElm);
    cout << "Siswa berhasil ditambahkan!\n";
}

void process_insert_tugas(list_siswa &listSiswa, list_guru listGuru) {
    string siswaId, guruId;
    infotype_tugas newTugas;

    cout << "Masukkan ID Siswa yang akan diberi tugas: ";
    cin >> siswaId;
    cout << "Masukkan ID Guru yang memberikan tugas: ";
    cin >> guruId;

    adr_siswa targetSiswa;
    adr_guru targetGuru;

    targetSiswa = search_siswa(listSiswa, siswaId, targetSiswa);
    targetGuru = search_guru(listGuru, guruId, targetGuru);

    if (targetSiswa != nullptr && targetGuru != nullptr) {
        cout << "Masukkan ID Tugas: ";
        cin >> newTugas.id;
        cout << "Masukkan Subjek Tugas: ";
        cin >> newTugas.subjek;
        cout << "Masukkan Bab Tugas: ";
        cin >> newTugas.bab;
        cout << "Masukkan Tenggat Tugas: ";
        cin >> newTugas.tenggat;

        adr_tugas newElm = create_elm_tugas(newTugas);
        insert_tugas(targetSiswa, targetGuru, newElm);
        cout << "Tugas berhasil ditambahkan!\n";
    } else {
        cout << "Siswa atau Guru tidak ditemukan!\n";
    }
}

void process_insert_guru(list_guru &listGuru) {
    infotype_guru newGuru;
    cout << "Masukkan Nama Guru: ";
    cin >> newGuru.nama;
    cout << "Masukkan ID Guru: ";
    cin >> newGuru.id;
    cout << "Masukkan Asal Guru: ";
    cin >> newGuru.asal;
    cout << "Masukkan Gelar Guru: ";
    cin >> newGuru.gelar;
    cout << "Masukkan Subjek yang Diajarkan: ";
    cin >> newGuru.guruSubjek;
    cout << "Masukkan Usia Guru: ";
    cin >> newGuru.usia;

    adr_guru newElm = create_elm_guru(newGuru);
    insert_guru(listGuru, newElm);
    cout << "Guru berhasil ditambahkan!\n";
}

void process_delete_siswa(list_siswa &listSiswa) {
    string siswaId;
    cout << "Masukkan ID Siswa yang akan dihapus: ";
    cin >> siswaId;

    adr_siswa targetSiswa, prevSiswa = nullptr;
    targetSiswa = search_siswa(listSiswa, siswaId, prevSiswa);

    if (targetSiswa != nullptr) {
        delete_siswa(listSiswa, targetSiswa, prevSiswa);
        cout << "Siswa berhasil dihapus!\n";
    } else {
        cout << "Siswa tidak ditemukan!\n";
    }
}


void process_delete_tugas(list_siswa &listSiswa) {
    string tugasId;
    cout << "Masukkan ID Tugas yang akan dihapus: ";
    cin >> tugasId;

    adr_siswa targetSiswa = nullptr;
    adr_tugas targetTugas = nullptr, prevTugas = nullptr;

    targetTugas = search_tugas(listSiswa, tugasId, prevTugas, targetSiswa);

    if (targetTugas != nullptr) {
        delete_tugas(targetSiswa, targetTugas, prevTugas);
        cout << "Tugas berhasil dihapus!\n";
    } else {
        cout << "Tugas tidak ditemukan!\n";
    }
}


void process_delete_guru(list_guru &listGuru) {
    string guruId;
    cout << "Masukkan ID Guru yang akan dihapus: ";
    cin >> guruId;

    adr_guru targetGuru, prevGuru;
    targetGuru = search_guru(listGuru, guruId, prevGuru);

    if (targetGuru != nullptr) {
        delete_guru(listGuru, targetGuru);
        cout << "Guru berhasil dihapus!\n";
    } else {
        cout << "Guru tidak ditemukan!\n";
    }
}

void process_search_siswa(list_siswa listSiswa) {
    string siswaId;
    cout << "Masukkan ID Siswa yang ingin dicari: ";
    cin >> siswaId;

    adr_siswa prec = nullptr;
    adr_siswa targetSiswa = search_siswa(listSiswa, siswaId, prec);

    if (targetSiswa != nullptr) {
        cout << "Siswa ditemukan:\n";
        print_siswa_details(targetSiswa);
    } else {
        cout << "Siswa dengan ID " << siswaId << " tidak ditemukan!\n";
    }
}

void process_search_tugas(list_siswa listSiswa) {
    string tugasId;
    cout << "Masukkan ID Tugas yang ingin dicari: ";
    cin >> tugasId;

    adr_tugas prec = nullptr;
    adr_siswa targetSiswa = nullptr;
    adr_tugas targetTugas = search_tugas(listSiswa, tugasId, prec, targetSiswa);

    if (targetTugas != nullptr) {
        cout << "Tugas ditemukan:\n";
        print_tugas_details(targetTugas);
        cout << "Tugas ini dimiliki oleh siswa:\n";
        print_siswa_details(targetSiswa);
    } else {
        cout << "Tugas dengan ID " << tugasId << " tidak ditemukan!\n";
    }
}

void process_search_guru(list_guru listGuru) {
    string guruId;
    cout << "Masukkan ID Guru yang ingin dicari: ";
    cin >> guruId;

    adr_guru prec = nullptr;
    adr_guru targetGuru = search_guru(listGuru, guruId, prec);

    if (targetGuru != nullptr) {
        cout << "Guru ditemukan:\n";
        print_guru_details(targetGuru);
    } else {
        cout << "Guru dengan ID " << guruId << " tidak ditemukan!\n";
    }
}