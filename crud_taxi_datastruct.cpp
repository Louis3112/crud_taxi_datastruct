#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#define MAX_QUEUE_SIZE 10
#define MAX_STACK_SIZE 10
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

void SetCurrent(Supir* TargetedSupir);
void InitSupir();
int isEmpty();

int CharToInt(char c);
string GenerateIdSupir(string Nama, string TglLahir, char Kelamin);
string CheckIdSupir(Supir *FindId,string Id);

string DisplayGender(char Kelamin);
void DisplayAllDataSupir();
void DisplayDataSupirUser();
void DisplayDataSupir();
void FindDataSupir(string TargetId);
void CreateDataSupir();
void EditDataSupir(string TargetId);
void DeleteDataSupir(string TargetId);
Supir* NextDataSupir();
Supir* PrevDataSupir();

int DisplayOptionsAdmin();
int DisplayOptionsUser();

struct Order{
    string Id;
    string Nama;
    string Supir;
    string PlatNomor;
    string Tujuan;
};
Order Queue[MAX_QUEUE_SIZE];
int Front;
int Length;

int StringToInt(const string& str);
string GenerateIdPesanan(const string &PlatNomor, const string &Id, const string &Tujuan, const string &Nama);

void InitOrder(int *Front, int *Length);
int QueueEmpty(int Length);
int QueueFull(int Length);
void EnqueueOrder(int Front, int *Length, Order Queue[],Order FromUser);
Order DequeueOrder(int *Front, int *Length, Order Queue[]);
void UserOrder();

struct Mobil{
    string PlatNomor;
    string JenisMobil;
    string BrandMobil;
};
Mobil Garage[MAX_STACK_SIZE];
int Top;

void InitMobil(int *Top);
int GarageFull(int Top);
int GarageEmpty(int Top);
void Push(int *Top, Mobil Garage[], Mobil Input);
Mobil Pop(int *Top, Mobil Garage[]);
void AddMobil();
void DisplayAllMobil();

int main(){
    InitSupir();
    InitOrder(&Front,&Length);
    InitMobil(&Top);
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
            cout << "5. Menampilkan Semua Data Supir\n";
            cout << "6. Proses Pesanan\n";
            cout << "7. Tambah Unit Mobil\n";
            cout << "8. Menampilkan Semua Unit Mobil\n";
            cout << "0. Exit\n";
            cin >> Input;
            cin.ignore();
        switch(Input){
        case 0:
            char Exit;
            cout << "Apakah anda ingin keluar dari akses Admin (y/n):";
            cin >> Exit;

            if(Exit == 'y' || Exit == 'Y'){
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
                    cout << "Opsi tidak valid. Silakan pilih opsi yang benar\n \n";
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

        case 5:
            DisplayAllDataSupir();
            break;
            
        case 6:
            if(QueueEmpty(Length)){
                    cout << "Tidak Ada Pesanan !!!\n \n"; 
            }

            else{
            int Counter = 1;
            int ControlOrder;
            while(Length > 0){     
                Order ReadOrder;
                ReadOrder = DequeueOrder(&Front, &Length, Queue);
                cout << "---Pesanan ke " << Counter << "---\n";
                cout << "Id         : " << ReadOrder.Id << endl;
                cout << "Nama       : " << ReadOrder.Nama << endl;
                cout << "Supir      : " << ReadOrder.Supir << endl;
                cout << "Plat Nomor : " << ReadOrder.PlatNomor << endl;
                cout << "Tujuan     : " << ReadOrder.Tujuan << endl;
                cout << "1. Accept\n";
                cout << "2. Reject\n";
                cout << "3. Exit\n";
                cin >> ControlOrder;
                switch (ControlOrder){
                    case 1:
                        cout << "Pesanan dengan Id " << ReadOrder.Id << " telah diproses\n \n";
                        break;
                    case 2:
                        cout << "Pesanan dengan Id " << ReadOrder.Id << " telah dibatalkan\n \n ";
                        break;
                    case 3:
                        break;
                    default:
                        break;
                }
                Counter++;
                }
            }
            break;

        case 7:
            char MobilChoice;
            do{
                AddMobil();
                cout << "Ingin menambah unit lagi lagi? (y/n) > ";
                cin >> MobilChoice;
                cin.ignore();
                if(MobilChoice == 'n'){
                    break;
                }
            } while(MobilChoice == 'y');
            break;
        
        case 8:
            DisplayAllMobil();
            break;

        default:
            cout << "Pilihan tidak ditemukan\n \n";
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
                char OrderChoice;
                cin.ignore();
                UserOrder();
                cout << "Ingin melakukan order lagi? (y/n) > "; 
                cin >> OrderChoice;
                if (OrderChoice == 'y'){
                    SetCurrent(NextDataSupir());
                    DisplayDataSupir();
                }
                else if (OrderChoice == 'n'){
                    break;
                }
            break;

            case 4:
                char Exit;
                cout << "Apakah anda ingin keluar dari akses User (y/n):";
                cin >> Exit;

                if(Exit == 'y' || Exit == 'Y'){
                LoginUser = 'n';
                Home = 'y';
                }
            
                else{
                LoginUser = 'y';
                }
            break;

            default:
                cout << "Opsi tidak valid. Silakan pilih opsi yang benar\n \n";
                break;
            }
        } while( InputFind !=4);
    }
    break;
}
    
    case 3:{
        char Exit;
        cout << "Apakah anda ingin menutup aplikasi? (y/n) > ";
        cin >> Exit;

        if(Exit == 'y' || Exit == 'Y'){
            cout << "Terima kasih telah menggunakkan jasa kami\n";
            return 0;
        }
        else{
            break;
        }
    }
    }
    }  
}
    
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
string GenerateIdSupir(string Nama, string TglLahir, char Kelamin){
    string FullId{};    

    char FirstLetter = Nama[0];
    char LastLetter = toupper(Nama[Nama.length()-1]);
    int SecondDigit = abs(static_cast<int>(FirstLetter) - static_cast<int>(LastLetter));
    stringstream ss;
    ss << setw(2) << setfill('0') << SecondDigit;

    int GenderDigit = (Kelamin == 'l') ? 1 : 0;
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

    FullId = CheckIdSupir(Current, FullId);
    return FullId;
}
string CheckIdSupir(Supir *FindId,string Id){
    if(Head == NULL){
        return Id;
    }
    else{
        FindId = Head;
        do{
            if(FindId->Id == Id){
                int TempId = stoi(Id);
                TempId++;
                ostringstream oss;
                oss << setw(5) << setfill('0') << TempId;
                Id = oss.str();
                return Id;
            }
            else{
                FindId = FindId->Next;
            }
        }while(FindId != Head);
    }
    return Id;
}

