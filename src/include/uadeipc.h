#ifndef _UADEIPC_H_
#define _UADEIPC_H_

#include <stdint.h>

#define UADE_MAX_MESSAGE_SIZE (4096)

enum uade_msgtype {
  UADE_MSG_FIRST = 0,
  UADE_COMMAND_CONFIG,
  UADE_COMMAND_SCORE,
  UADE_COMMAND_PLAYER,
  UADE_COMMAND_MODULE,
  UADE_COMMAND_SUBSONG,
  UADE_COMMAND_PLAY,
  UADE_COMMAND_READ,
  UADE_COMMAND_REBOOT,
  UADE_REPLY_MSG,
  UADE_REPLY_CANT_PLAY,
  UADE_REPLY_CAN_PLAY,
  UADE_REPLY_SONG_END,
  UADE_REPLY_CRASH,
  UADE_REPLY_SUBSONG_INFO,
  UADE_REPLY_PLAYERNAME,
  UADE_REPLY_MODULENAME,
  UADE_REPLY_FORMATNAME,
  UADE_REPLY_DATA,
  UADE_MSG_LAST
};

struct uade_msg {
  uint32_t msgtype;
  uint32_t size;
  uint8_t data[];
} __attribute__((packed));

#endif