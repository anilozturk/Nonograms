#include <stdio.h>
#include <stdlib.h>

int sayi_al(int,int);
void kopya_alt_yazdir(int,int [][10]);
void isaret_sec(char [][10],int [][10],int,int,int);
int main()
{
    int dogru_matris[10][10],m,c,d=0,isaret_kodu,satir,sutun,eslesti,cevap2_matris[10][10]={{0}};
    char cevap_matris[10][10];
    int i,j,satir_sutun_say[2],a=0,b,kopya_sag[10][5]={{0}},kopya_alt[5][10]={{0}};

    FILE *fptr;
    fptr=fopen("resim.txt","r");//dosya okunmak icin acilir
    while (!feof(fptr)){//dosyadaki veriler bitene kadar dongu doner
        for (i=0;i<2;i++){
            fscanf(fptr,"%d",&satir_sutun_say[i]);/*dosyadan gelen ilk iki veri satir ve sutun sayisi
            olarak diziye atanir*/
        }

        for (i=0;i<satir_sutun_say[0];i++){//dosyadan gelen diger verilerle cevap anahtari matrisi olusturulur
            for (j=0;j<satir_sutun_say[1];j++){
                fscanf(fptr,"%d",&dogru_matris[i][j]);
            }
        }
    }
    fclose(fptr);//dosya kapatýlýr
    printf("   ");

    for (i=0;i<satir_sutun_say[1];i++){
        printf("%d",i+1);//sutun numaralari yazilir
    }

    printf("\n");
    for (i=0;i<satir_sutun_say[0];i++){
        printf("\n%2d ",i+1);//satir numaralari yazilir
        b=0;
        for (j=0;j<satir_sutun_say[1];j++){
            cevap_matris[i][j]='O';//butun elemanlari O olan matris olusturulur
            printf("%c",cevap_matris[i][j]);
            if (dogru_matris[i][j]==1){
                kopya_sag[a][b]++;//sag taraftaki kopya matrisi olusturulur
                if (dogru_matris[i][j]==1 && dogru_matris[i][j+1]==0){
                    b++;//eger 1 den sonra 0 gelirse kopya matrisi yan sutuna gecirilir
                }
            }
        }

        for (m=0;m<5;m++){
            if (kopya_sag[i][m]!=0)
                printf("%2d",kopya_sag[i][m]);//sag taraftaki kopya matrisi yazilir
        }
        a++;//1 satir bittiginde kopya matrisi de bir satir atlar

    }

    for (j=0;j<satir_sutun_say[1];j++){
        c=0;
        for (i=0;i<satir_sutun_say[0];i++){
            if (dogru_matris[i][j]==1){
                kopya_alt[c][d]++;//alt taraftaki kopya matrisi olusturulur
                if (dogru_matris[i][j]==1 && dogru_matris[i+1][j]==0){
                    c++;//eger 1 den sonra 0 gelirse kopya matrisi alt satira gecirilir
                }
            }
        }
        d++;//1 sutun bittiginde kopya matrisi de bir sutun atlar
    }
    printf("\n");
    kopya_alt_yazdir(satir_sutun_say[1],kopya_alt);//alt taraftaki kopya matrisi yazdirilmak icin cagrilir

    do{
        eslesti=1;/*kullanici verileriyle cevap anahtari verilerini karsilastirmak icin olusturulan flag
        degiskeni ilk olarak dogru kabul ediliyor*/
        printf("Satir numarasini giriniz.");
        satir=sayi_al(1,satir_sutun_say[0]);//satir numarasinin istenen kosullarda girilmesi saglanir
        printf("\nSutun numarasini giriniz.");
        sutun=sayi_al(1,satir_sutun_say[1]);//sutun numarasinin istenen kosullarda girilmesi saglanir
        printf("\nIsaretleme kodunu giriniz.(1:dolu,0:bos,2:belirsiz)");
        isaret_kodu=sayi_al(0,2);//isaret kodunun istenen kosullarda girilmesi saglanir

        isaret_sec(cevap_matris,cevap2_matris,isaret_kodu,satir,sutun);/*secilen isaret koduna gore
        yapýlacak degisim belirlenir*/
        printf("\n");
        printf("   ");
        for (i=0;i<satir_sutun_say[1];i++){
            printf("%d",i+1);
        }

        printf("\n");
        for (i=0;i<satir_sutun_say[0];i++){
            printf("\n%2d ",i+1);//satir numaralari yazilir

            for (j=0;j<satir_sutun_say[1];j++){
                printf("%c",cevap_matris[i][j]);//yapilan degisiklige gore yeni olusan matris yazdirilir
            }

            for (m=0;m<5;m++){
                if (kopya_sag[i][m]!=0)
                    printf("%2d",kopya_sag[i][m]);//sag taraftaki kopya matrisi yazdirilir
            }

        }

        printf("\n");
        kopya_alt_yazdir(satir_sutun_say[1],kopya_alt);//alt taraftaki kopya matrisi yazdirilir

        for (i=0;i<satir_sutun_say[0];i++){
            for (j=0;j<satir_sutun_say[1];j++){
                if (dogru_matris[i][j]==1 && cevap2_matris[i][j]!=1)/*cevap anahtari matrisinde
                1 olan yerler kullanici matrisinde 1 degilse flag degiskeni yanlis duruma getirilir*/
                    eslesti=0;
                if (dogru_matris[i][j]!=1 && cevap2_matris[i][j]==1)/*kullanici matrisinde 1 olan
                yerler cevap anahtari matrisinde 1 degilse flag degiskeni yanlis duruma getirilir*/
                    eslesti=0;
            }
        }

    }
    while (eslesti==0);//eslesme olmadigi surece dongu doner
    printf("Tebrikler,gizli resmi ortaya cikardiniz!\n");
    return 0;
}

int sayi_al(int ALT_SINIR,int UST_SINIR)//girilen verilerin istenen kosullarda olmasi saglanir
{
    int sayi;

    do{
        printf("\nLutfen alt/ust sinir arasinda bir sayi giriniz.");
        scanf("%d",&sayi);
    }
    while (sayi<ALT_SINIR || sayi>UST_SINIR);

    return sayi;
}

void kopya_alt_yazdir(int sutun_say,int alt_matris[][10])//alt taraftaki kopya matrisi yazdirilir
{
    int l,j;

    printf("\n");
    for (l=0;l<5;l++){
        printf("   ");
        for (j=0;j<sutun_say;j++){
            if (alt_matris[l][j]==0)
                printf(" ");
            else
                printf("%d",alt_matris[l][j]);
        }
        printf("\n");
    }
}

void isaret_sec(char yanit_matris[][10],int yanit2_matris[][10],int isaret,int satir_say,int sutun_say)
{//secilen isaret koduna gore gerekli atamalar yapilir
    switch (isaret){
        case 0: yanit_matris[satir_say-1][sutun_say-1]='X';
                yanit2_matris[satir_say-1][sutun_say-1]=0;
        break;
        case 1: yanit_matris[satir_say-1][sutun_say-1]=219;
                yanit2_matris[satir_say-1][sutun_say-1]=1;
        break;
        case 2: yanit_matris[satir_say-1][sutun_say-1]='O';
                yanit2_matris[satir_say-1][sutun_say-1]=0;
        break;
    }
}
