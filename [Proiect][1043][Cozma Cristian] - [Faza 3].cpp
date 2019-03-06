#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>
#include<list>
#include<map>
#include<set>
using namespace std;
#pragma warning(disable:4996)

class iChelt
{
	virtual float getSuma_x() = 0;

	virtual int get_an_x_() = 0;
};

class Client{
private:
	char* nume;
	float salarii[12];
	virtual float client_x_()
	{
		return this->sumaclient();
	}

	virtual float client_y_()
	{
		return this->sumaclient()/12;
	}

public:
	static int nrClienti;

	explicit Client(char* nume= nullptr):nume(nume)
	{
		cout << "\nApel constructor un parametru Client"; 
		if (nume != nullptr)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
		else this->nume = nullptr;
		for (int i = 0; i < 12; i++)
			this->salarii[i] = 0;
		nrClienti++;
	}

	Client(char* nume, float salarii[12])
	{
		cout << "\nApel constructor cu 2 param. Client"; 
		if (nume != nullptr)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
		else this->nume = nullptr;
		memcpy(this->salarii, salarii, 12 * sizeof(int));
		nrClienti++;
	}


	Client(const Client &c)
	{
		cout << "\n Apel constructor de copiere Client \n";
		if (c.nume != nullptr)
		{
			this->nume = new char[strlen(c.nume) + 1];
			strcpy(this->nume, c.nume);
		}
		else
			this->nume = nullptr;
		memcpy(this->salarii, c.salarii, 12 * sizeof(int));
		nrClienti++;
	}

	~Client()
	{
		cout << "\n Apel destructor Client \n";
		if (this->nume != nullptr)
			delete[] this->nume;
		nrClienti--;
	}

	char* getnume()
	{
		return nume;
	}

	void setnume(char* nume)
	{
		if (this->nume != nullptr)
			delete[] this->nume;
		if (nume != nullptr)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}

	Client& operator=(const Client& c)
	{
		if (this->nume != nullptr)
			delete[] this->nume;
		if (c.nume != nullptr)
		{
			this->nume = new char[strlen(c.nume) + 1];
			strcpy(this->nume, c.nume);
		}
		else
			this->nume = nullptr;
		memcpy(this->salarii, c.salarii, 12 * sizeof(int));

		return *this;
	}

	void numararecaractere()
	{
		cout<<"\nClientul "<< this->nume<< " are un nume format din "<<strlen(this->nume)<<" caractere.";
	}

	void modifsalariu()
	{
		unsigned luna;
		float salariul;
		cout << "Pentru ce luna vreti sa modificati salariul?: ";
		cin >> luna;
		cout << "\nIntroduceti noul salariu: ";
		cin >> salariul;
		if (luna >= 1 && luna <= 12)
		{
			if (salariul >= 0)
			{
				cout << "\nSalariul a fost modificat";
				this->salarii[luna - 1] = salariul;
			}
			else cout << "\nSalariul nu poate fi negativ";
		}
		else cout << "\nNu exista luna " << luna;
	}

	void modifnume(char* nume)
	{
		if (nume != nullptr && strlen(nume) >= 3)
		{
			delete[] this->nume;
			this->nume = new char[strlen(nume) + 1];
			//memcpy(this->nume, nume, sizeof(char)* strlen(nume));
			strcpy(this->nume, nume);
		}
		else cout << "\nNoul nume este prea scurt sau nul";
	}


	void compararecl(const Client c)
	{
		float mt = 0, mc = 0;
		for (int i = 0; i < 12; i++)
		{
			mt += this->salarii[i];
			mc += c.salarii[i];
		}
		if (mt > mc)
			cout << "\n" << this->nume << " a fost mai productiv decat " << c.nume << ".";
		else if (mt < mc)
			cout << "\n" << c.nume << " a fost mai productiv decat " << this->nume << ".";
		else
			cout << "\n" << c.nume << " si " << this->nume << " au fost la fel de productivi.";
	}

	float operator[](int x)
	{
		float sal = 0;
		for (int i = 0; i < x; i++)
			sal += this->salarii[i];
		return sal;
	}

	void operator+(float const majoraresal)
	{
		for (int i = 0; i < 12; i++)
			this->salarii[i] += majoraresal;
	}

	bool operator<(const Client c)
	{
		float salthis = 0, salc = 0;
		for (int i = 0; i < 12; i++)
		{
			salthis += this->salarii[i];
			salc += c.salarii[i];
		}
		if (salthis < salc)
			return 1;
		else return 0;
	}

	Client& operator!()
	{
		for (int i = 0; i < 12; i++)
			if (this->salarii[i] != 0)
				this->salarii[i] = 0;
		return *this;
	}

	Client& operator++() //preincrementare - se aduna 100 -> bonus de salarizare
	{
		for (int i = 0; i < 12; i++)
			this->salarii[i] += 100;
		return *this;
	}

	Client operator++(int) //postincrementare - se aduna 100 -> bonus de salarizare
	{
		Client c = *this;
		for (int i = 0; i < 12; i++)
			this->salarii[i] += 100;
		return c;
	}

	operator int()
	{
		return this->nrClienti;
	}

	float sumaclient()
	{
		float sal=0;
		for(int i=0;i<12;i++)
			sal+=this->salarii[i];
		return sal;
	}

	friend ostream& operator<<(ostream& out, Client c);
	friend istream& operator>>(istream& in, Client& c);
	friend class Files;

};

int Client::nrClienti = 0;

istream& operator >> (istream& in, Client& c)
{
	if (c.nume != nullptr)
		delete[] c.nume;
	char buffer[100];
	cout << "\nIntroduceti numele clientului: ";
	in >> buffer;
	c.nume = new char[strlen(buffer) + 1];
	strcpy(c.nume, buffer);
	for (int i = 0; i < 12; i++)
	{
		cout << "Introduceti salariul luat in luna " << i + 1 << ": ";
		in >> c.salarii[i];
	}
	return in;
}

ostream& operator<<(ostream& out, const Client c)
{
	if (c.nume != nullptr)
		out << "Numele clientului este " << c.nume;
	out << "\nSalariile pentru acest an sunt: ";
	for (int i = 0; i < 12; i++)
		out << "\nPentru luna a " << i + 1 << "-a salariul este de " << c.salarii[i] << " lei";
	return out;
}


class CrediteBancare: public iChelt
	{
	private:
		char* numeBanca;
		double dobanda;
		float sumadatorata;
		char* numeDator;
		int data[3];
	public:
		const int idCredit;
		static int nrCrediteBancare;


		CrediteBancare(char* nume=nullptr):idCredit(++nrCrediteBancare)
	{
		cout << "Apel constructor cu un parametru";
		if (nume != nullptr)
		{
			this->numeDator = new char[strlen(nume) + 1];
			strcpy(this->numeDator, nume);
		}
		else this->numeDator = nullptr;
		this->numeBanca = nullptr;
		this->dobanda = 1;
		this->sumadatorata = 0;
	}

	CrediteBancare(char* numeDator, char*numeBanca, double dobanda,  float sumadatorata, int zi,
		int luna, int an):idCredit(++nrCrediteBancare)
	{
		cout << "\nApel constructor cu toti param. CrediteBancare\n";
		if (numeBanca != nullptr)
		{
			this->numeBanca = new char[strlen(numeBanca) + 1];
			strcpy(this->numeBanca, numeBanca);
		}
		else this->numeBanca = nullptr;
		if (numeDator != nullptr)
		{
			this->numeDator = new char[strlen(numeDator) + 1];
			strcpy(this->numeDator, numeDator);
		}
		else this->numeBanca = nullptr;
		this->sumadatorata = sumadatorata;
		this->dobanda = dobanda;
		this->data[0] = zi;
		this->data[1] = luna;
		this->data[2] = an;
	}

	CrediteBancare(const CrediteBancare &c):idCredit(c.idCredit)
	{
		cout << "\nApel constructor de copiere Credite Bancare\n";
		if (c.numeDator != nullptr)
		{
			this->numeDator = new char[strlen(c.numeDator) + 1];
			strcpy(this->numeDator, c.numeDator);
		}
		else
			this->numeDator = nullptr;
		if (c.numeBanca != nullptr)
		{
			this->numeBanca = new char[strlen(c.numeBanca) + 1];
			strcpy(this->numeBanca, c.numeBanca);
		}
		else
			this->numeBanca = nullptr;
		this->dobanda = c.dobanda;
		for (int i = 0; i < 3; i++)
			this->data[i] = c.data[i];
		this->sumadatorata = c.sumadatorata;
		nrCrediteBancare++;	
	}

	~CrediteBancare()
	{
		cout << "\nApel destructor Credite Bancare\n";
		if (this->numeBanca != nullptr)
			delete[] this->numeBanca;
		if (this->numeDator != nullptr)
			delete[] this->numeDator;
		nrCrediteBancare--;
	}

	CrediteBancare& operator=(const CrediteBancare& c)
	{
		if (this->numeBanca != nullptr)
			delete[] this->numeBanca;
		if (c.numeBanca != nullptr)
		{
			this->numeBanca = new char[strlen(c.numeBanca) + 1];
			strcpy(this->numeBanca, c.numeBanca);
		}
		else
			this->numeBanca = nullptr;

		if (this->numeDator != nullptr)
			delete[] this->numeDator;
		if (c.numeDator != nullptr)
		{
			this->numeDator = new char[strlen(c.numeDator) + 1];
			strcpy(this->numeDator, c.numeDator);
		}
		else
			this->numeDator = nullptr;

		for (int i = 0; i < 3; i++)
			this->data[i] = c.data[i];
		this->sumadatorata = c.sumadatorata;
		this->dobanda = c.dobanda;
		return *this;
	}

	void verificareFaliment()
	{
		if (this->data[2] < 1950)
			cout << "\nClientul " << this->numeDator << " este falimentat.";
		else
			cout << "\nClientul " << this->numeDator << " este inca activ.";
	}

	void sumadeinapoiat()
	{
		float sumainapoiata;
		sumainapoiata = this->sumadatorata * ((float)this->dobanda / 100) + this->sumadatorata;
		cout << "\nSuma care trebuie inapoiata este: " << sumainapoiata;
	}

	CrediteBancare operator-(float micsorare)
	{
		this->sumadatorata -= micsorare;
		return *this;
	}

	CrediteBancare& operator++() //preincrementare - se aduna 100 -> penalizare
	{
		this->sumadatorata += 100;
		return *this;
	}

	CrediteBancare operator++(int) //postincrementare - se aduna 100 -> penalizare
	{
		CrediteBancare cb = *this;
		this->sumadatorata += 100;
		return cb;
	}

	bool operator<(const CrediteBancare &cb)
	{
		/*if (this->sumadatorata < cb.sumadatorata)
			cout << "\nClientul " << this->numeDator << " are un credit mai mic decat " << cb.numeDator << ".";
		else if (this->sumadatorata > cb.sumadatorata)
			cout << "\nClientul " << cb.numeDator << " are un credit mai mic decat " << this->numeDator << ".";
		else cout << "\nClientul " << this->numeDator << " si " << cb.numeDator << "au credit de aceeasi valoare."; // pt void*/
		if (this->sumadatorata < cb.sumadatorata)
			return 1;
		else
			return 0;
	}

	CrediteBancare& operator[](double x)
	{
		this->dobanda = this->dobanda + x; //creste dobanda
		return *this;
	}

	CrediteBancare& operator!()
	{
		if (this->sumadatorata != 0)
			this->sumadatorata = 0;			//scapi de datorie
		return *this;
	}

	operator float()
	{
		return this->sumadatorata;
	}

	char* get_nume_banca() const
	{
		return numeBanca;
	}

	void set_nume_banca(char* nume_banca)
	{
		if (this->numeBanca != nullptr)
			delete[] this->numeBanca;
		if (nume_banca != nullptr)
		{
			this->numeBanca = new char[strlen(nume_banca) + 1];
			strcpy(this->numeBanca, nume_banca);
		}
	}

	double get_dobanda() const
	{
		return dobanda;
	}

	void set_dobanda(double dobanda)
	{
		if (dobanda > 0)
			this->dobanda = dobanda;
	}

	float get_sumadatorata() const
	{
		return sumadatorata;
	}

	void set_sumadatorata(float sumadatorata)
	{
		if (sumadatorata > 0)
			this->sumadatorata = sumadatorata;
	}

	char* get_nume_dator() const
	{
		return numeDator;
	}

	void set_nume_dator(char* nume_dator)
	{
		if (this->numeDator != nullptr)
			delete[] this->numeDator;
		if (nume_dator != nullptr)
		{
			this->numeDator = new char[strlen(nume_dator) + 1];
			strcpy(this->numeDator, nume_dator);
		}
	}

	int get_id_credit() const
	{
		return idCredit;
	}

	float getSuma_x()
		{
			return this->get_sumadatorata()+100; //taxe
		}

	int get_an_x_()
		{
			return this->data[2];
		}

	friend ostream& operator<<(ostream& out, CrediteBancare c);
	friend istream& operator>>(istream& in, CrediteBancare& c);
	friend class Files;
};
	int CrediteBancare::nrCrediteBancare = 0;