string DisplayGender(char Kelamin) {
    if (Kelamin == 'l') {
        return "Laki-laki";
    } else if (Kelamin == 'p') {
        return "Perempuan";
    }
    return "Tidak diketahui";
}
void DisplayAllDataSupir(){
    if (isEmpty() == 1) {
        cout << "\nTidak ada data supir saat ini\n";
        cout << "Klik Enter untuk melanjutkan > ";
        cin.get();
        return;
    }
    
    Current = Head;
    cout << "Data semua supir\n\n";
    int Total = 0;
    do{
        Total++;
        cout << "|-------------------------|\n";
        cout << "|Nama      : " << Current->Nama << " |\n";
        cout << "|Id        : " << Current->Id << " |\n";
        cout << "|Tgl Lahir : " << Current->TglLahir << " |\n";
        cout << "|Kelamin   : " << DisplayGender(Current->Kelamin) << " |\n";
        cout << "|Alamat    : " << Current->Alamat << " |\n";
        cout << "|-------------------------|\n\n";
        Current = Current->Next;       
    }while(Current != Head);
    cout << "Total supir yang terdaftar : " << Total << " supir\n";
    cout << "Klik enter untuk melanjutkan\n";
    cin.get();
}
void DisplayDataSupirUser(){
    Current = Head;
    if (Current) {
        cout << "\n|-------------------------|\n";
        cout << "|Nama      : " << Current->Nama << " |\n";
        cout << "|Id        : " << Current->Id << " |\n";
        cout << "|Tgl Lahir : " << Current->TglLahir << " |\n";
        cout << "|Kelamin   : " << DisplayGender(Current->Kelamin) << " |\n";
        cout << "|Alamat    : " << Current->Alamat << " |\n";
        cout << "|-------------------------|\n";
    } 
    else {
        cout << "Tidak ada data supir saat ini\n \n";
    }
}
void DisplayDataSupir() {
    if (Current) {
        cout << "\n|-------------------------|\n";
        cout << "|Nama      : " << Current->Nama << " |\n";
        cout << "|Id        : " << Current->Id << " |\n";
        cout << "|Tgl Lahir : " << Current->TglLahir << " |\n";
        cout << "|Kelamin   : " <<  DisplayGender(Current->Kelamin) << " |\n";
        cout << "|Alamat    : " << Current->Alamat << " |\n";
        cout << "|-------------------------|\n";
    } 
    else {
        cout << "Tidak ada data supir saat ini\n";
    }
}
void FindDataSupir(string TargetId){
    if (isEmpty() == 1) {
        cout << "\nTidak ada data supir saat ini\n";
        return;
    }
    Current = Head;
    bool Found = false;
    do {
        if (Current->Id == TargetId) {
            int Choice;
            cout << "\n|-------------------------|\n";
            cout << "|Nama      : " << Current->Nama << " |\n";
            cout << "|Id        : " << Current->Id << " |\n";
            cout << "|Tgl Lahir : " << Current->TglLahir << " |\n";
            cout << "|Kelamin   : " << DisplayGender(Current->Kelamin) << " |\n";
            cout << "|Alamat    : " << Current->Alamat << " |\n";
            cout << "|-------------------------|\n";
            Found = true;
            break;
        }
        Current = Current->Next;
    }while(Current != Head);
    if (!Found) {
        cout << "Data dengan Id " << TargetId << " tidak ditemukan\n \n";
        cout << "Klik Enter untuk melanjutkan > ";
        cin.get();
    }
}
void CreateDataSupir() {
    string IdBaru, NamaBaru, TglLahirBaru, AlamatBaru;
    char KelaminBaru;
    cout << "Nama: > ";
    getline(cin, NamaBaru);
    cout << "Tgl lahir (dengan format dd-mm-yy): > ";
    getline(cin, TglLahirBaru);
    cout << "Kelamin (l/p): > ";
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
    cout << "|Nama          : " << NewSupir->Nama << " |\n";
    cout << "|Id            : " << NewSupir->Id << " |\n";
    cout << "|Tanggal Lahir : " << NewSupir->TglLahir << " |\n";
    cout << "|Kelamin       : " <<  DisplayGender(NewSupir->Kelamin) << " |\n";
    cout << "|Alamat        : " << NewSupir->Alamat << " |\n";
    cout << "|-------------------------|\n\n";

    cout << "Klik Enter untuk melanjutkan > ";
    cin.get();
}
void EditDataSupir(string TargetId) {
    if (isEmpty() == 1) {
        cout << "\nTidak ada data supir saat ini\n";
        cout << "Klik Enter untuk melanjutkan > ";
        cin.get();
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
                    cout << "Masukkan Data Kelamin baru (l/p) > ";
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
                    cout << "Opsi tidak valid\n \n";
            }

            Found = true;

                cout << "|-------------------------|\n";
                cout << "|Nama      : " << Current->Nama << " |\n";
                cout << "|Id        : " << Current->Id << " |\n";
                cout << "|Tgl Lahir : " << Current->TglLahir << " |\n";
                cout << "|Kelamin   : " << DisplayGender(Current->Kelamin) << " |\n";
                cout << "|Alamat    : " << Current->Alamat << " |\n";
                cout << "|-------------------------|\n\n";

                cout << "Klik enter untuk melanjutkan\n";
                cin.get();
            break;
        }

        Current = Current->Next;
    } while (Current != Head);

    if (!Found) {
        cout << "\nData dengan Id " << TargetId << " tidak ditemukan\n \n";
        cout << "Klik Enter untuk melanjutkan > ";
        cin.get();
    }
}
void DeleteDataSupir(string TargetId) {
    if (isEmpty() == 1) {
        cout << "Tidak ada data supir saat ini\n \n";
        cout << "Klik Enter untuk melanjutkan > ";
        cin.get();
        return;
    }

    Current = Head;
    Supir* PrevNode = Tail;
    do {
        if (Current->Id == TargetId) {
            char Choice;
            cout << "\nSupir dengan data berikut akan dihapus\n \n";
            cout << "|-------------------------|\n";
            cout << "|Nama      : " << Current->Nama << " |\n";
            cout << "|Id        : " << Current->Id << " |\n";
            cout << "|Tgl Lahir : " << Current->TglLahir << " |\n";
            cout << "|Kelamin   : " << DisplayGender(Current->Kelamin) << " |\n";
            cout << "|Alamat    : " << Current->Alamat << " |\n";
            cout << "|-------------------------|\n\n";
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

                cout << "\nData berhasil dihapus\n\n";
            } 
            else {
                cout << "Penghapusan data dibatalkan\n\n";
            }
            return;
        }
        PrevNode = Current;
        Current = Current->Next;
    } while (Current != Head);

    cout << "Data dengan Id " << TargetId << " tidak ditemukan\n \n";
    cout << "Klik Enter untuk melanjutkan > ";
    cin.get();
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

