#include<iostream>
#include <string.h>

using namespace std;

typedef class Activity
{
public:
	char Id[5];
	float czas_trwania;
	int Est; //najwczesniejszy start
	int Lst; //najpozniejszy start
	int Eet; //najwczesniejszy koniec
	int Let; // najpozniejszy koniec
	int koszt;
	struct Activity *nastepniki[100];
	struct Activity *poprzedniki[100];
}

aktifitas;

int ilosc; // ilosc wezlow
int kritis; // krtyczyne 
aktifitas 
*node[100], 
*check, 
*check2, 
*activity;

void GetActivities();
void WalkListAhead();
void WalkListAback();
void CriticalPath();

int CheckActivity(char id[5], int i)
{
	for (int j = 0; j < i; j++)
	{
		if (strcmp(node[j]->Id, id) == 0)
			check = node[j];
	}
	return NULL;
}

int GetIndex(aktifitas *aux, int i)
{
	for (int j = 0; j < i; j++)
	{
		if (aux->Id == node[j]->Id)
			return j;
	}
	return 0;
}

int SetSuccessors(aktifitas *activity)
{
	int k = 0;
	while (activity->nastepniki[k] != NULL) {
		k++;
	}
	return k;
}

int main()
{
	char Key;
	do {
		node[0] = NULL;
		GetActivities();
		WalkListAhead();
		WalkListAback();
		CriticalPath();
		cout << " lagi? y\\n: ";
		cin >> Key;
	} while (Key == 'y' || Key == 'Y');
}

void GetActivities()
{
	do {
		cout << "Wprowadz ilosc dzialan ktore chcesz wykonac: ";
		cin >> ilosc;
	}
	
	while (ilosc < 2);
	for (int i = 0; i < ilosc; i++)
	{
		activity = new (class Activity);
		activity->poprzedniki[0] = NULL;
		activity->nastepniki[0] = NULL;
		cout << "Dzialania:" << (i + 1) << "\n";
		cout << "ID:";
		cin >> activity->Id;
		cout << "Czas trwania: ";
		cin >> activity->czas_trwania;
		cout << "Koszt: ";
		cin >> activity->koszt;
		int np;
		cout << "Liczba poprzednikow: ";
		cin >> np;
		node[i] = activity;
		if (np != 0) {
			char id[5];
			for (int j = 0; j < np; j++)
			{
				cout << "\t#" << (j + 1) << "Poprzednik: ";
				cin >> id;
				activity->poprzedniki[j] = new (class Activity);
				aktifitas *aux;
				aux = new (class Activity);
				int hasil;
				CheckActivity(id, i);
				if (check != NULL) {
					activity->nastepniki[j] = check;
					hasil = GetIndex(check, i);
					int k = SetSuccessors(node[hasil]);
					node[hasil]->nastepniki[k] = activity;
				}
				else {
					cout << "Blad.";
					j--;
				}
			}
		}
		else {
			activity->poprzedniki[0] = NULL;
		}

	}
}

void WalkListAhead()
{
	for (int i = 0; i <ilosc; i++)
	{
		if (node[i]->poprzedniki[0] == NULL) {
			node[i]->Est = 0;
			node[i]->Eet = node[i]->czas_trwania;
		}
		else {
			int k = 0;
			node[i]->Est = 0;
			while (node[i]->poprzedniki[k] != NULL) {
				if (node[i]->Est < node[i]->poprzedniki[k]->Eet)
					node[i]->Est = node[i]->poprzedniki[k]->Eet;
				// cout<<List[i]->Est<<" "<<List[i]->Predecessors[k]->Eet<<endl;
				k++;
			}
			node[i]->Eet =node[i]->Est + node[i]->czas_trwania;
		}
	}
}

void WalkListAback()
{
	int i;
	int max = node[0]->Eet;
	for (i = 1; i<ilosc; i++)
	{
		if (node[i]->Eet>max)
			max = node[i]->Eet;
	}
	kritis = max;
	int k = ilosc - 1;
	for (int i = k; i >= 0; i--)
	{
		if (node[i]->nastepniki[0] != NULL) {
			int k = 0;
			node[i]->Let = node[i]->nastepniki[0]->Lst;
			while (node[i]->nastepniki[k] != NULL) {
				if (node[i]->Let > node[i]->nastepniki[k]->Lst)
					node[i]->Let = node[i]->nastepniki[k]->Lst;
				k++;
			}
			node[i]->Lst = node[i]->Let - node[i]->czas_trwania;
		}
		else {
			node[i]->Let = max;
			node[i]->Lst = max - node[i]->czas_trwania;
		}
	}
}

void CriticalPath()
{
	for (int i = 0; i<ilosc; i++)
	{
		cout << "\n\tWezel:" << i << " = " << node[i]->Id;
		cout << "\n\tCzas trwania: = " << node[i]->czas_trwania;
		cout << "\n\tNajwczesniejszy start: = " << node[i]->Est;
		cout << "\n\tNajwczesniejszy koniec: = " << node[i]->Eet;
		cout << "\n\tNajpozniejszy start: = " << node[i]->Lst;
		cout << "\n\tNajpozniejszy koniec: = " << node[i]->Let;
		cout << "\n\tKoszt: = " << node[i]->koszt << endl << endl;
	}
	cout << endl;

	int total_biaya;
	total_biaya = 0;
	for (int i = 0; i<ilosc; i++)
	{
		if ((node[i]->Eet - node[i]->Let) == 0 && (node[i]->Est - node[i]->Lst) == 0)
			cout << "\t" << node[i]->Id << endl;
		total_biaya += node[i]->koszt;
	}
	cout << "\n\tCalkowity czas trwania:" << kritis;
	cout << "\n\tCalkowity koszt:" << total_biaya;
	cout << endl;
	cout << endl;


	system("pause");
	return;
}