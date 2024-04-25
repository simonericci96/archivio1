//Gru06_Donzellini_Liu_Ricci
//librerie
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <string.h>
#include <time.h>
using namespace std;

//rubrica
struct rubrica{
	string cognome;
	string nome;
	string fisso;
	string mobile;
};	
//dichiaro la costante
const int MAX=1000;
	
//prototipi funzioni
void InserisciVoce(rubrica[], int, int&);	//Inseriscivoce
void CercaVoce(rubrica[], int);	//Cercavoce
void StampaVoce(const char[], rubrica[], int);	//Stampavoce
int PosLibera(rubrica[], int);	//Ricerca posizione libera
void StampaRubrica(rubrica[], int);	//Stamparubrica
void ScalaVoci(rubrica[], int&, int, int&);	//ScalaVoci
void CancellaVoce(rubrica[], int);	//CancellaVoce
void Backup(const char[], const char[], const char[], rubrica[], int, int); //Backup
void Restore(const char[], const char[], const char[], rubrica[], int&, int&);	//Restore
void OrdinaRubrica(rubrica[], int);	//Ordinarubrica
void Scambia(rubrica&, rubrica&);	//Scambia

int main(){
	//dichiaro la lunghezza
	int L=0;
	//variabile dell'ultima posizione in cui è stata inserita la voce
	int ultPos=0;
	//variabile menu
	int n;
	//variabile della posizione libera se devo scalare le voci
	int pos=0;
	//dichiaro il vettore di rubriche
	rubrica vet[MAX];
	
	do{
		do{
			//menù a scelta multipla(switch)
			cout<<"Menu: \n";
			cout<<"Inserisci voce: 1 \n";
			cout<<"Cerca voce: 2 \n";
			cout<<"Stampa voce: 3 \n";
			cout<<"Cancella voce: 4 \n";
			cout<<"Stampa rubrica: 5 \n";
			cout<<"Backup: 6 \n";
			cout<<"Restore: 7 \n";
			cout<<"Ordina rubrica per cognome: 8 \n";
			cout<<"Esci: 9 \n";
			cin>>n;
			system("cls");
		}while(n<1 || n>9); //controllo che l'opzione inserita sia nel menù
		
		switch(n){
			//caso 1 con inserisci voce
			case(1):
				//inserisco la voce
				L++;
				InserisciVoce(vet, L, ultPos);
				//guardo se ho spazi vuoti in rubrica
				pos=PosLibera(vet, L);
				if(pos!=ultPos){
					ScalaVoci(vet, L, pos, ultPos);	//se ho spazi vuoti scalo le voci
				}
			break;
			//caso 2 con cerca voce
			case(2):
				CercaVoce(vet, L);
				system("pause");
				system("cls");
			break;
			//caso 3 con stampa voce
			case(3):
				StampaVoce("StampaVoce.txt",vet,L);
				system("pause");
				system("cls");
			break;
			//caso 4 con cancellavoce
			case(4):
				CancellaVoce(vet,L);
				system("pause");
				system("cls");
			break;
			//caso 5 con stamparubrica
			case(5):
				StampaRubrica(vet,L);
				system("pause");
				system("cls");
			break;
			//caso 6 con backup
			case(6):
				Backup("Backup.txt", "Lunghezza.txt", "ultPos.txt", vet, L, ultPos);
				system("pause");
				system("cls");
			break;
			//caso 7 con restore
			case(7):
				Restore("Backup.txt", "Lunghezza.txt", "ultPos.txt", vet, L, ultPos);
				system("pause");
				system("cls");
			break;
			//caso 8 con ordinarubrica per cognome
			case(8):
				OrdinaRubrica(vet, L);
				system("pause");
				system("cls");
			break;
		}
	}while(n!=9);

return 0;
}
//FUNZIONI
//funzione inseriscivoce
void InserisciVoce(rubrica vet[], int L, int& ultPos){
	//ciclo per inserire la voce in base all'ultima posizione libera e alla lunghezza
	for(int k=ultPos; k<L; k++){
		cout<<"Inserisci il Cognome: ";
		cin>>vet[k].cognome;
		cout<<"Inserisci il Nome: " ;
		cin>>vet[k].nome;
		cout<<"Inserisci il numero fisso: ";
		cin>>vet[k].fisso;
		cout<<"Inserisci il numero cellulare: ";
		cin>>vet[k].mobile;
		system("cls");
	}
	ultPos++; //aggiorno l'ultima posizione
}

//funzione cercavoce
void CercaVoce(rubrica vet[], int L){
	string cerca ="";
	int temp=0;	//variabile di controllo
	//lettura cognome 
	cout<<"Inserisci il cognome da cercare: "<<endl;
	cin>> cerca;
	//ciclo di ricerca
	for(int k=0; k<L; k++){
		if(vet[k].cognome == cerca){
			temp=1;
			cout<<"Cognome:"<<"\t"<<"Nome:"<<"\t"<<"Num.fisso:"<<"\t"<<"Num.cellulare:"<<endl;
			cout<<vet[k].cognome<<"\t\t"<<vet[k].nome<<"\t"<<vet[k].fisso<<"\t\t"<<vet[k].mobile<<endl;
		}		
	}
	if(temp==0) cout<<"Voce non trovata"<<endl;
}

