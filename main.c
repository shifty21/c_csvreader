#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <inttypes.h>

#define MAX_STR_LEN 256
#define MAX_BOOKS 256

struct book{
    double time;
    int32_t gx;
    int32_t gy;
    int32_t gz;
    int32_t ax;
    int32_t ay;
    int32_t az;
};


struct Header{
    char szHeader[8];
    int8_t bIsIntelOrMotorola;
    double dVersionNumber;
    int32_t bDeltaTheta;
    int32_t bDeltaVelocity;
    double dDataRateHz;
    double dGyroScaleFactor;
    double dAccelScaleFactor;
    int32_t iUtcOrGpsTime;
    int32_t iRcvTimeOrCorrTime;
    double dTimeTagBias;
    char szImuName[32];
    uint8_t reserved1[4];
    char szProgramName[32];
    char tCreate[12];
    bool bLeverArmValid;
    int32_t lXoffset;
    int32_t lYoffset;
    int32_t lZoffset;
    int8_t Reserved[354];
};


struct book books[MAX_BOOKS];

/* PROTOTYPE OF FUNCTIONS */
int readBookFile();
void printBookList();


int main(int argc, char **argv)
{   
    if (argc != 3) {
        printf("Please privide input and output file names with the binary.");
        return 1;
    }
    char *csvfile = argv[1];
    char *outputfile = argv[2];
    printf("Reading the file %s and output will be %s\n", csvfile, outputfile);
    struct Header header;
    strcpy(header.szHeader,"$IMURAW\0"); 
    header.bIsIntelOrMotorola = 0;
    header.dVersionNumber = 8.7;
    header.bDeltaTheta = 0;
    header.bDeltaVelocity = 0;
    header.dDataRateHz = 100;
    header.dGyroScaleFactor = 0.00000001;
    header.dAccelScaleFactor = 0.00000001;
    header.iUtcOrGpsTime = 0 ;
    header.iRcvTimeOrCorrTime = 0;
    header.dTimeTagBias = 0;
    strcpy(header.szImuName,"ADIS16488");
    // header->reserved1 = ;
    strcpy(header.szProgramName,"Decoder");
    // header->tCreate = ;
    header.bLeverArmValid = 0;
    header.lXoffset = 0;
    header.lYoffset = 0;
    header.lZoffset = 0;
    // header->Reserved = ;

    // Check the size of fields
    // printf ("Time_t=%d,int8_t=%d,int32_t=%d,char[32]=%d,uint8_t[4]=%d,double=%d,int8_t[354]=%d \n", sizeof(time_t),sizeof(int8_t),sizeof(int32_t),sizeof(char[32]),sizeof(uint8_t[4]),sizeof(double),sizeof(int8_t[354]));
    // printf ("char[8]=%lu,bool=%lu\n", sizeof(header.tCreate), sizeof(bool));
    // printf("szHeader=%lu, bIsIntelOrMotorola=%lu\n", sizeof(header.szHeader), sizeof(header.bIsIntelOrMotorola));
    // printf("dVersionNumber=%lu, bDeltaTheta=%lu\n", sizeof(header.dVersionNumber), sizeof(header.bDeltaTheta));
    // printf("bDeltaVelocity=%lu, dDataRateHz=%lu\n", sizeof(header.bDeltaVelocity), sizeof(header.dDataRateHz));
    // printf("dGyroScaleFactor=%lu, dAccelScaleFactor=%lu\n", sizeof(header.dGyroScaleFactor), sizeof(header.dAccelScaleFactor));
    // printf("iUtcOrGpsTime=%lu, iRcvTimeOrCorrTime=%lu\n", sizeof(header.iUtcOrGpsTime), sizeof(header.iRcvTimeOrCorrTime));
    // printf("dTimeTagBias=%lu, szImuName=%lu\n", sizeof(header.dTimeTagBias), sizeof(header.szImuName));
    // printf("reserved1=%lu, szProgramName=%lu\n", sizeof(header.reserved1), sizeof(header.szProgramName));
    // printf("tCreate=%lu, bLeverArmValid=%lu\n", sizeof(header.tCreate), sizeof(header.bLeverArmValid));
    // printf("lXoffset=%lu, lYoffset=%lu\n", sizeof(header.lXoffset), sizeof(header.lYoffset));
    // printf("lZoffset=%lu, Reserved=%lu\n", sizeof(header.lZoffset), sizeof(header.Reserved));
    int isOK = 0;

    isOK = readBookFile(header,csvfile, outputfile);
    printf("Run Completed!\n");
    return 0;
}

