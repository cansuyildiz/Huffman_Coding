/**
@file
Programlama Dilleri Guz 2015 Odev 1.
Bu program girilen bir stringdeki karakterlerin huffman kodlamasini cikartir
@author
Name: Elif Cansu YILDIZ
Student no: 14011067
Date: 27/11/2015
E-Mail: cansu96yildiz@gmail.com
Compiler used: GCC
IDE: Dev C++
Operating System Windows 10
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*
Frekans degerlerinin saklandigi frekans dizisinin elemanlarini kucukten buyuge siralar
@param karakter[][]		kullanicinin girdigi text[] teki farkli karakterlerin saklandigi matris
@param frekans[] 		text dizisindeki her farkli karakterin miktarini tutan dizi
@param karaktersayisi	kullanicinin girdigi text dizisindeki farkli karakterlerin sayisi
*/
void sort(int frekans[],char karakter[][2],int karaktersayisi){
	//BUBBLE SORT
	int degisim=1,i,tmp;
	char tmpchar[20];
	while(degisim==1){
		degisim=0;
		for(i=0;i<karaktersayisi-1;i++){
			if(frekans[i]>frekans[i+1]){
				tmp=frekans[i];
				frekans[i]=frekans[i+1];
				frekans[i+1]=tmp;
				strcpy(tmpchar,karakter[i]);		//karakter ile karakterin frekans degeri ayni indiste sakli olsun diye karakter dizisinin elemanlari da yer degistirilir
				strcpy(karakter[i],karakter[i+1]);
				strcpy(karakter[i+1],tmpchar);
				degisim=1;
			}
		}
	}
}

/*
Kullanicinin girdigi dizideki karakterlerin her birinin kac tane oldugunu bulur
@param text[] 			kullanicinin girdigi karakter toplulugu
@param karakter[][]		kullanicinin girdigi text[] teki farkli karakterlerin saklandigi matris
@param frekans[] 		text dizisindeki her farkli karakterin miktarini tutan dizi
@param karaktersayisi	text dizisindeki farkli karakterlerin sayisi
*/
void frekans_bulma(char text[],char karakter[][2],int frekans[],int *karaktersayisi){
	int i=0,j,kontrol;
	char x[2];
	
	while(text[i]){
		kontrol=0;
		j=0;
		x[0]=text[i];
		x[1]='\0';
		while(kontrol==0 && j<*karaktersayisi){
			if(strcmp(karakter[j],x)==0){
				frekans[j]++;
				kontrol=1;
			}
			j++;
		}
		if(kontrol==0){
			strcpy(karakter[*karaktersayisi],x);
			frekans[*karaktersayisi]=1;
			(*karaktersayisi)++;			
		}
		i++;
	}	
}
/**
Frekans dizisindeki degerleri ikili toplayarak agaca yerlestirilecek sirali diziyi olusturur
Ýki sayinin toplami ile olusturulmus degerler - ile carpilir
@param frekans[]		text dizisindeki her farkli karakterin miktarini tutan dizi
@param dizi[]			agaca yerlestirilmek icin frekans dizisinin elemanlari toplanarak yeni olusturulan dizi
@param karaktersayisi	text dizisindeki farkli karakterlerin sayisi
*/
void dizi_olusturma(int frekans[],int dizi[],int karaktersayisi){
	int k,j,m,max,toplam,i;
	max=karaktersayisi*2-1;
	j=0;

	for(i=0;i<karaktersayisi;i++){
		dizi[i]=frekans[i];
	}
	while(j+1<max){
		toplam=abs(dizi[j])+abs(dizi[j+1]);
		k=j+2;
		
		while(toplam>=abs(dizi[k]) && dizi[k]!=0){
			k++;
		}
		
		for(m=karaktersayisi-1; m>=k; m--){
			dizi[m+1]=dizi[m];
		}
			
		karaktersayisi++;
		dizi[k]=(-1)*toplam;
		j+=2;
		
	}
}

