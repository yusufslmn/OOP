

/////////////////////////////    ABDULKADİR PAŞAOGLU 402530  /////////////////////////////
/////////////////////////////   YUSUF SALMAN 402529			/////////////////////////////


#include <iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<istream>
#include<thread>
#include<chrono>
#include<vector>
#include<sstream>
#include<regex>
#include<ctime>
#include <conio.h>        
#include <stdlib.h>

using namespace std;


class Zaman
{
	friend ostream& operator<<(ostream&, Zaman&);
public:
	Zaman& operator+(Zaman&);
	bool operator>=(Zaman&);
	bool operator<=(Zaman&);
	bool operator==(Zaman&);
	Zaman& operator=(Zaman&);
	int saat;
	int dakika;

};


class Kiyafet
{
public:
	Kiyafet();
	string* kategori;
	string* kiyafet_adi;
	string* fiyat;
	string* boyut;
	string* renk;
	void kiyafet_bilgigir();
};


class Kisi
{
public:
	string* ad_soyad;
	string* tel_no;
};


class Siparis : public Kiyafet
{
public:
	int siparis_no;
	double siparis_fiyat;
	Zaman siparis_baslangic;
	Zaman siparis_ulasim;

};


class Kullanici :public Kisi
{
public:
	Kullanici();
	string* kullanici_adi;
	string* eposta;
	string* adres_ilce;
	string* sifre;
	string* indirim_kodu;
	string* dtarihi;

	void kbilgigir();
};


class Yonetici : public Kisi
{
public:
	Yonetici();
	string* sifre;
	void ybilgigir();

};


class Kurye : public Kisi
{
public:
	Kurye();
	int kurye_no;
	Zaman dagitim_bitisler;
	int siparis_numaralari;
	void kurye_bilgigir();
};


class  AnaMenu
{
public:

	static void ana_menu();
	static void sistem_giris();
	static void uye_kaydi();
	static void admin_kaydi();
};


class SistemGirisi
{
public:

	bool uservalidate(string, string);
	bool adminvalidate(string);
	static void musteri_giris();
	static void yonetici_giris();

};


class MusteriGirisi
{
public:
	static void kuponlarim();
	static void kiyafet_kategori();
	static void elbise_kategori();
	static void etek_kategori();
	static void tshirt_kategori();
	static void pantolon_kategori();
	static void gomlek_kategori();
	static void ayakkabi_kategori();
	static void sepet_alisveris();
	static void siparis_takip();
	static void sikayet_öneri();
	static void sifre_degistir();
	static void fatura_olustur();

};



class YoneticiGirisi
{
public:
	static void urun_girisi();
	static void kurye_ekle();
	static void kullanıcı_indirim();
	static void fatura_görüntüle();


};


class VarisZaman {

public:
	VarisZaman();
	Zaman decidetime(string);
	Zaman Ortahisar;
	Zaman Vakfikebir;
	Zaman Akcaabat;
	Zaman Arakli;
	Zaman Arsin;
	Zaman Besikduzu;
	Zaman Yomra;
};

void kuryeleri_dosyadan_cekis();

bool Email_check(string email);

void kullanici_kupon_atama();

char decision_control(string);

////////////////////////////////////////////////// Global Degıskenler /////////////////////////////////////////////////

vector<Kurye>kuryeler;
vector<string>discount_coupon; //Kullanıcı kuponları
vector<int>discount_price; //Kullanıcı kupon tutarı
vector<Kiyafet>sepet; //Sepet
vector<Kiyafet>elbise, tshirt, pantolon, gomlek, etek, ayakkabi;//Kıyafetlerin dosyalarını tutuyor
string username, password, adres;// Kullanıcı adı
int toplam = 0;//Siparis Total Price

int main()
{
	kuryeleri_dosyadan_cekis();

	AnaMenu AnaMenu;

	AnaMenu.ana_menu();
}

////////////////////////////////////////////////// ANA MENÜ //////////////////////////////////////////////////////////

void AnaMenu::ana_menu()
{
	string secim;
	cout << "Hosgeldiniz" << endl << "1.Sisteme Giris" << endl << "2.Kayit Ol" << endl << "3.Cikis" << endl << endl << "Lutfen ilerlemek icin seciniz :";
	cin >> secim;
	char decision = decision_control(secim);

	switch (decision)
	{
	case '1':
	{
		system("cls");
		sistem_giris();
		break;
	}
	case '2':
	{
		system("cls");
		cout << "1.Yonetici Kaydi" << endl << "2.Musteri kaydi\n3.Geri Don" << endl << "Lutfen secim yapiniz:";
		string secim2;
		cin >> secim2;
		char decision = decision_control(secim2);
		
		switch (decision)
		{
		case '1':
			system("cls"); AnaMenu::admin_kaydi(); break;
		case '2':
			system("cls"); AnaMenu::uye_kaydi(); break;
		case '3':
			system("cls"); AnaMenu::ana_menu(); break;
		default: {
			while (decision!='1' && decision != '2' && decision != '3')
			{
				system("cls");
				cout << "1.Yonetici Kaydi" << endl << "2.Musteri kaydi\n3.Geri Don" << endl << "Lutfen secim yapiniz:";
				string secim2;
				cin >> secim2;
				char decision = decision_control(secim2);

				if (decision == '1') { system("cls"); AnaMenu::admin_kaydi(); break; }
				if (decision == '2') { system("cls"); AnaMenu::uye_kaydi(); break; }
				if (decision == '3') { system("cls"); AnaMenu::ana_menu(); break; }
			}
			break;
		}


		}
		break;
	}
	case '3':
	{

		remove("kurye.txt");

		fstream fin;
		fin.open("kurye.txt", ios::out | ios::in | ios::app);
		fin.setf(ios::left);

		for (int i = 0; i < kuryeler.size(); i++)
		{
			fin << *(kuryeler[i].ad_soyad) <<
				"$" << *(kuryeler[i].tel_no) <<
				"$" << kuryeler[i].kurye_no <<
				"$" << kuryeler[i].dagitim_bitisler.saat <<
				"$" << kuryeler[i].dagitim_bitisler.dakika <<
				"$" << kuryeler[i].siparis_numaralari << endl;
		}
		fin.close();
		exit(EXIT_SUCCESS);
		break;
	}
	default: {
		
		cout << "Lutfen secenekleri seciniz !!";
		this_thread::sleep_for(std::chrono::milliseconds(1500));
		system("cls");
		secim.clear();
		AnaMenu::ana_menu();
		break; }
	}


}

