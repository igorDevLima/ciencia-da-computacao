#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

bool is_valid_base_input(int base);
int count_digits(int num);
int* create_digits_array(int num, int num_digits);
void print_converted_number_to_binary(int number, int number_length);
void print_converted_number_to_decimal (int number_digits[], int array_length);
void print_converted_binary_number_to_hexadecimal(int number_digits[], int array_length);
void print_converted_decimal_number_to_hexadecimal(int number, int number_length);
bool all_array_numbers_is_zero_or_one(int number_digits[], int array_length);

int main() {
	int not_converted_number, base;

	printf("Por favor, insira o numero deseja converter: ");
	scanf("%d", &not_converted_number);

	printf("Por favor, insira a base que deseja converter seu numero (2, 10, 16): ");
	scanf("%d", &base);

	while(is_valid_base_input(base) == false) {
		printf("Por favor, insira uma base valida (2, 10, 16): ");
		scanf("%d", &base);
	}

	int not_converted_number_digits_count = count_digits(not_converted_number);

	int *digits_array = create_digits_array(not_converted_number, not_converted_number_digits_count);

	if (digits_array == NULL) {
		printf("Erro de alocacao de memoria.\n");
		return 1;
	}

	printf("Resultado: ");
	switch (base) {
	case 2:
		print_converted_number_to_binary(not_converted_number, not_converted_number_digits_count);
		break;
	case 10:
		print_converted_number_to_decimal(digits_array, not_converted_number_digits_count);
		break;
	case 16:
		char is_binary_char;

		if(all_array_numbers_is_zero_or_one(digits_array, not_converted_number_digits_count) == true) {
			printf("Seu numero e um binario (Digite 's' para sim) ? ");
			scanf(" %c", &is_binary_char);
		}

		if(is_binary_char == 's') {
			print_converted_binary_number_to_hexadecimal(digits_array, not_converted_number_digits_count);
		} else {
			print_converted_decimal_number_to_hexadecimal(not_converted_number, not_converted_number_digits_count);
		}
		break;
	}

	free(digits_array);
	return 0;
}

bool is_valid_base_input(int base) {
	if (base != 2 && base != 10 && base != 16) {
		return false;
	}

	return true;
}

int count_digits(int num) {
	int count = 0;

	if (num == 0) {
		return 1;
	}

	if (num < 0) {
		num = -num;
	}

	while (num != 0) {
		num /= 10;
		count++;
	}

	return count;
}

int* create_digits_array(int num, int num_digits) {
	int *digits_array = malloc(num_digits * sizeof(int));
	if (digits_array == NULL) {
		return NULL;
	}

	for (int i = num_digits - 1; i >= 0; i--) {
		digits_array[i] = num % 10;
		num /= 10;
	}

	return digits_array;
}

void print_converted_number_to_binary (int number, int number_length) {
	int count_binary_digits = (int)floor(log2(number)) + 1;
	int rest;
	int binary_digits[count_binary_digits];

	for(int i = 0; number > 0; i++) {
		binary_digits[i] = number % 2;
		number /= 2;
	}

	for (int i = count_binary_digits - 1; i >= 0; i--) {
		printf("%d", binary_digits[i]);
	}
}

void print_converted_number_to_decimal (int number_digits[], int array_length) {
	int iterator = 0;

	for(int i = 0; i < array_length; i++) {

		if(number_digits[i] != 0 && number_digits[i] != 1) {
			printf("Numero nao e um binario!");
			exit(1);
		}

		iterator += number_digits[array_length - i - 1] * pow(2, i);
	}

	printf("%d", iterator);
}

void print_converted_binary_number_to_hexadecimal (int number_digits[], int array_length) {

	int hex_value = 0;
	int position = 0;

	for (int i = array_length - 1; i >= 0; i--) {
		hex_value += number_digits[i] << position;
		position++;

		if (position == 4 || i == 0) {
			if (hex_value < 10) {
				printf("%d", hex_value);
			} else {
				printf("%c", 'A' + (hex_value - 10));
			}

			hex_value = 0;
			position = 0;
		}
	}
}

void print_converted_decimal_number_to_hexadecimal (int number, int number_length) {
	char hex_string[number_length + 1];

	snprintf(hex_string, number_length + 1, "%X", number);
	printf("%s", hex_string);
}

bool all_array_numbers_is_zero_or_one(int number_digits[], int array_length) {
	bool all_is_binary = true;

	for(int i = 0; i < array_length; i++) {
		if(number_digits[i] != 0 && number_digits[i] != 1 ) {
			all_is_binary = false;
			break;
		}
	}

	return all_is_binary;
}