/**
Bu fonksiyon dizide tutulan degerleri agaca yerlestiriyor
@param agac[] 			agacta hangi elemanlarin oldugunu gosteren dizi
@param dizi[]			agaca yerlestirilmek icin frekans dizisinin elemanlari toplanarak yeni olusturulan dizi
@param yer[]			dizi dizisindeki elemanlarin sirayla agacta hangi indexte bulundugunu tutan dizi
@param karaktersayisi	agaca yerlestirilecek elemanlarin sayisi
*/
void agaca_yerlestirme(int agac[],int yer[],int dizi[],int karaktersayisi){
	int x=1,nokta,sayi=0,bulundu,k;
	nokta=karaktersayisi-2;
	
	agac[x]=dizi[karaktersayisi-1];  //agacin kokune dizinin son elemanini yerlestirir
	yer[karaktersayisi-1]=x; //dizinin son elemaninin agacta kacinci indexte buluncagi yer dizisine kaydedilir
	
	while(sayi<=karaktersayisi){	
		if(agac[x]<0){	//agac[x]teki deger - ise o degerin iki toplami aranir ve agaca kaydedilir
			k=nokta;
			bulundu=0;
			sayi++;		//agaca yerlestirilen elemanlarin sayisi 1 artirilir
			while(k>0 && bulundu==0){
				if(abs(agac[x])==abs(dizi[k])+abs(dizi[k-1])){	//agac[x] degerinin hangi iki art arda dizi degerinin toplamiyla olustugu aranir
					nokta=k-2;
					agac[2*x]=dizi[k];		//bulunan elemanlar agaca kaydedilir
					agac[2*x+1]=dizi[k-1];
					yer[k]=2*x;				//dizinin k. elemaninin agacta kacinci indexte oldugu yer dizisine kaydedilir
					yer[k-1]=2*x+1;
					bulundu=1;				//toplami saglayan elemanlar bulunduysa donguden cikilir
					
				}
				k--;	
			}
		}
		else{	//agac[x]teki deger + ise agaca yerlestirilen elemanlarin sayi degeri 1 artirilir
			if(agac[x]>0)
					sayi++;
			}
		x++;
	}	
}

/**
Bu fonksiyon elemanlarin agacta bulundugu indeksteki degerlere bakarak recursive islem yapiyor,huffman kodunu olusturuyor
Index degerinin cift mi tek mi oldugu kontrol ediliyor sagdan sola dogru ciftse 0 tekse 1 yazdiriliyor
Index degeri 1 olana kadar 2ye bolunuyor.
@param sayi		huffman kodu olusturulacak sayi
*/
void kod_olusturma(int sayi){
	if(sayi!=1){
		kod_olusturma(sayi/2);
		printf("%d",sayi%2);
		
	}
}
/**
Fonksiyon karakter dizisindeki elemanlarin huffman kodlamasini ekrana yazdirir
Her bir karakterin agactaki index degerine erismesi gerekmektedir.Bunun icin yer,agac ve frekans dizisinden yararlanir
@param karakter[][]		kullanicinin girdigi text[] teki farkli karakterlerin saklandigi matris
@param yer[] 			karakterlerin agacta bulundugu index degerini saklayan dizi
@param agac[] 			agacta hangi elemanlarin oldugunu gosteren dizi
@param frekans[]		text dizisindeki her farkli karakterin miktarini tutan dizi
@param karaktersayisi	text dizisindeki farkli karakterlerin sayisi
*/
void show(char karakter[][2],int agac[],int frekans[],int yer[],int karaktersayisi){
	int i,j=0,k=-1;
	//Her bir karakter agacta kacinci indexte bulunuyorsa o karakterin huffman kodu ekrana yazdirilir
	for(i=0;i<karaktersayisi;i++){
		j=k+1;
		while(frekans[i]!=agac[yer[j]]){	//ilk karakterin gosterdigi frekans degeri ile agac dizisinde yer dizisinin gosterdigi indexte bulunan elemanin degerleri ayni olana kadar bakilir
			j++;
		}
		printf("%s ",karakter[i]);
		kod_olusturma(yer[j]);  //karakterlerin huffman kodunu olusturan fonksiyonu cagirir
		printf("\n");
		k=j;
	}
}

int main(){
	char text[20],karakter[50][2];
	int frekans[50]={0},karaktersayisi,dizi[50]={0},agac[50]={0},yer[50]={0};
	
	printf("metin giriniz: ");
	gets(text);
	
	frekans_bulma(text,karakter,frekans,&karaktersayisi);	//kullanicinin girdigi texteki karakterlerin miktarini bulan fonksiyonu cagirir
	
	sort(frekans,karakter,karaktersayisi);	//karakterlerin sayisini kucukten buyuge siralayan fonksiyonu cagirir
	
	dizi_olusturma(frekans,dizi,karaktersayisi);	//agaca yerlestirmek icin gereken diziyi olusturan fonksiyonu cagirir

	agaca_yerlestirme(agac,yer,dizi,2*karaktersayisi-1);	//dizideki degerleri agaca yerlestiren fonksiyonu cagirir
	
	show(karakter,agac,frekans,yer,karaktersayisi);		//her bir karakterin huffman kodunu ekrana yazdiran fonksiyonu cagirir
	
	getch();
	return 0;
}