int StringToInt(const string& str) {
    istringstream iss(str);
    int result;
    iss >> result;
    return result;
}
string GenerateIdPesanan(const string &PlatNomor, const string &Id, const string &Tujuan, const string &Nama){
    stringstream ss;

    int FirstDigit = toupper(PlatNomor[0]) - 'A' + 1;
    ss << FirstDigit;

    int ThirdDigit = StringToInt(Id);
    ss << setw(5) << setfill('0') << ThirdDigit;

    char LastSecondLetter = toupper(Tujuan[Tujuan.length()-2]);
    char LastLetter = toupper(Tujuan[Tujuan.length()-1]);
    int EightDigit = (LastSecondLetter - 'A' + 1) + (LastLetter - 'A' + 1);
    ss << EightDigit;

    int TenthDigit = 0;
    for (char ch : Nama) {
        TenthDigit += (toupper(ch) - 'A' + 1);
    }
    TenthDigit %= 10;
    ss << TenthDigit;

    string FullId = ss.str();
    return FullId;
}

void InitOrder(int *Front, int *Length){
    *Front = *Length = 0;
}
int QueueEmpty(int Length){
    return Length == 0;
}
int QueueFull(int Length){
    return Length == MAX_QUEUE_SIZE;
}
void EnqueueOrder(int Front, int *Length, Order Queue[],Order FromUser){ 
    int Where;
    if(!QueueFull(*Length)){
        Where = Front + *Length;
        Queue[Where % MAX_QUEUE_SIZE] = FromUser;
        (*Length)++;
    }
}
Order DequeueOrder(int *Front, int *Length, Order Queue[]){ 
    int Where;
    if(!QueueEmpty(*Length)){
        Where = *Front;
        *Front = (Where + 1) % MAX_QUEUE_SIZE;
        (*Length)--;
        return Queue[Where];
    }
    else{
        Order EmptyOrder;
        return EmptyOrder;
    }
}
void UserOrder(){
    if(GarageEmpty(Top)){
        cout << "Unit mobil sedang kosong harap menunggu...\n";
    }

    else{
    Mobil MobilOrder = Pop(&Top, Garage);
    Order UserOrder;
    cout << "Masukkan nama pelanggan > ";
    getline(cin, UserOrder.Nama);
    cout << "Tujuan pelanggan > ";
    getline(cin, UserOrder.Tujuan);
    UserOrder.Supir = Current->Nama;
    UserOrder.PlatNomor = MobilOrder.PlatNomor;
    UserOrder.Id = GenerateIdPesanan(UserOrder.PlatNomor, Current->Id, UserOrder.Tujuan, UserOrder.Nama);

    cout << "\nOrder telah dilakukan\n";
    cout << "Id         : " << UserOrder.Id << endl;
    cout << "Nama       : " << UserOrder.Nama << endl;
    cout << "Supir      : " << UserOrder.Supir << endl;
    cout << "Plat nomor : " << UserOrder.PlatNomor << endl;
    cout << "Tujuan     : " << UserOrder.Tujuan << endl;

    EnqueueOrder(Front, &Length, Queue, UserOrder);
    }
}