istream& operator>>(istream& in, CrediteBancare& c)
{
	if (c.numeBanca != nullptr)
		delete[] c.numeBanca;
	char buffer[100];
	cout << "\nIntroduceti numele bancii: ";
	in >> buffer;
	c.numeBanca = new char[strlen(buffer) + 1];
	strcpy(c.numeBanca, buffer);

	if (c.numeDator != nullptr)
		delete[] c.numeDator;
	cout << "\nIntroduceti numele clientului dator: ";
	in >> buffer;
	c.numeDator = new char[strlen(buffer) + 1];
	strcpy(c.numeDator, buffer);

	cout << "\nIntroduceti data la care a fost acceptat creditul: \n";
	cout << "Ziua: ";
	in >> c.data[0];
	cout << "\nLuna: ";
	in >> c.data[1];
	cout << "\nAnul: ";
	in >> c.data[2];

	cout << "\nIntroduceti dobanda stabilita: ";
	in >> c.dobanda;
	cout << "\nIntroduceti suma imprumuta: ";
	in >> c.sumadatorata;
	return in;
}

ostream& operator<<(ostream& out, const CrediteBancare c)
{
	if (c.numeBanca != nullptr)
		out << "Numele bancii este " << c.numeBanca;
	if (c.numeDator != nullptr)
		out << ",iar numele clientului dator este " << c.numeDator;
	out << "\nCreditul are id-ul: " << c.idCredit;
	out << "\nCreditul in valoare de " << c.sumadatorata << ", cu dobanda " << c.dobanda;
	out << " a fost luat in data de " << c.data[0] << "-" << c.data[1] << "-" << c.data[2];
	return out;
}

class Intretinere:public iChelt
{
private:
	char* numelocatar;
	float costapa;
	float costgaze;
	float total;
	short int data[3];
public:
	Intretinere(char* numelocatar=nullptr):numelocatar(numelocatar)
	{
		cout << "\nApel constructor cu un parametru intretinere";
		if (numelocatar != nullptr)
		{
			this->numelocatar = new char[strlen(numelocatar) + 1];
			strcpy(this->numelocatar, numelocatar);
		}
		else {
			this->numelocatar=new char[strlen("Anonim")+1];
			strcpy(this->numelocatar, "Anonim");
		}
		this->costapa = 0;
		this->costgaze = 0;
		this->total = this->costapa + this->costgaze;
		this->data[0] = 1;
		this->data[1] = 1;
		this->data[2] = 1990;
	}

	Intretinere(char* numelocatar, float costapa, float costgaze, short int zi, short int luna,
		short int an):numelocatar(numelocatar) 
	{
		cout << "\nApel constructor cu 3 param. intretinere";
		if (numelocatar != nullptr)
		{
			this->numelocatar = new char[strlen(numelocatar) + 1];
			strcpy(this->numelocatar, numelocatar);
		}
		else {
			this->numelocatar=new char[strlen("Anonim")+1];
			strcpy(this->numelocatar, "Anonim");
		}
		this->costapa = costapa;
		this->costgaze = costgaze;
		this->total = this->costapa + this->costgaze;
		this->data[0] = zi;
		this->data[1] = luna;
		this->data[2] = an;
	}

	Intretinere(const Intretinere &tr)
	{
		cout << "\nApel constructor de copiere intretinere";
		if (tr.numelocatar != nullptr)
		{
			this->numelocatar = new char[strlen(tr.numelocatar) + 1];
			strcpy(this->numelocatar, tr.numelocatar);
		}
		else this->numelocatar = nullptr;
		this->costapa = tr.costapa;
		this->costgaze = tr.costgaze;
		this->total = tr.total;
		for (int i = 0; i < 3; i++)
			this->data[i] = tr.data[i];
	}

	~Intretinere()
	{
		cout << "\nApel destructor Intretinere";
		if (this->numelocatar != nullptr)
			delete[] this->numelocatar;
	}

	Intretinere& operator=(const Intretinere tr)
	{
		if (this->numelocatar != nullptr)
			delete[] this->numelocatar;
		if (tr.numelocatar != nullptr)
		{
			this->numelocatar = new char[strlen(tr.numelocatar) + 1];
			strcpy(this->numelocatar, tr.numelocatar);
		}
		this->costapa = tr.costapa;
		this->costgaze = tr.costgaze;
		this->total = tr.total;
		for (int i = 0; i < 3; i++)
			this->data[i] = tr.data[i];
		return *this;
	}

	Intretinere operator[](short int a) //creste anul cu 'a'
	{
			this->data[2] = this->data[2] + a; 
		return *this;
	}

	Intretinere operator+(const Intretinere& a)
	{
		this->total = this->total + a.total;
		this->costapa = this->costapa + a.costapa;
		this->costgaze = this->costgaze + a.costgaze;
		return *this;
	}

	Intretinere& operator++() //preincrementare - se aduna 100 -> penalizare
	{
		this->total += 100;
		this->costapa += 50;
		this->costgaze += 50;
		return *this;
	}

	Intretinere operator++(int) //postincrementare - se aduna 100 -> penalizare
	{
		Intretinere tr = *this;
		this->costapa += 50;
		this->costgaze += 50;
		this->total += 100;
		return tr;
	}

	Intretinere operator!()
	{
		Intretinere tr = *this;
		this->costapa = 0;
		this->costgaze = 0;
		this->total = 0;
		for (int i = 0; i < 3; i++)
			this->data[i] = 0;
		return *this;
	}

	bool operator>(const Intretinere &tr)
	{
		if (this->total > tr.total)
			return 1;
		else return 0;
	}

	void costmaimare()
	{
		if (this->costapa > this->costgaze)
			cout << "\nCheltuiala cu apa este mai mare decat cheltuiala cu gazele pentru " << this->numelocatar;
		else if (this->costapa < this->costgaze)
			cout << "\nCheltuiala cu gazele este mai mare decat cheltuiala cu apa pentru " << this->numelocatar;
		else cout << "\nCheltuiala cu apa este egala cu cea pentru gaze pentru " << this->numelocatar;
	}

	void extrageretreichar()
	{
		if (strlen(this->numelocatar) >= 3)
		{
			cout << "\nPrimele 3 litere ale numelui " << this->numelocatar << " sunt: ";
			for (int i = 0; i < 3; i++)
				cout << this->numelocatar[i];
		}
		else cout << "\nNumele are mai putin de 3 litere";
	}

	operator float()
	{
		return this->total;
	}

	char* get_numelocatar() const
	{
		return numelocatar;
	}

	void set_numelocatar(char* numelocatar)
	{
		if (this->numelocatar != nullptr)
			delete[] this->numelocatar;
		if (numelocatar != nullptr)
		{
			this->numelocatar = new char[strlen(numelocatar) + 1];
			strcpy(this->numelocatar, numelocatar);
		}
	}

	float get_costapa() const
	{
		return costapa;
	}

	void set_costapa(float costapa)
	{
		if (this->costapa >= 0)
			this->costapa = costapa;
	}

	float get_costgaze() const
	{
		return costgaze;
	}

	void set_costgaze(float costgaze)
	{
		if (this->costgaze >= 0)
			this->costgaze = costgaze;
	}

	float get_total() const
	{
		return total;
	}

	void set_total(float total)
	{
		if (this->total >= 0)
			this->total = total;
	}

	float getSuma_x()
	{
		return this->get_total() + 100; //penalizari
	}

	int get_an_x_()
	{
		return this->data[2];
	}

	friend ostream& operator<<(ostream& out, Intretinere tr);
	friend istream& operator>>(istream& in, Intretinere& tr);
	friend class Files;
};

istream& operator >> (istream& in, Intretinere& tr)
{
	if (tr.numelocatar != nullptr)
		delete[] tr.numelocatar;
	char buffer[100];
	cout << "\nIntroduceti numele locatarului care plateste intretinerea: ";
	in>>buffer;
	tr.numelocatar = new char[strlen(buffer) + 1];
	strcpy(tr.numelocatar, buffer);

	cout << "Introduceti cheltuiala cu apa: ";
	in >> tr.costapa;
	cout << "Introduceti cheltuiala cu gazele: ";
	in >> tr.costgaze;

	tr.total = tr.costapa + tr.costgaze;

	cout << "Introduceti data la care este platita intretinerea: \n";
	cout << "Ziua: ";
	in >> tr.data[0];
	cout << "Luna: ";
	in >> tr.data[1];
	cout << "Anul: ";
	in >> tr.data[2];

	return in;
}

ostream& operator<<(ostream& out, const Intretinere tr)
{
	if (tr.numelocatar != nullptr)
		out << "\nNumele locatarului care plateste intretinerea este " << tr.numelocatar;
	out << "\nFactura la intretinere este in valoare de " << tr.total << " dintre care " << tr.costapa;
	out << " lei reprezinta apa si " << tr.costgaze << " reprezinta gazele";
	out << "\nData la care a fost platita intretinerea este: " << tr.data[0] << "-" << tr.data[1] << "-" << tr.data[2];
	return out;
}

