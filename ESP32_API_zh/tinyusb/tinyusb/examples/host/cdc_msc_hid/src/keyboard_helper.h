#ifndef KEYBOARD_HELPER_H
#define KEYBAORD_HELPER_H

#include <stdbool.h>
#include <stdint.h>

#include "tusb.h"

// 在以前的密钥中查找新密钥
inline bool find_key_in_report(hid_keyboard_report_t const *p_report, uint8_t keycode)
{
  for(uint8_t i = 0; i < 6; i++)
  {
    if (p_report->keycode[i] == keycode)  return true;
  }

  return false;
}

inline uint8_t keycode_to_ascii(uint8_t modifier, uint8_t keycode)
{
  return keycode > 128 ? 0 :
    hid_keycode_to_ascii_tbl [keycode][modifier & (KEYBOARD_MODIFIER_LEFTSHIFT | KEYBOARD_MODIFIER_RIGHTSHIFT) ? 1 : 0];
}

void print_kbd_report(hid_keyboard_report_t *prev_report, hid_keyboard_report_t const *new_report)
{

  printf("Report: ");
  uint8_t c;

  // 我假设每个报告可能有多达6个按键事件？
  for (uint8_t i = 0; i < 6; i++)
  {
    // 检查是否有按键
    if (new_report->keycode[i])
    {
      // 如果不在上一个报告中，则重新按下
      if ( !find_key_in_report(prev_report, new_report->keycode[i]) )
        c = keycode_to_ascii(new_report->modifier, new_report->keycode[i]);
        printf("press %c ", c);
    }

    // 检查是否按下了键（即，上一次报告中有键，但此处没有键）
    if (prev_report->keycode[i])
    {
      // 如果当前报告中不存在，则按下
      if (!find_key_in_report(new_report, prev_report->keycode[i]))
      {
        c = keycode_to_ascii(prev_report->modifier, prev_report->keycode[i]);
        printf("depress %c ", c);
      }
    }
  }

  printf("\n");
}

#endif
