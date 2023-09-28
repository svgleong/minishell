#include <executer.h>

void    pwd_bi(void)
{
    char    cwd[PATH_MAX];

        printf("entrou pwd");

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("aqui");
        printf("%s", cwd);
    }
    else
        printf("error in finding directory");
}