class Telefonie:public Client
{
private:
	char* numeclient;
	int nrabonamente;
	float pretab[10];  //preturile pentru fiecare abonament in parte
public:

	Telefonie(char* numeclient=nullptr)
	{
		cout << "\nApel constructor cu un parametru Telefonie";
		if (numeclient != nullptr)
		{
			this->numeclient = new char[strlen(numeclient) + 1];
			strcpy(this->numeclient, numeclient);
		}
		else this->numeclient = nullptr;
		this->nrabonamente=0;
		for(int i=0;i<10;i++)
			pretab[i]=0;
	}

	Telefonie(char* numeclient, int nrabonamente, float pretab[10])
	{
		cout << "Apel constructor cu 3 param Telefonie";
		if (numeclient != nullptr)
		{
			this->numeclient = new char[strlen(numeclient) + 1];
			strcpy(this->numeclient, numeclient);
		}
		else this->numeclient = nullptr;
		if (nrabonamente >= 0)
			this->nrabonamente = nrabonamente;
		else throw exception("\nNumarul de abonamente nu poate fi negativ sau de tip caracter.");
		memcpy(this->pretab, pretab, nrabonamente * sizeof(float));
	}

	Telefonie(const Telefonie &t)
	{
		cout << "\nApel constructor de copiere Telefonie";
		if (t.numeclient != nullptr)
		{
			this->numeclient = new char[strlen(t.numeclient) + 1];
			strcpy(this->numeclient, t.numeclient);
		}
		else this->numeclient = nullptr;
		this->nrabonamente = t.nrabonamente;
	//	for (int i = 0; i < this->nrabonamente; i++)
		//	this->pretab[i] = t.pretab[i];
		memcpy(this->pretab, t.pretab, t.nrabonamente * sizeof(float));
	}

	void operator=(const Telefonie t)
	{
		cout<<"\nApel operator = Telefonie";
		if(this->numeclient!=nullptr)
			delete[] this->numeclient;
		if(t.numeclient!=nullptr)
		{
			this->numeclient=new char[strlen(t.numeclient)+1];
			strcpy(this->numeclient,t.numeclient);
		}
		this->nrabonamente=t.nrabonamente;
		memcpy(this->pretab, t.pretab, t.nrabonamente * sizeof(float));
	}

	Telefonie operator+(const Telefonie& t)
	{
		int i;

		if (this->numeclient != nullptr && t.numeclient != nullptr)
		{
			char buffer[100];
			strcpy(buffer, this->numeclient);
			delete[] this->numeclient;
			this->numeclient = new char[strlen(this->numeclient) + strlen(t.numeclient) + 1];
			strcpy(this->numeclient, buffer);
			strcat(this->numeclient, t.numeclient);
		}
		else if (this->numeclient == nullptr && t.numeclient != nullptr)
			strcpy(this->numeclient, t.numeclient);

		if (this->nrabonamente > t.nrabonamente)
			for (i = 0; i < t.nrabonamente; i++)
				this->pretab[i] += t.pretab[i];

		else if (this->nrabonamente == t.nrabonamente)
			for (i = 0; i < this->nrabonamente; i++)
				this->pretab[i] += t.pretab[i];
		else
		{
			for (i = 0; i < this->nrabonamente; i++)
				this->pretab[i] += t.pretab[i];
			while (i < t.nrabonamente)
			{
				this->pretab[i] = t.pretab[i];
				i++;
			}
			this->nrabonamente = t.nrabonamente;
		}
		return *this;
	}


	float operator[](int abonament)
	{
		return this->pretab[abonament-1];
	
	}

	Telefonie& operator++()		//preincrementare
	{
		for (int i = 0; i < this->nrabonamente; i++)
			this->pretab[i] += 10;
		return *this;
	}

	Telefonie operator++(int)
	{
		Telefonie aux = *this;
		for (int i = 0; i < this->nrabonamente; i++)
			this->pretab[i] += 10;
		return aux;
	}

	void operator!()
	{
		for (int i = 0; i < this->nrabonamente; i++)
			this->pretab[i] = 0;
		this->nrabonamente = 0;
	}

	bool operator>(Telefonie t) //verifica daca un utilizator are mai multe abonamente decat altul
	{
		/*float sumthis = 0, sumt = 0;
		for (int i = 0; i < this->nrabonamente; i++)
			sumthis += this->pretab[i];
		for (int i = 0; i < t.nrabonamente; i++)
			sumt += t.pretab[i];
		if (sumthis > sumt)
			return true;
		else return false;*/
		if (this->nrabonamente > t.nrabonamente)
			return true;
		else return false;
	}

	operator int()
	{
		return this->nrabonamente;
	}

	float totalplata()
	{
		float suma = 0;
		for (int i = 0; i < this->nrabonamente; i++)
			suma += this->pretab[i];
		return suma;
	}


	~Telefonie()
	{
		cout << "\nApel destructor Telefonie";
		if (this->numeclient != nullptr)
			delete[] this->numeclient;
	}

	char* get_numeclient() const
	{
		return numeclient;
	}

	void set_numeclient(char* numeclient)
	{
		if (this->numeclient != nullptr)
			delete[] this->numeclient;
		if (numeclient != nullptr)
		{
			this->numeclient = new char[strlen(numeclient) + 1];
			strcpy(this->numeclient, numeclient);
		}
	}

	int get_nrabonamente() const
	{
		return nrabonamente;
	}

	void set_nrabonamente(int nrabonamente)
	{
		this->nrabonamente = nrabonamente;
	}

	float mediaab()
	{
		float suma = 0;
		for (int i = 0; i < this->nrabonamente; i++)
			suma += this->pretab[i];
		return suma / this->nrabonamente;
	}

	float client_x_ __override(){
		return this->totalplata();
	}

	float client_y_ __override(){
		return this->mediaab();
	}

	friend ostream& operator<<(ostream& out, const Telefonie& t);
	friend istream& operator>>(istream& in, Telefonie& t);
	friend class Files;
}; 

ostream& operator<<(ostream& out, const Telefonie& t)
{
	if (t.numeclient != nullptr)
		out << "\nNumele clientului este: " << t.numeclient << " si are un numar de " << t.nrabonamente << " abonamente.";
	for (int i = 0; i < t.nrabonamente; i++)
		out << "\nAbonamentul " << i+1 << " este in valoare de " << t.pretab[i] << " lei.";
	return out;
}

istream& operator>>(istream& in, Telefonie& t)
{
	char buffer[100];
	if (t.numeclient != nullptr)
		delete[] t.numeclient;
	cout << "\nIntroduceti numele clientului serviciilor telefonice: ";
	in >> buffer;
	t.numeclient = new char[strlen(buffer) + 1];
	strcpy(t.numeclient, buffer);

	cout << "Introduceti numarul de abonamente detinute de client: ";
	in >> t.nrabonamente;

	for (int i = 0; i < t.nrabonamente; i++)
	{
		cout << "Introduceti pretul pentru abonamentul " << i + 1 << ": ";
		in >> t.pretab[i];
	}

	return in;
}

class CheltSanatate:public Client
{
private:
	char* numeasigurat;
	unsigned nrinterventii;
	float pretin[10];
public:
	CheltSanatate(char* numeasigurat=nullptr)
	{
		cout << "\nApel constructor cu un parametru CheltSanatate ";
		if (numeasigurat != nullptr)
		{
			this->numeasigurat = new char[strlen(numeasigurat) + 1];
			strcpy(this->numeasigurat, numeasigurat);
		}
		else this->numeasigurat = nullptr;
		this->nrinterventii=0;
	}

	CheltSanatate(char* numeasigurat, unsigned nrinterventii, float pretin[10])
	{
		cout << "\nApel constructor cu 3 param. CheltSanatate ";
		if (numeasigurat != nullptr)
		{
			this->numeasigurat = new char[strlen(numeasigurat) + 1];
			strcpy(this->numeasigurat, numeasigurat);
		}
		else this->numeasigurat = nullptr;
		this->nrinterventii = nrinterventii;
		memcpy(this->pretin, pretin, nrinterventii * sizeof(float));
	}

	CheltSanatate(const CheltSanatate &cs)
	{
		cout << "Apel constructor de copiere";
		if (cs.numeasigurat != nullptr)
		{
			this->numeasigurat = new char[strlen(cs.numeasigurat) + 1];
			strcpy(this->numeasigurat, cs.numeasigurat);
		}
		else this->numeasigurat = nullptr;
		this->nrinterventii = cs.nrinterventii;
		memcpy(this->pretin, cs.pretin, cs.nrinterventii * sizeof(float));
	}

	CheltSanatate& operator=(const CheltSanatate& cs)
	{
		if (this->numeasigurat != nullptr)
			delete[] this->numeasigurat;
		if (cs.numeasigurat != nullptr)
		{
			this->numeasigurat = new char[strlen(cs.numeasigurat) + 1];
			strcpy(this->numeasigurat, cs.numeasigurat);
		}
		else this->numeasigurat = nullptr;
		this->nrinterventii = cs.nrinterventii;
		memcpy(this->pretin, cs.pretin, nrinterventii * sizeof(float));
		return *this;
	}

	float operator[](unsigned a){
		if(a<this->nrinterventii)
			return this->pretin[a];
		else return -1;
	}

	CheltSanatate& operator+(const CheltSanatate& cs)
	{
		unsigned i;
		if (this->numeasigurat != nullptr && cs.numeasigurat != nullptr)
		{
			char buffer[100];
			strcpy(buffer, this->numeasigurat);
			delete[] this->numeasigurat;
			this->numeasigurat = new char[strlen(this->numeasigurat) + strlen(cs.numeasigurat) + 1];
			strcpy(this->numeasigurat, buffer);
			strcat(this->numeasigurat, cs.numeasigurat);
		}
		else if (this->numeasigurat == nullptr && cs.numeasigurat != nullptr)
			strcpy(this->numeasigurat, cs.numeasigurat);

		if (this->nrinterventii > cs.nrinterventii)
			for (i = 0; i < cs.nrinterventii; i++)
				this->pretin[i] += cs.pretin[i];

		else if (this->nrinterventii == cs.nrinterventii)
			for (i = 0; i < this->nrinterventii; i++)
				this->pretin[i] += cs.pretin[i];

		else
		{
			for (i = 0; i < this->nrinterventii; i++)
				this->pretin[i] += cs.pretin[i];
			while (i < cs.nrinterventii)
			{
				this->pretin[i] = cs.pretin[i];
				i++;
			}
			this->nrinterventii = cs.nrinterventii;
		}
		return *this;
	}

	CheltSanatate& operator++()
	{
		for (unsigned i = 0; i < this->nrinterventii; i++)
			this->pretin[i] += 1;
		return *this;
	}

	CheltSanatate operator++(int)
	{
		CheltSanatate aux = *this;
		for (unsigned i = 0; i < this->nrinterventii; i++)
			this->pretin[i] += 1;
		return aux;
	}