void AnaMenu::sistem_giris()
{
	string secim;
	cout << "1.Musteri Girisi\n2.Yonetici Girisi\n3.Geri Don" << endl << endl << "Lutfen ilerlemek icin seciniz :";
	cin >> secim;
	char decision = decision_control(secim);

	switch (decision)
	{
	case '1': {
		system("cls");
		string pass;
		string user;
		cout << "Kullanici Adi  (geri donus icin 'geri' yaziniz)  :";
		cin.ignore();
		getline(cin, user);
		if (user == "Geri" || user == "geri") { system("cls"); AnaMenu::sistem_giris(); };

		string password1, P;
		char p;
		cout << "Sifre giriniz: ";
		p = _getch();
		while (p != 13)// ASCII 13 = Enter tuşu girilene kadar
		{
			if (p == 8 && P.size()>0)
			{
				P.resize(P.length() - 1);  // ASCII 8 = backspace(silme tusu) 
				cout << P;
				password1.resize(password1.length() - 1); // Eğer silme tuşuna basarsa resize fonksiyonunu kullan(yeniden boyutlandırma fonksiyonu)
			}
			else {
				P = P + "*";
				cout << P;
				password1.push_back(p);
			}
			p = _getch();
			system("cls");
			cout << "Sifre giriniz: ";
		}

		pass = password1;

		SistemGirisi validate;

		if (validate.uservalidate(user, pass))
		{
			username = user;
			password = pass;
			kullanici_kupon_atama();
			cout << endl<<"Giris Basarili !";
			this_thread::sleep_for(std::chrono::milliseconds(1500));
			system("cls");
			SistemGirisi::musteri_giris();

		}
		else {
			while (!(validate.uservalidate(user, pass)))
			{
				cout << endl << "Kullanici Adi veya Sifre  hatali";
				this_thread::sleep_for(std::chrono::milliseconds(2000));
				system("cls");
				cout << "Kullanici Adi (geri donus icin 'geri' yaziniz):";
				
				getline(cin, user);
				if (user == "Geri" || user == "geri") { system("cls"); AnaMenu::sistem_giris(); };

				string password1, P;
				char p;
				P.clear();
				password1.clear();
				cout << "Sifre giriniz: ";
				p = _getch();
				while (p != 13)// ASCII 13 = Enter tuşu girilene kadar
				{
					if (p == 8 && P.size() > 0)
					{
						P.resize(P.length() - 1);  // ASCII 8 = backspace(silme tusu) 
						cout << P;
						password1.resize(password1.length() - 1); // Eğer silme tuşuna basarsa resize fonksiyonunu kullan(yeniden boyutlandırma fonksiyonu)
					}
					else {
						P = P + "*";
						cout << P;
						password1.push_back(p);
					}
					p = _getch();
					system("cls");
					cout << "Sifre giriniz: ";
				}
				pass = password1;
			}
			username = user;
			password = pass;
			kullanici_kupon_atama();
			cout << endl << "Giris Basarili !";
			this_thread::sleep_for(std::chrono::milliseconds(1500));
			system("cls");
			SistemGirisi::musteri_giris();
		}

		break;
	}
	case '2': {

		system("cls");


		cout << "Sifre(Geri Donus icin G):";
		string pass;
		string password, P;
		char p;
		cout << "Sifre giriniz: ";
		p = _getch();
		while (p != 13)        // ASCII 13 = Enter tuşu girilene kadar
		{
			if (p == 8 && P.size() > 0)
			{
				P.resize(P.length() - 1);  // ASCII 8 = backspace(silme tusu) 
				cout << P;
				password.resize(password.length() - 1); // Eğer silme tuşuna basarsa resize fonksiyonunu kullan(yeniden boyutlandırma fonksiyonu)
			}
			else {
				P = P + "*";
				cout << P;
				password.push_back(p);
			}
			p = _getch();
			system("cls");
			cout << "Sifre giriniz: ";
		}
		pass = password;

		if (pass == "G" || pass == "g") {
			system("cls");
			AnaMenu::sistem_giris();
		}
		SistemGirisi validate;

		if (validate.adminvalidate(pass))
		{
			cout << endl << "Giris Basarili !";
			this_thread::sleep_for(std::chrono::milliseconds(1500));
			system("cls");
			SistemGirisi::yonetici_giris();

		}
		else {
			while (!(validate.adminvalidate(pass)))
			{
				cout << endl << "Sifre  hatali";
				this_thread::sleep_for(std::chrono::milliseconds(2000));
				system("cls");
				string password2, P;
				char p;
				P.clear();
				password2.clear();
				cout << "Sifre giriniz: ";
				p = _getch();
				while (p != 13)// ASCII 13 = Enter tuşu girilene kadar
				{
					if (p == 8 && P.size() > 0)
					{
						P.resize(P.length() - 1);  // ASCII 8 = backspace(silme tusu) 
						cout << P;
						password2.resize(password2.length() - 1); // Eğer silme tuşuna basarsa resize fonksiyonunu kullan(yeniden boyutlandırma fonksiyonu)
					}
					else {
						P = P + "*";
						cout << P;
						password2.push_back(p);
					}
					p = _getch();
					system("cls");
					cout << "Sifre giriniz: ";

				}
				pass = password2;
			}
			cout << endl << "Giris Basarili !";
			this_thread::sleep_for(std::chrono::milliseconds(1500));
			system("cls");
			SistemGirisi::yonetici_giris();
		}
		break;

	}
	case '3':system("cls"); AnaMenu::ana_menu(); break;
	default: {
		cout << "Lutfen secenekleri seciniz !!";
		this_thread::sleep_for(std::chrono::milliseconds(1500));
		system("cls");
		sistem_giris();
		break;
	}
	}
}

void AnaMenu::uye_kaydi()
{
	Kullanici user{};
	user.kbilgigir();
	fstream dosya;
	dosya.open("kullanicilar.txt", ios::out | ios::in | ios::app);
	dosya.setf(ios::left);
	dosya << *(user.ad_soyad) <<
		"$" << *(user.eposta) <<
		"$" << *(user.tel_no) <<
		"$" << *(user.dtarihi) <<
		"$" << *(user.adres_ilce) <<
		"$" << *(user.kullanici_adi) <<
		"$" << *(user.sifre) << endl;

	dosya.close();

	username = *(user.kullanici_adi);
	password = *(user.sifre);
	adres=*(user.adres_ilce);

	SistemGirisi::musteri_giris();
}

void AnaMenu::admin_kaydi()
{

	Yonetici admin{};
	cout << "Yonetici kaydi icin ozel sifreyi giriniz(Cikis icin 0'i tuslayin):";
	const string sifre = "19Y19S";
	string pass;
	cin >> pass;
	if (pass == "0") {
		system("cls"); AnaMenu::ana_menu();
	}

	if (pass == sifre) {
		system("cls");
		admin.ybilgigir();
		fstream dosya;
		dosya.open("yonetici.txt", ios::out | ios::in | ios::app);
		dosya.setf(ios::left);
		dosya << *(admin.ad_soyad) <<
			"$" << *(admin.tel_no) <<
			"$" << *(admin.sifre) << endl;

		dosya.close();

		SistemGirisi::yonetici_giris();
	}
	else
	{
		while (pass != sifre)
		{
			system("cls");
			cout << "Yonetici kaydi icin ozel sifreyi giriniz(Cikis icin 0'i tuslayin):";
			cin >> pass;
			if (pass == "0") { system("cls"); AnaMenu::ana_menu(); break; }

		}

		SistemGirisi::yonetici_giris();
	}
}





/////////////////////////////////////////////////// SİSTEM GİRİŞİ ///////////////////////////////////////////////////

void SistemGirisi::musteri_giris()
{
	/////////////////////////////////////////////////////////////////////// MUSTERİ ANA MENUSU ////////////////////////////////////////////////////////////// 
	string secim;

	cout << "1.Kiyafet Kategorileri" << endl << "2.Siparis Takip" << endl << "3.Sikayet/Oneriler" << endl << "4.Sifre Degistir" << "\n5.Kuponlarim" << endl << "6.Sepet" << endl << "7.Geri Don" << endl << endl << "Lutfen Ilerlemek Icin Secim Yapiniz:";
	cin >> secim;
	char decision = decision_control(secim);

	switch (decision)
	{
	case '1':
	{
		system("cls");
		MusteriGirisi::kiyafet_kategori();
		break;
	}
	case '2':
	{
		system("cls");
		MusteriGirisi::siparis_takip();
		break;
	}
	case '3':
	{
		system("cls");
		MusteriGirisi::sikayet_öneri();
		break;
	}
	case '4':
	{
		system("cls");
		MusteriGirisi::sifre_degistir();
		break;
	}
	case '5':
	{
		system("cls");
		MusteriGirisi::kuponlarim();
		break;
	}
	case '6':
	{
		system("cls");
		MusteriGirisi::sepet_alisveris();
		break;
	}
	case '7':
	{
		system("cls");
		sepet.clear();
		toplam = 0;
		discount_price.clear();
		discount_coupon.clear();
		username.clear();
		adres.clear();
		password.clear();
		AnaMenu::ana_menu();
		break;
	}
	default:
	{
		system("cls");
		musteri_giris();
		break;
	}
	}


}

void SistemGirisi::yonetici_giris()
{
	string secim;
	cout << "1.Urun Girisi" << endl << "2.Kurye Ekle" << endl << "3.Sikayet Oku" << endl << "4.Kullanici Indirim Tanimla" << endl << "5.Fatura Goruntule" << endl << "6.Cikis" << endl << endl << "Lutfen Ilerlemek Icin Secim Yapiniz:";
	cin >> secim;
	char decision = decision_control(secim);

	switch (decision)
	{
	case '1': {
		system("cls");
		YoneticiGirisi::urun_girisi();
		break;
	}
	case '2': {
		system("cls");
		YoneticiGirisi::kurye_ekle();
		break; 
	}
	case '3':
	{
		system("cls");
		fstream suggest;
		string sikayet;
		int count = 1;
		suggest.open("sikayet.txt", ios::out | ios::in | ios::app);
		while (!suggest.eof())
		{
			getline(suggest, sikayet);
			cout << count << "." << sikayet << endl;
			count++;
		}
		suggest.close();
		this_thread::sleep_for(std::chrono::milliseconds(10000));
		system("cls");
		SistemGirisi::yonetici_giris();
		break;
	}
	case '4': {system("cls"); YoneticiGirisi::kullanıcı_indirim(); break; }
	case '5': {system("cls"); YoneticiGirisi::fatura_görüntüle(); break; }
	case '6': {system("cls"); AnaMenu::ana_menu(); break; }
	default: {
		system("cls");
		yonetici_giris();
	}
	}

}

