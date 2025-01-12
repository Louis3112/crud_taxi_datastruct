#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#define MAX_QUEUE_SIZE 10
using namespace std;

struct Supir{
    string Id;
    string Nama;
    string TglLahir;
    char Kelamin;
    string Alamat;
    Supir* Next;
    Supir* Prev;
};

Supir *Head, *Tail, *Current = nullptr;

void SetCurrent(Supir* TargetedSupir) {
    Current = TargetedSupir;
}

void InitSupir(){
    Head = nullptr;
    Tail = nullptr;
    Current = nullptr;
}

int isEmpty(){
    return (Tail == nullptr) ? 1 : 0;
}

int CharToInt(char c) {
    return static_cast<int>(c - '0');
}
string GenerateIdSupir(string Nama, string TglLahir, char Kelamin) {
    string FullId{};    

    char FirstLetter = Nama[0];
    char LastLetter = Nama[Nama.length()-1];
    int SecondDigit =  abs(static_cast<int>(FirstLetter) - static_cast<int>(LastLetter)) % 10;
    stringstream ss;
    ss << setw(2) << setfill('0') << SecondDigit;

    int GenderDigit = (Kelamin == 'L') ? 1 : 0;
    ss << GenderDigit;
 
    int Day = CharToInt(TglLahir[1]) % 10; 
    int Month = CharToInt(TglLahir[4]) % 10;
    int Year = CharToInt(TglLahir[9]) % 10;
    int FourthDigit = (Day + Month + Year) % 9;
    ss << setw(2) << setfill('0') << FourthDigit;

    int FifthDigit = 0;
    ss << FifthDigit;

    string SecondId = to_string(SecondDigit);
    string ThirdId = to_string(GenderDigit);
    string FourthId = to_string(FourthDigit);
    string FifthId = to_string(FifthDigit);

    if (SecondDigit < 10) {
        FullId = "0" + SecondId + ThirdId + FourthId + FifthId;
    } 
    else {
        FullId = SecondId + ThirdId + FourthId + FifthId;
    }

    return FullId;
}


void DisplayDataSupirUser(){
    Current = Head;
    if (Current) {
        cout << "|-------------------------|\n";
        cout << "|Nama: " << Current->Nama << " |\n";
        cout << "|Id: " << Current->Id << " |\n";
        cout << "|Tanggal Lahir: " << Current->TglLahir << " |\n";
        cout << "|Kelamin: " << Current->Kelamin << " |\n";
        cout << "|Alamat: " << Current->Alamat << " |\n";
        cout << "|-------------------------|\n";
    } 
    else {
        cout << "Tidak ada data supir saat ini\n";
    }
}
void DisplayDataSupir() {
    if (Current) {
        cout << "|-------------------------|\n";
        cout << "|Nama: " << Current->Nama << " |\n";
        cout << "|ID: " << Current->Id << " |\n";
        cout << "|Tanggal Lahir: " << Current->TglLahir << " |\n";
        cout << "|Kelamin: " << Current->Kelamin << " |\n";
        cout << "|Alamat: " << Current->Alamat << " |\n";
        cout << "|-------------------------|\n";
    } 
    else {
        cout << "Tidak ada data supir saat ini\n";
    }
}

void FindDataSupir(string TargetId){
    if (isEmpty() == 1) {
        cout << "Tidak ada data supir saat ini\n";
        return;
    }
    Current = Head;
    bool Found = false;
    do {
        if (Current->Id == TargetId) {
            int Choice;
            cout << "\n|-------------------------|\n";
            cout << "|Nama: " << Current->Nama << " |\n";
            cout << "|Id: " << Current->Id << " |\n";
            cout << "|Tanggal Lahir: " << Current->TglLahir << " |\n";
            cout << "|Kelamin: " << Current->Kelamin << " |\n";
            cout << "|Alamat: " << Current->Alamat << " |\n";
            cout << "|-------------------------|\n";
            Found = true;
            break;
        }
        Current = Current->Next;
    }while(Current != Head);
    if (!Found) {
        cout << "Data dengan Id " << TargetId << " tidak ditemukan\n";
    }
}

