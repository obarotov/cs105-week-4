# CS105 — Week 4 Problem Sets (C)

Solutions to the Week 4 (Memory) programming exercises for **CS105**, implemented in C.

## Course Information

| | |
|---|---|
| **Course** | CS105 |
| **Instructor** | Odina Kholiqov |
| **University** | DII |
| **Problem Set Source** | [cs105.barnomasoz.com](https://cs105.barnomasoz.com/) |
| **Language** | C |

## Structure

```
cs105-week-4/
├── volume/
├── filter-less/
└── recover/
```

## Compiling and Running

Sample media files (`input.wav`, the BMP images, `card.raw`) are not included in this repository. Download them from the starter archives on the problem set pages.

### Volume

Scales the volume of a WAV file by a given factor.

```bash
cc -std=c11 -Wall -Wextra -Wpedantic volume.c -o volume
./volume input.wav output.wav 0.5
```

### Filter (Less)

Applies grayscale, reflection, blur, or sepia filters to a BMP image.

```bash
make filter
./filter -g images/yard.bmp gray.bmp
./filter -r images/yard.bmp reflected.bmp
./filter -b images/yard.bmp blurred.bmp
./filter -s images/yard.bmp sepia.bmp
```

### Recover

Recovers JPEG images from a memory card image.

```bash
cc -std=c11 -Wall -Wextra -Wpedantic recover.c -o recover
./recover card.raw
```

## Note

This repository is shared for personal reference only. It is not intended to be used as a solution by other students, in this or future terms.