	CheltSanatate& operator!()
	{
		for (unsigned i = 0; i < this->nrinterventii; i++)
			this->pretin[i] = 0;
		this->nrinterventii = 0;
		return *this;
	}

	bool operator>(CheltSanatate s)
	{
		if (this->nrinterventii > s.nrinterventii)
			return true;
		else return false;
	}

	operator unsigned()
	{
		return this->nrinterventii;
	}

	unsigned numarareintervmaj()			// se numeste interventie majora interventia care costa mai mult de 100 de lei
	{
		unsigned nrmaj = 0;
		for (unsigned i = 0; i < this->nrinterventii; i++)
		{
			if (this->pretin[i] > 100)
				nrmaj++;
		}
		return nrmaj;
	}

	float medieinterv()
	{
		float med = 0;
		for (unsigned i = 0; i < this->nrinterventii; i++)
			med += pretin[i];
		med /= this->nrinterventii;
		return med;
	}

	~CheltSanatate()
	{
		cout<<"\nApel destructor CheltSanatate";
		if (this->numeasigurat != nullptr)
			delete[] this->numeasigurat;
	}

	char* get_numeasigurat() const
	{
		return numeasigurat;
	}

	void set_numeasigurat(char* numeasigurat)
	{
		if (this->numeasigurat != nullptr)
			delete[] this->numeasigurat;
		if (numeasigurat != nullptr)
		{
			this->numeasigurat = new char[strlen(numeasigurat) + 1];
			strcpy(this->numeasigurat, numeasigurat);
		}
	}

	unsigned get_nrinterventii() const
	{
		return nrinterventii;
	}

	void set_nrinterventii(unsigned nrinterventii)
	{
		this->nrinterventii = nrinterventii;
	}

	float client_x __override()
	{
		return this->medieinterv();
	}

	float client_y_ __override(){
		return static_cast<float>(this->numarareintervmaj());
	}

	friend ostream& operator<<(ostream& out, const CheltSanatate cs);
	friend istream& operator>>(istream& in, CheltSanatate& cs);
	friend class Files;
};

ostream& operator<<(ostream& out, const CheltSanatate cs)
{
	if (cs.numeasigurat != nullptr)
		out << "\nNumele asiguratului este " << cs.numeasigurat << ".";
	out << "\nAcesta a suferit " << cs.nrinterventii << " interventii";
	for (unsigned i = 0; i < cs.nrinterventii; i++)
		out << "\nInterventia cu numarul " << i + 1 << " a costat " << cs.pretin[i];
	return out;
}

istream& operator>>(istream& in, CheltSanatate& cs)
{
	if (cs.numeasigurat != nullptr)
		delete[] cs.numeasigurat;
	cout << "\nIntroduceti numele asiguratului: ";
	char buffer[70];
	in >> buffer;
	if (buffer != nullptr)
	{
		cs.numeasigurat = new char[strlen(buffer) + 1];
		strcpy(cs.numeasigurat, buffer);
	}
	cout << "\nIntroduceti numarul de interventii avute: ";
	in >> cs.nrinterventii;
	for (unsigned i = 0; i < cs.nrinterventii; i++)
	{
		cout << "\nIntroduceti pretul interventiei " << i + 1 << ": ";
		in >> cs.pretin[i];
	}
	return in;
}

class Files
{
public:

	//scriere fis. text Client
	void scrietxtclient(char* numeFisier, const Client& c)
	{
		ofstream f;
		f.open(numeFisier, ios::out);

		if (f.is_open())
		{
			if (c.nume != nullptr)
				f << "Numele este: " << c.nume << "\n";
			else
				f << "Nume NULL\n";
			f << "Salariile pe 12 luni: ";
			for (int i = 0; i < 12; i++)
				f << c.salarii[i] << " ";
		}
		else cout << "\nEroare la deschiderea fisierului.";
		f.close();
	}

	//citire fis. text Client
	void citestetxtclient(char* numeFisier, Client& c)
	{
		ifstream f;
		f.open(numeFisier, ios::in);

		if (f.is_open())
		{
			if (c.nume != nullptr)
				delete[] c.nume;


			char aux[100];

			f.getline(aux, 100);
			if (strcmp(aux, nullptr))
			{
				c.nume = new char[strlen(aux) + 1];
				strcpy(c.nume, aux);
			}
			else c.nume = nullptr;

			for (int i = 0; i < 12; i++)
				f >> c.salarii[i];
			f.get();
		}
		else cout << "\nFisierul are eroare la deschidere.";

		f.close();
	}

	void scrieClientBin(char* numeFisier, const Client& c)
	{
		ofstream f;
		f.open(numeFisier, ios::out | ios::binary);

		if (f.is_open())
		{
			if (c.nume != nullptr)
				f.write(c.nume, 100);
			else
				f.write("Numele este NULL", sizeof("Numele este NULL"));

			for (int i = 0; i < 12; i++)
				f.write((char*)&c.salarii[i], 4);
		}
		else
			cout << "\nEroare la deschiderea fisierului binar.";
		f.close();
	}

	void citesteClientBin(char* numeFisier, Client& c)
	{
		ifstream f;
		f.open(numeFisier, ios::in | ios::binary);

		if (f.is_open())
		{
			if (c.nume != NULL)
				delete[] c.nume;

			char aux[100];

			f.read(aux, 100);
			c.nume = new char[strlen(aux) + 1];
			strcpy(c.nume, aux);

			for (int i = 0; i < 12; i++)
				f.read((char*)&c.salarii[i], 4);
		}
		else cout << "\nEroare la deschiderea fisierului.";
		f.close();
	}


	//pentru clasa Credite Bancare
		//scriere si citire CrediteBancare in fisiere text
	void scrietxtcredbanc(char* numeFisier, const CrediteBancare& cb)
	{
		ofstream f;
		f.open(numeFisier, ios::out);

		if (f.is_open())
		{
			if (cb.numeBanca != nullptr)
				f << "Numele este: " << cb.numeBanca << "\n";
			else
				f << "Nume NULL\n";

			if (cb.numeDator != nullptr)
				f << "Numele este: " << cb.numeDator << "\n";
			else
				f << "Nume NULL\n";

			f << "Data: ";
			for (int i = 0; i < 3; i++)
				f << cb.data[i] << " ";

			f << "\nDobanda: " << cb.dobanda;

			f << "\nSuma datorata: " << cb.sumadatorata;
		}

		else cout << "\nEroare la deschiderea fisierului.";
		f.close();
	}


	void citestetxtcredbanc(char* numeFisier, CrediteBancare& cb)
	{
		ifstream f;
		f.open(numeFisier, ios::in);

		if (f.is_open())
		{
			if (cb.numeDator != nullptr)
				delete[] cb.numeDator;
			if (cb.numeBanca != nullptr)
				delete[] cb.numeBanca;

			char aux[100];

			f.getline(aux, 100);
			if (strcmp(aux, nullptr))
			{
				cb.numeDator = new char[strlen(aux) + 1];
				strcpy(cb.numeDator, aux);
			}
			else cb.numeDator = nullptr;


			f.getline(aux, 100);
			if (strcmp(aux, nullptr))
			{
				cb.numeBanca = new char[strlen(aux) + 1];
				strcpy(cb.numeBanca, aux);
			}
			else cb.numeBanca = nullptr;
			
			f >> cb.dobanda;
			f.get();

			f >> cb.sumadatorata;
			f.get();

			for (int i = 0; i < 3; i++)
				f >> cb.data[i];
			f.get();
		}
		else cout << "\nFisierul are eroare la deschidere.";
		f.close();
	}


	//Scriere si Citire Binare CrediteBancare
	void scrieCreditBancBin(char* numeFisier, const CrediteBancare& cb)
	{
		ofstream f;
		f.open(numeFisier, ios::out | ios::binary);

		if (f.is_open())
		{
			if (cb.numeDator != nullptr)
				f.write(cb.numeDator, 100);
			else
				f.write("Numele datorului este NULL", sizeof("Numele datorului este NULL"));

			if (cb.numeBanca != nullptr)
				f.write(cb.numeBanca, 100);
			else
				f.write("Numele bancii este NULL", sizeof("Numele bancii este NULL"));

			f.write((char*)&cb.dobanda, 8);

			f.write((char*)&cb.sumadatorata, 4);

			for (int i = 0; i < 3; i++)
				f.write((char*)&cb.data[i], 4);
		}
		else
			cout << "\nEroare la deschiderea fisierului binar.";
		f.close();
	}


	void citesteCreditBancBin(char* numeFisier, CrediteBancare& cb)
	{
		ifstream f;
		f.open(numeFisier, ios::in | ios::binary);

		if (f.is_open())
		{
			if (cb.numeDator != NULL)
				delete[] cb.numeDator;

			if (cb.numeBanca != NULL)
				delete[] cb.numeBanca;

			char aux[100];

			f.read(aux, 100);
			cb.numeDator = new char[strlen(aux) + 1];
			strcpy(cb.numeDator, aux);

			f.read(aux, 100);
			cb.numeBanca = new char[strlen(aux) + 1];
			strcpy(cb.numeBanca, aux);

			f.read((char*)&cb.dobanda, 8);
			f.read((char*)&cb.sumadatorata, 4);

			for (int i = 0; i < 3; i++)
				f.read((char*)&cb.data[i], 4);
		}
		else cout << "\nEroare la deschiderea fisierului.";
		f.close();
	}


	//Clasa Intretinere scriere/citire fisiere text
	void scrietxtintret(char* numeFisier, const Intretinere& it)
	{
		ofstream f;
		f.open(numeFisier, ios::out);

		if (f.is_open())
		{
			if (it.numelocatar != nullptr)
				f << "Numele este: " << it.numelocatar << "\n";
			else
				f << "Nume NULL\n";


			f << "Data: ";
			for (int i = 0; i < 3; i++)
				f << it.data[i] << " ";

			f << "\nCost apa: " << it.costapa;

			f << "\nCost gaze: " << it.costgaze;

			f << "\nCost total: " << it.total;
		}

		else cout << "\nEroare la deschiderea fisierului.";
		f.close();
	}


	void citestetxtintret(char* numeFisier, Intretinere& it)
	{
		ifstream f;
		f.open(numeFisier, ios::in);

		if (f.is_open())
		{
			if (it.numelocatar != nullptr)
				delete[] it.numelocatar;

			char aux[100];

			f.getline(aux, 100);
			if (strcmp(aux, nullptr))
			{
				it.numelocatar = new char[strlen(aux) + 1];
				strcpy(it.numelocatar, aux);
			}
			else it.numelocatar = nullptr;

			f >> it.costapa;
			f.get();

			f >> it.costgaze;
			f.get();

			for (int i = 0; i < 3; i++)
				f >> it.data[i];
			f.get();
		}
		else cout << "\nFisierul are eroare la deschidere.";
		f.close();
	}