bool SistemGirisi::uservalidate(string user, string pass)
{
	// File pointer
	fstream fin;
	Kullanici tempuser;
	// Open an existing file
	fin.open("kullanicilar.txt", ios::in);

	// Get the roll number
	// of which the data is required
	int  count = 0;

	// Read the Data from the file
	// as String Vector
	vector<string> row;
	string  line,word;

	while (!fin.eof())
	{
		row.clear();

		// read an entire row and
		// store it in a string variable 'line

		getline(fin, line);

		// used for breaking words
		stringstream s(line);
		// read every column data of a row and
		// store it in a string variable, 'word'
		while (getline(s, word, '$')) {

			// add all the column data
			// of a row to a vector
			row.push_back(word);
			if (row.size() == 7)
				break;
		}

		// Print the found data
		if (row.size() > 0) {
			count++;
			*(tempuser.ad_soyad) = row[0];
			*(tempuser.eposta) = row[1];
			*(tempuser.tel_no) = row[2];
			*(tempuser.dtarihi) = row[3];
			*(tempuser.adres_ilce) = row[4];
			*(tempuser.kullanici_adi) = row[5];
			*(tempuser.sifre) = row[6];
		}

		if (*(tempuser.kullanici_adi) == user) {
			if (*(tempuser.sifre) == pass)
			{
				adres = *(tempuser.adres_ilce);
				return true;

			}

		}
	}
	fin.close();
	if (count == 0) {
		cout << "Record not found\n";
	}

	return false;
}

bool SistemGirisi::adminvalidate(string password1)
{
	// File pointer
	fstream tin;
	Yonetici tempuser;
	// Open an existing file
	tin.open("yonetici.txt", ios::in);

	// Get the roll number
	// of which the data is required
	int count = 0;

	// Read the Data from the file
	// as String Vector
	vector<string> row;
	string line, word;

	while (!tin.eof())
	{
		row.clear();

		// read an entire row and
		// store it in a string variable 'line'
		getline(tin, line);

		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (getline(s, word, '$')) {

			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}

		// Print the found data
		if (row.size() > 0) {
			count++;
			*(tempuser.ad_soyad) = row[0];
			*(tempuser.tel_no) = row[1];
			*(tempuser.sifre) = row[2];
		}


		if (*(tempuser.sifre) == password1)
		{
			return true;

		}


	}
	tin.close();
	if (count == 0)
		cout << "Record not found\n";
	return false;
}

/////////////////////////////////////////////  KULLANICI CLASSI /////////////////////////////////////////////////////

void Kullanici::kbilgigir()
{
	cout << "Ad Soyad:";
	cin.ignore();
	getline(cin, *(this->ad_soyad));

	while (true)
	{
		cout << "E Posta:";
		getline(cin, *(this->eposta));
		if (Email_check(*(this->eposta))) break;
		cout << endl << "lutfen gecerli e-posta giriniz:" << endl;
	}

	cout << "Tel No:";

	getline(cin, *(this->tel_no));


	string temp;
	int day;
	int month;
	int year;

	while (true) {
		cout << "Dogum Tarihi Giriniz: gun/ay/yil : ";
		getline(cin, temp);

		day = stoi(temp.substr(0, 2));
		month = stoi(temp.substr(3, 5));
		year = stoi(temp.substr(6, 11));
		if (day >= 0 && day <= 31) {
			if (month >= 0 && month <= 12) {
				if (year >= 1900 && year <= 2020) { break; }
				else cout << "Gecersiz yil girisi " << endl;
			}
			else cout << "Gecersiz ay girisi" << endl;
		}
		else cout << "Gecersiz gun girisi" << endl;


		cout << "Lütfen tekrar deneyiniz"<<endl;

	}
	*this->dtarihi = temp;


	cout << "Adres Ilce:";

	getline(cin, *(this->adres_ilce));


	

	fstream fin;
	int  count = 0;
	bool deneme = false;

	do {

		cout << "Kullanici Adi:";
		getline(cin, *(this->kullanici_adi));

		fin.open("kullanicilar.txt", ios::in);
		vector<string> row;
		string  line, word;

		while (!fin.eof())
		{
			row.clear();
			
			getline(fin, line);

			// used for breaking words
			stringstream s(line);
			
			while (getline(s, word, '$')) {

				row.push_back(word);
			}

			if (row.size() > 0) {
				Kullanici tempuser;
				count++;
				*(tempuser.ad_soyad) = row[0];
				*(tempuser.eposta) = row[1];
				*(tempuser.tel_no) = row[2];
				*(tempuser.dtarihi) = row[3];
				*(tempuser.adres_ilce) = row[4];
				*(tempuser.kullanici_adi) = row[5];
				
				if (row[5] == *(this->kullanici_adi))
				{
					deneme = true;
					break;
				}
				else deneme = false;
			}

		}
		fin.close();
		if(deneme)cout << "Kullanici adi alinmis lutfen farklı kullanici adi giriniz!!!"<<endl;

	} while (deneme);

	string password1;


	do {
		string P;
		char p;
		cout << "Sifre giriniz: ";
		p = _getch();
		while (p != 13)// ASCII 13 = Enter tuşu girilene kadar
		{
			if (p == 8 && P.size() > 0)
			{
				P.resize(P.length() - 1);  // ASCII 8 = backspace(silme tusu) 
				cout << P;
				password1.resize(password1.length() - 1); // Eğer silme tuşuna basarsa resize fonksiyonunu kullan(yeniden boyutlandırma fonksiyonu)
			}
			else {
				P = P + "*";
				cout << P;
				password1.push_back(p);
			}
			p = _getch();
			system("cls");
			cout << "Sifre giriniz: ";

		}
		
		if (password1.size() < 6) { cout << endl << "Lutfen 6 karakterden fazla sifre giriniz!!!" << endl; P.clear(); password1.clear();}
	} while (password1.size()<6);

	*(this->sifre )= password1;

	system("cls");
	cout << "Kayit islemi basari ile tamamlandi." << endl << "Ana menuye donuluyor...";
	this_thread::sleep_for(std::chrono::milliseconds(2000));
	system("cls");

}


Kullanici::Kullanici()
{
	kullanici_adi = new string;
	eposta = new string;
	adres_ilce = new string;
	sifre = new string;
	indirim_kodu = new string;
	dtarihi = new string;
	ad_soyad = new string;
	tel_no = new string;

}



/////////////////////////////////// YÖNETİCİ CLASSI /////////////////////////////////////////////////////////////////

void Yonetici::ybilgigir()
{
	cout << "Ad Soyad:";
	cin.ignore();
	getline(cin, *(this->ad_soyad));

	cout << "Tel No:";
	getline(cin, *(this->tel_no));


	string password, P;
	char p;
	cout << "Sifre giriniz: ";
	p = _getch();
	while (p != 13)    // ASCII 13 = Enter tuşu girilene kadar
	{
		if (p == 8)
		{
			P.resize(P.length() - 1); // ASCII 8 = backspace(silme tusu) 
			cout << P;
			password.resize(password.length() - 1); // Eğer silme tuşuna basarsa resize fonksiyonunu kullan(yeniden boyutlandırma fonksiyonu)
		}
		else {
			P = P + "*";
			cout << P;
			password.push_back(p);
		}
		p = _getch();
		system("cls");
		cout << "Sifre giriniz: ";
	}

	*this->sifre = password;

	cout << "Kayit islemi basari ile tamamlandi." << endl << "Ana menuye donuluyor...";
	this_thread::sleep_for(std::chrono::milliseconds(2000));
	system("cls");

}

Yonetici::Yonetici()
{
	sifre = new string;
	ad_soyad = new string;
	tel_no = new string;

}


////////////////////// MUSTERİ GİRİSİ (GİRİS YAPILDI İSE BURAYA YÖNLENDİR) //////////////////////////////////////////


