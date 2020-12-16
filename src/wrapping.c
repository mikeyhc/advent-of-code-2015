#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _POSIX_C_SOURCE 200809L

int
main(int argc, char **argv)
{
	FILE *input = stdin;
	char *line = NULL;
	size_t len = 0;
	int sum = 0, h, w, l, m, lw, wh, hl, s1, s2, ribbon_sum = 0;

	if (argc > 1)
		input = fopen(argv[1], "r");

	if (input == NULL) {
		perror("failure opening input file");
		return -1;
	}

	while (getline(&line, &len, input) > 0) {
		l = atoi(strtok(line, "x\n"));
		w = atoi(strtok(NULL, "x\n"));
		h = atoi(strtok(NULL, "x\n"));
		lw = l * w;
		wh = w * h;
		hl = h * l;
		m = lw < wh ? (lw < hl ? lw : hl) : (wh < hl ? wh : hl);
		if (l <= w && l <= h) {
			s1 = l;
			s2 = w < h ? w : h;
		} else if (w <= l && w <= h) {
			s1 = w;
			s2 = l < h ? l : h;
		} else {
			s1 = h;
			s2 = l < w ? l : w;
		}

		sum += 2 * lw + 2 * wh + 2 * hl + m;
		ribbon_sum += 2 * s1 + 2 * s2 + l * w * h;
	}

	free(line);
	if (input != stdin)
		fclose(input);

	printf("%d\n", sum);
	printf("%d\n", ribbon_sum);

	return 0;
}