void CreateDataSupir() {
    string IdBaru, NamaBaru, TglLahirBaru, AlamatBaru;
    char KelaminBaru;
    cout << "Nama: > ";
    getline(cin, NamaBaru);
    cout << "Tanggal lahir (dengan format dd-mm-yy): > ";
    getline(cin, TglLahirBaru);
    cout << "Kelamin (L/P): > ";
    cin >> KelaminBaru;
    cin.ignore();
    IdBaru = GenerateIdSupir(NamaBaru, TglLahirBaru,KelaminBaru);
    cout << "Alamat: > ";
    getline(cin, AlamatBaru);


    Supir* NewSupir = new Supir;
    NewSupir->Id = IdBaru;
    NewSupir->Nama = NamaBaru;
    NewSupir->TglLahir = TglLahirBaru;
    NewSupir->Kelamin = KelaminBaru;
    NewSupir->Alamat = AlamatBaru;
    NewSupir->Next = NewSupir;
    NewSupir->Prev = NewSupir;

    if (isEmpty() == 1) {
        Head = NewSupir;
        Tail = NewSupir;
        Head->Next = Head;
        Head->Prev = Head;
        Tail->Next = Tail;
        Tail->Prev = Tail;
    } 
    else {
        NewSupir->Next = Head;
        Head->Prev = NewSupir;
        Head = NewSupir;
        Head->Prev = Tail;
        Tail->Next = Head;
    }

    cout << "\nData berhasil ditambahkan!\n";
    cout << "|-------------------------|\n";
    cout << "|Nama: " << NewSupir->Nama << " |\n";
    cout << "|Id: " << NewSupir->Id << " |\n";
    cout << "|Tanggal Lahir: " << NewSupir->TglLahir << " |\n";
    cout << "|Kelamin: " << NewSupir->Kelamin << " |\n";
    cout << "|Alamat: " << NewSupir->Alamat << " |\n";
    cout << "|-------------------------|\n";
}

void EditDataSupir(string TargetId) {
    if (isEmpty() == 1) {
        cout << "Tidak ada data supir saat ini\n";
        return;
    }

    Current = Head;
    bool Found = false;

    do {
        if (Current->Id == TargetId) {
            int Choice;

            cout << "\n- Mengubah supir dengan Id " << TargetId << " -\n";
            cout << "1. Ubah Nama\n";
            cout << "2. Ubah Kelamin\n";
            cout << "3. Ubah Alamat\n";
            cout << "4. Ubah Tgl Lahir\n";
            cout << "> ";
            cin >> Choice;
            cin.ignore();

            switch (Choice) {
                case 1: {
                    string NamaBaru;
                    cout << "Masukkan Nama baru > ";
                    getline(cin, NamaBaru);
                    Current->Nama = NamaBaru;
                    cout << "Data Id " << Current->Id << " telah berubah! \n";
                    Current->Id = GenerateIdSupir(Current->Nama, Current->TglLahir, Current->Kelamin);
                    break;
                }
                case 2: {
                    char KelaminBaru;
                    cout << "Masukkan Data Kelamin baru (L/P) > ";
                    cin >> KelaminBaru;
                    Current->Kelamin = KelaminBaru;
                    cout << "Data Id " << Current->Id << " telah berubah! \n";
                    Current->Id = GenerateIdSupir(Current->Nama, Current->TglLahir, Current->Kelamin);
                    break;
                }
                case 3: {
                    string AlamatBaru;
                    cout << "Masukkan Alamat baru > ";
                    getline(cin, AlamatBaru);
                    Current->Alamat = AlamatBaru;
                    cout << "Data Id " << Current->Id << " telah berubah! \n";
                    break;
                }
                case 4: {
                    string TglLahirBaru;
                    cout << "Masukkan Tanggal lahir baru (dengan format dd-mm-yy) > ";
                    getline(cin, TglLahirBaru);
                    Current->TglLahir = TglLahirBaru;
                    cout << "Data Id " << Current->Id << " telah berubah! \n";
                    Current->Id = GenerateIdSupir(Current->Nama, Current->TglLahir, Current->Kelamin);
                    break;
                }
                default:
                    cout << "Opsi tidak valid";
            }

            Found = true;

            cout << "Nama: " << Current->Nama << endl;
            cout << "Id: " << Current->Id << endl;
            cout << "Kelamin: " << Current->Kelamin << endl;
            cout << "Tanggal Lahir: " << Current->TglLahir << endl;
            cout << "Alamat: " << Current->Alamat << endl;
            break;
        }

        Current = Current->Next;
    } while (Current != Head);

    if (!Found) {
        cout << "Data dengan Id " << TargetId << " tidak ditemukan\n";
    }
}

void DeleteDataSupir(string TargetId) {
    if (isEmpty() == 1) {
        cout << "Tidak ada data supir saat ini\n";
        return;
    }

    Current = Head;
    Supir* PrevNode = Tail;
    do {
        if (Current->Id == TargetId) {
            char Choice;
            cout << "Supir dengan data berikut akan dihapus\n";
            cout << "Id: " << Current->Id << endl;
            cout << "Nama: " << Current->Nama << endl;
            cout << "Kelamin: " << Current->Kelamin << endl;
            cout << "Tanggal Lahir: " << Current->TglLahir << endl;
            cout << "Alamat: " << Current->Alamat << endl;
            cout << "Lanjutkan? (y/n): ";
            cin >> Choice;

            if (Choice == 'y' || Choice == 'Y') {
                if (Current == Head) {
                    Head = Current->Next;
                    Tail->Next = Head;
                    delete Current;
                } 
                else if (Current == Tail) {
                    Tail = PrevNode;
                    Tail->Next = Head;
                    delete Current;
                } 
                else {
                    PrevNode->Next = Current->Next;
                    delete Current;
                }

                cout << "\nData berhasil dihapus\n";
            } 
            else {
                cout << "Penghapusan data dibatalkan\n";
            }
            return;
        }
        PrevNode = Current;
        Current = Current->Next;
    } while (Current != Head);
    cout << "Data dengan Id " << TargetId << " tidak ditemukan\n";
}

