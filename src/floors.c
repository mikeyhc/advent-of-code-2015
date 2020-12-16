#include <stdio.h>
#include <stdlib.h>

#define _POSIX_C_SOURCE 200809L

int
main(int argc, char **argv)
{
	FILE *input = stdin;
	char *line = NULL;
	size_t len = 0;
	int floor = 0, basement = -1;
	char *s;

	if (argc > 1)
		input = fopen(argv[1], "r");

	if (input == NULL) {
		perror("failure opening input file");
		return -1;
	}

	if (getline(&line, &len, input) <= 0) {
		fprintf(stderr, "no input provided\n");
		exit(1);
	}

	s = line;
	while (*s != '\n' && *s != '\0') {
		if (*s == '(') {
			++floor;
		} else if (*s == ')') {
			--floor;
		} else {
			fprintf(stderr, "unknown instruction: %c\n", *s);
			return 1;
		}

		if (basement < 0 && floor < 0)
			basement = s - line + 1;
		++s;
	}

	free(line);
	if (input != stdin)
		fclose(input);

	printf("%d\n", floor);
	printf("%d\n", basement);

	return 0;
}