void InitMobil(int *Top){
    *Top = -1;
}
int GarageFull(int Top){
    return Top == MAX_STACK_SIZE-1;
}
int GarageEmpty(int Top){
    return Top == -1;
}
void Push(int *Top, Mobil Garage[], Mobil Input){
    if(!GarageFull(*Top)){
        Garage[++(*Top)] = Input;
    }
}
Mobil Pop(int *Top,Mobil Garage[]){
    if(!GarageEmpty(*Top)){
        return Garage[(*Top)--];
    }
    else{
        Mobil EmptyMobil;
        return EmptyMobil;
    }
}
void AddMobil(){
    Mobil NewMobil;
    cout << "Masukkan plat nomor mobil > ";
    getline(cin, NewMobil.PlatNomor);
    cout << "Masukkan jenis mobil > ";
    getline(cin, NewMobil.JenisMobil);
    cout << "Masukkan brand mobil > ";
    getline(cin, NewMobil.BrandMobil);

    Push(&Top, Garage, NewMobil);
    cout << "\nData berhasil ditambahkan !!!\n \n";
}
void DisplayAllMobil(){
    if(GarageEmpty(Top)){
        cout << "Tidak ada mobil yang tersedia\n";
        cout << "Klik enter untuk melanjutkan\n";
        cin.get();
        return;
    }
    int Total= 0;
    cout << "Daftar mobil yang masih tersedia\n";
    for(int i = 0; i <= Top; i++){
        Total++;
        cout << "\nMobil ke-" << i+1 << endl;
        cout << "Plat nomor: " << Garage[i].PlatNomor << "\n";
        cout << "Jenis mobil: " << Garage[i].JenisMobil << "\n";
        cout << "Brand mobil: " << Garage[i].BrandMobil << "\n\n";
    }

    cout << "Total mobil yang tersedia : " << Total << " mobil\n";
    cout << "Klik enter untuk melanjutkan\n";
    cin.get();
}