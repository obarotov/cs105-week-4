#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "rb");
    if (card == NULL)
    {
        perror("Input file");
        return 1;
    }

    uint8_t buffer[512];
    int count = 0;
    FILE *img = NULL;
    char filename[8];

    while (fread(buffer, sizeof(uint8_t), 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }

            snprintf(filename, sizeof(filename), "%03i.jpg", count);
            count++;

            img = fopen(filename, "wb");
            if (img == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                fclose(card);
                return 1;
            }
        }

        if (img != NULL)
        {
            if (fwrite(buffer, sizeof(uint8_t), 512, img) != 512)
            {
                fprintf(stderr, "Could not write %s.\n", filename);
                fclose(img);
                fclose(card);
                return 1;
            }
        }
    }

    if (ferror(card))
    {
        fprintf(stderr, "Could not read %s.\n", argv[1]);
        if (img != NULL)
        {
            fclose(img);
        }
        fclose(card);
        return 1;
    }

    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
    return 0;
}