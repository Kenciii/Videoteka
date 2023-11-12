#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

// enumeracija vrsta filma
enum Vrsta { komedija = 1, akcija, drama, horor };

// struktura film
struct Film {
	int id;
	string naziv;
	Vrsta vrsta;
};

// struktura osoba
struct Osoba {
	int id;
	string ImePrezime;
	bool aktivan;
};

// struktura izdato
struct Izdato {
	int id;
	int idFilm;
	int idOsoba;
};

// struktura videoteka
struct Videoteka {
	string naziv;
	vector<Film>filmovi;
	vector<Osoba>korisnici;
	vector<Izdato>izdati;
	float cijenaFilma;
};

// funkcija za unos filma
void unosFilma(Videoteka& v, Film& f) {
	int br;
	cout << "Unesi id filma: ";
	cin >> f.id;
	cout << "Unesi naziv filma: ";
	cin.ignore();
	getline(cin, f.naziv);
	cout << "Unesi vrstu filma: (1-komedija, 2-akcija, 3-drama, 4-horor)"<<endl;
	cin >> br;
	if (br == 1) f.naziv = komedija;
	else if (br == 2) f.naziv = akcija;
	else if (br == 3) f.naziv = drama;
	else if (br == 4) f.naziv = horor;
	v.filmovi.push_back(f);
}

// funkcija za unos korisnika
void unosKorisnika(Videoteka& v, Osoba& o) {
	cout << "Unesi id osobe: ";
	cin >> o.id;
	cout << "Unesi ime i prezime korisnika: ";
	cin.ignore();
	getline(cin, o.ImePrezime);
	int s;
	cout << "Unesite status osobe, 0 za neaktivan, 1 za aktivan: ";
	cin >> s;
	if (s == 0) o.aktivan = false;
	else if (s == 1) o.aktivan = true;
	v.korisnici.push_back(o);

}

// funkcija za pretragu filmova po vrsti
void pretragaFilmaVrsta(Videoteka& v, Vrsta vrsta) {
	for (int i = 0; v.filmovi.size(); i++) {
		if (v.filmovi[i].vrsta == vrsta) {
			cout << v.filmovi[i].naziv << endl;
		}
		else cout << "Nema filmova te vrste u videoteci." << endl;
	}
}

// funkcija za izdavanje filmova
void izdatiFilm(Videoteka& v) {
	int idFilma, idOsobe;
	Izdato izdato;
	cout << "Unesite id filma: ";
	cin >> idFilma;
	cout << "Unesite id osobe: ";
	cin >> idOsobe;
	izdato.id = v.izdati.size() + 1;
	izdato.idFilm = idFilma;
	izdato.idOsoba = idOsobe;
	v.izdati.push_back(izdato);
}

// funkcija za popis izdatih filmova
int popisIzdatihFilmova(Videoteka& v) {
	if (v.izdati.size() == 0) {
		cout << "Nema izdatih filmova! " << endl;
		return 0;
	}
	for (int i=0; i < v.izdati.size(); i++) {
		for (int j=0; j < v.filmovi.size(); j++) {
			if (v.izdati[i].idFilm == v.filmovi[j].id) {
				for (int k=0; k < v.korisnici.size(); k++) {
					if (v.izdati[i].idOsoba == v.korisnici[k].id) {
						cout << v.filmovi[j].naziv << " - " << v.korisnici[k].ImePrezime << endl;
					}
				}
			}
		}
	}
	return v.izdati.size();

}

// rekurzivna funkcija za racunanje zakasnine
float projekcijaZakasnine(int n, float cijena) {
	if (n == 0) {
		return cijena;
	}
	if (n % 5 == 0) {
		cijena += cijena * 0.1;
	}
	return projekcijaZakasnine(n - 1, cijena);
}

// funkcija za ispis filmova
void ispisFilma(Film& f) {
	cout << "ID filma: " << f.id << endl;
	cout << "Naziv filma: " << f.naziv << endl;
	cout << "Vrsta filma: " << f.vrsta << endl;
}

// funkcija za ispis osoba
void ispisOsoba(Osoba& o) {
	cout << "ID osobe: " << o.id << endl;
	cout << "Ime i prezime : " << o.ImePrezime << endl;
	cout << "Status: " << o.aktivan << endl;
}

// funkcija za ispis izdatih filmova
void ispisIzdato(Izdato& i) {
	cout << "ID: " << i.id << endl;
	cout << "ID filma: " << i.idFilm << endl;
	cout << "ID osobe: " << i.idOsoba << endl;
}

