#ifndef __FREQUENCY__DG__H__
#define __FREQUENCY__DG__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/******************************************************************************
 * INTERNAL API
 *****************************************************************************/
frequency_t * count_frequencies(char *message, size_t length);// todo: this method should return a pointer (dynamically allocated)

/******************************************************************************
 * SUPPORT FUNCTIONS
 *****************************************************************************/
size_t unique_characters(char *message, size_t length);
int find_matching_index(frequency_pair_t * frequencies, size_t length, char symbol);


#ifdef __cplusplus
}
#endif

#endif
