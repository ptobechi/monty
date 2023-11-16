#include "monty.h"

instruction_t ops[] = {
	{"push", push},
	{"pall", pall},
	{"pint", pint},
	{"pop", pop},
};

/**
 * main - program entry point
 * @argc: argument counts
 * @argv: argument variable
 *
 * Return: always 0 (Success)
 */
int main(int argc, char **argv)
{
	FILE *filepath;
	char *opcode = NULL;
	size_t len = 0;
	ssize_t nread;
	unsigned int line_num = 1;
	int i = 0;
	stack_t *stack;

	if (argc != 2)
		fprintf(stderr, "USAGE: monty file\n"), exit(EXIT_FAILURE);

	filepath = fopen(argv[1], "r");
	if (filepath == NULL)
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]), exit(EXIT_FAILURE);

	while ((nread = getline(&opcode, &len, filepath)) != -1)
	{
		/* Extract the opcode (first word) from the line*/
		char *token = strtok(opcode, " \t\n");

		if (token != NULL)
		{
			/*perfom a search on the array structure*/
			for (; i < (int)sizeof(ops) / (int)sizeof(ops[0]); i++)
			{
				/*if op is found in the array invoke func*/
				if (strcmp(token, ops[i].opcode) == 0)
				{
					ops[i].f(&stack, line_num);
					break;
				}
			}
		}
		line_num++;
	}
	free(opcode), fclose(filepath), exit(EXIT_SUCCESS);
	return (0);
}

/**
 * push - add an elemnt to the stack
 * @stack: stack pointer
 * @line_num: line number of the file
 *
 * Return: void
 */
void push(stack_t **stack, unsigned int line_num)
{
	int value;
	char *arg;

	/* get the argument after the push opcode*/
	arg = strtok(NULL, " \t\n");

	if (arg == NULL || !is_numeric(arg))
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_num);
		exit(EXIT_FAILURE);
	}

	value = atoi(arg);
	/*push_stack function*/
	push_stack(stack, value);
}

/**
 * push_stack - Pushes a new node onto the stack.
 * @stack: A pointer to the top of the stack.
 * @value: The value to be pushed onto the stack.
 *
 * Return: A pointer to the newly created node.
 */
stack_t *push_stack(stack_t **stack, int value)
{
	stack_t *new_node = malloc(sizeof(stack_t));

	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;

	if (*stack == NULL)
	{
		new_node->next = NULL;
	}
	else
	{
		new_node->next = *stack;
		(*stack)->prev = new_node;
	}

	*stack = new_node;

	return (new_node);
}

/**
 * pall - prints all the value of a stack
 * @stack: pointer to the stack
 * @line_num: line numbers in the file
 *
 * Return: void
 */
void pall(stack_t **stack, unsigned int line_num)
{
	stack_t *current = *stack;
	(void)line_num;

	/* Check if the stack is empty */
	if (current == NULL)
		return;

	/* Print all values on the stack */
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

