#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ch2num(char ch1,char ch2)
{
	int nout;

	if((ch1 >= '0')&&('9' >= ch1)) nout = (ch1 & 0xf) * 0x10;
	else nout = ((ch1 & 0xf) + 9) * 0x10;
	if((ch2 >= '0')&&('9' >= ch2)) return (ch2 & 0xf) + nout;
	else return ((ch2 & 0xf) + 9) + nout;
}

int main(int argc, char *argv[])
{
	char		*p;
	char		buf[255];
	long		start;
	FILE		*fpIn, *fpOut;
	long		forge;
	long		search;
	int		mode;
	long		address;
	long		detect = 0;
	int		size;
	int		i;

	if (argc != 4)
		goto error;

	p = strtok(argv[1], "=");
	if (strcmp(p, "--start-address") != 0)
		goto error;
	p = strtok(NULL, "=");
	if (p == NULL)
		goto error;
	strcpy(buf, p);
	start = strtol(buf, NULL, 16);

	if ((fpIn = fopen(argv[2], "rb")) == NULL) {
		printf("Cannot open input file.\n");
		return 1;
	}
	if ((fpOut = fopen(argv[3], "wt")) == NULL) {
		printf("Cannot open output file.\n");
		return 1;
	}

	forge = start + 0x8000;
	search = start;

	while (NULL != fgets(buf, 254, fpIn)) {
		if ((buf[0] != ':') ||
		(!isalnum(buf[1])) ||
		(!isalnum(buf[2]))) {
			continue;
		}
		mode = ch2num(buf[7],buf[8]);
		if (mode != 0)
			continue;
		address = (long)(ch2num(buf[3], buf[4])) * 0x100L;
		address += (long)(ch2num(buf[5], buf[6]));
		if (!detect) {
			if (address != search)
				continue;
			detect = 1;
		} else {
			if (address != search)
				break;
		}
		size = ch2num(buf[1], buf[2]) * 2;
		fprintf(fpOut,"S2%02X%06X", 4 + (size / 4), forge);
		for (i = 0; i < size; i+=2) {
			search++;
			if ((start % 4)) {
				if (i & 0x4)
					continue;
			} else {
				if (!(i & 0x4))
					continue;
			}
			forge++;
			fprintf(fpOut, "%02X", ch2num(buf[i + 9], buf[i + 10]));
		}
		fprintf(fpOut,"%02X\n",0xFF);
	}

	fprintf(fpOut,"S804000000FB\n");

	fclose(fpIn);
	fclose(fpOut);

	return 0;

error:
	printf("Parameter Error!\n\n");
	return -1;
}