void MusteriGirisi::kiyafet_kategori()
{
	string secim;
	cout << "Kategoriler\n1)Elbise\n2)Etek\n3)Gomlek\n4)Pantolon\n5)Ayakkabi\n6)Tshirt\n7)Geri Don\n\n\nLutfen Kategori Seciniz:";
	cin >> secim;
	char decision = decision_control(secim);

	elbise.clear(); tshirt.clear(); pantolon.clear();  gomlek.clear(); etek.clear(); ayakkabi.clear();

	fstream fin;
	fin.open("kiyafet.txt", ios::in);
	int  count = 0;
	vector<string> row;
	string line, word;
	while (!fin.eof())
	{
		row.clear();

		getline(fin, line);

		stringstream s(line);

		while (getline(s, word, '$'))
		{

			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}
		// Print the found data
		if (row.size() > 0)
		{
			Kiyafet user;
			count++;
			*(user.kategori) = row[0];
			*(user.kiyafet_adi) = row[1];
			*(user.fiyat) = row[2];
			*(user.boyut) = row[3];
			*(user.renk) = row[4];

			if (*(user.kategori) == "Elbise")elbise.push_back(user);
			if (*(user.kategori) == "Etek")etek.push_back(user);
			if (*(user.kategori) == "Gomlek")gomlek.push_back(user);
			if (*(user.kategori) == "Pantolon")pantolon.push_back(user);
			if (*(user.kategori) == "Ayakkabi")ayakkabi.push_back(user);
			if (*(user.kategori) == "Tshirt")tshirt.push_back(user);
		}

	}


	system("cls");
	switch (decision)
	{
	case '1':
	{
		MusteriGirisi::elbise_kategori();
		break;
	}
	case '2':
	{
		MusteriGirisi::etek_kategori();
		break;
	}
	case '3':
	{
		MusteriGirisi::gomlek_kategori();
		break;
	}
	case '4':
	{
		MusteriGirisi::pantolon_kategori();
		break;
	}
	case '5':
	{
		MusteriGirisi::ayakkabi_kategori();
		break;
	}
	case '6':
	{
		MusteriGirisi::tshirt_kategori();
		break;
	}
	case '7':
	{
		SistemGirisi::musteri_giris();
		break;
	}
	default: {
		system("cls"); MusteriGirisi::kiyafet_kategori();

	}

	}

}

void MusteriGirisi::elbise_kategori()
{
	for (int i = 0; i < elbise.size(); i++)
	{
		cout << i + 1 << ")" << endl <<
			"Kiyafet Adi:" << *(elbise[i].kiyafet_adi) << endl <<
			"Fiyat:" << *(elbise[i].fiyat) << endl <<
			"---------------------------------------" << endl;

	}

	string secim ;
	string beden, renk;

	cout << "\n\n1)Devam Et \n2)Sepete Git\n3)Geri Don\n\nSeciniz:";
	cin >> secim;
	char decision = decision_control(secim);

	switch (decision)
	{
	case '1': {
		int decision;
		cout << "\n\nUrun Seciniz:";
		cin >> decision;

			system("cls");
			cout << "Kiyafet Adi:" << *(elbise[decision - 1].kiyafet_adi) << endl
				<< "Fiyat:" << *(elbise[decision - 1].fiyat) << endl
				<< "Boyut: 'S' 'M' 'L' 'XL' 'XXL' \nRenk: 'Mavi' 'Kirmizi' 'Yesil' 'Siyah' 'Kahverengi' 'Beyaz' \n\n";
			cout << "1)Sepete Ekle\n2)Geri Don\nLutfen ilerlemek icin seciniz:";
			cin >>secim;
			char decision1 = decision_control(secim);
			
			if (decision1 == '1')
			{
				cout << "\nLutfen Beden Seciniz:"; cin >> beden;
				cout << "\nLutfen Renk Seciniz:"; cin >> renk;
				*(elbise[decision - 1].boyut) = beden;
				*(elbise[decision - 1].renk) = renk;
				sepet.push_back(elbise[decision - 1]);

				cout << "\nSepete Eklendi."; this_thread::sleep_for(std::chrono::milliseconds(1500)); system("cls"); MusteriGirisi::elbise_kategori();
			}
			if (decision1 == '2' || decision1 != '1') { secim.clear(); system("cls"); MusteriGirisi::elbise_kategori(); }break;
		
		
	}

	case '2': {
		system("cls");
		MusteriGirisi::sepet_alisveris(); break;
	}
	case '3': 
	{
		system("cls");
		MusteriGirisi::kiyafet_kategori(); break; 
	}
	default: {
		secim.clear();
		cout << "Lutfen secenekleri seciniz !!";
		this_thread::sleep_for(std::chrono::milliseconds(2000));
		system("cls");
		MusteriGirisi::elbise_kategori(); break; }

	}


}

void MusteriGirisi::etek_kategori()
{
	for (int i = 0; i < etek.size(); i++)
	{
		cout << i + 1 << ")" << endl <<

			"Kiyafet Adi:" << *(etek[i].kiyafet_adi) << endl <<
			"Fiyat:" << *(etek[i].fiyat) << endl <<
			"---------------------------------------" << endl;

	}
	int secim;
	int decision = 0;
	string beden, renk;
	cout << "\n\n1)Devam Et \n2)Sepete Git\n3)Geri Don\nSeciniz:";
	cin >> decision;
	switch (decision)
	{
	case 1:
		cout << "\n\nUrun Seciniz:";
		cin >> decision;
		system("cls");
		cout << "Kiyafet Adi:" << *(etek[decision - 1].kiyafet_adi) << endl
			<< "Fiyat:" << *(etek[decision - 1].fiyat) << endl
			<< "Boyut: 'S' 'M' 'L' 'XL' 'XXL' \nRenk: 'Mavi' 'Kirmizi' 'Yesil' 'Siyah' 'Kahverengi' 'Beyaz' \n\n";
		cout << "1)Sepete Ekle\n2)Geri Don\nLutfen ilerlemek icin seciniz:";
		cin >> secim;
		if (secim == 1)
		{
			cout << "\nLutfen Beden Seciniz:"; cin >> beden;
			cout << "\nLutfen Renk Seciniz:"; cin >> renk;
			*(etek[decision - 1].boyut) = beden;
			*(etek[decision - 1].renk) = renk;
			sepet.push_back(etek[decision - 1]);

			cout << "\nSepete Eklendi."; this_thread::sleep_for(std::chrono::milliseconds(1500)); system("cls"); MusteriGirisi::etek_kategori();
		}
		if (secim == 2) { system("cls"); MusteriGirisi::etek_kategori(); }break;
	case 2:system("cls");
		MusteriGirisi::sepet_alisveris(); break;
	case 3:system("cls");
		MusteriGirisi::kiyafet_kategori(); break;
	default: {
		cout << "Lutfen secenekleri seciniz !!";
		this_thread::sleep_for(std::chrono::milliseconds(2000));
		system("cls");
		MusteriGirisi::etek_kategori(); break; }

	}
}

void MusteriGirisi::tshirt_kategori()
{
	for (int i = 0; i < tshirt.size(); i++)
	{
		cout << i + 1 << ")" << endl <<

			"Kiyafet Adi:" << *(tshirt[i].kiyafet_adi) << endl <<
			"Fiyat:" << *(tshirt[i].fiyat) << endl <<
			"---------------------------------------" << endl;

	}
	int secim;
	int decision = 0;
	string beden, renk;
	cout << "\n\n1)Devam Et \n2)Sepete Git\n3)Geri Don\nSeciniz:";
	cin >> decision;
	switch (decision)
	{
	case 1:
		cout << "\n\nUrun Seciniz:";
		cin >> decision;
		system("cls");
		cout << "Kiyafet Adi:" << *(tshirt[decision - 1].kiyafet_adi) << endl
			<< "Fiyat:" << *(tshirt[decision - 1].fiyat) << endl
			<< "Boyut: 'S' 'M' 'L' 'XL' 'XXL' \nRenk: 'Mavi' 'Kirmizi' 'Yesil' 'Siyah' 'Kahverengi' 'Beyaz' \n\n";
		cout << "1)Sepete Ekle\n2)Geri Don\nLutfen ilerlemek icin seciniz:";
		cin >> secim;
		if (secim == 1)
		{
			cout << "\nLutfen Beden Seciniz:"; cin >> beden;
			cout << "\nLutfen Renk Seciniz:"; cin >> renk;
			*(tshirt[decision - 1].boyut) = beden;
			*(tshirt[decision - 1].renk) = renk;
			sepet.push_back(tshirt[decision - 1]);

			cout << "Sepete Eklendi."; this_thread::sleep_for(std::chrono::milliseconds(1500)); system("cls"); MusteriGirisi::tshirt_kategori();
		}
		if (secim == 2) { system("cls"); MusteriGirisi::tshirt_kategori(); }break;
	case 2:system("cls");
		MusteriGirisi::sepet_alisveris(); break;
	case 3:system("cls");
		MusteriGirisi::kiyafet_kategori(); break;
	default: {
		cout << "Lutfen secenekleri seciniz !!";
		this_thread::sleep_for(std::chrono::milliseconds(2000));
		system("cls");
		MusteriGirisi::tshirt_kategori(); break; }

	}
}