int readBookFile(struct Header header,char *csvfile, char *outputfile)
{
    // printf ("size of struct %lu\n",sizeof(struct Header));
    FILE* f = fopen(outputfile, "w");
    int64_t total_size = 0;
    total_size = sizeof(header.szHeader)+ sizeof(header.bIsIntelOrMotorola) +sizeof(header.dVersionNumber)+
                    sizeof(header.bDeltaTheta)+ sizeof(header.bDeltaVelocity)+sizeof(header.dDataRateHz)+
                    sizeof(header.dGyroScaleFactor)+sizeof(header.dAccelScaleFactor)+ sizeof(header.iUtcOrGpsTime)+
                    sizeof(header.iRcvTimeOrCorrTime)+sizeof(header.dTimeTagBias)+sizeof(header.szImuName)+
                    sizeof(header.reserved1)+ sizeof(header.szProgramName)+sizeof(header.tCreate)+
                    sizeof(header.bLeverArmValid)+sizeof(header.lXoffset)+sizeof(header.lYoffset)+
                    sizeof(header.lZoffset)+sizeof(header.Reserved);
    fwrite(&header.szHeader, sizeof(header.szHeader), 1, f);
    fwrite(&header.bIsIntelOrMotorola, sizeof(header.bIsIntelOrMotorola), 1, f);
    fwrite(&header.dVersionNumber, sizeof(header.dVersionNumber), 1, f);
    fwrite(&header.bDeltaTheta, sizeof(header.bDeltaTheta), 1, f);
    fwrite(&header.bDeltaVelocity, sizeof(header.bDeltaVelocity), 1, f);
    fwrite(&header.dDataRateHz, sizeof(header.dDataRateHz), 1, f);
    fwrite(&header.dGyroScaleFactor, sizeof(header.dGyroScaleFactor), 1, f);
    fwrite(&header.dAccelScaleFactor, sizeof(header.dAccelScaleFactor), 1, f);
    fwrite(&header.iUtcOrGpsTime, sizeof(header.iUtcOrGpsTime), 1, f);
    fwrite(&header.iRcvTimeOrCorrTime, sizeof(header.iRcvTimeOrCorrTime), 1, f);
    fwrite(&header.dTimeTagBias, sizeof(header.dTimeTagBias), 1, f);
    fwrite(&header.szImuName, sizeof(header.szImuName), 1, f);
    fwrite(&header.reserved1, sizeof(header.reserved1), 1, f);
    fwrite(&header.szProgramName, sizeof(header.szProgramName), 1, f);
    fwrite(&header.tCreate, sizeof(header.tCreate), 1, f);
    fwrite(&header.bLeverArmValid, sizeof(header.bLeverArmValid), 1, f);
    fwrite(&header.lXoffset, sizeof(header.lXoffset), 1, f);
    fwrite(&header.lYoffset, sizeof(header.lYoffset), 1, f);
    fwrite(&header.lZoffset, sizeof(header.lZoffset), 1, f);
    fwrite(&header.Reserved, sizeof(header.Reserved), 1, f);
    // printf("total_size of header %lld\n", total_size);
    /* FileStream for the Library File */
    FILE *bookFile;

    /* allocation of the buffer for every line in the File */
    char *buf = malloc(MAX_STR_LEN);
    char *tmp; 

    /* if the space could not be allocaed, return an error */
    if (buf == NULL) {
        printf ("No memory\n");
        return 1;
    }

    if ( ( bookFile = fopen(csvfile, "r" ) ) == NULL ) //Reading a file
    {
        printf( "File could not be opened.\n" );
    }

    int i = 0;
    while (fgets(buf, 255, bookFile) != NULL)
    {
        if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n'))
            buf[strlen (buf) - 1] = '\0';       

        tmp = strtok(buf, ";");
        books[i].time = strtod(strdup(tmp),NULL);
        // *100000000
        tmp = strtok(NULL, ";");
        books[i].gx = (int32_t)(strtod(strdup(tmp),NULL)*100000000);

        tmp = strtok(NULL, ";");
        books[i].gy = (int32_t)(strtod(strdup(tmp),NULL)*100000000);

        tmp = strtok(NULL, ";");
        books[i].gz = (int32_t)(strtod(strdup(tmp),NULL)*100000000);

        tmp = strtok(NULL, ";");
        books[i].ax = (int32_t)(strtod(strdup(tmp),NULL)*100000000);

        tmp = strtok(NULL, ";");
        books[i].ay = (int32_t)(strtod(strdup(tmp),NULL)*100000000);

        tmp = strtok(NULL, ";");
        books[i].az = (int32_t)(strtod(strdup(tmp),NULL)*100000000);

        //tempBook.ID = atoi(buf);
        // printf("index i= %i  time: %f, %d, %d, %d, %d, %d, %d \n",i, books[i].time , books[i].gx, books[i].gy , books[i].gz , books[i].ax, books[i].ay , books[i].az);
        // printf("size of book %lu\n", sizeof(struct book));
        
        fwrite(&books[i], sizeof(struct book), 1, f);
        i++;
    }
    //free(buf);
    fclose(bookFile);
        
    fclose(f);
    return 0;
}