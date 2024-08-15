#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define RECORD_LENGTH 2
#define ADRESS_LENGTH 4
#define RECORD_TYPE_LENGTH 2
#define CHECKSUM_LENGTH 2


typedef struct HexElements
{
    char Record_Length[3];
    char Adress[5];
    char Record_Type[3];
    char Data[33];
    char checkSum[3];

}HexElements;

typedef struct HexDegerler
{
    uint32_t recordLength;
    uint32_t adress;
    uint32_t recordType;
    uint64_t data;
    int checksum;

}HexDegerler;


char Databin[256];
int datagecici;
int databin2 ;

char adressbin[10];
int adressgecici;


void hex_to_bin(const char *hex_file,const char *bin_file)
{

    FILE *hex_f = fopen(hex_file,"r");
    if(hex_f == NULL)
        printf("Hex Dosyasi Acilmadi.");
    else
        printf("acildi\n");

    FILE *bin_f = fopen(bin_file, "wb");
    if (bin_f == NULL) {
        printf("Bin Dosyası Açılamadı.\n");
        fclose(hex_f);
        return;
    }

    char hexlineLenght[256];

    HexElements Hex1;
    HexDegerler HexD1;

    int DATA_LENGTH;

    while (fgets(hexlineLenght, sizeof(hexlineLenght), hex_f)) {
        if(hexlineLenght[0] == ':')
        {
            // Record_Length Degiskene Atandi.
            strncpy(Hex1.Record_Length, &hexlineLenght[1], RECORD_LENGTH);
            HexD1.recordLength = strtol(Hex1.Record_Length,NULL,16);

            // Adress Degiskene Atandi.
            strncpy(Hex1.Adress,&hexlineLenght[3],ADRESS_LENGTH);
            HexD1.adress = strtol(Hex1.Adress,NULL,16);

            // Record_Type Degiskene Atandi.
            strncpy(Hex1.Record_Type,&hexlineLenght[7],RECORD_TYPE_LENGTH);
            HexD1.recordType = strtol(Hex1.Record_Type,NULL,16);

           DATA_LENGTH = HexD1.recordLength * 2;

            strncpy(Hex1.Data,&hexlineLenght[9],(DATA_LENGTH));
            HexD1.data = strtoll(Hex1.Data,NULL,DATA_LENGTH);

            strncpy(Hex1.checkSum,&hexlineLenght[9+ DATA_LENGTH],(CHECKSUM_LENGTH));
            HexD1.checksum = strtoll(Hex1.checkSum,NULL,16);

            //printf("0000");
            for(int i = 3;i <7;i+=2)
            {
                strncpy(adressbin,&hexlineLenght[i],2);
                adressgecici = strtoll(adressbin,NULL,16);
                //printf("%02X",adressgecici);
                fwrite(&adressgecici, 1, sizeof(uint8_t), bin_f);
            }
            //printf("\t");

            for(int i = 9;i< (9 + DATA_LENGTH);i+=2)
            {
                strncpy(Databin,&hexlineLenght[i],2);
                datagecici = strtoll(Databin,NULL,16);
                //printf("%02X ",datagecici);
                fwrite(&datagecici, 1, sizeof(uint8_t), bin_f);
            }
            //printf("\n");

        }
    }    
    printf("Hex Dosyasi Bin dosyasina Cevrildi !\n");
    fclose(hex_f);
    fclose(bin_f);
}

int main(int argc,char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Kullanım: %s <hex_dosya> <bin_dosya>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    hex_to_bin(argv[1],argv[2]);
    return 0;
}
