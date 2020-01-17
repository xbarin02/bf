#include <stddef.h>
#include <stdio.h>

FILE *pstream;
unsigned char mem[0x10000];
size_t ptr;

long skip()
{
	long pos = ftell(pstream);

	while (1) {
		switch (fgetc(pstream)) {
			case '[':
				skip();
				break;
			case ']':
				return pos;
			case EOF:
				return pos;
			default:
				;
		}
	}
}

void call();

long exec()
{
	long pos = ftell(pstream);

	while (1) {
		switch (fgetc(pstream)) {
			case '>':
				ptr = (ptr + 1) % sizeof mem;
				break;
			case '<':
				ptr = (ptr - 1) % sizeof mem;
				break;
			case '+':
				++mem[ptr];
				break;
			case '-':
				--mem[ptr];
				break;
			case '.':
				putchar(mem[ptr]);
				break;
			case ',':
				mem[ptr] = getchar();
				break;
			case '[':
				if (mem[ptr]) {
					call();
				} else {
					skip();
				}
				break;
			case ']':
				return pos;
			case EOF:
				return pos;
			default:
				;
		}
	}
}

void call()
{
	fseek(pstream, exec() - 1, SEEK_SET);
}

int main(int argc, char *argv[])
{
	if (argc > 1) {
		pstream = fopen(argv[1], "r");
	}

	if (NULL == pstream) {
		pstream = stdin;
	}

	exec();

	if (stdin != pstream) {
		fclose(pstream);
	}

	return 0;
}
