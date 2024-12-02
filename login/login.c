#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"

// 중복 아이디 확인 함수
int check_id(char *id){
    FILE *fp = fopen("users.txt", "r");
    if (!fp) {
        perror("Unable to open file.\n");
        return 0;
    }

    char file_id[MAX_USERID];
    char file_password[MAX_PASSWORD];

    while (fscanf(fp, "%s %s", file_id, file_password) != EOF) {
        if (strcmp(id, file_id) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// 회원가입 함수
int register_user(char *user_id, char *password) {
    // 먼저 중복 아이디 체크
    if (check_id(user_id)) {
        return 0;  // 중복된 아이디 존재
    }

    FILE *fp = fopen("users.txt", "a");  
    if (!fp) {
        perror("Unable to open file.\n");
        return -1; 
    }

    // 파일 끝에 개행 문자가 있는지 확인
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size > 0) {
        fseek(fp, size - 1, SEEK_SET);
        char last_char;
        if (fread(&last_char, 1, 1, fp) == 1 && last_char != '\n') {
            // 마지막 문자가 개행이 아니면 개행 추가
            fprintf(fp, "\n");
        }
        fseek(fp, 0, SEEK_END);
    }

    // 새로운 사용자 정보 추가
    fprintf(fp, "%s %s\n", user_id, password);
    fclose(fp);

    return 1; // 회원가입 성공
}

// 로그인 함수
int login_user(char *user_id, char *password) {
    FILE *fp = fopen("users.txt", "r");
    if (!fp) {
        perror("Unable to open file.\n");
        return 0;
    }

    char file_id[MAX_USERID];
    char file_password[MAX_PASSWORD];
    while (fscanf(fp, "%s %s", file_id, file_password) != EOF) {
        if (strcmp(user_id, file_id) == 0 && strcmp(password, file_password) == 0) {
            fclose(fp);
            return 1; // 로그인 성공
        }
    }

    fclose(fp);
    return 0; // 로그인 실패
}