	//Intretinere scriere si citire fisiere binare
	void scrieIntretinereBin(char* numeFisier, const Intretinere& it)
	{
		ofstream f;
		f.open(numeFisier, ios::out | ios::binary);

		if (f.is_open())
		{
			if (it.numelocatar != nullptr)
				f.write(it.numelocatar, 100);
			else
				f.write("Numele datorului este NULL", sizeof("Numele datorului este NULL"));


			f.write((char*)&it.costapa, 4);

			f.write((char*)&it.costgaze, 4);

			for (int i = 0; i < 3; i++)
				f.write((char*)&it.data[i], 4);
		}
		else
			cout << "\nEroare la deschiderea fisierului binar.";
		f.close();
	}


	void citesteIntretinereBin(char* numeFisier, Intretinere& it)
	{
		ifstream f;
		f.open(numeFisier, ios::in | ios::binary);

		if (f.is_open())
		{
			if (it.numelocatar != NULL)
				delete[] it.numelocatar;

			char aux[100];

			f.read(aux, 100);
			it.numelocatar = new char[strlen(aux) + 1];
			strcpy(it.numelocatar, aux);


			f.read((char*)&it.costapa, 4);

			f.read((char*)&it.costgaze, 4);

			for (int i = 0; i < 3; i++)
				f.read((char*)&it.data[i], 4);
		}
		else cout << "\nEroare la deschiderea fisierului.";
		f.close();
	}


	//Pentru clasa Telefonie
	void scrietxttelefon(char* numeFisier, const Telefonie& t)
	{
		ofstream f;
		f.open(numeFisier, ios::out);

		if (f.is_open())
		{
			if (t.numeclient != nullptr)
				f << "Numele este: " << t.numeclient << "\n";
			else
				f << "Nume NULL\n";

			f << "\nNumarul de abonamente: " << t.nrabonamente;

			f << "\nPretul fiecarui abonament in parte";
			for (int i = 0; i < t.nrabonamente; i++)
				f << t.pretab[i] << " ";
		}
		else cout << "\nEroare la deschiderea fisierului.";
		f.close();
	}

	void citestetxttelefon(char* numeFisier, Telefonie& t)
	{
		ifstream f;
		f.open(numeFisier, ios::in);

		if (f.is_open())
		{
			if (t.numeclient != nullptr)
				delete[] t.numeclient;

			char aux[100];

			f.getline(aux, 100);
			if (strcmp(aux, nullptr)!=0)
			{
				t.numeclient = new char[strlen(aux) + 1];
				strcpy(t.numeclient, aux);
			}
			else t.numeclient = nullptr;

			f >> t.nrabonamente;

			for (int i = 0; i < t.nrabonamente; i++)
				f >> t.pretab[i];
			//f.get();
		}
		else cout << "\nFisierul are eroare la deschidere.";

		f.close();
	}

	void scrieTelefonBin(char* numeFisier, const Telefonie& t)
	{
		ofstream f;
		f.open(numeFisier, ios::out | ios::binary);

		if (f.is_open())
		{
			if (t.numeclient != nullptr)
				f.write(t.numeclient, 100);
			else
				f.write("Numele este NULL", sizeof("Numele este NULL"));

			f.write((char*)&t.nrabonamente, 4);

			for (int i = 0; i < t.nrabonamente; i++)
				f.write((char*)&t.pretab[i], 4);
		}
		else
			cout << "\nEroare la deschiderea fisierului binar.";
		f.close();
	}

	void citesteTelefonBin(char* numeFisier, Telefonie& t)
	{
		ifstream f;
		f.open(numeFisier, ios::in | ios::binary);

		if (f.is_open())
		{
			if (t.numeclient != NULL)
				delete[] t.numeclient;

			char aux[100];

			f.read(aux, 100);
			t.numeclient = new char[strlen(aux) + 1];
			strcpy(t.numeclient, aux);

			f.read((char*)&t.nrabonamente, 4);

			for (int i = 0; i < t.nrabonamente; i++)
				f.read((char*)&t.pretab[i], 4);
		}
		else cout << "\nEroare la deschiderea fisierului.";
		f.close();
	}

	//Pentru clasa CheltSanatate
		//scrierea in fisier text clasa CheltSanatate
	void scrietxtchsanatate(char* numeFisier, const CheltSanatate& cs)
	{
		ofstream f;
		f.open(numeFisier, ios::out);

		if (f.is_open())
		{
			if (cs.numeasigurat != nullptr)
				f << "Numele este: " << cs.numeasigurat << "\n";
			else
				f << "Nume NULL\n";

			f << "\nNumarul de abonamente: " << cs.nrinterventii;

			f << "\nPretul fiecarei interventii in parte: ";
			for (unsigned i = 0; i < cs.nrinterventii; i++)
				f << cs.pretin[i] << " ";
		}
		else cout << "\nEroare la deschiderea fisierului.";
		f.close();
	}

	//citire fis. text CheltSanatate
	void citestetxtchsanatate(char* numeFisier, CheltSanatate& cs)
	{
		ifstream f;
		f.open(numeFisier, ios::in);

		if (f.is_open())
		{
			if (cs.numeasigurat != NULL)
				delete[] cs.numeasigurat;


			char aux[100];

			f.getline(aux, 100);
			if (strcmp(aux, "NULL")!=0)
			{
				cs.numeasigurat = new char[strlen(aux) + 1];
				strcpy(cs.numeasigurat, aux);
			}
			else cs.numeasigurat = NULL;

			f >> cs.nrinterventii;
			f.get();

			for (unsigned i = 0; i < cs.nrinterventii; i++)
				f >> cs.pretin[i];
			f.get();
		}
		else cout << "\nFisierul are eroare la deschidere.";

		f.close();
	}

	void scriechSanatateBin(char* numeFisier, const CheltSanatate& cs)
	{
		ofstream f;
		f.open(numeFisier, ios::out | ios::binary);

		if (f.is_open())
		{
			if (cs.numeasigurat != nullptr)
				f.write(cs.numeasigurat, 100);
			else
				f.write("Numele este NULL", sizeof("Numele este NULL"));

			f.write((char*)&cs.nrinterventii, 4);

			for (unsigned i = 0; i < cs.nrinterventii; i++)
				f.write((char*)&cs.pretin[i], 4);
		}
		else
			cout << "\nEroare la deschiderea fisierului binar.";
		f.close();
	}

	void citesteCheltSanatateBin(char* numeFisier, CheltSanatate& cs)
	{
		ifstream f;
		f.open(numeFisier, ios::in | ios::binary);

		if (f.is_open())
		{
			if (cs.numeasigurat != NULL)
				delete[] cs.numeasigurat;

			char aux[100];

			f.read(aux, 100);
			cs.numeasigurat = new char[strlen(aux) + 1];
			strcpy(cs.numeasigurat, aux);

			f.read((char*)&cs.nrinterventii, 4);

			for (unsigned i = 0; i < cs.nrinterventii; i++)
				f.read((char*)&cs.pretin[i], 4);
		}
		else cout << "\nEroare la deschiderea fisierului.";
		f.close();
	}

	
	//Rapoarte pentru clasa Client
	void RapMedieCostClient(char* numeFisier, int nrPers, Client* listaclienti)
	{
		ofstream rap;
		rap.open(numeFisier, ios::out);
		if (rap.is_open())
		{
			float medie = 0;
			for (int i = 0; i < nrPers; i++)
				for (int j = 0; j < 12; j++)
					medie += listaclienti[i].salarii[j];
			medie /= nrPers;
			rap << "Media este: " << medie;
			cout << "\nMedia este: " << medie;
		}
		else cout << "\nEroare la deschiderea fisierului";
		rap.close();
	}

	void RapListaCompletaClient(char* numeFisier, int nrPers, Client* listaclienti)
	{
		ofstream rapc;
		rapc.open(numeFisier, ios::out);
		if (rapc.is_open())
		{
			cout << "\nLista completa a clientilor este: ";
			rapc << "\nLista completa a clientilor este: ";
			for (int i = 0; i < nrPers; i++)
			{
				cout << "\n" << i+1 << ". " << listaclienti[i].nume;
				rapc << "\n" << i+1 << ". " << listaclienti[i].nume;
			}
		}
		else cout << "\nEroare la deschiderea fisierului.";
		rapc.close();
	}

	//Rapoarte pentru clasa CrediteBancare
	void RapCBbancaBT(char* numeFisier, int nrCredit, CrediteBancare* listacb)
	{
		ofstream raportbt;
		raportbt.open(numeFisier, ios::out);
		if (raportbt.is_open())
		{
			unsigned k = 0;
			double suma = 0;
			for (int i = 0; i < nrCredit; i++)
				if (strcmp("Banca Transilvania", listacb[i].numeBanca) == 0)
				{
					k++;
					suma += listacb[i].sumadatorata * listacb[i].dobanda;
				}
			cout << "\nBanca Transilvania are " << k << " clienti si " << suma << " bani de primit.";
			raportbt << "\nBanca Transilvania are " << k << " clienti si " << suma << " bani de primit.";
		}
		else
			cout << "\nEroare la deschiderea fisierului";
		raportbt.close();
	}

	void RaportCBdobanzi(char* numeFisier, int nrCredit, CrediteBancare* listacb)
	{
		ofstream rapd;
		rapd.open(numeFisier, ios::out);
		if (rapd.is_open())
		{
			double aux;
			double copdob[10];
			for (int i = 0; i < nrCredit; i++)
				copdob[i] = listacb[i].dobanda;
			for (int i = 0; i < nrCredit - 1; i++)
				for (int j = 0; j < nrCredit - i - 1; j++)
					if (copdob[i] > copdob[i + 1])
					{
						aux = copdob[i];
						copdob[i] = copdob[i + 1];
						copdob[i + 1] = aux;
					}
			cout << "\nDobanzile (de la mica la mare) sunt: ";
			rapd << "\nDobanzile (de la mica la mare) sunt: ";
			for (int i = 0; i < nrCredit; i++)
			{
				cout << "\n" << i + 1 << ". " << copdob[i] << " ";
				rapd << "\n" << i + 1 << ". " << copdob[i] << " ";
			}
		}
		else cout << "\nEroare la deschiderea fisierului";
		rapd.close();
	}

	//Rapoarte pentru clasa Intretinere
	void CalculApaGazBl(char* numeFisier, int nrLocatari, Intretinere* listabloc)
	{
		ofstream rapintret;
		rapintret.open(numeFisier, ios::out);
		if (rapintret.is_open())
		{
			float apa = 0, gaze = 0;
			for (int i = 0; i < nrLocatari; i++)
				apa += listabloc[i].costapa, gaze += listabloc[i].costgaze;
			cout << "\nPentru bloc costul total de apa a fost " << apa << ", iar costul total de gaze a fost " << gaze << ".";
			rapintret << "\nPentru bloc costul total de apa a fost " << apa << ", iar costul total de gaze a fost " << gaze << ".";
		}
		else cout << "\nEroare la deschiderea fisierului.";
		rapintret.close();
	}

