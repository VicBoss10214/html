#include <stdio.h>
#include <stdint.h>
typedef uint8_t BYTE;
int main()
{
    FILE *src = fopen("source.tif", "rb");
    FILE *flp = fopen("flipped.tif", "wb");

    BYTE metaData1[8];
    fread(metaData1, sizeof(BYTE), 8, src);
    fwrite(metaData1, sizeof(BYTE), 8, flp);

    BYTE srcRow[1192];
    BYTE flpRow[1192];

    for (int i = 0; i < 500; i++)
    {
        fread(srcRow, sizeof(BYTE), 1192, src);
        for (int j = 1191, k = 0; j >= 0; j--, k++)
        {
            flpRow[k] = srcRow[j];
        }
        fwrite(flpRow, sizeof(BYTE), 1192, flp);
    }

    fseek(src, 0, SEEK_SET);

    int bytes = 0;
    BYTE b;

    while (fread(&b, sizeof(BYTE), 1, src) != 0)
    {
        bytes++;
    }

    fseek(src, 0, SEEK_SET);

    int meta2Size = bytes - (8 + (1192 * 500));
    BYTE metaData2[meta2Size];

    fseek(src, 8 + (1192 * 500), SEEK_SET);
    fread(metaData2, sizeof(BYTE), meta2Size, src);
    fwrite(metaData2, sizeof(BYTE), meta2Size, flp);

    fclose(src);
    fclose(flp);
    return 0;
}