void MusteriGirisi::pantolon_kategori()
{
	for (int i = 0; i < pantolon.size(); i++)
	{
		cout << i + 1 << ")" << endl <<
			"Kiyafet Adi:" << *(pantolon[i].kiyafet_adi) << endl <<
			"Fiyat:" << *(pantolon[i].fiyat) << endl <<
			"---------------------------------------" << endl;

	}
	int secim;
	int decision = 0;
	string beden, renk;
	cout << "\n\n1)Devam Et \n2)Sepete Git\n3)Geri Don\nSeciniz:";
	cin >> decision;
	switch (decision)
	{
	case 1:
		cout << "\n\nUrun Seciniz:";
		cin >> decision;
		system("cls");
		cout << "Kiyafet Adi:" << *(pantolon[decision - 1].kiyafet_adi) << endl
			<< "Fiyat:" << *(pantolon[decision - 1].fiyat) << endl
			<< "Boyut: 'S' 'M' 'L' 'XL' 'XXL' \nRenk: 'Mavi' 'Kirmizi' 'Yesil' 'Siyah' 'Kahverengi' 'Beyaz' \n\n";
		cout << "1)Sepete Ekle\n2)Geri Don\nLutfen ilerlemek icin seciniz:";
		cin >> secim;
		if (secim == 1)
		{
			cout << "\nLutfen Beden Seciniz:"; cin >> beden;
			cout << "\nLutfen Renk Seciniz:"; cin >> renk;
			*(pantolon[decision - 1].boyut) = beden;
			*(pantolon[decision - 1].renk) = renk;
			sepet.push_back(pantolon[decision - 1]);

			cout << "\nSepete Eklendi."; this_thread::sleep_for(std::chrono::milliseconds(1500)); system("cls"); MusteriGirisi::pantolon_kategori();
		}
		if (secim == 2) { system("cls"); MusteriGirisi::pantolon_kategori(); }
		break;
	case 2:system("cls");
		MusteriGirisi::sepet_alisveris(); break;

	case 3:system("cls");
		MusteriGirisi::kiyafet_kategori(); break;
	default: {
		cout << "Lutfen secenekleri seciniz !!";
		this_thread::sleep_for(std::chrono::milliseconds(2000));
		system("cls");
		MusteriGirisi::pantolon_kategori(); break; }


	}

}

void MusteriGirisi::gomlek_kategori()
{
	for (int i = 0; i < gomlek.size(); i++)
	{
		cout << i + 1 << ")" << endl <<
			"Kiyafet Adi:" << *(gomlek[i].kiyafet_adi) << endl <<
			"Fiyat:" << *(gomlek[i].fiyat) << endl <<
			"---------------------------------------" << endl;

	}
	int secim;
	int decision = 0;
	string beden, renk;
	cout << "\n\n1)Devam Et \n2)Sepete Git\n3)Geri Don\nSeciniz:";
	cin >> decision;
	switch (decision)
	{
	case 1:
		cout << "\n\nUrun Seciniz:";
		cin >> decision;
		system("cls");
		cout << "Kiyafet Adi:" << *(gomlek[decision - 1].kiyafet_adi) << endl
			<< "Fiyat:" << *(gomlek[decision - 1].fiyat) << endl
			<< "Boyut: 'S' 'M' 'L' 'XL' 'XXL' \nRenk: 'Mavi' 'Kirmizi' 'Yesil' 'Siyah' 'Kahverengi' 'Beyaz' \n\n";
		cout << "1)Sepete Ekle\n2)Geri Don\nLutfen ilerlemek icin seciniz:";
		cin >> secim;
		if (secim == 1)
		{
			cout << "\nLutfen Beden Seciniz:"; cin >> beden;
			cout << "\nLutfen Renk Seciniz:"; cin >> renk;
			*(gomlek[decision - 1].boyut) = beden;
			*(gomlek[decision - 1].renk) = renk;
			sepet.push_back(gomlek[decision - 1]);

			cout << "\nSepete Eklendi."; this_thread::sleep_for(std::chrono::milliseconds(1500)); system("cls"); MusteriGirisi::gomlek_kategori();
		}
		if (secim == 2) { system("cls"); MusteriGirisi::gomlek_kategori(); }
		break;
	case 2:system("cls");
		MusteriGirisi::sepet_alisveris(); break;

	case 3:system("cls");
		MusteriGirisi::kiyafet_kategori(); break;
	default: {		cout << "Lutfen secenekleri seciniz !!";
		this_thread::sleep_for(std::chrono::milliseconds(2000));
		system("cls");
		MusteriGirisi::gomlek_kategori(); break; }

	}
}

void MusteriGirisi::ayakkabi_kategori()
{
	for (int i = 0; i < ayakkabi.size(); i++)
	{
		cout << i + 1 << ")" << endl <<
			"Kiyafet Adi:" << *(ayakkabi[i].kiyafet_adi) << endl <<
			"Fiyat:" << *(ayakkabi[i].fiyat) << endl <<
			"---------------------------------------" << endl;

	}
	int secim;
	int decision = 0;
	string beden, renk;
	cout << "\n\n1)Devam Et \n2)Sepete Git\n3)Geri Don\nSeciniz:";
	cin >> decision;
	switch (decision)
	{
	case 1:
		cout << "\n\nUrun Seciniz:";
		cin >> decision;
		system("cls");
		cout << "Kiyafet Adi:" << *(ayakkabi[decision - 1].kiyafet_adi) << endl
			<< "Fiyat:" << *(ayakkabi[decision - 1].fiyat) << endl
			<< "Boyut: '38' '39' '40' '41' '42' '43' '44' '45' \nRenk: 'Mavi' 'Kirmizi' 'Yesil' 'Siyah' 'Kahverengi' 'Beyaz' \n\n";
		cout << "1)Sepete Ekle\n2)Geri Don\nLutfen ilerlemek icin seciniz:";
		cin >> secim;
		if (secim == 1)
		{
			cout << "\nLutfen Beden Seciniz:"; cin >> beden;
			cout << "\nLutfen Renk Seciniz:"; cin >> renk;
			*(ayakkabi[decision - 1].boyut) = beden;
			*(ayakkabi[decision - 1].renk) = renk;
			sepet.push_back(ayakkabi[decision - 1]);

			cout << "\nSepete Eklendi."; this_thread::sleep_for(std::chrono::milliseconds(1500)); system("cls"); MusteriGirisi::ayakkabi_kategori();
		}
		if (secim == 2) { system("cls"); MusteriGirisi::ayakkabi_kategori(); }break;
	case 2:system("cls");
		MusteriGirisi::sepet_alisveris(); break;
	case 3:system("cls");
		MusteriGirisi::kiyafet_kategori(); break;
	default: {
		cout << "Lutfen secenekleri seciniz !!";
		this_thread::sleep_for(std::chrono::milliseconds(2000));
		system("cls");
		MusteriGirisi::ayakkabi_kategori(); break; }

	}

}

void MusteriGirisi::sepet_alisveris()
{
	/////////////////// Sepet Kısmı//////////////////////////////////////////////////////////

	string indirim;
	bool karar = true;
	string secim;
	char decision;
	cout << "Sepetiniz:\n\n";
	for (int i = 0; i < sepet.size(); i++)
	{
		cout << i + 1 << ")" << endl <<
			"Kiyafet Adi:" << *(sepet[i].kiyafet_adi) << endl <<
			"Fiyat:" << *(sepet[i].fiyat) << endl <<
			"Beden:" << *(sepet[i].boyut) << endl <<
			"Renk:" << *(sepet[i].renk) << endl <<
			"---------------------------------------" << endl;
		toplam += stoi(*(sepet[i].fiyat));

	}
	if (sepet.size() == 0) {
		cout << "Sepetiniz Bos!!";
		this_thread::sleep_for(std::chrono::milliseconds(1500));
		system("cls");
		SistemGirisi::musteri_giris();
	}
	cout << endl << "Toplam:" << toplam << endl;
	cout << "1.Sepeti Sil\n2.Devam Et\n3.Geri Don\nLutfen ilerlemek icin seciniz:";
	cin >> secim;
	decision = decision_control(secim);
	switch (decision)
	{
	case '1':
	{
		sepet.clear();
		toplam = 0;
		cout << "Sepet Silindi!!!\n\n Ana Menuye donuluyor!!";
		this_thread::sleep_for(std::chrono::milliseconds(1500));
		system("cls");
		SistemGirisi::musteri_giris();

	}
	case '2': break;
	case '3': {
		cout << "Ana Menuye donuluyor!!";
		this_thread::sleep_for(std::chrono::milliseconds(1500));
		system("cls");
		toplam = 0;
		SistemGirisi::musteri_giris();
		break;
	}
	default:
		toplam = 0;
		system("cls");
		MusteriGirisi::sepet_alisveris();
		break;
	}

	secim.clear();

	do {
		cout << "\nKupon Kullanmak Istiyormusunuz?\n1)Evet\n2)Hayir\n\nLutfen Seciniz:";
		cin >> secim;
		char decision = decision_control(secim);
		if (decision == '1') {
			cout << "\nKupon Giriniz:";
			cin >> indirim;
			for (int i = 0; i < discount_coupon.size(); i++)
			{
				if (indirim == discount_coupon[i]) {
					cout << "Kupon Uygulandı !!";
					toplam = toplam - discount_price[i];
					karar = false;
				}
			}
			if (karar) cout << "Tanimsiz Kupon!!";
		}
		if (decision == '2') { karar = false; }

	} while (karar);

	cout << endl << "Toplam:" << toplam << endl;

	cout << "Sepeti Onayliyormusunuz?\n1)Evet\n2)Geri Don\n\nSecim Yapiniz:";
	cin >> secim;
	char decision1 = decision_control(secim);
	switch (decision1) {
	case '1': {system("cls"); MusteriGirisi::fatura_olustur(); break; }
	case '2': {system("cls"); toplam = 0; MusteriGirisi::kiyafet_kategori(); break; }
	default: {system("cls"); MusteriGirisi::sepet_alisveris(); break; }
	}
}

