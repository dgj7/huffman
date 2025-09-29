#include <stdlib.h>		// malloc(), exit()
#include <stdio.h>		// printf()

#include "frequency.h"
#include "huffman.h"

static const int ERROR_MALLOC_FREQUENCY = 200;
static const int ERROR_MALLOC_FREQUENCIES = 201;

static size_t unique_characters(char *message, size_t length);
static int find_matching_index(struct frequency_pair_t * frequencies, size_t length, char symbol);

struct frequency_t * count_frequencies(char *message, size_t length)
{
	/* initialize frequency; panic if we can't get memory */
	struct frequency_t * wrapper = malloc(sizeof(struct frequency_t));
	if (wrapper == NULL)
	{
		printf("ERROR: %d: can't allocate memory for frequency_t", ERROR_MALLOC_FREQUENCY);
		exit(ERROR_MALLOC_FREQUENCY);
	}

	/* initialize the frequency array; panic if we can't get memory */
	size_t uniques = unique_characters(message, length);
	wrapper->pairs = malloc(uniques * sizeof(struct frequency_pair_t));
	int used = 0;
	if (wrapper->pairs == NULL)
	{
		printf("ERROR: %d: can't allocate memory for frequencies", ERROR_MALLOC_FREQUENCIES);
		exit(ERROR_MALLOC_FREQUENCIES);
	}

	/* count characters */
	for (int c = 0; c < length; c++)
	{
		char symbol = message[c];
		int index = find_matching_index(wrapper->pairs, used, symbol);
		if (index >= 0)
		{
			wrapper->pairs[index].frequency = wrapper->pairs[index].frequency + 1;
		}
		else
		{
			wrapper->pairs[used] = (struct frequency_pair_t) { .symbol = symbol, .frequency = 1 };
			used++;
		}
	}

	/* update structure */
	wrapper->count = used;

	/* done */
	return wrapper;
}

static size_t unique_characters(char *message, size_t length)
{
	if (message)
	{
		size_t count = 0;
		for (size_t i = 0; i < length; i++)
		{
			short flag = 0;
			for (size_t j = 0; j < i; j++)
			{
				char left = message[i];
				char right = message[j];
				if (left == right)
				{
					flag = 1;
					break;
				}
			}

			if (flag == 0)
			{
				count++;
			}
		}
		return count;
	}
	return 0;
}

static int find_matching_index(struct frequency_pair_t *frequencies, size_t length, char symbol)
{
	for (int c = 0; c < length; c++)
	{
		char potential = frequencies[c].symbol;
		if (potential == symbol)
		{
			return c;
		}
	}
	return -1;
}
