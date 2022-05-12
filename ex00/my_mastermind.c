#include "my_mastermind.h"

int random_number(int min, int max)
{
    int result = 0;
    int low_nbr = 0;
    int hi_nbr = 0;

    low_nbr = min;
    hi_nbr = max + 1;
    srand(time(NULL));
    result = (rand() % (hi_nbr-low_nbr)) + low_nbr;
    return result;
}

int my_strlen(char* str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len += 1;
    }
    return len;
}

int my_strcmp(char* str1, char* str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i])
    {
        i += 1;
    }
    return (str1[i]-str2[i]);
}



int number_of_attempts(struct init_options *options)
{
    if (options->t == true)
    {
        return options->attempts;
    }
    else
    {
        return 10;
    }
}

int init_option(int ac, char** av, struct init_options *options)
{
    int i = 1;
    options->c = false;
    options->t = false;
    options->code = 0;
    options->attempts = 0;
    options->random_code = random_number(1000, 7777);

    if (ac > 1 && ac < 6)
    {
        if (my_strcmp(av[i], "-c") != 0 && my_strcmp(av[i], "-t") != 0)
        {
            return -1;
        }
        while (i < ac)
        {
            if (my_strcmp(av[i], "-c") == 0 && av[i+1] != NULL)
            {
                options->c = true;
                if (is_valid(av[i+1]) == true)
                {
                    options->code = av[i+1];
                }
                else
                {
                    return -1;
                }
            }
            if (my_strcmp(av[i], "-t") == 0 && av[i+1] != NULL)
            {
                options->t = true;
                if (atoi(av[i+1]) > 0)
                {
                    options->attempts = atoi(av[i+1]);
                }
                else
                {
                    printf("Number of attemps must be a positive number\n");
                    return -1;
                }
            }
            if ((my_strcmp(av[i], "-c") == 0 && av[i+1] == NULL) || (my_strcmp(av[i], "-t") == 0 && av[i+1] == NULL))
            {
                return -1;
            }
            i += 1;
        }
        return 0;
    }
    else if (ac == 1)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

bool is_digit(char* str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 48 && str[i] <= 55)
        {
            i += 1;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool is_valid(char* user_guess)
{
    if (my_strlen(user_guess) == CODE_SIZE)
    {

       if (is_digit(user_guess) == false)
       {
           return false;
       }
    }
    else
    {
        return false;
    }
    return true;
}

bool is_digit_input(char* str)
{
    int i = 0;
    while (str[i] != '\n')
    {
        if (str[i] >= 48 && str[i] <= 55)
        {
            i += 1;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool is_valid_input(char* user_guess)
{
    if (my_strlen(user_guess) == CODE_SIZE+1)
    {
       if (is_digit_input(user_guess) == false)
       {
           return false;
       }
    }
    else
    {
        return false;
    }
    return true;
}

int check_code(char* code, struct init_options *options)
{
    int misplaced_pieces = 0;
    int wellplaced_pieces = 0;
    int i = 0;
    int j = 0;
    char* secret_code = malloc(sizeof(char) * CODE_SIZE+1);

    if (options->c == true)
    {
        secret_code = options->code;
    }
    else
    {
        snprintf(secret_code, sizeof(char)*5, "%d", options->random_code);
    }
    while (code[i] != '\n')
    {
        if (code[i] == secret_code[i])
        {
            wellplaced_pieces += 1;
        }
        j = 0;
        while (secret_code[j] != '\0')
        {
            if (i != j && code[i] == secret_code[j])
            {
                misplaced_pieces += 1;
            }
            j += 1;                    
        }
        i += 1;
    }
    if (wellplaced_pieces == 4)
    {
        printf("Congratulations! You won!\n");
        return EXIT_SUCCESS;
    }
    else
    {
        printf("Well placed pieces: %d\n", wellplaced_pieces);
        printf("Misplaced pieces: %d\n", misplaced_pieces);
        return EXIT_FAILURE;
    }
}

void print_first_round(int round, int attempts)
{
    printf("Will you find the secret code?\n");
    printf("You have %d attempts, good luck!\n", attempts);
    printf("---\n");
    printf("Round %d\n", round);
}

void print_rounds(int round)
{
    printf("---\n");
    printf("Round %d\n", round);
}

void print_secret_code(struct init_options *options)
{
    if (options->c == false)
    {
        printf("The secret code was: --> %d <--\nGood luck next time!\n", options->random_code);
    }
    else
    {
        printf("The secret code was: --> %s <--\nGood luck next time!\n", options->code);
    }
}

int main(int ac, char** av)
{
   struct init_options options;
   int valid_option = init_option(ac, av, &options);
   int round = 0;
   char code[128];
   int attempts;

   if (valid_option == 0)
   {
            attempts = number_of_attempts(&options);
            print_first_round(round, attempts);
            while (1)
            {
                read(0, code, sizeof(code));
                round += 1;
                if (is_valid_input(code) == true)
                {
                    if (check_code(code, &options) == EXIT_SUCCESS)
                    {
                        return EXIT_SUCCESS;
                    }
                }
                else
                {
                    printf("Code should be 4 digits in range [0 to 7]\nPlease, start again!\n");
                    return EXIT_FAILURE; 
                }
                if (round >= attempts)
                {
                    printf("KO! Game over!\n");
                    print_secret_code(&options);
                    return EXIT_SUCCESS;
                }
                print_rounds(round);
            }
   }
   else
   {
        printf("My_Mastermind accepts only: [-c] + a code of 4 digits in range [0 to 7] + [-t] + a number bigger than zero.\nExample: ./my_mastermind -c 1234 -t 8\n");
   }
   return EXIT_SUCCESS;
}
