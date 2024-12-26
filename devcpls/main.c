#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int rastgele(int ustlimit);     //rastgele sayi uretme fonksiyonu
int kordinatVar(int row,int x,int collumn, int y);      //kordinatlar geçerli mi için kullanılan fonksiyon
void stahtakur(int row,int collumn,char dizi[row][collumn]);    //sayi ve mayin tahtasinin kurumu
void gtahtakur(int row,int collumn, int dizi[row][collumn], int mine);    //oyuncuya gozuken tahtanin kurumu
void stahtayaz(int row, int collumn,char dizi[row][collumn]);    //gorunen tahtanin kurulumu
void gtahtayaz(int row, int collumn,int dizi[row][collumn]);    //debug icin duruyor
void kareac(int row, int collumn,int x, int y,int sayidizi[row][collumn],char karakterdizi[row][collumn]);   //verilen kareyi acar, return degeri karenin karakterinin char hali(9 icin X)
void bayrak(int row,int collumn,int x, int y,char dizi[row][collumn]);  //bayrak koymak icin
void acilis(int row,int collumn,int sayidizi[row][collumn], char karakterdizi[row][collumn]);   //oyun basinda alan vermek icin
void gameover();    //kaybetme fonksiyonu
void win();         //kazanam fonksiyonu
void bittiMi(int row,int collumn,int sayidizi[row][collumn],char karakterdizi[row][collumn],int mine);  //oyun sonu geldi mi kontrolu


int oyna=1;     //asıl oyun döngüsünü devam ettiren değişken
int kapaliKare; //oyunun devam etmesi kontrolünü yapan değişken
int mayinSAYAC; //oyuncuya kaç mayın kaldığını bildiren değişken

int main(void) {
    srand(time(NULL));  //rastgele sayi seedi
    int satir, sutun,mayin;  //tahta oluşturma için kullanılacak değişkenler

    while (1) {     //istenen satir sayısı girilimesi
        printf("satir sayisi giriniz, tavsiye edilen max 10, min 5\n");
        scanf("%d",&satir);
        if (satir>10 || satir<5) {
            printf("lutfen gecerli bir satir sayisi giriniz\n");
            continue;
        }
        else {
            break;
        }
    }
    while (1) {     //istenen sutun sayısı girilmesi
        printf("sutun sayisi giriniz, tavsiye edilen max 10,min 5\n");
        scanf("%d",&sutun);
        if (sutun>10 || sutun<5) {
            printf("lutfen gecerli bir sutun sayisi giriniz\n");
            continue;
        }
        else {

            break;
        }
    }
    kapaliKare=satir*sutun;
    int zorluk;
    while (1) {     //Seçilen zorluğa göre mayın sayısı atanması
        printf("Zorluk seviyesi seciniz:\n1-Kolay\n2-Orta\n3-Zor");
        scanf(" %d",&zorluk);
        if (zorluk==1) {
            mayin=(int)(satir*sutun*0.1);
            mayinSAYAC=mayin;
            break;
        }
        else if (zorluk==2){
            mayin=(int)(satir*sutun*0.15);
            mayinSAYAC=mayin;
            break;
        }
        else if (zorluk==3) {
            mayin=(int)(satir*sutun*0.32);
            mayinSAYAC=mayin;
            break;
        }
        else {
            printf("Lutfen gecerli bir zorluk seciniz");
        }
    }
    int gtahta[satir][sutun];       //tahtalarin tanitilmasi
    char stahta[satir][sutun];

    gtahtakur(satir,sutun,gtahta,mayin);
    stahtakur(satir,sutun,stahta);      //tahtalarin kurulmasi

    int x,y;    //kordiant inputu için kullanılacak değişkenler
    char hamle='a';     //hamle inputu için kullanılacak değişken
    acilis(satir,sutun,gtahta,stahta);  //baslangic alani olusturma

    do {      //oyun oynama dongusu
        stahtayaz(satir,sutun,stahta);      //oyun tahtasinin yazlisi


        while (1) {         //hamle icin satir inputu
            printf("acmak istediginiz satiri yaziniz");
            scanf("%d",&x);
            if (x>=0 && x<=satir) {
                break;
            }
            else {
                printf("Gecerli bir satir giriniz");
            }
        }
        while (1) {         //hamle icin sutun inputu
            printf("acmak istediginiz sutun yaziniz");
            scanf("%d",&y);
            if (y>=0 && y<=sutun) {
                break;
            }
            else {
                printf("Gecerli bir sutun giriniz");
            }
        }       //hamle için karakter inputu
        while (1) {
            printf("Kareyi acmak istiyorsaniz a, bayrak koymak istiyorsaniz f giriniz \n");
            scanf(" %c",&hamle);

            if (hamle=='a') {
                kareac(satir,sutun,x,y,gtahta,stahta);
                break;
            }
            else if (hamle=='f') {
                bayrak(satir,sutun,x,y,stahta);
                break;
            }
            else {
                printf("Lutfen gecerli bir hamle giriniz\n");

            }
        }
    bittiMi(satir,sutun,gtahta,stahta,mayin);
    }
    while (oyna);

    return 0;
}
//-----------------------------//
void bittiMi(int row,int collumn,int sayidizi[row][collumn],char karakterdizi[row][collumn],int mine) {     //oyun sonu geldi mi kontrolu
    if (kapaliKare==mine) {
        win();
    }

}
/////////////////////////////////
void win() {        //oyun kazanma bildirisi
    printf("Kazandin!!! WOOOO!!!\n");
    oyna=0;
}
/////////////////////////////////
void gameover() {       //oyun kaybetme bildirisi
    printf("Kaybettin! Actigin kare mayindi!");
    oyna=0;
}
/////////////////////////////////
int kordinatVar(int row,int x,int collumn, int y) {     //girilen kordinatlarin satir ve sutun icinde var mı kontrolu
    if (x<0 || x>row-1 || y<0 || y>collumn-1) {
        return 0;
    }
    else {
        return 1;
    }
}
/////////////////////////////////

