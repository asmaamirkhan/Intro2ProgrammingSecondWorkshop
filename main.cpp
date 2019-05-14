#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<fstream>
using namespace std;

class Nesil{
private:
    int boyut;
    int sag_say;
    int olu_say;
    int zombie_say;
    int ** nesilMatrisi;
    static int inci_nesil;
public:
    Nesil();
    Nesil(int);
    void ilkNesilUret();
    void nesilGoster();
    void nesilYazdir();
    void yasaVeyaOl();
    bool canlandi_mi(int, int);
    bool oldu_mu(int, int);
    void istatistik_yap();
};

void Nesil::nesilYazdir(){
	ofstream nesilDosya;
	nesilDosya.open("Nesiller.txt", ios::app);
	nesilDosya << "************** " <<inci_nesil<<".Nesil **************\n";

	int i,j;
	for(i = 0; i < boyut; i++){
		for(j = 0; j < boyut; j++){
			nesilDosya << "| " <<nesilMatrisi[i][j] << " |";
		}
		nesilDosya << endl <<"--------------------------" << endl;
	}
	nesilDosya << "Insan sayisi = " << sag_say << endl
			   << "Olu sayisi = " << olu_say << endl
			   << "Zombie sayisi = " << zombie_say<< endl << "**************************" <<endl;

	nesilDosya.close();
}


int Nesil::inci_nesil=0;

Nesil::Nesil(){
    boyut =0;
    sag_say=0;
    olu_say=0;
    zombie_say=0;
    nesilMatrisi=NULL;
}

Nesil::Nesil(int boyut){
    this->boyut = boyut;
    nesilMatrisi = new int * [boyut];
    for(int i=0; i<boyut; i++){
        nesilMatrisi[i] = new int [boyut];
    }
    ilkNesilUret();
}

void Nesil::ilkNesilUret(){
    int i,j;
    srand(time(NULL));
    for(i=0; i<boyut; i++){
        for(j=0; j<boyut; j++){
            nesilMatrisi[i][j] = rand()%3;
        }
    }
}

void Nesil::yasaVeyaOl(){
    int ** nesilMatrisi2, i, j;
    nesilMatrisi2 = new int *[boyut];
    for(i=0; i<boyut; i++){
        nesilMatrisi2[i] = new int [boyut];
    }

    for(i=0; i<boyut; i++){
        for(j=0; j<boyut; j++){

            //olu 0, sag 1, zombie 2
            //olu 0
            if(nesilMatrisi[i][j]==0){
                if(canlandi_mi(i,j)){
                    nesilMatrisi2[i][j]=1;
                }else{
                    nesilMatrisi2[i][j]=0;
                }
            }
            // sag 1
            else if(nesilMatrisi[i][j] == 1){
                if(oldu_mu(i,j)){
                    nesilMatrisi2[i][j]=0;
                }else{
                    nesilMatrisi2[i][j]=1;
                }
            }else{
                nesilMatrisi2[i][j] = 2;
            }
        }
    }

    for(i=0; i<boyut; i++){
        for(j=0; j<boyut; j++){
            nesilMatrisi[i][j] = nesilMatrisi2[i][j];
        }
    }
    inci_nesil++;
}

void Nesil::istatistik_yap(){
    int i,j;
    this->olu_say=0;
    this->sag_say=0;
    this->zombie_say = 0;
    for(i=0; i<boyut; i++){
        for(j=0; j<boyut; j++){
            if(nesilMatrisi[i][j]==0)
                olu_say++;
            else if(nesilMatrisi[i][j]==1)
                sag_say++;
            else
                zombie_say++;
        }
    }
}

void Nesil::nesilGoster(){
    istatistik_yap();
    int i,j;
    cout<<"------- "<< inci_nesil <<".inci nesil"<<" --------"<<endl;
    for(i=0; i<boyut; i++){
        for(j=0; j<boyut; j++){
            cout<<nesilMatrisi[i][j]<<" || ";
        }
        cout<<"\n-----------------------------\n";
    }
    cout<<"Istatistk: Sag Sayisi: "<<sag_say<<", Olu Sayisi: "<<olu_say<<", Zombie Saisi: "<<zombie_say;
    cout<<endl<<endl;
    nesilYazdir();
}

bool Nesil::canlandi_mi(int satir, int sutun){
    int k,m,temp=0;
    for(k=-1; k<2; k++){
        for(m=-1; m<2; m++){
            if(m==0 && k==0)
                continue;
            if(sutun+m < boyut && satir+k<boyut && sutun+m>=0 && satir+k>=0){
                if(nesilMatrisi[satir+k][sutun+m]==1){
                    temp++;
                }
            }
        }
    }
    if(temp==3){
        return true;
    }else{
        return false;
    }
}

bool Nesil::oldu_mu(int satir, int sutun){
    int k,m,temp_i=0, temp_z=0;
    for(k=-1; k<2; k++){
        for(m=-1; m<2; m++){
            if(m==0 && k==0)
                continue;
            if(sutun+m < boyut && satir+k < boyut && sutun+m>=0 && satir+k>=0){
                if( nesilMatrisi[satir+k][sutun+m]==1){
                    temp_i++;
                }else if(nesilMatrisi[satir+k][sutun+m]==2){
                    temp_z++;
                }
            }
        }
    }
    if((temp_i == 2|| temp_i==3) && (temp_z<2)){
        return false;
    }else{
        return true;
    }
}

int main()
{
    int boyut, m;
    cout<<"Boyut gir: ";
    cin>>boyut;
    Nesil n(boyut);
    n.nesilGoster();
    cout<<"Sayi gir: ";
    cin>>m;
    for(int i=0; i<m; i++){
        n.yasaVeyaOl();
        n.nesilGoster();
    }
}