void MusteriGirisi::siparis_takip()
{
	time_t now = time(0);
	tm* timeinfo = localtime(&now);
	Zaman kontrol{};
	kontrol.saat= timeinfo->tm_hour;
	kontrol.dakika = timeinfo->tm_min;
	Zaman ulasim{};

	cout.fill(' ');
	cout << setw(15)<< left << "Siparis No"
		<< setw(15) << left << "Kurye No"
		<< setw(20) << left << "Varis Noktasi"
		<< setw(25) << left << "Siparis Baslagic Zamani"
		<< setw(10) << left << "Sure"
		<< setw(25) << left << "Siparis Teslim Tarihi" 
		<<"Teslim Durumu" << endl<<endl;

	fstream tin;
	string user;
	Kurye temp;
	Siparis siparis;
	VarisZaman varis;
	Zaman sure= varis.decidetime(adres);
	string str = to_string(sure.saat) + ":" + to_string(sure.dakika);


	tin.open("fatura.txt", ios::in);
	int count = 0;int count2 = 1; int a = 0;

	vector<string> row;
	string line, word;

	while (!tin.eof())
	{
		row.clear();
		getline(tin, line);
		stringstream s(line);
		while (getline(s, word, '$')) {
			row.push_back(word);

		}

		if (row.size() > 0)
		{
			count++;
			user = row[0];
			if (username == user)
			{
				for (int i = 0; i < kuryeler.size(); i++)
				{
					if (stoi(row[4]) == kuryeler[i].siparis_numaralari)
					{
						a = i;
						break;
					}
				}
				ulasim.saat = stoi(row[2].substr(0, 2));
				ulasim.dakika= stoi(row[2].substr(3, 2));

				cout<< setw(15) << left << row[4];
				cout << setw(15) << left << kuryeler[a].kurye_no;
				cout<< setw(20)	<< left << adres;
				cout<< setw(25) << left << row[1];
				cout <<setw(10)<<left << str;
				cout <<setw(25)<<left << row[2];
				if (kontrol >=ulasim )cout <<left<< "Teslim Edildi."<<endl;
				else cout <<left<< "Yolda."<<endl;
			}

		}
	}

	tin.close();

	if (count == 0) cout << "Siparis Bulunamadi.";

	cout << "\n\nGeri Donmek icin 1 Tuslayiniz  !!!" << endl;
	string secim;
	cin >> secim;
	char decision = decision_control(secim);
	

	if (decision == '1') { system("cls"); SistemGirisi::musteri_giris(); }

	system("cls");
	MusteriGirisi::siparis_takip();
}

void MusteriGirisi::sikayet_öneri()
{
	fstream dosya1;
	string* sikayet = new string;
	system("cls");
	dosya1.open("sikayet.txt", ios::out | ios::in | ios::app);
	cout << "Lutfen Sikayetiniz Giriniz:";
	cin.ignore();
	getline(cin, *(sikayet));
	dosya1 << *(sikayet) << '$' << endl;
	cout << "Sikayetiniz alinmistir...." << endl << "Ana menuye yonlendiriliyorsunuz......";
	this_thread::sleep_for(std::chrono::milliseconds(3000));
	system("cls");
	SistemGirisi::musteri_giris();

}

void MusteriGirisi::sifre_degistir()
{
	fstream user;
	fstream temp;
	Kullanici tempuser;

	user.open("kullanicilar.txt", ios::in);
	temp.open("temp.txt", ios::out);

	int count = 0;

	vector<string> row;
	string line, word;

	while (!user.eof())
	{
		row.clear();

		getline(user, line);

		// used for breaking words
		stringstream s(line);

		while (getline(s, word, '$'))
		{

			row.push_back(word);
			if (row.size() == 7)break;
		}
		if (row.size() > 0) {
			*(tempuser.ad_soyad) = row[0];
			*(tempuser.eposta) = row[1];
			*(tempuser.tel_no) = row[2];
			*(tempuser.dtarihi) = row[3];
			*(tempuser.adres_ilce) = row[4];
			*(tempuser.kullanici_adi) = row[5];
			*(tempuser.sifre) = row[6];


			if (*(tempuser.kullanici_adi) == username)
			{
				count++;
				string pass;
				cout << "Yeni Sifreyi Giriniz:";
				cin.ignore();
				getline(cin, *(tempuser.sifre));
				pass = *(tempuser.sifre);

				while (pass.size() < 6)
				{
					cout << "Lutfen 6 karakterden buyuk sifre giriniz:" << endl;
					cout << "Yeni Sifreyi Giriniz:";
					getline(cin, *(tempuser.sifre));
					pass = *(tempuser.sifre);

				}

				password = *(tempuser.sifre);
				temp << *(tempuser.ad_soyad) <<
					"$" << *(tempuser.eposta) <<
					"$" << *(tempuser.tel_no) <<
					"$" << *(tempuser.dtarihi) <<
					"$" << *(tempuser.adres_ilce) <<
					"$" << *(tempuser.kullanici_adi) <<
					"$" << *(tempuser.sifre) << endl;

			}

			else
			{
				temp << *(tempuser.ad_soyad) <<
					"$" << *(tempuser.eposta) <<
					"$" << *(tempuser.tel_no) <<
					"$" << *(tempuser.dtarihi) <<
					"$" << *(tempuser.adres_ilce) <<
					"$" << *(tempuser.kullanici_adi) <<
					"$" << *(tempuser.sifre) << endl;
			}
		}



		


	}
	user.close();
	temp.close();
	remove("kullanicilar.txt");

	user.open("kullanicilar.txt", ios::out);
	temp.open("temp.txt", ios::in);
	int  count2 = 0;

	string line2,word2;

	while (!temp.eof())
	{
		row.clear();
		getline(temp, line2);

		// used for breaking words
		stringstream s(line2);
		
		while (getline(s, word2, '$'))
		{
			row.push_back(word2);
			if (row.size() == 7)break;
		}

		if (row.size() > 0)
		{
			count2++;
			*(tempuser.ad_soyad) = row[0];
			*(tempuser.eposta) = row[1];
			*(tempuser.tel_no) = row[2];
			*(tempuser.dtarihi) = row[3];
			*(tempuser.adres_ilce) = row[4];
			*(tempuser.kullanici_adi) = row[5];
			*(tempuser.sifre) = row[6];

			user << *(tempuser.ad_soyad) <<
				"$" << *(tempuser.eposta) <<
				"$" << *(tempuser.tel_no) <<
				"$" << *(tempuser.dtarihi) <<
				"$" << *(tempuser.adres_ilce) <<
				"$" << *(tempuser.kullanici_adi) <<
				"$" << *(tempuser.sifre) <<endl;
		}

	}
	temp.close();
	user.close();
	remove("temp.txt");
	cout << "\n basarili !!  \nAna menuye donuluyor !!";
	this_thread::sleep_for(std::chrono::milliseconds(3000));
	system("cls");
	SistemGirisi::musteri_giris();
}