// funkcija za ispis videoteke
void ispisVideoteke(Videoteka& v) {
	cout << "Naziv filma: " << v.naziv << endl;
	cout << "Cijena filma: " << v.cijenaFilma << endl;
	cout << "Filmovi: " << endl;
	for (int i = 0; i < v.filmovi.size(); i++) {
		ispisFilma(v.filmovi[i]);
	}
	cout << "Korisnici: " << endl;
	for (int i = 0; i < v.korisnici.size(); i++) {
		ispisOsoba(v.korisnici[i]);
	}
	cout << "Izdato: " << endl;
	for (int i = 0; i < v.izdati.size(); i++) {
		ispisIzdato(v.izdati[i]);
	}
}

// funkcija za upis filma u .txt datoteku
void upisFilma(Film& f) {
	fstream upis;
	upis.open("filmovi.txt", ios::app);
	upis << f.id << endl;
	upis << f.naziv << endl;
	if (f.vrsta == 1) upis << "komedija" << endl;
	else if (f.vrsta == 2) upis << "akcija" << endl;
	else if (f.vrsta == 3) upis << "drama" << endl;
	else if (f.vrsta == 4) upis << "horor" << endl;

	upis.close();
}

// funkcija za upis osobe u .txt datoteku
void upisOsobe(Osoba& o) {
	ofstream upis;
	upis.open("korisnici.txt", ios::app);
	upis << o.id << endl;
	upis << o.ImePrezime << endl;
	upis << o.aktivan << endl;

	upis.close();
}

// funkcija za upis izdatog u .txt datoteku
void upisIzdato(Izdato& i) {
	fstream upis;
	upis.open("izdati.txt", ios::app);
	upis << i.id << endl;
	upis << i.idFilm << endl;
	upis << i.idOsoba << endl;

	upis.close();

}

int main() {
	Film film;
	Osoba osoba;
	Izdato izdato;
	Videoteka videoteka;

	// citanje iz datoteke
	fstream films;
	films.open("filmovi.txt", ios::in);
	string podatak;
	Film temp;
	string vrsta;
	while (films >> temp.id >> temp.naziv >> vrsta) {
		if (vrsta == "akcija")  temp.vrsta = akcija;
		else if (vrsta == "komedija") temp.vrsta = komedija;
		else if (vrsta == "drama") temp.vrsta = drama;
		else if (vrsta == "horor") temp.vrsta = horor;

		videoteka.filmovi.push_back(temp);
	}
	films.close();

	int izbor;
	cout << "Unesite naziv videoteke: ";
	cin.ignore();
	getline(cin, videoteka.naziv);
	cout << "Unesite cijenu filma: ";
	cin >> videoteka.cijenaFilma;
	do {
		cout << "1. Unos filma" << endl;
		cout << "2. Unos korisnika" << endl;
		cout << "3. Pretraga filma po vrsti" << endl;
		cout << "4. Izdati film" << endl;
		cout << "5. Popis izdatih filmova" << endl;
		cout << "6. Projekcija zakasnine" << endl;
		cout << "7. Ispis videoteke" << endl;
		cout << "8. Kraj" << endl;
		cout << "Izbor: "<<endl;
		cin >> izbor;
		switch (izbor) {
		case 1:
			unosFilma(videoteka, film);
			upisFilma(film);
			break;
		case 2:
			unosKorisnika(videoteka, osoba);
			upisOsobe(osoba);
			break;
		case 3:
			int vrsta;
			cout << "Unesite vrstu filma koju zelite pretraziti(1,2,3 ili 4): ";
			cin >> vrsta;
			pretragaFilmaVrsta(videoteka, (Vrsta)vrsta);
			break;
		case 4:
			izdatiFilm(videoteka);
			upisIzdato(izdato);
			break;
		case 5:
			popisIzdatihFilmova(videoteka);
			ispisIzdato(izdato);
			break;
		case 6:
			int brDana;
			cout << "Unesite broj dana kanjenja: ";
			cin >> brDana;
			cout << "Zakasnina: " << projekcijaZakasnine(brDana, videoteka.cijenaFilma) << endl;
			break;
		case 7:
			ispisVideoteke(videoteka);
			break;
		case 8:
			cout << "IZLAZ" << endl;
			break;
		default:
			cout << "Pogrešan unos!" << endl;
			break;
		}

	} while (izbor != 8);

	return 0;
}
