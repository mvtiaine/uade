/* 
 * UADE sound output
 * 
 * Copyright 1997 Bernd Schmidt
 * Copyright 2000-2005 Heikki Orsila <heikki.orsila@iki.fi>
 */

#include <assert.h>
#include <stdint.h>

#include <ao/ao.h>
#include <errno.h>
#include <string.h>

#include "uade.h"

#define MAX_SOUND_BUF_SIZE (65536)

extern uae_u16 sndbuffer[];
extern uae_u16 *sndbufpt;
extern int sndbufsize;
extern int sound_bytes_per_sample;
extern ao_device *libao_device;

extern void finish_sound_buffer (void);


static void check_sound_buffers (void) {
  assert(uade_read_size > 0);
  intptr_t bytes = ((intptr_t) sndbufpt) - ((intptr_t) sndbuffer);
  if (bytes == 2048 || bytes == uade_read_size) {
    uade_check_sound_buffers(uade_read_size > 2048 ? 2048 : uade_read_size);
    sndbufpt = sndbuffer;
  }
}

#define PUT_SOUND_BYTE(b) do { *(uae_u8 *)sndbufpt = b; sndbufpt = (uae_u16 *)(((uae_u8 *)sndbufpt) + 1); } while (0)
#define PUT_SOUND_WORD(b) do { *(uae_u16 *)sndbufpt = b; sndbufpt = (uae_u16 *)(((uae_u8 *)sndbufpt) + 2); } while (0)
#define PUT_SOUND_BYTE_LEFT(b) PUT_SOUND_BYTE(b)
#define PUT_SOUND_WORD_LEFT(b) PUT_SOUND_WORD(b)
#define PUT_SOUND_BYTE_RIGHT(b) PUT_SOUND_BYTE(b)
#define PUT_SOUND_WORD_RIGHT(b) PUT_SOUND_WORD(b)
#define SOUND16_BASE_VAL 0
#define SOUND8_BASE_VAL 128

#define DEFAULT_SOUND_MAXB 8192
#define DEFAULT_SOUND_MINB 8192
#define DEFAULT_SOUND_BITS 16
#define DEFAULT_SOUND_FREQ 44100
#define HAVE_STEREO_SUPPORT