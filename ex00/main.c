#include <stdio.h>
#include <unistd.h>

void    ft_putstr(char *s)
{
    if (*s){
        s++;
        ft_putstr(s);
        write(1, --s, 1);}
}

int main(void)
{
    ft_putstr("ali asasfdsfsdfsa");
	return (0);
}