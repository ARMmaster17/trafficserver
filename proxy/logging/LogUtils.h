/** @file

  A brief file description

  @section license License

  Licensed to the Apache Software Foundation (ASF) under one
  or more contributor license agreements.  See the NOTICE file
  distributed with this work for additional information
  regarding copyright ownership.  The ASF licenses this file
  to you under the Apache License, Version 2.0 (the
  "License"); you may not use this file except in compliance
  with the License.  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 */
#pragma once

#include <ctime>

#include "tscore/ink_platform.h"
#include "tscore/Arena.h"
#include <tscpp/util/TextView.h>

class MIMEHdr;

namespace LogUtils
{
enum AlarmType {
  LOG_ALARM_ERROR = 0,
  LOG_ALARM_WARNING,
  LOG_ALARM_N_TYPES,
};

static inline long
timestamp()
{
  return (long)time(nullptr);
}

int timestamp_to_str(long timestamp, char *buf, int size);
char *timestamp_to_netscape_str(long timestamp);
char *timestamp_to_date_str(long timestamp);
char *timestamp_to_time_str(long timestamp);
unsigned ip_from_host(char *host);
void strip_trailing_newline(char *buf);
char *escapify_url(Arena *arena, char *url, size_t len_in, int *len_out, char *dst = nullptr, size_t dst_size = 0,
                   const unsigned char *map = nullptr);
char *pure_escapify_url(Arena *arena, char *url, size_t len_in, int *len_out, char *dst = nullptr, size_t dst_size = 0,
                        const unsigned char *map = nullptr);
char *int64_to_str(char *buf, unsigned int buf_size, int64_t val, unsigned int *total_chars, unsigned int req_width = 0,
                   char pad_char = '0');
void remove_content_type_attributes(char *type_str, int *type_len);
int timestamp_to_hex_str(unsigned timestamp, char *str, size_t len, size_t *n_chars = nullptr);
int seconds_to_next_roll(time_t time_now, int rolling_offset, int rolling_interval);
int file_is_writeable(const char *full_filename, off_t *size_bytes = nullptr, bool *has_size_limit = nullptr,
                      uint64_t *current_size_limit_bytes = nullptr);

/** Given a rolled file, determine the unrolled filename.
 *
 * For example, given this:
 *   diags.log.20191114.21h43m16s-20191114.21h43m17s.old
 *
 * Return this:
 *   diags.log
 *
 * @param[in] rolled_filename The rolled filename from which to derive the
 * unrolled filename.
 *
 * @return The unrolled filename if it looked like a rolled log file or the
 * input filename if it didn't.
 */
ts::TextView get_unrolled_filename(ts::TextView rolled_filename);

// Marshals header tags and values together, with a single terminating nul character.  Returns buffer space required.  'buf' points
// to where to put the marshaled data.  If 'buf' is null, no data is marshaled, but the function returns the amount of space that
// would have been used.
int marshalMimeHdr(MIMEHdr *hdr, char *buf);

// Unmarshelled/printable format is {{{tag1}:{value1}}{{tag2}:{value2}} ... }
//
// Returns -1 if data corruption is detected, otherwise the actual amount of data put into the 'dest' buffer.  '*buf' is advanced
// to byte after the last byte consumed.
int unmarshalMimeHdr(char **buf, char *dest, int destLength);

}; // namespace LogUtils
