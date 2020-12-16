#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define _POSIX_C_SOURCE 200809L

#define MAPSIZE 5000

int
main(int argc, char **argv)
{
	FILE *input = stdin;
	char *line = NULL;
	size_t len = 0;
	char *p, *map, *robomap;
	int count = 0, x, y;
	int robocount = 0, sx, sy, rx, ry;
	char robot = 0;

	if (argc > 1)
		input = fopen(argv[1], "r");

	if (input == NULL) {
		perror("failure opening input file");
		return -1;
	}

	map = calloc(1, MAPSIZE * MAPSIZE);
	assert(map);
	robomap = calloc(1, MAPSIZE * MAPSIZE);
	assert(robomap);

	assert(getline(&line, &len, input) > 0);
	p = line;
	rx = ry = sx = sy = x = y = MAPSIZE / 2;
	map[y * MAPSIZE + x] = 1;
	robomap[sy * MAPSIZE + sx] = 1;
	++count;
	++robocount;
	while (*p != '\n' && *p != '\0') {
		switch (*p) {
		case '^':
			--y;
			if (robot)
				--ry;
			else
				--sy;
			break;
		case 'v':
			++y;
			if (robot)
				++ry;
			else
				++sy;
			break;
		case '<':
			--x;
			if (robot)
				--rx;
			else
				--sx;
			break;
		case '>':
			++x;
			if (robot)
				++rx;
			else
				++sx;
			break;
		default:
			fprintf(stderr, "unknown command: %c\n", *p);
			exit(-1);
		}

		if (!map[y * MAPSIZE + x]) {
			++count;
			map[y * MAPSIZE + x] = 1;
		}

		if (robot) {
			if (!robomap[ry * MAPSIZE + rx]) {
				++robocount;
				robomap[ry * MAPSIZE + rx] = 1;
			}
		} else {
			if (!robomap[sy * MAPSIZE + sx]) {
				++robocount;
				robomap[sy * MAPSIZE + sx] = 1;
			}
		}

		robot = !robot;
		++p;
	}

	free(line);
	if (input != stdin)
		fclose(input);

	free(map);
	free(robomap);

	printf("%d\n", count);
	printf("%d\n", robocount);

	return 0;
}