Supir* NextDataSupir() {
    if (Current) {
        Current = Current->Next;
    }
    return Current;
}

Supir* PrevDataSupir() {
    if (Current) {
        Current = Current->Prev;
    }
    return Current;
}

int DisplayOptionsAdmin() {
    int input;
    cout << "1. Next\n";
    cout << "2. Prev\n";
    cout << "3. Exit\n";
    cout << "Pilih opsi: ";
    cin >> input;
    return input;
}

int DisplayOptionsUser() {
    int input;
    cout << "1. Next\n";
    cout << "2. Prev\n";
    cout << "3. Order\n";
    cout << "4. Exit\n";
    cout << "Pilih opsi: ";
    cin >> input;
    return input;
}

int main(){
    InitSupir();
    int Login;
    char IsContinue;
    string SearchId;

    char Home = 'y';
    while (Home == 'y'){
        system("cls");
        cout << "=========================\n";
        cout << "      Selamat Datang     \n";
        cout << "=========================\n";
        cout << "1. Masuk sebagai Admin \n";
        cout << "2. Masuk sebagai User \n";
        cout << "3. Keluar\n";
        cin >> Login;

    switch (Login){
    case 1 :{
        char LoginAdmin = 'y';
            while (LoginAdmin == 'y' || LoginAdmin == 'Y'){
            int Input;
            cout << "==== Dashboard Admin ====\n";
            cout << "1. Mencari Data Supir\n";
            cout << "2. Menghapus Data Supir\n";
            cout << "3. Mengubah Data Supir\n";
            cout << "4. Menambah Data Supir\n";
            cout << "0. Exit\n";
            cin >> Input;
            cin.ignore();
        switch(Input){
        case 0:
            char Exit;
            cout << "Apakah anda ingin keluar dari akses Admin (y/n):";
            cin >> Exit;

            if(Exit == 'y'){
                LoginAdmin = 'n';
                Home = 'y';
            }
            else{
                LoginAdmin = 'y';
            }
            break;

        case 1:
            cout << "Mencari Data Supir\n";
            cout << "Masukkan Id Supir yang ingin dicari : ";
            getline(cin,SearchId);
            FindDataSupir(SearchId);
            int InputFind;
            do{
                InputFind = DisplayOptionsAdmin();
                switch (InputFind) {
                case 1:
                    SetCurrent(NextDataSupir());
                    DisplayDataSupir();
                    break;

                case 2:
                    SetCurrent(PrevDataSupir());
                    DisplayDataSupir();
                    break;

                case 3:
                    break;

                default:
                    cout << "Opsi tidak valid. Silakan pilih opsi yang benar\n";
                    break;
                }
            } while (InputFind != 3);
		    break;

		case 2:
			cout << "Menghapus Data Supir\n";
            cout << "Id yang ingin dihapus : ";
            getline(cin,SearchId);
            DeleteDataSupir(SearchId);
            break;

		case 3:
			cout << "Mengubah Data Supir\n";
            cout << "Masukkan Id Supir yang ingin diubah : ";
            getline(cin,SearchId);
            EditDataSupir(SearchId);
		    break;

		case 4:
            cout << "Menambah Data Supir\n";
            CreateDataSupir();
		    break;

        default:
                cout << "Pilihan tidak ditemukan\n";
                break;
        }
    }
    break;
}

    case 2: {
    char LoginUser = 'y';
    while (LoginUser == 'y' || LoginUser == 'Y') {
        DisplayDataSupirUser();
        int InputFind;

        do {
            InputFind = DisplayOptionsUser();

            switch (InputFind) {
                case 1:
                    SetCurrent(NextDataSupir());
                    DisplayDataSupir();
                    break;

                case 2:
                    SetCurrent(PrevDataSupir());
                    DisplayDataSupir();
                    break;

                case 3:
                    cout << "Kamu telah memilih driver, silahkan tunggu konfirmasi driver\n";
                    break;

                case 4:
                    char Exit;
                    cout << "Apakah anda ingin berhenti menggunakan aplikasi (y/n):";
                    cin >> Exit;

                    if (Exit == 'y') {
                        LoginUser = 'n';
                        Home = 'y';
                    } 
                    else {
                        LoginUser = 'y';
                    }
                    break;

                default:
                    cout << "Opsi tidak valid. Silakan pilih opsi yang benar\n";
                    break;
            }
        } while (InputFind != 4);
    }
    break;
}
    
    case 3:{
        cout << "Terima kasih telah menggunakkan jasa kami\n";
        return 0;
    }
    }
    }  
}
    
