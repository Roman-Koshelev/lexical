/* Copyright (C) 2017 Roman Koshelev */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Usage()
{
	fprintf(stderr, "Strings. Usage: \n"
					"strings [flags]\n"
					"\n"
					"Flags:\n"
					"  --from - left string.\n"
					"  --to   - right string.\n");
	exit(1);
}

void interval_puts(char* left, const char* right)  // ����� ������
{
	for (char* i = left; i != right + 1; ++i)
	{
		putchar(*i);
	}
	putchar('\n');
}

int comparison(const char* Lhs, const char* Rhs, const size_t size)  // ��������� �����
{
	size_t i;
	for (i = 0; i < size; ++i)
	{
		if (Lhs[i] != Rhs[i])
		{
			break;
		}
	}
	return (int)i;
}

void increment_row(char** right, char** left)
{
	int flag = 0;
	for (char* j = *right; j != (*left - 1); --j)  // ��������� ������������� ������
	{
		if (++(*j) > 'z')
		{
			(*j) -= 'z' - 'a' + 1;
		}
		else
		{
			flag = 1;
			break;
		}
	}

	if (!flag)
		*(--(*left)) = 'a';
}

void kernel(char* from, char* to)
{
	const size_t size_to = strlen(to);
	const size_t size_from = strlen(from);

	char* mem = (char*)malloc(size_to + 1);  // �������� ������ ��� ������������� ������
	char* inter_line = mem;
	memset(inter_line, 0, size_to + 1);

	char* left =
		inter_line +
		(size_to - size_from);  // ������ ��������� �� ������ � ����� ������������� ������

	char* right = inter_line + size_to - 1;
	memcpy(left, from, size_from);  // ��������� ��������� ����� � ������������� ������

	interval_puts(left, right);  // ����� ��������� ������

	int bias;
	while (((bias = comparison(to, inter_line, right - inter_line + 1)) !=
			right - inter_line + 1))  // ���� ������������� �� ����� ��������
	{
		to += bias;
		inter_line += bias;  // ����� ���������� �� ����� ���� ������� ����� (����� ��
							 // ���� ���������� ���������)

		increment_row(&right, &left);

		interval_puts(left, right);  // ����� ������������� ������
	}

	free(mem);
}

int main(int argc, char** argv)
{
	char* from = NULL;
	char* to = NULL;

	int opt_idx = 1;
	for (; opt_idx < argc; ++opt_idx)  // ������ ��������� ��������� ������
	{
		if (strnlen(argv[opt_idx], 2) < 2 || argv[opt_idx][0] != '-' ||
			argv[opt_idx][1] != '-')
		{
			break;
		}
		if (!strcmp(argv[opt_idx], "--from"))
		{
			++opt_idx;
			if (opt_idx >= argc)
				Usage();

			from = argv[opt_idx];
		}
		else if (!strcmp(argv[opt_idx], "--to"))
		{
			++opt_idx;
			if (opt_idx >= argc)
				Usage();
			to = argv[opt_idx];
		}
		else if (!strcmp(argv[opt_idx], "--"))
		{
			break;
		}
		else
		{
			fprintf(stderr, "Unknown commandline flag: %s\n", argv[opt_idx]);
			Usage();
		}
	}

	if ((from == NULL) || (to == NULL))
	{
		Usage();
	}

	kernel(from, to);  // �������� �������

	return EXIT_SUCCESS;
}
