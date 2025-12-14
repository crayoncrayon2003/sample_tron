/* src/sample1.c */
#include <kernel.h>
#include <stdio.h>
#include "sample1.h"
#include "kernel_cfg.h"

/*
 * メイン関数に相当するタスク
 * OS起動時に最初に呼ばれます。
 */
void main_task(intptr_t exinf)
{
    printf("==================================\n");
    printf("[Main] System Start.\n");

    /* Task1 を起動 */
    printf("[Main] Activating Task1...\n");
    act_tsk(TASK1);

    /* 少しタイミングをずらす */
    dly_tsk(100);

    /* Task2 を起動 */
    printf("[Main] Activating Task2...\n");
    act_tsk(TASK2);

    printf("[Main] All tasks activated. Main task exits.\n");
    printf("==================================\n");

    /* 自分の役目は終わったので終了 */
    ext_tsk();
}


/* 共通の作業関数 */
void do_heavy_work(const char* name)
{
    /* 1. セマフォ取得待ち */
    printf("%s[WAIT]\n", name);

    /* セマフォ獲得 (P操作) */
    wai_sem(SEM1);

    /* 2. 取得成功・ロック中 */
    printf("%s[LOCKED]\n", name);

    /* 重い処理のシミュレーション（3秒） */
    dly_tsk(3000);

    /* 3. 解放 */
    printf("%s[UNLOCKED]\n", name);

    /* セマフォ返却 (V操作) */
    sig_sem(SEM1);
}

void task1(intptr_t exinf)
{
    setbuf(stdout, NULL);

    while(1) {
        do_heavy_work("[Task1]");

        /* 次の作業まで少し休む */
        dly_tsk(1000);
    }
}

void task2(intptr_t exinf)
{
    setbuf(stdout, NULL);

    while(1) {
        do_heavy_work("[Task2]");

        /* 次の作業まで少し休む */
        dly_tsk(1000);
    }
}

