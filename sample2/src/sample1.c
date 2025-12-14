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

    /* Task2 を起動 */
    printf("[Main] Activating Task2...\n");
    act_tsk(TASK2);

    printf("[Main] All tasks activated. Main task exits.\n");
    printf("==================================\n");

    /* 自分の役目は終わったので終了 */
    ext_tsk();
}

/*
 * タスク1 (Task1)
 * 5秒待機 -> 入力待ち -> フラグセット
 */
void task1(intptr_t exinf)
{
    int count = 0; /* 加算し続ける変数 */

    setbuf(stdout, NULL);
    printf("[Task1] Started.\n");

    while(1) {
        /* 2秒待つ */
        printf("[Task1] Sleeping 2 sec...\n");
        dly_tsk(2000);

        count++;
		count %= 4;

        if (count == 0) {
            printf("[Task1] Count=%d. Setting Flag...\n", count);
            set_flg(FLG1, 0x01);
        } else {
            printf("[Task1] Count=%d. Skip.\n", count);
        }
    }
}

/*
 * タスク2 (Task2)
 * フラグ待ち -> 表示
 */
void task2(intptr_t exinf)
{
    FLGPTN flgptn;

    printf("    [Task2] Started.\n");

    while(1) {
        printf("    [Task2] Waiting for EventFlag...\n");
		/* フラグ待ち */
        wai_flg(FLG1, 0x01, TWF_ANDW, &flgptn);

        printf("    [Task2] !!! EVENT FLAG RECEIVED !!! (ptn=0x%x)\n", flgptn);

        /* フラグクリア */
        clr_flg(FLG1, ~0x01);
    }
}