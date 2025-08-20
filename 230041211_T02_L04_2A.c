#include <stdio.h>
#include <stdint.h>
typedef uint8_t BYTE;
int main()
{
    FILE *src = fopen("source.tif", "rb");
    FILE *blr = fopen("blurred.tif", "wb");

    BYTE metaData1[8];
    fread(metaData1, sizeof(BYTE), 8, src);
    fwrite(metaData1, sizeof(BYTE), 8, blr);

    BYTE image[500][1192];
    fread(image, sizeof(BYTE), 500 * 1192, src);

    BYTE blurred[500][1192];

    for (int i = 1; i < 500; i++)
    {
        for (int j = 1; j < 1191; j++)
        {
            int sum = 0;
            for (int m = -1; m <= 1; m++)
            {
                for (int n = -1; n <= 1; n++)
                {
                    sum += image[i + m][j + n];
                }
            }

            blurred[i][j] = sum / 9;
        }
    }

    for (int i = 0; i < 1192; i++)
    {
        blurred[0][i] = image[0][i];
        blurred[499][i] = image[499][i];
    }
    for (int j = 0; j < 500; j++)
    {
        blurred[j][0] = image[j][0];
        blurred[j][1191] = image[j][1191];
    }

    fwrite(blurred, sizeof(BYTE), 500 * 1192, blr);

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
    fwrite(metaData2, sizeof(BYTE), meta2Size, blr);

    fclose(src);
    fclose(blr);
    return 0;
}