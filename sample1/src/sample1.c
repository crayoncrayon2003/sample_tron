#include <kernel.h>
#include <stdio.h>
#include "sample1.h"
#include "kernel_cfg.h"

/* メインタスク (TASK1) */
void task1(intptr_t exinf)
{
    FLGPTN flgptn;
    printf("==================================\n");
    printf("[Task1] Start. Priority=High\n");

    act_tsk(TASK2);
    printf("[Task1] Task2 Activated.\n");

    printf("[Task1] Waiting for EventFlag...\n");
    wai_flg(FLG1, 0x01, TWF_ANDW, &flgptn);

    printf("[Task1] Flag Received! (ptn=0x%x)\n", flgptn);
    printf("[Task1] Finish.\n");
    printf("==================================\n");
    ext_ker();
}

/* サブタスク (TASK2) */
void task2(intptr_t exinf)
{
    printf("    [Task2] Running.\n");
    printf("    [Task2] Sleeping 1sec...\n");
    dly_tsk(1000);
    printf("    [Task2] Set Flag (0x01).\n");
    set_flg(FLG1, 0x01);
    printf("    [Task2] Finish.\n");
    ext_tsk();
}