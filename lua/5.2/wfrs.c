#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <dirent.h>
int atoi(const char *string);
size_t null_data(void *buffer, size_t size, size_t nmemb, void *userp);
int file_exists(const char * filename);
int dir_exists(char *dirname);
int IsComment(const char *__line__);
int main(int argc, char **argv) {
    CURL *curl;
    CURLcode res;
    int return_code = 0;
    if (!dir_exists("/home/telegram-bot")) {
        fprintf(stderr, "wfrs: cannot load scripting directory /home/telegram-bot\n");
        return 1;
    } else {
        if (argv[1] == NULL) {
            printf("wfrs: usage: wfrs lua_script_name (optional)file_for_redis_config\n");
            return 0;
        } else {
            char *__lua_script__ = malloc(23+strlen(argv[1]));
            sprintf(__lua_script__, "/home/telegram-bot/%s.lua", argv[1]);
            if (!file_exists(__lua_script__)) {
                fprintf(stderr, "wfrs: cannot open %s: No such file\n", __lua_script__);
                free(__lua_script__);
                return 1;
            }
            free(__lua_script__);
        }
        if (argv[2] != NULL) {
            FILE * fp;
            fp = fopen(argv[2], "r");
            if (!fp) {
                fprintf(stderr, "wfrs: cannot open %s: No such file\n", argv[2]);
                return 1;
            }
            size_t buff = 0;
            ssize_t read;
            char *line, *tmp_val, *tmp_var, *var_find;
            int position, len, tmp_val_len, line_num;
            tmp_val = malloc(sizeof(char*));
            tmp_var = malloc(sizeof(char*));
            line = malloc(sizeof(char*)*32);
            line_num = 1;
            while ((read = getline(&line, &buff, fp)) != -1) {
                strtok(line, "\n");
                len = strlen(line);
                if (IsComment(line) == 0) {
                    var_find = strchr(line, '=');
                    position = var_find-line;
                    tmp_var = (char *)realloc(tmp_var, position);
                    strncpy(tmp_var, line, position);
                    tmp_var[position] = '\0';
                    if (line[position+1] == '"' || line[position+1] == '\'') {
                        tmp_val = (char *)realloc(tmp_val, len-position);
                        strcpy(tmp_val, &line[position+2]);
                        int last_poc;
                        if (strrchr(tmp_val, '"')) last_poc = strrchr(tmp_val, '"')-tmp_val;
                        else if (strrchr(tmp_val, '\'')) last_poc = strrchr(tmp_val, '\'')-tmp_val;
                        else {
                            // error unfinished string ex. HELLO="hello
                            fprintf(stderr, "wfrs: %s:%i: warning: unfinished string near '%s'\n", argv[2], line_num, tmp_val);
                            continue;
                        }
                        tmp_val[last_poc] = '\0'; // delete last character " or '
                        // add var in line ex. HELLO="hello" HELLO='hello'
                    } else if (line[len-1] == '"' || line[len-1] == '\'') {
                        // error unfinished string ex. HELLO=hello"
                        fprintf(stderr, "wfrs: %s:%i: warning: unfinished string near '%s'\n", argv[2], line_num, tmp_val);
                        continue;
                    } else {
                        // add var in line ex. HELLO=hello
                        tmp_val = (char *)realloc(tmp_val, len-position);
                        strcpy(tmp_val, &line[position+1]);
                        strtok(tmp_val, " ");
                    }
                    int last_poc = strrchr(line, '"')-line;
                    setenv(tmp_var, tmp_val, 1);
                }
                line_num++;
            }
            fclose(fp);
            free(line); free(tmp_var); free(tmp_val);
        }
    }
    char *redis_host = getenv("REDIS_HOST");
    char *redis_port_str = getenv("REDIS_PORT");
    printf("wfrs: loading redis-server...\n");
    if (redis_host == NULL) {
        fprintf(stderr, "wfrs: error loading redis-server, environment variable REDIS_HOST not found.\n\trun: export REDIS_HOST='redis_host'\n\tor: wfrs script_to_init.lua file_for_redis_config.env\n");
        return 1;
    } else if (redis_port_str == NULL) {
        fprintf(stderr, "wfrs: error loading redis-server, environment variable REDIS_PORT not found.\n\trun: export REDIS_PORT='redis_port'\n\tor: wfrs script_to_init.lua file_for_redis_config.env\n");
        return 1;
    }
    curl = curl_easy_init();
    if (curl) {
        int redis_port = atoi(redis_port_str);
        curl_easy_setopt(curl, CURLOPT_PORT, redis_port);
        curl_easy_setopt(curl, CURLOPT_URL, redis_host);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, null_data);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "wfrs: error while running redis-server (%s:%d), response not found, check your port/host redis.\n", redis_host, redis_port);
            return_code = 1;
        } else {
            printf("redis-server (%s:%d) running.\n", redis_host, redis_port);
            printf(" bot.lua...");
            curl_easy_cleanup(curl);

            char *__order_bash__ = malloc(32+strlen(argv[1]));
            sprintf(__order_bash__, "cd /home/telegram-bot ; lua %s.lua", argv[1]);
            system(__order_bash__);
            free(__order_bash__);
            return 0;
        }
        curl_easy_cleanup(curl);
    }
    return return_code;
}
size_t null_data(void *buffer, size_t size, size_t nmemb, void *userp) {
    return size * nmemb;
}
int file_exists(const char * filename) {
    FILE *file;
    if (file = fopen(filename, "r")) {
        fclose(file);
        return 1;
    }
    return 0;
}
int dir_exists(char *dirname) {
    DIR * dir;
    dir = opendir(dirname);
    if (dir != NULL) {
        closedir(dir);
        return 1;
    }
    return 0;
}
int IsComment(const char *__line__) {
    return strncmp("#", __line__, 1) == 0;
}
