#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Program boyunca kullan�lan "iter" pointer de�i�keni mevcut d���m� i�aret etmek i�in kullan�lm��t�r.

struct node
{
    int no;
    char ad[40];
    char soyad[40];
    char bolum[40];
    int sinif;
    struct node* next;
    struct node* prev;
};

// ogrenci bilgileri aliniyor
void ogrEkle(struct node** head)
{
    struct node ogr;
    printf("\nOgrencinin numarasini giriniz: ");
    scanf("%d", &(ogr.no));
    printf("Ogrencinin adini giriniz: ");
    scanf("%s", &(ogr.ad));
    printf("Ogrencinin soyadini giriniz: ");
    scanf("%s", &(ogr.soyad));
    printf("Ogrencinin bolumunu giriniz: ");
    scanf("%s", &(ogr.bolum));
    printf("Ogrencinin sinifini giriniz: ");
    scanf("%d", &(ogr.sinif));
    printf("Ogrenci eklendi!\n");

    dugumeOgrEkle(head, ogr.no, ogr.ad, ogr.soyad, ogr.bolum, ogr.sinif);
}

// ogrEkle fonksiyonu ile al�nan parametreler d���me eklenmek i�in dugumeOgrEkle fonksiyonuna aktar�l�yor
void dugumeOgrEkle(struct node** head, int ogr_no, char ogr_ad[], char ogr_soyad[], char ogr_bolum[], int ogr_sinif)
{
    struct node* iter = (struct node*)malloc(sizeof(struct node));
    if (iter == NULL)
    {
        printf("Hafiza tahsisi basarisiz oldu!\n");
        exit(1); // Bellek tahsisi ba�ar�s�zsa program� sonland�r�yoruz
    }
    iter->no = ogr_no;
    strcpy(iter->ad, ogr_ad);
    strcpy(iter->soyad, ogr_soyad);
    strcpy(iter->bolum, ogr_bolum);
    iter->sinif = ogr_sinif;
    iter->next = NULL;

    if (*head == NULL)
    {
        *head = iter;
    }
    else
    {
        iter->next = *head;
        *head = iter;
    }
}

// numaras� al�nan ��rencinin silme i�lemi yap�l�yor
void ogrSil(struct node** head)
{
    struct node* iter1 = *head;
    struct node* iter2 = *head;
    int num;
    printf("Silmek istediginiz ogrencinin numarasini giriniz: ");
    scanf("%d", &num);

    while (iter1 != NULL)
    {
        if (iter1->no == num)
        {
            if (iter1 == iter2)
            {
                *head = (*head)->next;
                free(iter1);
            }
            else
            {
                iter2->next = iter1->next;
                free(iter1);
            }
            printf("Ogrenci silindi!\n");
            return;
        }
        iter2 = iter1;
        iter1 = iter1->next;
    }
    printf("%d numarali ogrenci bulunamadi!\n\n", num);
}

// numaras� al�nan ��rencinin bilgileri g�steriliyor
void ogrBul(struct node* head)
{
    struct node* iter = head;
    int num;
    printf("Bulmak istediginiz ogrencinin numarasini giriniz: ");
    scanf("%d", &num);
    while (iter != NULL)
    {
        if (iter->no == num)
        {
            printf("\nOgrencinin numarasi: %d\n", iter->no);
            printf("Ogrencinin adi: %s\n", iter->ad);
            printf("Ogrencinin soyadi: %s\n", iter->soyad);
            printf("Ogrencinin bolumu: %s\n", iter->bolum);
            printf("Ogrencinin sinifi: %d\n\n", iter->sinif);
            return;
        }
        iter = iter->next;
    }
    printf("%d numarali ogrenci bulunamadi!\n\n", num);
}

// listedeki t�m ��renciler sondan ba�a do�ru ekranda g�steriliyor
void ogrleriGoster(struct node* head)
{
    struct node* iter = head;

    if (head == NULL)
    {
        printf("Listede kayitli ogrenci yok!\n");
    }
    else
    {
        while (iter != NULL)
        {
            printf("\nOgrencinin numarasi: %d\n", iter->no);
            printf("Ogrencinin adi: %s\n", iter->ad);
            printf("Ogrencinin soyadi: %s\n", iter->soyad);
            printf("Ogrencinin bolumu: %s\n", iter->bolum);
            printf("Ogrencinin sinifi: %d\n\n", iter->sinif);
            iter = iter->next;
        }
    }
}

// listedeki her bir d���m free edilerek listeden siliniyor ve listede herhangi bir bilgi kalm�yor
void listeyiYokEt(struct node** head)
{
    struct node* iter = *head;
    struct node* diger_dugum;

    while (iter != NULL)
    {
        diger_dugum = iter->next;
        free(iter);
        iter = diger_dugum;
    }
    *head = NULL;
    printf("Liste siliniyor...\n");
}

int main()
{
    struct node* head = NULL;

    // sonsuz d�ng� i�erisinde kullan�c�dan komutlar al�n�yor
    while (1)
    {
        printf("\n--------ANA MENU--------\n\n");
        printf("1.Listeye ogrenci eklemek icin 1'e basiniz.\n");
        printf("2.Listeden ogrenci silmek icin 2'e basiniz.\n");
        printf("3.Listeden ogrenci bulmak icin 3'e basiniz.\n");
        printf("4.Listede gezinmek icin 4'e basiniz.\n");
        printf("5.Listeyi silmek icin 5'e basiniz.\n");
        printf("6.Programi sonlandirmak icin 0'a basiniz.\n");
        printf("Komutu giriniz: ");
        int komut;
        scanf("%d", &komut);

        switch (komut)
        {
        case 1:
            ogrEkle(&head); // parametre olarak head'i ge�iyoruz
            break;
        case 2:
            ogrSil(&head);
            break;
        case 3:
            ogrBul(head);
            break;
        case 4:
            ogrleriGoster(head);
            break;
        case 5:
            listeyiYokEt(&head);
            break;
        case 0:
            printf("Program kapatiliyor!");
            exit(0);
        default:
            ;
        }
    }
}