//funzione stampavoce
void StampaVoce(const char mioFile[], rubrica vet[], int L){
	//apro il file di stampavoce in scrittura
	ofstream SV(mioFile);
	string stampa ="";
	int temp=0; //variabile di controllo
	//lettura cognome
	cout<<"Inserisci il cognome della voce da stampare: "<<endl;
	cin>> stampa;
	//ciclo di ricerca
	for(int k=0; k<L; k++){
		if (!SV.is_open()) {
       		cout << "Errore nell'apertura del file." << endl;
      		return;
   		}
		if(vet[k].cognome==stampa){
			temp=1;
			//stampo la voce sul file
			SV<<"Cognome: "<<"\t"<<"Nome: "<<"\t"<<"Num.fisso: "<<"\t"<<"Num.cellulare:"<<endl;
			SV<<vet[k].cognome<<"\t\t"<<vet[k].nome<<"\t"
			<<vet[k].fisso<<"\t\t"<<vet[k].mobile<<endl;
		}
	}
	if(temp==0) cout<<"Voce non trovata"<<endl;
	else cout<<"Stampa avvenuta con successo"<<endl;
	//chiudo il file
	SV.close();
}
//funzione posizione libera
int PosLibera(rubrica vet[], int L){
	//ciclo di ricerca per la posizione libera
	for(int k=0; k<L; k++){
		if(vet[k].cognome==" "){
				return k;
			}	
		}
}
//funzione stamparubrica
void StampaRubrica(rubrica vet[], int L){
	//ciclo per stampare la rubrica completa
	for(int k=0; k<L; k++){
		cout<<"Cognome: "<<"\t"<<"Nome: "<<"\t"<<"Num.fisso: "<<"\t"<<"Num.cellulare:"<<endl;
		cout<<vet[k].cognome<<"\t\t"<<vet[k].nome<<"\t"<<vet[k].fisso<<"\t\t"<<vet[k].mobile<<endl;
	}
}
//funzione scalavoci
void ScalaVoci(rubrica vet[], int& L, int pos, int& ultPos){
	//ciclo che scala le voci a parire dalla prima posizione vuota
	for(int k=pos; k<L; k++){
		vet[k]=vet[k+1];
	}
	//aggiorno lunghezza e ultima posizione
	L--;
	ultPos--;
}
//funzione cancella voce
void CancellaVoce(rubrica vet[], int L){
	string cancella ="";
	int temp=0; //variabile di controllo
	cout<<"Inserisci il cognome da cancellare: "<<endl;
	cin>> cancella;
	//ciclo di ricerca
	for(int k=0; k<L; k++){
		if(vet[k].cognome==cancella){
			temp=1;
			//cancellazione
			vet[k].cognome=" ";
			vet[k].nome=" ";
			vet[k].fisso=" ";
			vet[k].mobile=" ";
		}
	}
	if(temp==0) cout<<"Voce non trovata"<<endl;
	else cout<<"Cancellazione avvenuta con successo"<<endl;
}
//funzione backup
void Backup(const char mioFile[], const char lung[], const char posiz[], rubrica vet[], int L, int ultPos){
	// Apre il file backup.txt in modalità scrittura
    ofstream file(mioFile);
    // Verifica se il file è stato aperto correttamente
    if (!file.is_open()) {
        cout << "Errore nell'apertura del file di backup." << endl;
        return;
    }
	else{
		//ciclo per scrivere i dati dell'agenda sul file backup
		for(int k=0; k<L; k++){	
			file<<vet[k].cognome<<"\t"<<vet[k].nome<<"\t"<<vet[k].fisso<<"\t"<<vet[k].mobile<<endl;	
    	}
    cout<<"Backup avvenuto con successo"<<endl;
	}
	file.close();
	
		//salvo la lunghezza nel file
		ofstream fL(lung);
		if(fL.is_open()){
			fL<<L;
		}
		else cout<<"File della lunghezza non aperto correttamente"<<endl;
		fL.close();
			
		//salvo l'ultima posizione nel file
		ofstream fpos(posiz);
		if(fpos.is_open()){
			fpos<<ultPos;
		}
		else cout<<"File dell'ultima posizione non aperto correttamente"<<endl;
		fpos.close();
}
//funzione restore
void Restore(const char mioFile[], const char lung[], const char posiz[], rubrica vet[], int& L, int& ultPos){
	//apro il file del bckup in lettura
	ifstream file(mioFile);
    rubrica x;
    int k=0;
    // Verifica se il file è stato aperto correttamente
    if (!file.is_open()) {
        cout << "Errore nell'apertura del file di backup." << endl;
        return;
    }
	else{
		//mentre leggo il file aggiorno l'agenda
		while((file>>x.cognome,
				file>>x.nome,
				file>>x.fisso,
				file>>x.mobile)&& (!file.eof())){
						vet[k]=x;
						k++;
					}	
    		}	
    cout<<"Restore avvenuto con successo"<<endl;
	file.close();
	//aggiorno la lunghezza 
	ifstream fL(lung);
	if(fL.is_open()){
		fL>>L;
	}
	else cout<<"File della lunghezza non aperto correttamente"<<endl;
	fL.close();
			
	//aggiorno l'ultima posizione
	ifstream fpos(posiz);
	if(fpos.is_open()){
		fpos>>ultPos;
	}
	else cout<<"File dell'ultima posizione non aperto correttamente"<<endl;
	fpos.close();
}
//funzione ordinarubrica
void OrdinaRubrica(rubrica vet[], int L){
	//ciclo che confronta il vettore con is successivo
	for(int k=0; k<L-1; k++){
		for(int j=k+1; j<L; j++){
			//se il cognmome del precedente è maggiore del successivo scambio i due vettori
			if(vet[k].cognome>vet[j].cognome) Scambia(vet[k],vet[j]); 
		}
	}
	cout<<"Ordinamento avvenuto con successo"<<endl;
}
//funzione scambia
void Scambia(rubrica& a, rubrica& b){
	rubrica c;
	c=a;
	a=b;
	b=c;
}



