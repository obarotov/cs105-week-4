#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        fclose(input);
        return 1;
    }

    float factor = atof(argv[3]);

    uint8_t header[HEADER_SIZE];
    if (fread(header, sizeof(uint8_t), HEADER_SIZE, input) != (size_t) HEADER_SIZE ||
        fwrite(header, sizeof(uint8_t), HEADER_SIZE, output) != (size_t) HEADER_SIZE)
    {
        printf("Could not copy header.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input) == 1)
    {
        sample = (int16_t) (sample * factor);

        if (fwrite(&sample, sizeof(int16_t), 1, output) != 1)
        {
            printf("Could not write sample.\n");
            fclose(input);
            fclose(output);
            return 1;
        }
    }

    if (ferror(input))
    {
        printf("Could not read samples.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    fclose(input);
    fclose(output);
    return 0;
}