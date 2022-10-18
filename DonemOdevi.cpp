
#include <iostream>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;

class Zaman
{
	int saat;
	int dakika;

};

class Kiyafet
{
	char* kategori;
	int kiyafet_adi;
	double fiyat;
	char* boyut;
	char* renk;
};

class Kisi
{
public:
	string *ad_soyad;
	string *tel_no;
};

class Sipariş : public Kiyafet
{
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
	void bilgigir();
	/*Kullanici* next;*/
};

class Yonetici : public Kisi
{
	char* sifre;

};

class kurye : public Kisi
{
	Zaman* dagitim_bitisler;
	int* siparis_numaralari;

};

class  AnaMenu
{
public:
	
	static void ana_menu();
	static void sistem_giris();
	static void uye_kaydi();
};

class SistemGirisi
{	
public:

	static void musteri_giris();
	static void yonetici_giris();

};

class MusteriGirisi
{
public: 
	static void kiyafet_kategori();
	static void siparis_takip();
	static void sikayet_öneri();
	static void sifre_degistir();
	static void geri_don();

};

class YoneticiGirisi 
{
public:
	static void urun_girisi();
	static void kurye_ekle();
	static void sikayet_oku();
	static void kullanıcı_indirim();
	static void fatura_görüntüle();
	

};

//class SinglyLinkedList
//{
//public:
//	Kullanici *head;
//
//	SinglyLinkedList()
//	{
//		head = NULL;
//	}
//
//	void addBack(Kullanici *a)
//	{
//		
//		a->next = NULL;
//
//		if (head == NULL) head = a;
//		else
//		{
//			Kullanici* first = head;
//			while (first->next != NULL) first = first->next;
//			first->next = a;
//		}
//		
//	}
//	
//
//};

int main()
{
	AnaMenu AnaMenu;

	AnaMenu.ana_menu();
}

void AnaMenu :: ana_menu()
{
	int secim;
	cout << "Hosgeldiniz" << endl << "1.Sisteme Giris" << endl << "2.Kayit Ol" << endl << "3.Cikis" << endl <<endl<< "Lutfen ilerlemek icin seciniz :";
	cin >> secim;

	switch (secim)
	{
	case 1:
		system("cls");
		sistem_giris();
		break;
	case 2:
		system("cls");
		uye_kaydi();
		break;
	case 3:
		exit(EXIT_SUCCESS);
		break;
	default:
		system("cls");
		ana_menu();
	}


}
void AnaMenu :: sistem_giris()
{
	int secim;
	cout << "1.Musteri Girisi" << endl << "2.Yonetici Girisi" << endl<<endl<<"Lutfen ilerlemek icin seciniz :";
	cin >> secim;

	switch (secim)
	{
	case 1:
		system("cls");
		SistemGirisi::musteri_giris();
		break;
	case 2:
		system("cls");
		SistemGirisi::yonetici_giris();
		break;
	default:
		system("cls");
		sistem_giris();
	}

}
void AnaMenu :: uye_kaydi()
{
	Kullanici user{};
	user.bilgigir();
	//SinglyLinkedList list;
	//list.addBack(user);
	fstream dosya;
	dosya.open("kullanicilar.txt", ios::out | ios::in | ios::app);
	dosya.setf(ios::left);
	dosya << setw(15) << *(user.ad_soyad)<<
	setw(20) << *(user.tel_no )<<
	setw(20) << *(user.kullanici_adi)<<
	setw(20) << *(user.eposta)<<
	setw(20) << *(user.adres_ilce)<<
	setw(20) << *(user.sifre)<<
	setw(20) << *(user.indirim_kodu)<<
	setw(20) << *(user.dtarihi)<<endl;
	
	dosya.close();
}


void SistemGirisi::musteri_giris()
{
	int secim;
	cout << "1.Kiyafet Kategorileri" << endl << "2.Siparis Takip" << endl << "3.Sikayet/Oneriler" << endl << "4.Sifre Degistir" <<endl<< "5.Geri Don" << endl <<endl<<"Lutfen Ilerlemek Icin Secim Yapiniz:";
	cin >> secim;

	switch (secim)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:

	default:
		system("cls");
		musteri_giris();
		
	}


}
void SistemGirisi::yonetici_giris()
{
	int secim;
	cout << "1.Urun Girisi" << endl << "2.Kurye Ekle" << endl << "3.Sikayet Oku" << endl << "4.Kullanici Indirim Tanimla" << endl << "5.Fatura Goruntule" << endl << endl << "Lutfen Ilerlemek Icin Secim Yapiniz:";
	cin >> secim;

	switch (secim)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:

	default:
		system("cls");
		yonetici_giris();

	}

}
void Kullanici::bilgigir()
{

	cout << "Ad Soyad:"; 		
	cin >> *(this->ad_soyad);

	cout <<endl<<"Tel No:";			
	cin >> *(this->tel_no);

	cout <<endl<< "Kullanici Adi:";	
	cin >> *(this->kullanici_adi);

	cout << endl<< "E Posta:";
	cin >> *(this->eposta);

	cout << endl<< "Adres Ilce:";
	cin >> *(this->adres_ilce);

	cout << endl <<"Sifre:";
	cin >> *(this->sifre);

	cout << endl<<"Indirim kodu:";
	cin >> *(this->indirim_kodu);

	cout << endl<<"Dogum Tarihi:";
	cin >> *(this->dtarihi);

}
Kullanici::Kullanici()
{
	kullanici_adi=new string ;
	eposta=new string;
	adres_ilce = new string;
	sifre = new string;
	indirim_kodu = new string;
	dtarihi = new string;
	ad_soyad = new string;
	tel_no = new string;

}