	void ConsumIntretEcon(char* numeFisier, int nrLocatari, Intretinere* listabloc)
	{
		ofstream conec;
		conec.open(numeFisier, ios::out);
		if (conec.is_open())
		{
			if (listabloc != NULL)
			{
				float totmin = listabloc[0].total;
				for (int i = 0; i < nrLocatari; i++)
					if (totmin > listabloc[i].total)
						totmin = listabloc[i].total;
				cout << "\nCel mai mic consum il are: ";
				conec << "\nCel mai mic consum il are: ";
				for (int i = 0; i < nrLocatari; i++)
					if (totmin == listabloc[i].total)
					{
						cout << listabloc[i].numelocatar << " ";
						conec << listabloc[i].numelocatar << " ";
					}
			}
		}
		else cout<<"\nEroare la deschiderea fisierului.";
		conec.close();
	}

	//Rapoarte pentru clasa Telefonie
	void raport1telefoncl(char* numeFisier, int nrClTelef, Telefonie* listatelefon, Telefonie& t)
	{
		ofstream g;
		g.open(numeFisier, ios::out);
		if (g.is_open())
		{
			for (int i = 0; i < nrClTelef; i++)
				if (t.numeclient != listatelefon[i].numeclient)
					cout << "\nClientul de telefonie " << t.numeclient << " plateste " << (t.mediaab() / listatelefon[i].mediaab()) *
						100 << "% din banii pe care ii da " << listatelefon[i].numeclient;
		}
		else cout << "\nFisierul nu a putut fi deschis";
		g.close();
	}

	void raport2telefon(char* numeFisier, int nrClTelef, Telefonie* listatelefon)
	{
		ofstream g;
		g.open(numeFisier, ios::out);
		if (g.is_open())
		{
			int k = 0;
			for (int i = 0; i < nrClTelef; i++)
				k += listatelefon[i].nrabonamente;
			cout << "\nUn utilizator are in medie " << (float)k / nrClTelef << " abonamente.";
			g << "\nUn utilizator are in medie " << (float)k / nrClTelef << " abonamente.";
		}
		else cout << "\nFisierul nu a putut fi deschis";
		g.close();
	}

	//Rapoarte pentru clasa Chelt Sanatate

	void raport1CheltSanatate(char* numeFisier, int nrCheltSanat, CheltSanatate* listachelt)
	{
		ofstream g;
		g.open(numeFisier, ios::out);
		if (g.is_open())
		{
			cout << "\nLista cu toti asiguratii:";
			for (int i = 0; i < nrCheltSanat; i++)
			{
				cout << "\nAsiguratul " << listachelt[i].numeasigurat << " cu " << listachelt[i].nrinterventii<<" interventii.";
				g << "\nAsiguratul " << listachelt[i].numeasigurat << " cu " << listachelt[i].nrinterventii<<" interventii.";
			}
		}
		else cout << "\nEroare la deschiderea fisierului";
		g.close();
	}

	void raport2CheltSanatate(char* numeFisier, int nrCheltSanat, CheltSanatate* listachelt)
	{
		ofstream g;
		g.open(numeFisier, ios::out);
		if (g.is_open())
		{
			float k = 0;
			for (int i = 0; i < nrCheltSanat; i++)
				k += listachelt[i].medieinterv();
			k /= nrCheltSanat;
			cout << "\nO interventie costa in medie: " << k << " lei.";
			g << "\nO interventie costa in medie: " << k << " lei.";
		}
		else cout << "\nEroare la deschiderea fisierului.";
		g.close();
	}

	//Citire fisier CSV Client
	void citireCSVClient(char* numeFisier, Client& cl)
	{
		ifstream f;
		f.open(numeFisier, ios::in);

		if (f.is_open())
		{
			char* p;
			char* linie;
			char ma[10][100];

			linie = new char[100];

			for (int k = 0; k < 10; k++)
				strcpy(ma[k], "0");

			if (cl.nume != NULL)
				delete[] cl.nume;

			while (f.good())
			{
				f.getline(linie, 100);
				p = strtok(linie, ",");

				int j = 0;

				while (p != NULL)
				{
					strcpy(ma[j], p);
					j++;
					p = strtok(NULL, ",");
				}

				cl.nume = new char[strlen(ma[0]) + 1];
				strcpy(cl.nume, ma[0]);

				char* psalarii;
				psalarii = strtok(ma[1], " ");
				int l = 0;
				char a[100];
				while (psalarii != NULL)
				{
					strcpy(a, psalarii);
					cl.salarii[l] = atof(a);
					l++;
					psalarii = strtok(NULL, " ");
				}
			}
		}
		else cout << "\nEroare deschidere fisier.";
		f.close();
	}

	//Citire CSV CrediteBancare
	void citireCSVCredBanc(char* numeFisier, CrediteBancare& cb)
	{
		ifstream f;
		f.open(numeFisier, ios::in);

		if (f.is_open())
		{
			char* p;
			char* linie;
			char ma[10][100];

			linie = new char[100];

			int i = 0;
			while (i < 10)
			{
				strcpy(ma[i], "0");
				i++;
			}

			if (cb.numeDator != NULL)
				delete[] cb.numeDator;

			if (cb.numeBanca != NULL)
				delete[] cb.numeBanca;

			while (f.good())
			{
				f.getline(linie, 100);
				p = strtok(linie, ",");

				int j = 0;

				while (p != NULL)
				{
					strcpy(ma[j], p);
					j++;
					p = strtok(NULL, ",");
				}

				cb.numeDator = new char[strlen(ma[0]) + 1];
				strcpy(cb.numeDator, ma[0]);

				cb.numeBanca = new char[strlen(ma[1]) + 1];
				strcpy(cb.numeBanca, ma[1]);

				char* pdata;
				pdata = strtok(ma[2], " ");
				int l = 0;
				char a[100];
				while (pdata != NULL)
				{
					strcpy(a, pdata);
					cb.data[l] = atoi(a);
					l++;
					pdata = strtok(NULL, " ");
				}

				cb.sumadatorata =  atof(ma[3]);
				
				cb.dobanda = atof(ma[4]);
			}
		}
		else cout << "\nEroare deschidere fisier.";
		f.close();
	}

	//Citire CSV Intretinere
	void citireCSVIntretinere(char* numeFisier, Intretinere& it)
	{
		ifstream f;
		f.open(numeFisier, ios::in);

		if (f.is_open())
		{
			char* p;
			char* linie;
			char ma[10][100];

			linie = new char[100];

			int i = 0;
			while (i < 10)
			{
				strcpy(ma[i], "0");
				i++;
			}

			if (it.numelocatar != NULL)
				delete[] it.numelocatar;

			while (f.good())
			{
				f.getline(linie, 100);
				p = strtok(linie, ",");

				int j = 0;

				while (p != NULL)
				{
					strcpy(ma[j], p);
					j++;
					p = strtok(NULL, ",");
				}

				it.numelocatar = new char[strlen(ma[0]) + 1];
				strcpy(it.numelocatar, ma[0]);

				char* pdata;
				pdata = strtok(ma[1], " ");
				int l = 0;
				char a[100];
				while (pdata != NULL)
				{
					strcpy(a, pdata);
					it.data[l] = atoi(a);
					l++;
					pdata = strtok(NULL, " ");
				}

				it.costapa = atof(ma[2]);

				it.costgaze = atof(ma[3]);

				it.total = it.costapa + it.costgaze;
			}
		}
		else cout << "\nEroare deschidere fisier.";
		f.close();
	}

	//Citire fisier CSV Telefonie
	void citireCSVTelefonie(char* numeFisier, Telefonie& tel)
	{
		ifstream f;
		f.open(numeFisier, ios::in);

		if (f.is_open())
		{
			char* p;
			char* linie;
			char ma[10][100];

			linie = new char[100];

			int i = 0;
			while (i < 10)
			{
				strcpy(ma[i], "0");
				i++;
			}

			if (tel.numeclient != NULL)
				delete[] tel.numeclient;

			while (f.good())
			{
				f.getline(linie, 100);
				p = strtok(linie, ",");

				int j = 0;

				while (p != NULL)
				{
					strcpy(ma[j], p);
					j++;
					p = strtok(NULL, ",");
				}

				tel.numeclient = new char[strlen(ma[0]) + 1];
				strcpy(tel.numeclient, ma[0]);

				char* ppretab;
				ppretab = strtok(ma[1], " ");
				int l = 0;
				char a[100];
				while (ppretab != NULL)
				{
					strcpy(a, ppretab);
					tel.pretab[l] = float(atof(a));
					l++;
					ppretab = strtok(NULL, " ");
				}

				tel.nrabonamente = atoi(ma[2]);
			}
		}
		else cout << "\nEroare deschidere fisier.";
		f.close();
	}

	//Citire fisier CSV CheltSanatate
	void citireCSVCheltSanatate(char* numeFisier, CheltSanatate& cs)
	{
		ifstream f;
		f.open(numeFisier, ios::in);

		if (f.is_open())
		{
			char* p;
			char* linie;
			char ma[10][100];

			linie = new char[100];

			int i = 0;
			while (i < 10)
			{
				strcpy(ma[i], "0");
				i++;
			}

			if (cs.numeasigurat != NULL)
				delete[] cs.numeasigurat;

			while (f.good())
			{
				f.getline(linie, 100);
				p = strtok(linie, ",");

				int j = 0;

				while (p != NULL)
				{
					strcpy(ma[j], p);
					j++;
					p = strtok(NULL, ",");
				}

				cs.numeasigurat = new char[strlen(ma[0]) + 1];
				strcpy(cs.numeasigurat, ma[0]);

				char* ppretin;
				ppretin = strtok(ma[1], " ");
				int l = 0;
				char a[100];
				while (ppretin != NULL)
				{
					strcpy(a, ppretin);
					cs.pretin[l] = float(atof(a));
					l++;
					ppretin = strtok(NULL, " ");
				}

				cs.nrinterventii = atoi(ma[2]);
			}
		}
		else cout << "\nEroare deschidere fisier.";
		f.close();
	}
};

class familieTelefonie:public Telefonie
{
	// In caz ca o familie are abonamente telefonice pe numele mai multor membri
private:
	int nrPersoaneAb; //numar persoane abonate
	Telefonie** abPers;
	const int idFamilie;
public:

	familieTelefonie(int idFamilie, int nrPersoaneAb, Telefonie** abPers):idFamilie(idFamilie)
	{
		this->nrPersoaneAb = nrPersoaneAb;
		if (abPers != NULL)
		{
			this->abPers = new Telefonie*[nrPersoaneAb];
			for (int i = 0; i < nrPersoaneAb; i++)
				this->abPers[i] = abPers[i];
		}
		else this->abPers = NULL;
	}

	familieTelefonie(const familieTelefonie &ft):idFamilie(ft.idFamilie)
	{
		this->nrPersoaneAb=ft.nrPersoaneAb;
		if (ft.abPers != NULL)
		{
			this->abPers = new Telefonie*[ft.nrPersoaneAb];
			for (int i = 0; i < ft.nrPersoaneAb; i++)
				this->abPers[i] = ft.abPers[i];
		}
		else this->abPers = NULL;
	}

