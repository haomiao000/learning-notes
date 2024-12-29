#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // for usleep

int main() {
    long s, t;
    int num = 1;

    while (1) {
        system("clear"); // 清屏 (macOS 和 Linux 使用 "clear")
        do {
            system("./data > in.txt"); // 数据生成程序
            s = clock();
            system("./wa < in.txt > wa.txt"); // 自己程序
            t = clock();
            system("./ac < in.txt > ac.txt"); // 答案

            // 比较两个文件是否相同，macOS 和 Linux 使用 "diff"
            if (system("diff wa.txt ac.txt > /dev/null")) {
                printf("\033[1;31m"); // 设置终端字体为红色
                printf("P%d  ", num);
                break;
            } else {
                printf("\033[1;32m"); // 设置终端字体为绿色
                printf("P%d  ", num);
                printf("Accept time: %ldms\n", (t - s) * 1000 / CLOCKS_PER_SEC);
            }
            num++;
            printf("\n\n\n\n");
        } while (1);

        // 如果文件内容不一致
        printf("\033[1;31m"); // 设置终端字体为红色
        printf("Wrong Answer time: %ldms\n", (t - s) * 1000 / CLOCKS_PER_SEC);
        printf("\033[0m");    // 重置终端字体颜色
        system("diff wa.txt ac.txt"); // 显示文件差异
        system("read -n1 -rsp $'Press any key to continue...\n'"); // macOS 和 Linux 的暂停操作
    }
}