void acilis(int row,int collumn,int sayidizi[row][collumn], char karakterdizi[row][collumn]) {      //oyun açıldığında başlangıç alanı oluşturma
    while (1) {
        int x= rastgele(row);
        int y= rastgele(collumn);
        if (sayidizi[x][y]==0) {        //rastgele bir kare seçer ve 0 ise o kareyi açar
            kareac(row, collumn,x,y,sayidizi,karakterdizi);
            break;
        }
    }
}


/////////////////////////////////
void bayrak(int row,int collumn,int x, int y, char dizi[row][collumn]) {     //bayrak koyma fonksiyonu, stahtadaki karakterleri manipule ederek yapiyor
    if (dizi[x][y] == '*') {
        dizi[x][y]='X';     //X bayrak karakteri
        mayinSAYAC-=1;
    }
    else if (dizi[x][y] == 'X') {
        dizi[x][y]='*';
        mayinSAYAC+=1;
    }
    else {
        printf("Acik olan karelere bayrak konulamaz\n");
    }
}
/////////////////////////////////
void kareac(int row, int collumn,int x, int y,int sayidizi[row][collumn],char karakterdizi[row][collumn]) {  //gtahtadan alinan degerin stahtaya gecirilmesi icin  //xy kordinatli kare stahtada acilmissa kontrole sokma
    int sayi = sayidizi[x][y];
    char karakter = karakterdizi[x][y];
    char cikti='X';
    if (karakter=='*' || karakter=='F'){ //kare acilmamis ise kontrolu
       if (sayi==9) {     //acilan kare mayinsa oyun biter
           gameover();
       }
       else if (sayi!=0) {      //acilan kare mayin degilse stahtaya gecirilir
           cikti='0'+sayi;      //int degerini char karsiligina gecirme
           karakterdizi[x][y]=cikti;
           kapaliKare-=1;
       }
       else  {          //acilan kare sifirsa ozel durum oldugu icin etrafindaki kareler sifir mi diye bakilir
           cikti='0'+sayi;      //
           karakterdizi[x][y]=cikti;
           kapaliKare-=1;
            for (int i=-1;i<=1;i++) {
                 for (int j=-1;j<=1;j++) {
                     int komsusayi=sayidizi[x+i][y+j];
                     char komsukarakter=karakterdizi[x+i][y+j];
                     if (kordinatVar(row,x+i,collumn,y+j)==1 && komsusayi!=9 && komsukarakter== '*' ) {      //etrafinda sifir oldugu
                         kareac(row,collumn,x+i,y+j,sayidizi,karakterdizi);
                     }
                 }
            }
       }
    }
    else {
        printf("Kare zaten acilmis\n");
    }
}
/////////////////////////////////
void gtahtayaz(int row, int collumn,int dizi[row][collumn]) {       //gtahtayaz(satir,sutun,gtahta) seklinde cagir

    for (int i =0;i<row;i++) {
        for (int j=0;j<collumn;j++) {
            printf("[%d]",dizi[i][j]);
        }
        printf("\n");
    }
}
/////////////////////////////////
void stahtayaz(int row, int collumn,char dizi[row][collumn]) {
    printf("  ");
    for (int a=0;a<collumn;a++) {
        printf(" %d ",a);
    }
    printf("\n");
    for (int i=0; i<row; i++) {
        printf("%d ",i);
        for (int j=0; j<collumn; j++) {
            printf("[%c]",dizi[i][j]);
        }
        printf("\n");
    }
    printf("\nKalan mayin= [%d]\n",mayinSAYAC);     //kalan mayın sayacı
}
/////////////////////////////////
void gtahtakur(int row,int collumn, int dizi[row][collumn],int mine) {
    //tahtanin matris olarak kurlumu
    for (int i=0;i<row;i++) {
        for ( int j=0;j<collumn;j++) {
            dizi[i][j]=0;
        }
    }

    //karelere mayin eklenmesi
    int m=0;
    while (m<mine) {
        int x=rastgele(row);
        int y=rastgele(collumn);

        if (dizi[x][y]==9) {
            continue;   //rastgele gelen kare zaten mayin ise islem yapmadan basa don
        }
        dizi[x][y]=9;   //kareyi mayin olarak ata
        for (int i=-1;i<=1;i++) {
            for (int j=-1;j<=1;j++) {   //sirasiyla etrafindaki karelerin kontrolu
                if (kordinatVar(row,x+i,collumn,y+j)==0) {     //eger kare tahtanin disindaysa islem yapma
                    continue;
                }
                else if (dizi[x+i][y+j]==9) {       //kare mayin ise islem yapma
                    continue;
                    }
                else {      //mayin etrafindaki kareyi +1 yap
                    dizi[x+i][y+j]+=1;
                }
            }
        }
        m+=1;   //mayin sayacini +1 yap
    }
}
/////////////////////////////////
void stahtakur(int row,int collumn,char dizi[row][collumn]) {
    for (int i=0;i<row;i++) {
        for (int j=0;j<collumn;j++) {
            dizi[i][j]='*';
        }
    }
}
/////////////////////////////////
int rastgele(int ustlimit) {    //rastgele sayi uretimi
    int cikti=rand()%(ustlimit);
    return cikti;
}





