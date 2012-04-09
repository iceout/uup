/******************************************************************
 * Filename: ls
 * Date:     2012-04-09
 * Description:     自己实现ls命令
 * Last Modified:   2012-04-09
 *****************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void do_ls(const char []);

int main(int argc, const char *argv[])
{
    if (argc == 1) {
        do_ls(".");
    }
    else {
        while (--argc) {
            printf("%s:\n", * ++argv);
            do_ls(*argv);
        }
    }
    return 0;
}

void do_ls(const char dirname[])
{
    DIR *dir_ptr;
    struct dirent *direntp;

    if ((dir_ptr = opendir(dirname)) == NULL)  {
        fprintf(stderr, "ls: cannot open %s\n", dirname);
    }
    else {
        while ((direntp = readdir(dir_ptr)) != NULL) {
            printf("%s\n", direntp->d_name);
        }
        closedir(dir_ptr);
    }
}
