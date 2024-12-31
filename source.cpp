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
    if (listSiswa.first == nullptr) { // List kosong
        listSiswa.first = x;
        listSiswa.last = x;
    } else { // Tambahkan di akhir list
        listSiswa.last->next = x;
        listSiswa.last = x;
    }
}

void insert_tugas(adr_siswa &xs, adr_guru xg, adr_tugas x) {
    if (xs->listtugas == nullptr) { // Belum ada tugas
        xs->listtugas = x;
    } else { // Tambahkan di akhir list tugas
        adr_tugas temp = xs->listtugas;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = x;
    }
    x->from = xg; // Hubungkan tugas dengan guru
}

void insert_guru(list_guru &listGuru, adr_guru x) {
    if (listGuru.first == nullptr) { // List kosong
        listGuru.first = x;
        listGuru.last = x;
    } else { // Tambahkan di akhir list
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
    return current; // Mengembalikan alamat node jika ditemukan, atau nullptr jika tidak ditemukan
}

adr_guru search_guru(list_guru listGuru, string id, adr_guru &prec) {
    prec = nullptr;
    adr_guru current = listGuru.first;
    while (current != nullptr && current->info.id != id) {
        prec = current;
        current = current->next;
    }
    return current; // Mengembalikan alamat node jika ditemukan, atau nullptr jika tidak ditemukan
}

adr_tugas search_tugas(list_siswa listSiswa, string id, adr_tugas &prec, adr_siswa &siswa) {
    prec = nullptr;
    adr_tugas current = nullptr;
    siswa = listSiswa.first;

    while (siswa != nullptr) {
        current = siswa->listtugas;
        prec = nullptr; // Reset prec for each siswa's tugas list
        while (current != nullptr && current->info.id != id) {
            prec = current;
            current = current->next;
        }
        if (current != nullptr) break; // Tugas ditemukan
        siswa = siswa->next;
    }

    if (current == nullptr) { // Tugas tidak ditemukan
        siswa = nullptr;
    }

    return current; // Mengembalikan alamat node jika ditemukan, atau nullptr jika tidak ditemukan
}

void delete_siswa(list_siswa &listSiswa, adr_siswa &p, adr_siswa &q) {
    if (listSiswa.first == p && listSiswa.last == p){
        // Node p adalah satu satunya node
        listSiswa.first = nullptr;
        listSiswa.last = nullptr;
    }else if (listSiswa.first == p) {
        // Node p adalah node pertama
        listSiswa.first = p->next;
        delete p;
    } else if (listSiswa.last == p){
        // Node p adalah node terakhir
        listSiswa.last = q;
        q->next = nullptr;
        delete p;
    } else {
        // Kondisi normal
        q->next = p->next;
        delete p;
        p = nullptr;
    }
}

void delete_tugas(adr_siswa &siswa, adr_tugas &p, adr_tugas &q) {
    if (siswa->listtugas == nullptr) {
        // Node p adalah node pertama
        siswa->listtugas = p->next;
        delete p;
    } else {
        // Node p bukan node pertama
        q->next = p->next;
        delete p;
    }
}

void delete_guru(list_guru &listGuru, adr_guru &p) {
    if (listGuru.first == p && listGuru.last == p){
        // Node p adalah satu satunya node
        listGuru.first = nullptr;
        listGuru.last = nullptr;
        delete p;
    } else if (listGuru.first == p){
        // Node p adalah node pertama
        listGuru.first = p->next;
        delete p;
    } else if (listGuru.last == p){
        // Node p adalah node terakhir
        listGuru.last = p->prev;
        listGuru.last->next = nullptr;
        delete p;
    } else {
        // Kondisi normal
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
    // Pastikan tugas (xt) dan guru (xg) valid
    if (xt != nullptr && xg != nullptr) {
        // Menugaskan guru baru (xg) ke tugas (xt)
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

void process_show_tugas_siswa_from(list_siswa listSiswa) {
    string siswaId;
    cout << "Masukkan ID Siswa yang ingin dilihat tugasnya: ";
    cin >> siswaId;

    adr_siswa targetSiswa, prevSiswa;
    targetSiswa = search_siswa(listSiswa, siswaId, prevSiswa);

    if (targetSiswa != nullptr) {
        show_tugas_siswa_from(targetSiswa);
    } else {
        cout << "Siswa dengan ID " << siswaId << " tidak ditemukan!\n";
    }
}

void process_show_siswa_from_guru(list_siswa listSiswa, list_guru listGuru) {
    string guruId;
    cout << "Masukkan ID Guru yang ingin dilihat siswanya: ";
    cin >> guruId;

    adr_guru targetGuru, prevGuru;
    targetGuru = search_guru(listGuru, guruId, prevGuru);

    if (targetGuru != nullptr) {
        show_siswa_from_guru(listSiswa, targetGuru);
    } else {
        cout << "Guru dengan ID " << guruId << " tidak ditemukan!\n";
    }
}

void process_show_tugas_siswa_from_guru(list_siswa listSiswa, list_guru listGuru) {
    string guruId;
    cout << "Masukkan ID Guru yang ingin dilihat tugas-tugasnya: ";
    cin >> guruId;

    adr_guru targetGuru, prevGuru;
    targetGuru = search_guru(listGuru, guruId, prevGuru);

    if (targetGuru != nullptr) {
        show_tugas_siswa_from_guru(listSiswa, targetGuru);
    } else {
        cout << "Guru dengan ID " << guruId << " tidak ditemukan!\n";
    }
}

void process_count_tugas_from_siswa(list_siswa listSiswa) {
    string siswaId;
    cout << "Masukkan ID Siswa untuk menghitung jumlah tugas: ";
    cin >> siswaId;

    adr_siswa targetSiswa, prevSiswa;
    targetSiswa = search_siswa(listSiswa, siswaId, prevSiswa);

    if (targetSiswa != nullptr) {
        int tugasCount = count_tugas_from_siswa(targetSiswa);
        cout << "Jumlah tugas yang dimiliki oleh siswa dengan ID " << siswaId << " adalah: " << tugasCount << endl;
    } else {
        cout << "Siswa dengan ID " << siswaId << " tidak ditemukan!\n";
    }
}

void process_swap_guru_from_tugas(list_siswa &listSiswa, list_guru &listGuru) {
    string tugasId, guruId;
    cout << "Masukkan ID Tugas yang ingin diubah gurunya: ";
    cin >> tugasId;

    adr_tugas targetTugas, prevTugas;
    adr_siswa targetSiswa;
    targetTugas = search_tugas(listSiswa, tugasId, prevTugas, targetSiswa);

    if (targetTugas != nullptr) {
        cout << "\nDetail Tugas yang dipilih:\n";
        print_tugas_details(targetTugas);

        cout << "\nDaftar Guru yang tersedia:\n";
        show_all_guru(listGuru);

        cout << "\nMasukkan ID Guru yang baru: ";
        cin >> guruId;

        adr_guru targetGuru, prevGuru;
        targetGuru = search_guru(listGuru, guruId, prevGuru);

        if (targetGuru != nullptr) {
            swap_guru_from_tugas(targetTugas, targetGuru);
            cout << "Guru untuk tugas berhasil diubah!\n";
        } else {
            cout << "Guru dengan ID " << guruId << " tidak ditemukan!\n";
        }
    } else {
        cout << "Tugas dengan ID " << tugasId << " tidak ditemukan!\n";
    }
}

//dummy data
void generate_dummy_data(list_siswa &listSiswa, list_guru &listGuru) {
    // Dummy Siswa 1
    adr_siswa siswa1 = new elm_siswa;
    siswa1->info.name = "Siswa A";
    siswa1->info.id = "S001";
    siswa1->info.asal = "Sekolah A";
    siswa1->info.kelas = "X-A";
    siswa1->info.usia = 16;
    siswa1->next = nullptr;
    siswa1->listtugas = nullptr;

    // Dummy Siswa 2
    adr_siswa siswa2 = new elm_siswa;
    siswa2->info.name = "Siswa B";
    siswa2->info.id = "S002";
    siswa2->info.asal = "Sekolah B";
    siswa2->info.kelas = "X-B";
    siswa2->info.usia = 17;
    siswa2->next = nullptr;
    siswa2->listtugas = nullptr;

    // Dummy Siswa 3
    adr_siswa siswa3 = new elm_siswa;
    siswa3->info.name = "Siswa C";
    siswa3->info.id = "S003";
    siswa3->info.asal = "Sekolah C";
    siswa3->info.kelas = "X-C";
    siswa3->info.usia = 18;
    siswa3->next = nullptr;
    siswa3->listtugas = nullptr;

    // Link the students into the list
    listSiswa.first = siswa1;
    siswa1->next = siswa2;
    siswa2->next = siswa3;
    listSiswa.last = siswa3;

    // Dummy Guru 1
    adr_guru guru1 = new elm_guru;
    guru1->info.nama = "Guru A";
    guru1->info.id = "G001";
    guru1->info.asal = "Sekolah A";
    guru1->info.gelar = "S.Pd";
    guru1->info.guruSubjek = "Matematika";
    guru1->info.usia = 40;
    guru1->next = nullptr;
    guru1->prev = nullptr;

    // Dummy Guru 2
    adr_guru guru2 = new elm_guru;
    guru2->info.nama = "Guru B";
    guru2->info.id = "G002";
    guru2->info.asal = "Sekolah B";
    guru2->info.gelar = "S.Si";
    guru2->info.guruSubjek = "IPA";
    guru2->info.usia = 35;
    guru2->next = nullptr;
    guru2->prev = nullptr;

    // Dummy Tugas 1 for Siswa A
    adr_tugas tugas1 = new elm_tugas;
    tugas1->info.id = "T001";
    tugas1->info.subjek = "Matematika";
    tugas1->info.bab = 1;
    tugas1->info.tenggat = "2024-12-20";
    tugas1->next = nullptr;
    tugas1->from = guru1;

    siswa1->listtugas = tugas1;

    // Dummy Tugas 2 for Siswa A
    adr_tugas tugas2 = new elm_tugas;
    tugas2->info.id = "T002";
    tugas2->info.subjek = "IPA";
    tugas2->info.bab = 2;
    tugas2->info.tenggat = "2024-12-22";
    tugas2->next = nullptr;
    tugas2->from = guru1;

    tugas1->next = tugas2;

    // Dummy Tugas for Siswa B
    adr_tugas tugas3 = new elm_tugas;
    tugas3->info.id = "T003";
    tugas3->info.subjek = "Bahasa Indonesia";
    tugas3->info.bab = 3;
    tugas3->info.tenggat = "2024-12-18";
    tugas3->next = nullptr;
    tugas3->from = guru2;

    siswa2->listtugas = tugas3;

    // Link the guru ke list
    listGuru.first = guru1;
    guru1->next = guru2;
    listGuru.last = guru2;
}
