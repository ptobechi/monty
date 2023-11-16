#include "monty.h"

/**
 * is_numeric - Checks if a string represents a numeric value.
 * @str: The input string to be checked.
 *
 * Return: 1 if the string is numeric, 0 otherwise.
 */
int is_numeric(const char *str)
{
	/* Check for NULL or empty string */
	if (str == NULL || *str == '\0')
		return (0);

	/* Iterate through each character in the string */
	while (*str != '\0')
	{
		/* Check if the character is not a digit and not a '-' at the beginning */
		if (!isdigit(*str) && (*str != '-' || str == 0))
			return (0);

		/* Move to the next character in the string */
		str++;
	}

	/* The string is numeric */
	return (1);
}

/**
 * pint - prints the value at the top of the stack.
 *
 * @stack: A pointer to the top of the stack.
 * @line_num: The current line number in the Monty bytecode file.
 */
void pint(stack_t **stack, unsigned int line_num)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_num);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}

