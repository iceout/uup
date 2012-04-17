/******************************************************************
 * Filename: ls
 * Date:     2012-04-09
 * Description:     自己实现ls命令
 * Last Modified:   2012-04-09
 *****************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

void do_ls(char []);
void dostat(char *fname);
void show_file_info(char *fname, struct stat *info);
void mode_to_letters(int mode, char str[]);
char *uid_to_name( uid_t );
char *gid_to_name( gid_t );

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
        if (lsl == 1) {
            while ((direntp = readdir(dir_ptr)) != NULL) {
                dostat(direntp->d_name);
            }
        }
        else {
            while ((direntp = readdir(dir_ptr)) != NULL) {
                printf("%s\n", direntp->d_name);
            }
        }
        closedir(dir_ptr);
    }
}
void dostat(char * fname)
{
    struct stat info;
    if (stat(fname, &info) == -1) {
        perror(fname);
    }
    else {
        show_file_info(fname, &info);
    }
}
void show_file_info(char *fname, struct stat *info)
{
    char modestr[11];

    mode_to_letters(info->st_mode, modestr);
    
    printf("%s", modestr);
    printf(" %4d", (int)info->st_nlink);
	printf(" %-6s" , uid_to_name(info->st_uid) );
	printf(" %-6s" , gid_to_name(info->st_gid) );
	printf(" %4ld" , (long)info->st_size);
    printf(" %.12s", 4+ctime(&info->st_mtime));
    printf(" %s\n", fname);
}
void mode_to_letters(int mode, char str[])
{
    strcpy(str, "----------");

    if (S_ISDIR(mode)) {
        str[0] = 'd';
    }
    if (S_ISCHR(mode)) {
        str[0] = 'c';
    }
    if (S_ISBLK(mode)) {
        str[0] = 'b';
    }
    if ( mode & S_IRUSR ) str[1] = 'r';    /* 3 bits for user  */
    if ( mode & S_IWUSR ) str[2] = 'w';
    if ( mode & S_IXUSR ) str[3] = 'x';

    if ( mode & S_IRGRP ) str[4] = 'r';    /* 3 bits for group */
    if ( mode & S_IWGRP ) str[5] = 'w';
    if ( mode & S_IXGRP ) str[6] = 'x';

    if ( mode & S_IROTH ) str[7] = 'r';    /* 3 bits for other */
    if ( mode & S_IWOTH ) str[8] = 'w';
    if ( mode & S_IXOTH ) str[9] = 'x';
}
#include	<pwd.h>

char *uid_to_name( uid_t uid )
/* 
 *	returns pointer to username associated with uid, uses getpw()
 */	
{
	struct	passwd *getpwuid(), *pw_ptr;
	static  char numstr[10];

	if ( ( pw_ptr = getpwuid( uid ) ) == NULL ){
		sprintf(numstr,"%d", uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name ;
}

#include	<grp.h>

char *gid_to_name( gid_t gid )
/*
 *	returns pointer to group number gid. used getgrgid(3)
 */
{
	struct group *getgrgid(), *grp_ptr;
	static  char numstr[10];

	if ( ( grp_ptr = getgrgid(gid) ) == NULL ){
		sprintf(numstr,"%d", gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}
