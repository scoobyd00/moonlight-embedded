/*
 * This file is part of Moonlight Embedded.
 *
 * Copyright (C) 2015 Iwan Timmer
 *
 * Moonlight is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Moonlight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Moonlight; if not, see <http://www.gnu.org/licenses/>.
 */

#include "../video.h"

#include <stdio.h>

static FILE* fd;
static const char* fileName = "fake.h264";

void decoder_renderer_setup(int width, int height, int redrawRate, void* context, int drFlags) {
  printf("decoder_renderer_setup %dx%d %dfps\n", width, height, redrawRate);
  fd = fopen(fileName, "w");
}

void decoder_renderer_release() {
  printf("decoder_renderer_release\n");
  fclose(fd);
}

int decoder_renderer_submit_decode_unit(PDECODE_UNIT decodeUnit) {
  PLENTRY entry = decodeUnit->bufferList;
  while (entry != NULL) {
    fwrite(entry->data, entry->length, 1, fd);
    entry = entry->next;
  }
  return DR_OK;
}

DECODER_RENDERER_CALLBACKS decoder_callbacks_fake = {
  .setup = decoder_renderer_setup,
  .start = NULL,
  .stop = NULL,
  .release = decoder_renderer_release,
  .submitDecodeUnit = decoder_renderer_submit_decode_unit,
};