void MusteriGirisi::fatura_olustur()
{

	time_t now = time(0);
	tm* timeinfo = localtime(&now);
	Siparis siparis; siparis.siparis_no = 1;
	VarisZaman varis;
	Zaman ulasim{};
	siparis.siparis_baslangic.saat = timeinfo->tm_hour;
	siparis.siparis_baslangic.dakika = timeinfo->tm_min;

	//////////////////////siparis no için/////////////////////////////////////////////////////////////////////////////////////
	fstream  tin;
	tin.open("fatura.txt", ios::in);
	vector<string> row;
	string line, word;
	while (!tin.eof())
	{
		row.clear();
		// read an entire row and
		// store it in a string variable 'line'
		getline(tin, line);

		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (getline(s, word, '$')) {
			row.push_back(word);
			if (row.size() == 6)
				break;
		}

		// Print the found data
		if (row.size() > 0)
		{
			siparis.siparis_no = stoi(row[4]) + 1;
		}
	}
	tin.close();

	///////////////////////////////////////////////Kurye Atama////////////////////////////////////////////////////////////

	Kurye atama;
	int karar{};
	bool a = false;

	for (int i = 1; i < kuryeler.size(); i++)
	{
		if (kuryeler[0].dagitim_bitisler <= siparis.siparis_baslangic)
		{
			a = false;
			karar = 0;
			break;
		}

		if (kuryeler[i].dagitim_bitisler <= siparis.siparis_baslangic)
		{
			a = false;
			karar = i;
			break;
		}

		if (kuryeler[i].dagitim_bitisler <= kuryeler[0].dagitim_bitisler)
		{
			a = true;
			karar = i;
		}

	}

	if (a)
	{
		siparis.siparis_ulasim = varis.decidetime(adres) + kuryeler[karar].dagitim_bitisler;
	}
	else
	{
		siparis.siparis_ulasim = varis.decidetime(adres) + siparis.siparis_baslangic;
	}

	kuryeler[karar].siparis_numaralari = siparis.siparis_no;
	kuryeler[karar].dagitim_bitisler = siparis.siparis_ulasim;

	cout <<"Kurye Ad:" << *(kuryeler[karar].ad_soyad) << endl;
	cout << "Kurye No:" << kuryeler[karar].kurye_no << endl;

	/////////////////////////////////////////////////// Fatura Bastırma ///////////////////////////////////////////////////
	cout << "Faturaniz\n\nMusteri Adi:" << username
		<< "\nSiparis No:" << siparis.siparis_no
		<< "\nUrun Siparis Zamani:" << siparis.siparis_baslangic
		<< "\nUrun Bilgileri\n";

	for (int i = 0; i < sepet.size(); i++)
	{
		cout << i + 1 << ")" << endl <<
			"Kiyafet Adi:" << *(sepet[i].kiyafet_adi) << endl <<
			"Fiyat:" << *(sepet[i].fiyat) << endl <<
			"Beden:" << *(sepet[i].boyut) << endl <<
			"Renk:" << *(sepet[i].renk) << endl <<
			"---------------------------------------" << endl;
	}


	siparis.siparis_fiyat = toplam;
	cout << "Toplam:" << toplam;



	///////////////////////////// faturayı dosyaya yazma ///////////////////////////////////////////////////////////////////////

	fstream dosya;
	dosya.open("fatura.txt", ios::out | ios::in | ios::app);
	dosya.setf(ios::left);


	dosya << username <<
		"$" << siparis.siparis_baslangic <<
		"$" << siparis.siparis_ulasim <<
		"$" << adres <<
		"$" << siparis.siparis_no <<
		"$" << siparis.siparis_fiyat << endl;
	dosya.close();

	sepet.clear();
	int geri;
	cout << "\nGeri Icin 1 tuslayiniz!!!";
	cin >> geri;
	switch (geri)
	{
	case 1: {system("cls"); SistemGirisi::musteri_giris(); break; }
	default:
		system("cls");
		SistemGirisi::musteri_giris();
		break;
	}


}

void MusteriGirisi::kuponlarim()
{
	int secim;
	cout << "Kuponlarim" << endl;

	for (int i = 0; i < discount_coupon.size(); i++)
	{
		cout << setw(15)<< discount_coupon[i] << endl;
		cout << "--------------------" << endl;

	}

	if (discount_coupon.size() == 0) {
		cout << "Kuponunuz Bulunmamaktadir.\n";
		this_thread::sleep_for(std::chrono::milliseconds(1500));
		system("cls");
		SistemGirisi::musteri_giris();
	}

	cout << "\n1)Geri Don\n Lutfen Secim Yapiniz:";
	cin >> secim;
	if (secim == 1) { system("cls"); SistemGirisi::musteri_giris(); }
	else { system("cls"); MusteriGirisi::kuponlarim(); }



}



///////////////////////////////////////////  EMAİL CHECK AND ZAMAN OPERATOR OVERLOADİNG ////////////////////////////////////////////////////

ostream& operator<<(ostream& output, Zaman& zaman)
{
	output << setw(2) << setfill('0') <<right << zaman.saat << ":" << setw(2)<< setfill('0')<<right<< zaman.dakika;
	return output;
}

bool Email_check(string email)
{
	const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return regex_match(email, pattern);
}


//////////////////////////////////////  KIYAFET CLASSI /////////////////////////////////////////////////////////

Kiyafet::Kiyafet()
{
	kategori = new string;
	kiyafet_adi = new string;
	fiyat = new string;
	boyut = new string;
	renk = new string;
}

void Kiyafet::kiyafet_bilgigir()
{
	cout << "Kategori giriniz: ";
	cin.ignore();
	getline(cin, *(this->kategori));

	cout << "Kiyafet adini giriniz: ";

	getline(cin, *(this->kiyafet_adi));

	cout << "Kiyafetin fiyatini giriniz: ";

	getline(cin, *(this->fiyat));

	cout << "Kiyafetin boyutunu giriniz:  ";

	getline(cin, *(this->boyut));

	cout << "Kiyafetin rengini giriniz:  ";

	getline(cin, *(this->renk));

	cout << "Kayit islemi basari ile tamamlandi." << endl << " Menuye donuluyor...";
	this_thread::sleep_for(std::chrono::milliseconds(2000));
	system("cls");
}




///////////////////////// YONETICI GİRİSİ (GİRİS YAPILDI İSE BURAYA YÖNLENDİR )//////////////////////////////////

void YoneticiGirisi::urun_girisi()
{
	Kiyafet user{};
	user.kiyafet_bilgigir();
	fstream dosya;
	dosya.open("kiyafet.txt", ios::out | ios::in | ios::app);
	dosya.setf(ios::left);
	dosya << *(user.kategori) <<
		"$" << *(user.kiyafet_adi) <<
		"$" << *(user.fiyat) <<
		"$" << *(user.boyut) <<
		"$" << *(user.renk) << endl;

	dosya.close();
	SistemGirisi::yonetici_giris();
}

void YoneticiGirisi::kurye_ekle()
{
	Kurye user{};
	user.kurye_bilgigir();
	fstream fin;
	fin.open("kurye.txt", ios::out | ios::in | ios::app);
	fin.setf(ios::left);
	vector<string> row;
	string line, word;

	while (!fin.eof())
	{
		row.clear();


		getline(fin, line);


		stringstream s(line);

		while (getline(s, word, '$'))
		{

			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}

		// Print the found data
		if (row.size() > 0)
		{
			user.kurye_no = stoi(row[2]) + 1;
		}

	}
	fin.close();
	fin.open("kurye.txt", ios::out | ios::in | ios::app);
	fin.setf(ios::left);

	fin << *(user.ad_soyad) 
		<< "$" << *(user.tel_no) 
		<< "$" << user.kurye_no 
		<< "$" << setw(2) << right << setfill('0') << user.dagitim_bitisler.saat 
		<< "$" << setw(2) << right << setfill('0') << user.dagitim_bitisler.dakika 
		<< "$" << user.siparis_numaralari << endl;
	fin.close();
	kuryeler.push_back(user);
	SistemGirisi::yonetici_giris();

}

