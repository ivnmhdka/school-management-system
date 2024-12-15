#ifndef HEADER_SEKOLAH_INCLUDED
#define HEADER_SEKOLAH_INCLUDED
#include <iostream>

using namespace std;

struct infotype_siswa
{
    string name;
    string id;
    string asal;
    string kelas;
    int usia;
};

struct infotype_tugas
{
    string id;
    string subjek;
    int bab;
    string tenggat;
};

struct infotype_guru
{
    string nama;
    string id;
    string asal;
    string gelar;
    string guruSubjek;
    int usia;
};

typedef struct elm_siswa *adr_siswa;
typedef struct elm_tugas *adr_tugas;
typedef struct elm_guru *adr_guru;

struct elm_siswa
{
    infotype_siswa info;
    adr_siswa next;
    adr_tugas listtugas;
};

struct elm_tugas
{
    infotype_tugas info;
    adr_tugas next;
    adr_guru from;
};

struct elm_guru
{
    infotype_guru info;
    adr_guru next;
    adr_guru prev;
};

struct list_siswa
{
    adr_siswa first;
    adr_siswa last;
};

struct list_guru
{
    adr_guru first;
    adr_guru last;
};

void create_list_siswa(list_siswa &listSiswa);
void create_list_guru(list_guru &listGuru);

adr_siswa create_elm_siswa(infotype_siswa x);
adr_guru create_elm_guru(infotype_guru x);
adr_tugas create_elm_tugas(infotype_tugas x);

void insert_siswa(list_siswa &listSiswa, adr_siswa x);
void insert_tugas(adr_siswa &xs, adr_guru xg, adr_tugas x); //abc
void insert_guru(list_guru &listGuru, adr_guru x);

void delete_siswa(list_siswa &listSiswa, adr_siswa &p, adr_siswa &q);
void delete_tugas(adr_siswa &siswa, adr_tugas &p, adr_tugas &q); //def
void delete_guru(list_guru &listGuru, adr_guru &p);

adr_siswa search_siswa(list_siswa listSiswa, string id, adr_siswa &prec);
adr_guru search_guru(list_guru listGuru, string id, adr_guru &prec); //ghi
adr_tugas search_tugas(list_siswa listSiswa, string id, adr_tugas &prec, adr_siswa &siswa);

void show_all_siswa(list_siswa listSiswa);//j
void show_all_guru(list_guru listGuru);//k
void show_tugas_siswa_from(adr_siswa x);//l
void show_all_tugas_siswa_from(list_siswa listSiswa);//m
void show_siswa_from_guru(list_siswa listSiswa, adr_guru x);//n
void show_tugas_siswa_from_guru(list_siswa listSiswa, adr_guru x);//o

void print_siswa_details(adr_siswa siswa);
void print_tugas_details(adr_tugas tugas);
void print_guru_details(adr_guru guru);

int count_all_tugas(list_siswa listSiswa);//p
int count_tugas_from_siswa(adr_siswa x);//q
int count_siswa_with_no_tugas(list_siswa listSiswa);//r

void swap_guru_from_tugas(adr_tugas &xt, adr_guru xg);//s

#endif