
#include "case.h"
#include "routing/route_all.h"
#include "buffer/buffer_all.h"

#include <stdio.h>

void test_section (
        struct test_section_t* section, 
        const char** names, 
        const char** messages,
        enum test_result_t* results,
        int* test_count) {
    printf("Running tests for section \"%s\"\n", section->name);

    const char* message;

    for (int test_id = 0; test_id < section->test_count; test_id ++) {
        struct test_case_t* test = section->tests[test_id];

        printf("\tRunning test case \"%s\"... ", test->name);

        enum test_result_t result = test->test(&message);

        switch (result) {
            case OK:
                printf("OK\n");
                break ;
            case WRONG_BEHAVIOR:
                printf("WRONG BEHAVIOR\n");
                break ;
            case TIME_LIMIT_EXCEEDED:
                printf("TIME LIMIT EXCEEDED\n");
                break ;
        }

        names   [*test_count] = test->name;
        messages[*test_count] = message;
        results [*test_count] = result;

        *test_count = *test_count + 1;
    }
}

const char*          name_buffer[10000];
const char*           msg_buffer[10000];
enum test_result_t result_buffer[10000];

int test_count = 0;

int main () {
    test_section(&route_section, name_buffer, msg_buffer, result_buffer, &test_count);
    test_section(&buffer_section, name_buffer, msg_buffer, result_buffer, &test_count);

    int ok_count = 0;
    for (int i = 0; i < test_count; i ++) {
        if (result_buffer[i] != OK) continue ;
        ok_count ++;
    }

    for (int i = 0; i < test_count; i ++) {
        if (result_buffer[i] == OK) continue ;

        printf("\n============================================\n");
        printf("Report for test : \"%s\"\n", name_buffer[i]);
        printf("Result of the test : ");
        switch (result_buffer[i]) {
            case OK:
                printf("OK\n");
                break ;
            case WRONG_BEHAVIOR:
                printf("WRONG BEHAVIOR\n");
                break ;
            case TIME_LIMIT_EXCEEDED:
                printf("TIME LIMIT EXCEEDED\n");
                break ;
        }
        printf("\nError message : \n");
        printf("%s\n", msg_buffer[i]);
    }
    printf("\n\n");
    printf("Test report for IoT-TP\n\n");
    printf("\tERROR COUNT %d\n", test_count - ok_count);
    printf("\tVALID COUNT %d\n\n", ok_count);

    printf("\tTOTAL TEST COUNT %d\n", test_count);

    if (ok_count == test_count) {
        printf("\n\nThe software is ready to be pushed in production\n");
        return 0;
    }

    printf("\n\nA BUG HAS BEEN DETECTED, THE SOFTWARE ISN'T PRODUCTION READY.\n");
    return 1;
}