	~familieTelefonie()
	{
		if(this->abPers!=NULL)
			delete[] this->abPers;
	}

	friend ostream& operator<<(ostream& out, const familieTelefonie& ft)
	{
		out << "\nID-ul familiei este " << ft.idFamilie << " si are " << ft.nrPersoaneAb << " persoane.";
		for (int i = 0; i < ft.nrPersoaneAb; i++)
			out << *ft.abPers[i];
		return out;
	}
};

class IntretinereCam: public Intretinere
{
private:
	int nrCamere;

public:
	IntretinereCam(int nrCamere):Intretinere()
	{
		cout<<"\nConstructor derivare Intretinere\n";
		this->nrCamere = nrCamere;
	}

	IntretinereCam(char* numelocatar, int nrCamere):Intretinere(numelocatar)
	{
		cout<<"\nConstructor derivare Intretinere\n";
		this->nrCamere=nrCamere;
	}

	float calculCam()
	{
		return this->get_total()/this->nrCamere;
	}
};

class DerivCheltSan:public CheltSanatate
{
private:
	int varsta;
public:
	DerivCheltSan(char* numeasigurat, int varsta):CheltSanatate(numeasigurat)
	{
		cout<<"\nConstructor derivare CheltSanatate\n";
		this->varsta= varsta;
	}

	DerivCheltSan(char* numeasigurat, int varsta, unsigned nrinterventii, float* pretin):CheltSanatate(numeasigurat, nrinterventii, pretin)
	{
		cout<<"\nConstructor derivare CheltSanatate\n";
		this->varsta=varsta;
	}

	float calculInterv() const //returneaza cati an pe interventii are
	{
		return this->varsta / (float)this->get_nrinterventii();
	}
};

bool operator<(Intretinere a, Intretinere b)
{
	if (a.get_total() > b.get_total())
		return true;
	else return false;
}

