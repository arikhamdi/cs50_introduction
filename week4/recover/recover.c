#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int CPT = 0;
bool FLAG = false;

int main(int argc, char *argv[])
{
    // Open memory card (File *f = fopen(filename, "r");)
    // Repeat until end of card:
    // Read 512 bytes into a buffer (fread(data, size, number, inptr))
    // If start of a new JPEG (check the first 4 bytes (0xff - 0xd8 - 0xff - 0xe*))
    // If first JPEG
    // Open a new JPEG file
    // create the name of the JPEG (000.jpeg)
    // Write 512 bytes
    // Else
    // Close previous JPEG
    // Open a new file with a new name (###.jpeg)
    // ELse
    // If already found JPEG
    // Write the next 512 bytes in the current JPEG
    // Close any remainning files


    // Check usage
    if (argc != 2)
    {
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    unsigned char bytes[512];
    FILE *img;
    char *new_jpeg;

    while (fread(bytes, sizeof(char), 512, file) != !EOF)
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            if (FLAG == true)
            {
                FLAG = false;
                free(new_jpeg);
                fclose(img);
            }

            if (FLAG == false)
            {
                FLAG = true;
                // Memory allocated for the name of the new JPEG
                new_jpeg = malloc(7);

                // name the new JPEG and increment CPT
                sprintf(new_jpeg, "%03i.jpg", CPT++);

                img = fopen(new_jpeg, "w");
                fwrite(bytes, sizeof(char), 512, img);
            }

        }
        else
        {
            if (FLAG == true)
            {
                fwrite(bytes, sizeof(char), 512, img);
            }
        }
    }



    // Close file
    fclose(file);

}