void YoneticiGirisi::kullanıcı_indirim()
{

	fstream fin;

	// Open an existing file
	fin.open("kullanicilar.txt", ios::in | ios::out);

	// Get the roll number
	// of which the data is required
	int  count = 0;
	int count2 = 0;
	string indirim_tutari;

	vector<Kullanici>users;

	// Read the Data from the file
	// as String Vector
	vector<string> row;
	string  line,word;

	while (!fin.eof())
	{
		row.clear();
		getline(fin, line);

		// used for breaking words

		stringstream s(line);
		while (getline(s, word, '$')) {

			row.push_back(word);
			if (row.size() == 7)
				break;
		}

		// Print the found data
		if (row.size() > 0) {
			count++;
			Kullanici tempuser;
			*(tempuser.ad_soyad) = row[0];
			*(tempuser.eposta) = row[1];
			*(tempuser.tel_no) = row[2];
			*(tempuser.dtarihi) = row[3];
			*(tempuser.adres_ilce) = row[4];
			*(tempuser.kullanici_adi) = row[5];
			*(tempuser.sifre) = row[6];

			cout << count2 + 1 << ".)Adi Soyadi:" << *(tempuser.ad_soyad) << endl;
			cout << "Kullanici Adi:" << *(tempuser.kullanici_adi) << endl;
			cout << "Sifre:" << *(tempuser.sifre) << endl << endl;

			count2++;
			users.push_back(tempuser);
		}




	}
	fin.close();

	cout << "Lutfen indirim kodu vermek istediginiz Kullaniciyi secin: ";
	int secim;
	cin >> secim;
	cout << "Indirim kuponunu giriniz :";
	string kupon;
	cin.ignore();
	getline(cin, kupon);
	cout << "\nIndirim tutarini  giriniz:";
	cin >> indirim_tutari;
	secim -= 1;

	*(users[secim].indirim_kodu) = kupon;

	fstream dosya;

	dosya.open("kuponlar.txt", ios::out | ios::in | ios::app);
	dosya.setf(ios::left);

	dosya << *(users[secim].ad_soyad) << "$" <<
		*(users[secim].kullanici_adi) << "$" <<
		*(users[secim].sifre) << "$" << *(users[secim].indirim_kodu) << "$" << (indirim_tutari) << endl;
	dosya.close();
	users.clear();
	system("cls");
	SistemGirisi::yonetici_giris();

}

void YoneticiGirisi::fatura_görüntüle()
{
	fstream tin;
	string user, siparisno, siparisbaslangic, siparisbitis, adres1, fiyat;

	tin.open("fatura.txt", ios::in);

	int count = 0;
	int count2 = 1;

	vector<string> row;
	string line, word;

	while (!tin.eof())
	{
		row.clear();
		getline(tin, line);
		stringstream s(line);

		while (getline(s, word, '$')) {
			row.push_back(word);
		}

		if (row.size() > 0)
		{
			count++;
			user = row[0];
			siparisbaslangic = row[1];
			siparisbitis = row[2];
			adres1 = row[3];
			siparisno = row[4];
			fiyat = row[5];

			cout << count2 << "." << endl << "Kullanici Adi:" << user << endl;
			cout << "Siparis No:" << siparisno << endl;
			cout << "Siparis Baslangic:" << siparisbaslangic << endl;
			cout << "Siparis Bitis:" << siparisbitis << endl;
			cout << "Adres:" << adres1 << endl;
			cout << "Siparis Toplam:" << fiyat << endl << endl;
			count2++;
		}
	}
	tin.close();

	if (count == 0) cout << "Kayit bulunamadi.";

	cout << "Geri Donmek icin 1 Tuslayiniz  !!!" << endl;
	int secim;
	cin >> secim;

	if (secim == 1) { system("cls"); SistemGirisi::yonetici_giris(); }

	system("cls");
	YoneticiGirisi::fatura_görüntüle();
}


///////////////////////////////// ZAMAN SINIFI OPERATORLERİ //////////////////////////////////////////////////////

Zaman& Zaman::operator+(Zaman& zaman)
{

	if (dakika + zaman.dakika >= 60) { saat = saat + zaman.saat + 1; dakika = (dakika + zaman.dakika) - 60; return *this; }
	saat = saat + zaman.saat; dakika = dakika + zaman.dakika;
	return *this;
}

bool Zaman::operator>=(Zaman& zaman)
{
	if (saat > zaman.saat) return true;

	if (saat == zaman.saat) {
		if (dakika >= zaman.dakika) return true;

		return false;
	}

	return false;
}

bool Zaman::operator<=(Zaman& zaman)
{
	if (saat < zaman.saat) return true;

	if (saat == zaman.saat) {
		if (dakika <= zaman.dakika) return true;

		return false;
	}

	return false;
}

Zaman& Zaman::operator=(Zaman& zaman)
{

	saat = zaman.saat;
	dakika = zaman.dakika;

	return *this;
}

bool Zaman::operator==(Zaman& zaman)
{

	if (saat = zaman.saat)
	{
		if (dakika = zaman.dakika) return true;
	}


	return false;
}



/////////////////////////////// VARIS NOKTASI ZAMAN SURELERİ ////////////////////////////////////////////////////

VarisZaman::VarisZaman()
{
	Ortahisar.saat = 00;
	Ortahisar.dakika = 35;

	Akcaabat.saat = 00;
	Akcaabat.dakika = 50;

	Vakfikebir.saat = 01;
	Vakfikebir.dakika = 30;

	Besikduzu.saat = 01;
	Besikduzu.dakika = 50;

	Yomra.saat = 00;
	Yomra.dakika = 55;

	Arsin.saat = 01;
	Arsin.dakika = 10;

	Arakli.saat = 01;
	Arakli.dakika = 40;

}

Zaman VarisZaman::decidetime(string a)
{
	if (a == "Ortahisar" || a == "ortahisar") return Ortahisar;
	if (a == "Arakli" || a == "arakli") return Arakli;
	if (a == "Besikduzu" || a == "besikduzu") return Besikduzu;
	if (a == "Yomra" || a == "yomra") return Yomra;
	if (a == "Akcaabat" || a == "akcaabat") return Akcaabat;
	if (a == "Arsin" || a == "arsin") return Arsin;
	if (a == "Vakfikebir" || a == "vakfikebir") return Vakfikebir;
}

///////////////////////////////// KULLANICI SİSTEME GİRİNCE KUPONLARI TANIMLAMA /////////////////////////////////

void kullanici_kupon_atama()
{
	////////////////////////KUPON KONTROL KISMI///////////////////////////////////////////
	fstream tin;
	Kullanici tempuser;
	// Open an existing file
	tin.open("kuponlar.txt", ios::in);

	// Get the roll number
	// of which the data is required
	int count = 0;
	string indirim_tutari;
	// Read the Data from the file
	// as String Vector
	vector<string> row;
	string line, word;

	while (!tin.eof())
	{
		row.clear();

		// read an entire row and
		// store it in a string variable 'line'
		getline(tin, line);

		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (getline(s, word, '$')) {

			// add all the column data
			// of a row to a vector
			row.push_back(word);

		}

		// Print the found data
		if (row.size() > 0) {
			count++;
			*(tempuser.ad_soyad) = row[0];
			*(tempuser.kullanici_adi) = row[1];
			*(tempuser.sifre) = row[2];
			*(tempuser.indirim_kodu) = row[3];
			indirim_tutari = row[4];

			if (*(tempuser.kullanici_adi) == username) {
				
				
					discount_coupon.push_back(*(tempuser.indirim_kodu));
					discount_price.push_back(stoi(indirim_tutari));


				
			}
		}

	}

	tin.close();
}

/////////////////////////////////// KURYE CLASSI ////////////////////////////////////////////////////////////////

Kurye::Kurye()
{
	ad_soyad = new string;
	tel_no = new string;
	dagitim_bitisler.saat = 0;
	dagitim_bitisler.dakika = 0;
	siparis_numaralari = 0;
	kurye_no = 1;

}

void Kurye::kurye_bilgigir()
{
	cout << "Ad Soyad:";
	cin.ignore();
	getline(cin, *(this->ad_soyad));

	cout << "Tel No:";
	getline(cin, *(this->tel_no));

	cout << "Kayit islemi basari ile tamamlandi." << endl << "Ana menuye donuluyor...";
	this_thread::sleep_for(std::chrono::milliseconds(2000));
	kurye_no = 1;
	system("cls");

}

void kuryeleri_dosyadan_cekis()
{

	fstream fin;
	fin.open("kurye.txt", ios::out | ios::in | ios::app);
	fin.setf(ios::left);
	vector<string> row;
	string line, word;

	while (!fin.eof())
	{
		row.clear();


		getline(fin, line);


		stringstream s(line);

		while (getline(s, word, '$'))
		{

			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}

		// Print the found data
		if (row.size() > 0)
		{
			Kurye user{};
			*(user.ad_soyad) = row[0];
			*(user.tel_no) = row[1];
			user.kurye_no = stoi(row[2]);
			user.dagitim_bitisler.saat = stoi(row[3]);
			user.dagitim_bitisler.dakika = stoi(row[4]);
			user.siparis_numaralari = stoi(row[5]);
			kuryeler.push_back(user);
		}

	}
	fin.close();
}


char decision_control(string deneme) 
{
	char a='0';
	if (deneme.size() > 1) return a;

	if (deneme.size() == 1) {
		a = deneme[0]; 
		return a;
	}

	return a;
}