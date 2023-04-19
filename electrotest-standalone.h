#ifndef ELECTROTESTSTANDALONE_H
#define ELECTROTESTSTANDALONE_H

#include <stdbool.h>
#include <stddef.h>
#include <float.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int e_resistance(float orig_resistance, float *res_array);
float calc_power_i(float volt, float current);
float calc_power_r(float volt, float resistance);
float calc_resistance(int count, char conn, float *array);

#endif