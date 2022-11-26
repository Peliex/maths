#include <stdio.h>
#include <stdint.h>
#include <malloc.h>

enum process_state
{
	PROCESS_RUNNING = 0,
	PROCESS_STOPPED = -1,
	PROCESS_FAILED_INPUT = -2,
	PROCESS_FAILED_MEMORY = -3
};

process_state request_input(uint32_t *num)
{
	void* buffer = malloc(sizeof(int32_t));

	if (buffer != NULL)
	{
		printf("Please insert an amount of money in cents. ($/100)\n");
		scanf_s("%d", (int32_t*)buffer);
		*num = *(uint32_t*)buffer;
		free(buffer);
		if (getchar() != '\n')
		{
			*num = 0;
			printf("Invalid input.\n");
			while (getchar() != '\n');
			return PROCESS_FAILED_INPUT;
		}
		if (*num < 0)
		{
			printf("Cannot make change on a negative balance.\n");
			return PROCESS_FAILED_INPUT;
		}
		else if (*num == 0)
		{
			printf("Cannot make change on a zero balance.\n");
			return PROCESS_FAILED_INPUT;
		}
		else if (*num > 0)
		{
			return PROCESS_RUNNING;
		}
		else
		{
			printf("Invalid input.\n");
			return PROCESS_FAILED_INPUT;
		}
	}
	else
	{
		free(buffer);
		return PROCESS_FAILED_MEMORY;
	}
}

process_state makeChange(const int32_t changeInCents)
{
	uint32_t remainingChange = changeInCents;
	uint32_t quarters = 0;
	uint32_t dimes = 0;
	uint32_t nickels = 0;
	uint32_t pennies = 0;

	while (quarters < (remainingChange / 25)) quarters = quarters + 1;
	if (remainingChange % 25 != 0)
	{
		remainingChange = remainingChange - (quarters * 25);
		while (dimes < (remainingChange / 10)) dimes = dimes + 1;
		if (remainingChange % 10 != 0)
		{
			remainingChange = remainingChange - (dimes * 10);
			while (nickels < (remainingChange / 5)) nickels = nickels + 1;
			if (remainingChange % 5 != 0)
			{
				remainingChange = remainingChange - (nickels * 5);
				pennies = remainingChange;
			}
		}
	}

	printf("Your change is ");
	if (quarters != 0)
	{
		if (quarters > 1)
		{
			printf("%u quarters", quarters);
		}
		else
		{
			printf("%u quarter", quarters);
		}
	}
	// Evaluate if there is any change in dimes
	if (dimes != 0)
	{
		// Check if both bigger and smaller denominations are nonzero
		if (quarters != 0 && (nickels != 0 || pennies != 0))
		{
			printf(", ");
		}
		// If only larger denomination is nonzero
		else if (quarters != 0)
		{
			printf(" and ");
		}
		if (dimes > 1)
		{
			printf("%u dimes", dimes);
		}
		else
		{
			printf("%u dime", dimes);
		}
	}
	// Evaluate if there is any change in nickels
	if (nickels != 0)
	{
		//Check if both bigger and smaller denominations are nonzero
		if (pennies != 0 && (dimes != 0 || quarters != 0))
		{
			printf(", ");
		}
		// If only larger denomination is nonzero
		else if (dimes != 0 || quarters != 0)
		{
			printf(" and ");
		}
		if (nickels > 1)
		{
			printf("%u nickels", nickels);
		}
		else
		{
			printf("%u nickel", nickels);
		}
	}
	// Evaluate if there is any change in pennies
	if (pennies != 0)
	{
		//Check if bigger denomination is nonzero
		if (nickels != 0 || dimes != 0 || quarters != 0)
		{
			printf(" and ");
		}
		if (pennies > 1)
		{
			printf("%u pennies", pennies);
		}
		else
		{
			printf("%u penny", pennies);
		}
	}
	printf(".\n");
	return PROCESS_RUNNING;
}

int main()
{
	process_state process = PROCESS_RUNNING;
	while (process != PROCESS_STOPPED)
	{
		uint32_t num = 0;
		process = request_input(&num);
		if (process == PROCESS_RUNNING)
		{
			process = makeChange(num);
		}
		else if (process == PROCESS_FAILED_INPUT)
		{
			printf("Please try again.\n");
		}
		else if (process == PROCESS_FAILED_MEMORY)
		{
			printf("Failed to allocate memory, please close the program and try again.\n");
			process = PROCESS_STOPPED;
			return -1;
		}
	}
	return 0;
}
