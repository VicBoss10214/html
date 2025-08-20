#include <stdio.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main()
{
    FILE *src = fopen("source.tif", "rb");
    if (!src) { printf("Error opening source file\n"); return 1; }

    // Open 8 output files for 8 bit planes
    FILE *planes[8];
    char planeName[20];
    for (int bit = 0; bit < 8; bit++) {
        sprintf(planeName, "bit_plane_%d.tif", bit);
        planes[bit] = fopen(planeName, "wb");
        if (!planes[bit]) { printf("Error creating file %s\n", planeName); return 1; }
    }

    // Read first 8 bytes of metadata and copy to all planes
    BYTE meta[8];
    fread(meta, sizeof(BYTE), 8, src);
    for (int bit = 0; bit < 8; bit++) {
        fwrite(meta, sizeof(BYTE), 8, planes[bit]);
    }

    // Assume image is 500 rows of 1192 bytes (like your example)
    BYTE row[1192], outRow[1192];
    for (int i = 0; i < 500; i++) {
        fread(row, sizeof(BYTE), 1192, src);
        for (int b = 0; b < 8; b++) {       // for each bit plane
            for (int j = 0; j < 1192; j++) {
                outRow[j] = (row[j] & (1 << b)) ? 255 : 0; // extract bit
            }
            fwrite(outRow, sizeof(BYTE), 1192, planes[b]);
        }
    }

    // Copy remaining metadata (if any) after image data
    fseek(src, 0, SEEK_END);
    long fileSize = ftell(src);
    long meta2Size = fileSize - (8 + 1192 * 500);
    if (meta2Size > 0) {
        BYTE *meta2 = (BYTE*)malloc(meta2Size);
        fseek(src, 8 + 1192 * 500, SEEK_SET);
        fread(meta2, sizeof(BYTE), meta2Size, src);
        for (int b = 0; b < 8; b++) {
            fwrite(meta2, sizeof(BYTE), meta2Size, planes[b]);
        }
        free(meta2);
    }

    // Close files
    fclose(src);
    for (int b = 0; b < 8; b++) fclose(planes[b]);

    printf("Bit-plane slicing complete!\n");
    return 0;
}
