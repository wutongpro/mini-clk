/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include <arpa/inet.h>         /* ���� ip_addr_t �ȵ�ַ��ص�ͷ�ļ� */
#include <netdev.h>            /* ����ȫ���� netdev ��ز����ӿں��� */
#include <ntp.h>

/* defined the LED0 pin: PE7 */
#define LED0_PIN    GET_PIN(E, 7)

int main(void)
{
    int count = 1;
    time_t cur_time;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    //��ȡ��������
    struct netdev* net = netdev_get_by_name("esp0");
    //�����жϵ�ǰ�����Ƿ���������
    while(netdev_is_internet_up(net) != 1) {
       rt_thread_mdelay(200);
    }
    //��ʾ��ǰ�����Ѿ���
    rt_kprintf("network is ok!\n");
    //NTP�Զ���ʱ
    cur_time = ntp_sync_to_rtc(NULL);
    if (cur_time) {
        rt_kprintf("Cur Time: %s", ctime((const time_t*) &cur_time));
    }
    else {
        rt_kprintf("NTP sync fail.\n");
    }
    while (count++) {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
