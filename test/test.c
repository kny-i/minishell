#include <unistd.h>

int main()
{
    extern char **environ;
    char    *args[5] = {"cat", "hoge", ">", "out", NULL};

//	char	*vim[2] = {"vim", NULL};
//	execve("usr/bin/bin")

    execve("/bin/cat", args, NULL);
    return (0);
}