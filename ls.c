/******************************************************************
 * Filename: ls
 * Date:     2012-04-09
 * Description:     自己实现ls命令
 * Last Modified:   2012-04-09
 *****************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

void do_ls(char []);
int lsa = 0, lsl = 0;
int main(int argc, char *argv[])
{
    const char* optstring = "al";
    char *pwd;
    int opt = 0;
    int ind = 0;
    while ((opt = getopt(argc, argv, optstring)) != -1){
        switch (opt) {
            case 'a':
                lsa = 1;
                printf("lsa = true\n");
                break;
            case 'l':
                lsl = 1;
                printf("lsl = true\n");
                break;
            case '?':
            default:
                printf("???\n");
                break;
        }
    }
    ind = optind;
    if (ind < argc) {
        while (ind < argc) {
            printf("ind == %d\n", ind);
            do_ls(*(argv+ind));
            ind++;
            if (ind != argc) {
                printf("\n");
            }
        }
    }
    else {
        do_ls(".");
    }
    /*if (argc == 1) {
        do_ls(".");
    }
    else {
        while (--argc) {
            printf("%s:\n", * ++argv);
            do_ls(*argv);
        }
    }*/
    return 0;
}

void do_ls(char dirname[])
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
