#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <dirent.h>
int atoi(const char *string);
size_t null_data(void *buffer, size_t size, size_t nmemb, void *userp);
char* concat(const char *string_1, const char *string_2);
int file_exists(const char * filename);
int dir_exists(char *dirname);
int startsWith(const char *pre, const char *str);
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
            char *__lua_script__ = concat("/home/telegram-bot/", argv[1]);
            __lua_script__ = concat(__lua_script__, ".lua");
            if (!file_exists(__lua_script__)) {
                char *__ffd__ = concat("wfrs: cannot open ", __lua_script__);
                __ffd__ = concat(__ffd__, " No such file");
                fprintf(stderr, "%s\n", __ffd__);
                free(__ffd__); free(__lua_script__);
                return 1;
            }
            free(__lua_script__);
        }
        if (argv[2] != NULL) {
            if (!file_exists(argv[2])) {
                char *__ffd__ = concat("wfrs: cannot open ", argv[2]);
                __ffd__ = concat(__ffd__, ": No such file");
                fprintf(stderr, "%s\n", __ffd__);
                free(__ffd__);
                return 1;
            }
            FILE * fp;
            size_t len;
            ssize_t read;
            char *line, *tmp_val, *tmp_var, *var_find;
            int position, len_line;
            tmp_val = malloc(sizeof(char));
            tmp_var = malloc(sizeof(char));
            line = malloc(sizeof(char));
            len = 0;
            fp = fopen(argv[2], "r");
            while ((read = getline(&line, &len, fp)) != -1 && strlen(line) > 1) {
                strtok(line, "\n");
                if (startsWith("#", line) == 0) {
                    len_line = strlen(line);
                    var_find = strchr(line, '"');
                    if (var_find == NULL) var_find = strchr(line, '\'');
                    if (var_find == NULL) continue;
                    position = (var_find-line);
                    tmp_var = (char *)realloc(tmp_var, position);
                    strncpy(tmp_var, line, position-1);
                    tmp_val = (char *)realloc(tmp_val, len_line-position);
                    strcpy(tmp_val, &line[position]+1);
                    tmp_var[position-1] = '\0';
                    tmp_val[strlen(tmp_val)-1] = '\0';
                    printf("%s === %s %li\n", tmp_var, tmp_val, strlen(tmp_val));
                    setenv(tmp_var, tmp_val, 1);
                }
            }
            printf("BOT_CHANNEL=%s\n", getenv("BOT_CHANNEL"));
            fclose(fp);
            free(line); free(tmp_var); free(tmp_val);
        }
    }
    char *redis_host = getenv("REDIS_HOST");
    char *redis_port_str = getenv("REDIS_PORT");
    printf("\033[1mRunning Redis...\033[0m\n");
    if (redis_host == NULL) {
        fprintf(stderr, "\033[1;31mError while running redis\033[0m, host not found.\n\tRun: export REDIS_HOST='redis_host'\n\tor: wfrs script_to_init.lua file_for_redis_config.env\n");
        return 1;
    } else if (redis_port_str == NULL) {
        fprintf(stderr, "\033[1;31mError while running redis\033[0m, port not found.\n\tRun: export REDIS_PORT='redis_port'\n\tor: wfrs script_to_init.lua file_for_redis_config.env\n");
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
            fprintf(stderr, "\033[1;31mError while running redis\033[0m, response not found, check your port/host redis.\n");
            return_code = 1;
        } else {
            printf("\033[1;32mScript running.\033[0m\n\t\033[1mREDIS_HOST\033[0m %s\n\t\033[1mREDIS_PORT\033[0m %i\n", redis_host, redis_port);
            printf("Running bot.lua...");
            curl_easy_cleanup(curl);
            char *order_bash = concat("cd /home/telegram-bot ; lua '", argv[1]);
            order_bash = concat(order_bash, ".lua'");
            system(order_bash);
            return 0;
        }
        curl_easy_cleanup(curl);
    }
    return return_code;
}
size_t null_data(void *buffer, size_t size, size_t nmemb, void *userp) {
    return size * nmemb;
}
char* concat(const char *string_1, const char *string_2) {
    const size_t length_1 = strlen(string_1);
    const size_t length_2 = strlen(string_2);
    char *result = malloc(length_1 + length_2 + 1);
    memcpy(result, string_1, length_1);
    memcpy(result + length_1, string_2, length_2 + 1);
    return result;
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
int startsWith(const char *pre, const char *str) {
    size_t lenpre = strlen(pre), lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}
