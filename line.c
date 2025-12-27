#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// lists
const char *insert_cmd[] = {"i", "a", "w", ":i", ":a", ":w", NULL};
const char *quit_cmd[]   = {"q", "b", ":q", ":b", NULL};
const char *fpath_cmd[]  = {"f", ":f", NULL};
const char *print_cmd[]  = {"p", ":p", NULL};

// yanked from git@github.com:jstmaxlol/g
int matches(const char *cmd, const char *list[]);

int main(int argc, char **argv) {
    char cmd[32];
    char tmp[768];
    char line[1024];
    bool oob = false;
    bool fpath_arg = false;
    FILE *f = NULL;

    printf("----------------------------\n");

    if (argc == 2) {
        printf("a\'%s\',y\n!q\n", argv[1]);
        if (strlen(argv[1]) >= 1) {
            f = fopen(argv[1], "a");
            fpath_arg = true;
        }
        else {
            printf("df?!\n");
            return 1;
        }
    } else if (argc >= 3) {
        printf("?!\n");
        printf("%s? (Y/n)", argv[1]);
        scanf("%s", tmp);
        if (strcmp(tmp, "y") == 0 || strcmp(tmp, "Y") == 0 || strlen(tmp) < 1) {
            if (strlen(argv[1]) >= 1) {
                f = fopen(argv[1], "a");
                fpath_arg = true;
            } else {
                printf("df?!\n");
                return 1;
            }
        }
    } else {
        printf("u\'buff\'\n!q\n");
        f = fopen("buff", "a");
    }

    if (!f) {
        printf("!F\nq.\n:(\n");
        return 1;
    }

    printf(":)\n");                         // welcome msg
    while (true) {
        cmd[0] = '\0';
        printf("?\n");
        scanf("%s", cmd);

        if (matches(cmd, insert_cmd) == 0) {
            while (!oob && fgets(line, sizeof line, stdin)) {
                if (strcmp(line, ".\n") == 0 || strcmp(line, ".") == 0)
                    break;
                fputs(line, f);
            }
        }
        else if (matches(cmd, fpath_cmd) == 0) {
            // TODO
            printf("!\n");
            break;
        }
        else if (matches(cmd, print_cmd) == 0) {
            fclose(f);
            if (fpath_arg)
                f = fopen(argv[1], "r");
            else
                f = fopen("buff", "r");
            int c;
            while ((c = fgetc(f)) != EOF)
                putchar(c);
            fclose(f);
            if (fpath_arg)
                f = fopen(argv[1], "a");
            else
                f = fopen("buff", "a");
        }
        else if (matches(cmd, quit_cmd) == 0) {
            break;
        }
    }

    printf("----------------------------\n");
    fclose(f);
    return 0;
}

int matches(const char *cmd, const char *list[]) {
    for (int i = 0; list[i] != NULL; i++) {
        if (strcmp(cmd, list[i]) == 0) {
            return 0;
        }
    }
    return 1;
}