void main()
{
	Files fIn;
	Files fOut;
	float v2[12], v1[12];
	for (int i = 0; i < 12; i++)
		v2[i] = static_cast<float>(i) + 3, v1[i] = float(i) + 10;

	Client listaclienti[10];
	listaclienti[0] = Client("Romeo", v2);
	listaclienti[1] = Client("Mihaela", v1);

	CrediteBancare listacb[5];
	listacb[0] = CrediteBancare("Viorica", "Banca Transilvania", 1.2, 2000, 24, 10, 2017);
	listacb[1] = CrediteBancare("Darius", "BRD", 1.3, 4500, 28, 8, 2015);

	Intretinere listabloc[5];
	listabloc[0] = Intretinere("Leonard", 100, 150, 24, 12, 2017);
	listabloc[1] = Intretinere("Dorin", 300, 125, 15, 03, 2012);

	Telefonie listatelefon[3];
	float xt[5], xt1[5];
	for (int i = 0; i < 5; i++)
		xt[i] = (float)i + 2 + 3, xt1[i] = (float)i + 10 + 2;
	listatelefon[0] = Telefonie("Raul", 5, xt);
	listatelefon[1] = Telefonie("Mimi", 5, xt1);

	CheltSanatate listachsan[3];
	float vch[] = {3,1,2};
	float vch1[] = {1,4,9,20};
	listachsan[0] = CheltSanatate("Leonard", 3, vch);
	listachsan[1] = CheltSanatate("Robi", 4, vch1);

	//Meniu
	int choice;
	cout << "\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\n-------------++++-----------------Managerul bugetului-----------------+++++--------------";

	do
	{
		cout << "\n\nCATEGORIILE DISPONIBILE:";
		cout << "\n1.Categoria CLIENT";
		cout << "\n2.Categoria CREDITE BANCARE";
		cout << "\n3.Categoria INTRETINERE";
		cout << "\n4.Categoria TELEFONIE";
		cout << "\n5.Categoria CHELTUIELI CU SANATATEA";
		cout << "\n6.Testare compunere clase+STL";
		cout << "\n7.IESIRE";
		cout << "\n\nIntroduceti numarul categoriei dorite: ";

		cin >> choice;

		switch (choice)
		{
		case 1:
			{
				int choice1;
				do
				{
					cout << "\n11. Testare faza 1";
					cout << "\n12. Testarea rapoarte";
					cout << "\n13. Testare fisiere";
					cout << "\n14. Testare fisiere CSV";
					cout << "\n15. IESIRE";
					cout << "\nIntroduceti numarul categoriei dorite: ";
					cin >> choice1;

					switch (choice1)
					{
					case 11:
						{
							float v[13];
							for (int i = 0; i < 12; i++)
								v[i] = 1;
							Client a("Mihaela", v);
							cout << a;
							Client b("Maria");
							cin >> b;
							cout << "\n\nNumele introdus de la tastatura se va schimba in Stela\n";
							b.modifnume("Stela"); //Va modifica numele introdus de la tastatura in Stela
							cout << b;

							b.modifsalariu();
							cout << b;

							a.numararecaractere();

							a.compararecl(b);

							if (a < b)
								cout << "\nOperator<: " << b.getnume() << " a produs mai multi bani decat " << a.getnume() << ".";
							else
								cout << "\nOperator<: " << b.getnume() << " a produs mai putini bani decat /la fel ca " << a.getnume() <<
									".";

							cout << "\nSuma primelor 4 luni(operator []): " << a[4]; //Va afisa suma primelor 4 luni

							cout << "\nOperator+: ";
							a.operator+(15);
							cout << a;

							cout << "\n++pre\n";
							++a; // creste cu 100, bonus la salariu
							cout << a << "\n++post\n";
							a++; // creste cu 100, bonus la salariu
							cout << endl << a;

							cout << "\nOperator cast: ";
							cout << int(a) << endl;

							cout << "Set, se va schimba numele din Mihaela in Popa:\n";
							a.setnume("Popa");
							cout << a;
							break;
						}

					case 12:
						{
							fIn.RapMedieCostClient("Text2.txt", 2, listaclienti);
							fIn.RapListaCompletaClient("Text3.txt", 2, listaclienti);
							fIn.RapListaCompletaClient("C:\\Users\\Cristi\\Desktop\\FisierDesk.txt", 2, listaclienti);
							break;
						}
					case 13:
						{
							fOut.scrietxtclient("AfisClient.txt", listaclienti[0]);
							fOut.scrieClientBin("S_ClientBinar.txt", listaclienti[0]);
							fIn.citestetxtclient("CitClient.txt", listaclienti[0]);
							fIn.citesteClientBin("C_BinClient.txt", listaclienti[0]);
							break;
						}
					case 14:
						{
							Client clcsv;
							fIn.citireCSVClient("clientcsv.csv", clcsv);
							cout << clcsv;
							break;
						}
					case 15:
						{
							cout << "\nAti ales sa iesiti";
							break;
						}
					default:
						{
							cout << "\nNu ati introdus un cod corect, va rog sa reincercati" << endl;
							break;
						}
					}
				}
				while (choice1 != 15);
				break;
			}

		case 2:
			{
				int choice2;
				do
				{
					cout << "\n21. Testare faza 1";
					cout << "\n22. Testarea rapoarte";
					cout << "\n23. Testare fisiere";
					cout << "\n24. Testare fisiere CSV";
					cout << "\n25. IESIRE";
					cout << "\nIntroduceti numarul categoriei dorite: ";
					cin >> choice2;

					switch (choice2)
					{
					case 21:
						{
							CrediteBancare abc("Alex");
							cin >> abc;
							CrediteBancare cb2("Daniel", "ING", 12, 2500, 17, 11, 2017);
							//cin>>cb2;
							cb2.verificareFaliment(); //-verifica daca creditul este facut mai devreme de anul 1950
							cb2.sumadeinapoiat(); //calculeaza suma care trebuie inapoiata luand in calcul si dobanda
							cout << cb2;
							cout << "\nOperator -: ";
							cb2.operator-(20); //scade 20 din sumadatorata
							cout << cb2;
							cout << "\nOperator++: ";
							cb2++;
							++cb2; //Va adauga 100 de lei penalizare, in total 200
							cout << cb2;

							if (abc < cb2)
								cout << endl << abc.get_nume_dator() << " are un credit mai mic decat " << cb2.get_nume_dator() << ".";
							else
								cout << endl << cb2.get_nume_dator() << " are un credit mai mic decat " << abc.get_nume_dator() << ".";

							cout << "\nOperator[]: ";
							cb2[2]; //creste dobanda cu 2
							cout << cb2;

							cout << endl << "Operator=";
							abc = cb2;
							cout << abc;

							cout << "\nOperator cast: ";
							cout << float(cb2);

							cout << "\nOperator !: "; //face sumadatorata 0
							!cb2;
							cout << cb2;

							cb2.set_sumadatorata(99999);
							cout << cb2;
							break;
						}
					case 22:
						{
							fOut.RapCBbancaBT("Raport1CB.txt", 2, listacb);
							fOut.RaportCBdobanzi("Raport2CB.txt", 2, listacb);
							fOut.RaportCBdobanzi("C:\\Users\\Cristi\\Desktop\\FisierDesk2.txt", 2, listacb);
							break;
						}

					case 23:
						{
							fOut.scrieCreditBancBin("Afi_CB_B.dat", listacb[0]);
							fOut.scrietxtcredbanc("Afi_CB_T.txt", listacb[0]);
							fIn.citestetxtcredbanc("Cit_CB_T", listacb[0]);
							fIn.citesteCreditBancBin("Cit_CB_B.dat", listacb[0]);
							break;
						}
					case 24:
						{
							CrediteBancare credbacsv;
							fIn.citireCSVCredBanc("creditebancarecsv.csv", credbacsv);
							cout << credbacsv;
							break;
						}
					case 25:
						{
							cout << "\nAti ales sa iesiti";
							break;
						}
					default:
						{
							cout << "\nAti introdus un cod gresit, va rog sa reincercati";
							break;
						}
					}
				}
				while (choice2 != 25);
				break;
			}
		case 3:
			{
				int choice3;
				do
				{
					cout << "\n31. Testare faza 1";
					cout << "\n32. Testarea rapoarte";
					cout << "\n33. Testare fisiere";
					cout << "\n34. Testare fisiere CSV";
					cout << "\n35. IESIRE";
					cout << "\nIntroduceti numarul categoriei dorite: ";
					cin >> choice3;

					switch (choice3)
					{
					case 31:
						{
							Intretinere tr1(nullptr);
							cout << tr1;
							cin >> tr1;
							Intretinere tr2("Catalin", 100, 321, 17, 11, 2017);
							cout << tr2;
							cout << tr1;

							cout << "\nOperator []: "; //creste anul cu valoarea din interiorul parantezelor
							tr1[100]; //in cazul acesta va creste cu 100
							cout << tr1;

							cout << "\nOperator ++ post si pre: ";
							tr1++;
							++tr1; //adauga penalizari in valoare de 100 de lei;
							cout << tr1;

							cout << "\nOperator >:\n";
							if (tr1 > tr2)
								cout << tr1.get_numelocatar() << " are costuri mai mari decat " << tr2.get_numelocatar() << ".\n";
							else
								cout << tr1.get_numelocatar() << " are costuri mai mici sau egale cu " << tr2.get_numelocatar() << ".\n";

							tr1.costmaimare(); // arata care dintre cheltuieli au fost mai mari(cu apa sau cu gazele)

							tr1.extrageretreichar(); //extrage primele 3 numere ale numelui

							cout << "\nOperator cast: ";
							cout << float(tr1);

							cout << "\nOperator+: ";
							tr1 + tr2;
							cout << tr1;

							cout << "\nOperator!: ";
							!tr1;
							cout << tr1;

							cout << "\nOperator =";
							tr1 = tr2;
							cout << tr1;

							tr1.set_numelocatar("Madalin"); //va schimba numele lui Catalin in Madalin
							cout << tr1;
							break;
						}
					case 32:
						{
							fOut.CalculApaGazBl("Raport1Intretinere.txt", 2, listabloc);
							fOut.ConsumIntretEcon("Raport2Intretinere.txt", 2, listabloc);
							fIn.ConsumIntretEcon("C:\\Users\\Cristi\\Desktop\\FisierDesk3.txt", 2, listabloc);
							break;
						}
					case 33:
						{
							fOut.scrieIntretinereBin("S_Bin_Intret.dat", listabloc[0]);
							fOut.scrietxtintret("S_T_Intret.txt", listabloc[0]);
							fIn.citestetxtintret("C_T_Intret.txt", listabloc[0]);
							fIn.citesteIntretinereBin("C_Bin_Intret.dat", listabloc[0]);
							break;
						}
					case 34:
						{
							Intretinere intrcsv;
							fIn.citireCSVIntretinere("intretinerecsv.csv", intrcsv);
							cout << intrcsv;
							break;
						}
					case 35:
						{
							cout << "\nAti ales sa iesiti\n";
							break;
						}
					default:
						{
							cout << "\nAti ales un numar gresit, va rog sa reincercati\n";
							break;
						}
					}
				}
				while (choice3 != 35);
				break;
			}

		case 4:
			{
				int choice4;
				do
				{
					cout << "\n\n\n41. Testare faza 1";
					cout << "\n42. Testarea rapoarte";
					cout << "\n43. Testare fisiere";
					cout << "\n44. Testare fisiere CSV";
					cout << "\n45. IESIRE";
					cout << "\nIntroduceti numarul categoriei dorite: ";
					cin >> choice4;

					switch (choice4)
					{
					case 41:
						{
							float vec[20];
							try
							{
								Telefonie ctc("Maria", 10, vec);
							}
							catch (exception ex)
							{
								cout << ex.what();
							}

							Telefonie tlf1("Viorica");
							cin >> tlf1;

							Telefonie tlf2("Dorin");
							cin >> tlf2;

							cout << "\nOperator[]: ";
							cout << "Pretul abonamentului cu numarul 1 este: " << tlf1[1] << endl;

							cout << "\nOperator ++ post si pre ";
							++tlf1;
							tlf1++; //creste cu 10 fiecare abonament

							cout << tlf1;

							cout << "\nOperator >: ";
							if (tlf1 > tlf2)
								cout << endl << tlf1.get_numeclient() << " are mai multe abonamente decat " << tlf2.get_numeclient() << ".";
							else
								cout << endl << tlf2.get_numeclient() << " are mai multe sau egale abonamente cu " << tlf1.get_numeclient() <<
									".";

							cout << "\nOperator cast: ";
							cout << int(tlf1);

							cout << "\nSuma totala de plata suportata de " << tlf1.get_numeclient() << " este " << tlf1.totalplata();

							cout << "\nMedia preturilor abonamentelor este: " << tlf1.mediaab();

							cout << "\nOperator+";
							tlf1 + tlf2;
							cout << tlf1;

							cout << "\nOperator=";
							tlf1 = tlf2;
							cout << tlf1;

							cout << "\nOperator!";
							!tlf1;
							cout << tlf1;
							break;
						}
					case 42:
						{
							fOut.raport1telefoncl("Raport1Tel.txt", 2, listatelefon, listatelefon[1]);
							fOut.raport2telefon("Raport2Tel.txt", 2, listatelefon);
							fIn.raport2telefon("C:\\Users\\Cristi\\Desktop\\FisierDesk4.txt", 2, listatelefon);
							break;
						}

					case 43:
						{
							fOut.scrieTelefonBin("S_Bin_Telefon.dat", listatelefon[0]);
							fOut.scrietxttelefon("S_T_Telefon.txt", listatelefon[0]);
							fIn.scrieTelefonBin("C_Bin_Telefon.dat", listatelefon[0]);
							fIn.scrietxttelefon("S_T_Telefon.txt", listatelefon[0]);
							break;
						}

					case 44:
						{
							Telefonie telefoncsv;
							fIn.citireCSVTelefonie("telefoniecsv.csv", telefoncsv);
							cout << telefoncsv;
							break;
						}

					case 45:
						{
							cout << "\nAti ales sa iesiti\n";
							break;
						}
					default:
						{
							cout << "\nAti ales un numar gresit, va rog sa reincercati\n";
							break;
						}
					}
				}
				while (choice4 != 45);
				break;
			}
		case 5:
			{
				int choice5;
				do
				{
					cout << "\n\n\n51. Testare faza 1";
					cout << "\n52. Testarea rapoarte";
					cout << "\n53. Testare fisiere";
					cout << "\n54. Testare fisiere CSV";
					cout << "\n55. IESIRE";
					cout << "\nIntroduceti numarul categoriei dorite: ";
					cin >> choice5;

					switch (choice5)
					{
					case 51:
						{
							CheltSanatate c("Mmmmm");
							cin >> c;
							cout << c;

							CheltSanatate d("Maria");
							cin >> d;
							cout << d;

							cout << "\nOperator egal:";
							d = c;
							cout << d;

							cout << "\nOperator[]: " << c[2]; //afiseaza a 3-a valoare, iar daca nu exista afiseaza -1

							cout << "\nOperator+: ";
							cout << d + c; //va dubla valoarea lui c pentru ca a fost apelat operatorul = mai sus
							cout << d;

							cout << "\nMedia costurilor cu interventiile este: " << c.medieinterv() << endl;

							c++; //Creste pretul fiecarei interventii cu 1
							cout << c;

							if (c > d) //compara numarul de interventii
								cout << endl << c.get_numeasigurat() << " a suferit mai multe interventii decat " << d.get_numeasigurat() <<
									endl;
							else
								cout << endl << d.get_numeasigurat() << " a suferit mai multe interventii decat " << c.get_numeasigurat() <<
									endl;

							cout << "\nOperator Cast:";
							cout << unsigned(c) << endl;

							cout << "\nNumarul de interventii majore este: " << c.numarareintervmaj(); // se considera interventie majora
							//interventia care a costat mai mult de 100 de lei
							cout << "\nOperator!: ";
							!c; //face toate preturile interventiilor si numarul de interventii 0
							cout << c;
							break;
						}
					case 52:
						{
							fIn.raport1CheltSanatate("TextCh.txt", 2, listachsan);
							fIn.raport2CheltSanatate("TextCh2.txt", 2, listachsan);
							fIn.raport2CheltSanatate("C:\\Users\\Cristi\\Desktop\\FisierDesk5.txt", 2, listachsan); //calea
							break;
						}
					case 53:
						{
							fOut.scriechSanatateBin("A_Bin_Chsan.dat", listachsan[0]);
							fOut.scrietxtchsanatate("A_T_ChSan.txt", listachsan[0]);
							fIn.citesteCheltSanatateBin("C_Bin_Chsan.dat", listachsan[0]);
							fIn.citestetxtchsanatate("C_T_ChSan.txt", listachsan[0]);
							break;
						}
					case 54:
						{
							CheltSanatate cscsv;
							fIn.citireCSVCheltSanatate("cheltsancsv.csv", cscsv);
							cout << cscsv;
							break;
						}
					case 55:
						{
							cout << "\n\nAti ales sa iesiti\n";
							break;
						}
					default:
						{
							cout << "\n\nAti ales o optiune invalida, va rog sa reincercati\n";
							break;
						}
					}
				}
				while (choice5 != 55);
				break;
			}

		case 6:
			{
				IntretinereCam camIn("Turrr", 2);

				DerivCheltSan derIn("Danlol", 20);

				//pentru testarea compunerii claselor
				float cc[5], cc1[5];
				for (int i = 0; i < 5; i++)
					cc[i] = static_cast<float>(i) + 2 + 3, cc1[i] = static_cast<float>(i) + 10 + 2;
				Telefonie tfe("Edi", 5, cc);
				Telefonie tfd("Dani", 5, cc1);
				Telefonie *ptfe;
				Telefonie *ptfd;
				Telefonie *lTelefon[2];
				ptfe=&tfe;
				ptfd=&tfd;
				lTelefon[0]=ptfe;
				lTelefon[1]=ptfd;
				familieTelefonie FamTelE(1, 2, lTelefon);
				cout << FamTelE;

				Intretinere list1("Ungureanu", 150, 120, 21, 12, 2016);
				Intretinere list2("Dumitrescu", 300, 125, 15, 03, 2012);
				Intretinere list3("Andrei", 270, 140, 18, 06, 2014);

				cout << "\n\n**Testare lista**\n";
				list<Intretinere> listaIC;
				listaIC.push_back(list1);
				listaIC.push_back(list2);
				listaIC.push_back(list3);
				listaIC.sort();
				list<Intretinere>::iterator itIC;
				cout << "\n\nAfisare lista sortata\n";
				for (itIC = listaIC.begin(); itIC != listaIC.end(); itIC++)
					cout << *itIC << " ";

				cout << "\n\n**Testare vector**\n";
				vector<Intretinere> vectorIC;
				vectorIC.push_back(list1);
				vectorIC.push_back(list2);
				vectorIC.push_back(list3);
				for (unsigned i = 0; i < vectorIC.size(); i++)
					cout << vectorIC[i];

				cout << "\n\n**Testare map**\n";
				map<int, Intretinere> mapIC;
				map<int, Intretinere>::iterator it = mapIC.begin();
				mapIC.insert(it, std::pair<int, Intretinere>(1, list1));
				mapIC.insert(it, std::pair<int, Intretinere>(2, list2));
				mapIC.insert(it, std::pair<int, Intretinere>(3, list3));
				for (it = mapIC.begin(); it != mapIC.end(); ++it)
					cout << endl << it->first << " => " << it->second << '\n';


				cout << "\n\n**Testare SET**\n";
				set<Intretinere> setIC;
				setIC.insert(list1);
				setIC.insert(list2);
				setIC.insert(list3);

				set<Intretinere>::iterator itS;
				for (itS = setIC.begin(); itS != setIC.end(); itS++)
				{
					cout << *itS << " ";
				}

				break;
			}

		case 7:
			{
				cout << "\n\nAti ales sa iesiti din aplicatie, o zi buna!\n";
				break;
			}
		}
	}

	while (choice != 7);
}