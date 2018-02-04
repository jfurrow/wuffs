#ifndef WUFFS_ZLIB_H
#define WUFFS_ZLIB_H

// Code generated by wuffs-c. DO NOT EDIT.

#ifndef WUFFS_BASE_HEADER_H
#define WUFFS_BASE_HEADER_H

// Copyright 2017 The Wuffs Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Wuffs requires a word size of at least 32 bits because it assumes that
// converting a u32 to usize will never overflow. For example, the size of a
// decoded image is often represented, explicitly or implicitly in an image
// file, as a u32, and it is convenient to compare that to a buffer size.
//
// Similarly, the word size is at most 64 bits because it assumes that
// converting a usize to u64 will never overflow.
#if __WORDSIZE < 32
#error "Wuffs requires a word size of at least 32 bits"
#elif __WORDSIZE > 64
#error "Wuffs requires a word size of at most 64 bits"
#endif

// WUFFS_VERSION is the major.minor version number as a uint32. The major
// number is the high 16 bits. The minor number is the low 16 bits.
//
// The intention is to bump the version number at least on every API / ABI
// backwards incompatible change.
//
// For now, the API and ABI are simply unstable and can change at any time.
//
// TODO: don't hard code this in base-header.h.
#define WUFFS_VERSION (0x00001)

// wuffs_base__slice_u8 is a 1-dimensional buffer (a pointer and length).
//
// A value with all fields NULL or zero is a valid, empty slice.
typedef struct {
  uint8_t* ptr;
  size_t len;
} wuffs_base__slice_u8;

// wuffs_base__buf1 is a 1-dimensional buffer (a pointer and length), plus
// additional indexes into that buffer, plus an opened / closed flag.
//
// A value with all fields NULL or zero is a valid, empty buffer.
typedef struct {
  uint8_t* ptr;  // Pointer.
  size_t len;    // Length.
  size_t wi;     // Write index. Invariant: wi <= len.
  size_t ri;     // Read  index. Invariant: ri <= wi.
  bool closed;   // No further writes are expected.
} wuffs_base__buf1;

// wuffs_base__limit1 provides a limited view of a 1-dimensional byte stream:
// its first N bytes. That N can be greater than a buffer's current read or
// write capacity. N decreases naturally over time as bytes are read from or
// written to the stream.
//
// A value with all fields NULL or zero is a valid, unlimited view.
typedef struct wuffs_base__limit1 {
  uint64_t* ptr_to_len;             // Pointer to N.
  struct wuffs_base__limit1* next;  // Linked list of limits.
} wuffs_base__limit1;

typedef struct {
  // TODO: move buf into private_impl? As it is, it looks like users can modify
  // the buf field to point to a different buffer, which can turn the limit and
  // mark fields into dangling pointers.
  wuffs_base__buf1* buf;
  // Do not access the private_impl's fields directly. There is no API/ABI
  // compatibility or safety guarantee if you do so.
  struct {
    wuffs_base__limit1 limit;
    uint8_t* mark;
  } private_impl;
} wuffs_base__reader1;

typedef struct {
  // TODO: move buf into private_impl? As it is, it looks like users can modify
  // the buf field to point to a different buffer, which can turn the limit and
  // mark fields into dangling pointers.
  wuffs_base__buf1* buf;
  // Do not access the private_impl's fields directly. There is no API/ABI
  // compatibility or safety guarantee if you do so.
  struct {
    wuffs_base__limit1 limit;
    uint8_t* mark;
  } private_impl;
} wuffs_base__writer1;

#endif  // WUFFS_BASE_HEADER_H

// ---------------- Use Declarations

// ---------------- BEGIN USE "std/deflate"

#ifndef WUFFS_DEFLATE_H
#define WUFFS_DEFLATE_H

// Code generated by wuffs-c. DO NOT EDIT.

// ---------------- Use Declarations

#ifdef __cplusplus
extern "C" {
#endif

// ---------------- Status Codes

// Status codes are int32_t values:
//  - the sign bit indicates a non-recoverable status code: an error
//  - bits 10-30 hold the packageid: a namespace
//  - bits 8-9 are reserved
//  - bits 0-7 are a package-namespaced numeric code
//
// Do not manipulate these bits directly. Use the API functions such as
// wuffs_deflate__status__is_error instead.
typedef int32_t wuffs_deflate__status;

#define wuffs_deflate__packageid 848533  // 0x000CF295

#define WUFFS_DEFLATE__STATUS_OK 0                               // 0x00000000
#define WUFFS_DEFLATE__ERROR_BAD_WUFFS_VERSION -2147483647       // 0x80000001
#define WUFFS_DEFLATE__ERROR_BAD_RECEIVER -2147483646            // 0x80000002
#define WUFFS_DEFLATE__ERROR_BAD_ARGUMENT -2147483645            // 0x80000003
#define WUFFS_DEFLATE__ERROR_INITIALIZER_NOT_CALLED -2147483644  // 0x80000004
#define WUFFS_DEFLATE__ERROR_INVALID_I_O_OPERATION -2147483643   // 0x80000005
#define WUFFS_DEFLATE__ERROR_CLOSED_FOR_WRITES -2147483642       // 0x80000006
#define WUFFS_DEFLATE__ERROR_UNEXPECTED_EOF -2147483641          // 0x80000007
#define WUFFS_DEFLATE__SUSPENSION_SHORT_READ 8                   // 0x00000008
#define WUFFS_DEFLATE__SUSPENSION_SHORT_WRITE 9                  // 0x00000009
#define WUFFS_DEFLATE__ERROR_CANNOT_RETURN_A_SUSPENSION \
  -2147483638                                                   // 0x8000000A
#define WUFFS_DEFLATE__ERROR_INVALID_CALL_SEQUENCE -2147483637  // 0x8000000B

#define WUFFS_DEFLATE__ERROR_BAD_HUFFMAN_CODE_OVER_SUBSCRIBED \
  -1278585856  // 0xB3CA5400
#define WUFFS_DEFLATE__ERROR_BAD_HUFFMAN_CODE_UNDER_SUBSCRIBED \
  -1278585855  // 0xB3CA5401
#define WUFFS_DEFLATE__ERROR_BAD_HUFFMAN_CODE_LENGTH_COUNT \
  -1278585854  // 0xB3CA5402
#define WUFFS_DEFLATE__ERROR_BAD_HUFFMAN_CODE_LENGTH_REPETITION \
  -1278585853                                              // 0xB3CA5403
#define WUFFS_DEFLATE__ERROR_BAD_HUFFMAN_CODE -1278585852  // 0xB3CA5404
#define WUFFS_DEFLATE__ERROR_BAD_HUFFMAN_MINIMUM_CODE_LENGTH \
  -1278585851                                                     // 0xB3CA5405
#define WUFFS_DEFLATE__ERROR_BAD_DISTANCE -1278585850             // 0xB3CA5406
#define WUFFS_DEFLATE__ERROR_BAD_DISTANCE_CODE_COUNT -1278585849  // 0xB3CA5407
#define WUFFS_DEFLATE__ERROR_BAD_FLATE_BLOCK -1278585848          // 0xB3CA5408
#define WUFFS_DEFLATE__ERROR_BAD_LITERAL_LENGTH_CODE_COUNT \
  -1278585847  // 0xB3CA5409
#define WUFFS_DEFLATE__ERROR_INCONSISTENT_STORED_BLOCK_LENGTH \
  -1278585846  // 0xB3CA540A
#define WUFFS_DEFLATE__ERROR_MISSING_END_OF_BLOCK_CODE \
  -1278585845                                              // 0xB3CA540B
#define WUFFS_DEFLATE__ERROR_NO_HUFFMAN_CODES -1278585844  // 0xB3CA540C
#define WUFFS_DEFLATE__ERROR_INTERNAL_ERROR_INCONSISTENT_HUFFMAN_DECODER_STATE \
  -1278585843  // 0xB3CA540D
#define WUFFS_DEFLATE__ERROR_INTERNAL_ERROR_INCONSISTENT_HUFFMAN_END_OF_BLOCK \
  -1278585842  // 0xB3CA540E
#define WUFFS_DEFLATE__ERROR_INTERNAL_ERROR_INCONSISTENT_DISTANCE \
  -1278585841  // 0xB3CA540F
#define WUFFS_DEFLATE__ERROR_INTERNAL_ERROR_INCONSISTENT_N_BITS \
  -1278585840  // 0xB3CA5410

bool wuffs_deflate__status__is_error(wuffs_deflate__status s);

const char* wuffs_deflate__status__string(wuffs_deflate__status s);

// ---------------- Public Consts

// ---------------- Structs

typedef struct {
  // Do not access the private_impl's fields directly. There is no API/ABI
  // compatibility or safety guarantee if you do so. Instead, use the
  // wuffs_deflate__decoder__etc functions.
  //
  // In C++, these fields would be "private", but C does not support that.
  //
  // It is a struct, not a struct*, so that it can be stack allocated.
  struct {
    wuffs_deflate__status status;
    uint32_t magic;

    uint32_t f_bits;
    uint32_t f_n_bits;
    uint32_t f_huffs[2][1234];
    uint32_t f_n_huffs_bits[2];
    uint8_t f_history[32768];
    uint32_t f_history_index;
    uint8_t f_code_lengths[320];
    bool f_end_of_block;

    struct {
      uint32_t coro_susp_point;
      wuffs_deflate__status v_z;
      uint64_t v_n_copied;
      uint32_t v_already_full;
    } c_decode[1];
    struct {
      uint32_t coro_susp_point;
      uint32_t v_final;
      uint32_t v_type;
    } c_decode_blocks[1];
    struct {
      uint32_t coro_susp_point;
      uint32_t v_length;
      uint32_t v_n_copied;
      uint64_t scratch;
    } c_decode_uncompressed[1];
    struct {
      uint32_t coro_susp_point;
      uint32_t v_i;
    } c_init_fixed_huffman[1];
    struct {
      uint32_t coro_susp_point;
      uint32_t v_bits;
      uint32_t v_n_bits;
      uint32_t v_n_lit;
      uint32_t v_n_dist;
      uint32_t v_n_clen;
      uint32_t v_i;
      uint32_t v_mask;
      uint32_t v_table_entry;
      uint32_t v_table_entry_n_bits;
      uint32_t v_n_extra_bits;
      uint8_t v_rep_symbol;
      uint32_t v_rep_count;
    } c_init_dynamic_huffman[1];
    struct {
      uint32_t coro_susp_point;
      uint32_t v_bits;
      uint32_t v_n_bits;
      uint32_t v_table_entry;
      uint32_t v_table_entry_n_bits;
      uint32_t v_lmask;
      uint32_t v_dmask;
      uint32_t v_redir_top;
      uint32_t v_redir_mask;
      uint32_t v_length;
      uint32_t v_distance;
      uint32_t v_n_copied;
      uint32_t v_hlen;
      uint32_t v_hdist;
    } c_decode_huffman_slow[1];
  } private_impl;
} wuffs_deflate__decoder;

// ---------------- Public Initializer Prototypes

// wuffs_deflate__decoder__initialize is an initializer function.
//
// It should be called before any other wuffs_deflate__decoder__* function.
//
// Pass WUFFS_VERSION and 0 for wuffs_version and for_internal_use_only.
void wuffs_deflate__decoder__initialize(wuffs_deflate__decoder* self,
                                        uint32_t wuffs_version,
                                        uint32_t for_internal_use_only);

// ---------------- Public Function Prototypes

wuffs_deflate__status wuffs_deflate__decoder__decode(
    wuffs_deflate__decoder* self,
    wuffs_base__writer1 a_dst,
    wuffs_base__reader1 a_src);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // WUFFS_DEFLATE_H

// ---------------- END   USE "std/deflate"

#ifdef __cplusplus
extern "C" {
#endif

// ---------------- Status Codes

// Status codes are int32_t values:
//  - the sign bit indicates a non-recoverable status code: an error
//  - bits 10-30 hold the packageid: a namespace
//  - bits 8-9 are reserved
//  - bits 0-7 are a package-namespaced numeric code
//
// Do not manipulate these bits directly. Use the API functions such as
// wuffs_zlib__status__is_error instead.
typedef int32_t wuffs_zlib__status;

#define wuffs_zlib__packageid 2064249  // 0x001F7F79

#define WUFFS_ZLIB__STATUS_OK 0                                   // 0x00000000
#define WUFFS_ZLIB__ERROR_BAD_WUFFS_VERSION -2147483647           // 0x80000001
#define WUFFS_ZLIB__ERROR_BAD_RECEIVER -2147483646                // 0x80000002
#define WUFFS_ZLIB__ERROR_BAD_ARGUMENT -2147483645                // 0x80000003
#define WUFFS_ZLIB__ERROR_INITIALIZER_NOT_CALLED -2147483644      // 0x80000004
#define WUFFS_ZLIB__ERROR_INVALID_I_O_OPERATION -2147483643       // 0x80000005
#define WUFFS_ZLIB__ERROR_CLOSED_FOR_WRITES -2147483642           // 0x80000006
#define WUFFS_ZLIB__ERROR_UNEXPECTED_EOF -2147483641              // 0x80000007
#define WUFFS_ZLIB__SUSPENSION_SHORT_READ 8                       // 0x00000008
#define WUFFS_ZLIB__SUSPENSION_SHORT_WRITE 9                      // 0x00000009
#define WUFFS_ZLIB__ERROR_CANNOT_RETURN_A_SUSPENSION -2147483638  // 0x8000000A
#define WUFFS_ZLIB__ERROR_INVALID_CALL_SEQUENCE -2147483637       // 0x8000000B

#define WUFFS_ZLIB__ERROR_CHECKSUM_MISMATCH -33692672  // 0xFDFDE400
#define WUFFS_ZLIB__ERROR_INVALID_ZLIB_COMPRESSION_METHOD \
  -33692671  // 0xFDFDE401
#define WUFFS_ZLIB__ERROR_INVALID_ZLIB_COMPRESSION_WINDOW_SIZE \
  -33692670                                                    // 0xFDFDE402
#define WUFFS_ZLIB__ERROR_INVALID_ZLIB_PARITY_CHECK -33692669  // 0xFDFDE403
#define WUFFS_ZLIB__ERROR_TODO_UNSUPPORTED_ZLIB_PRESET_DICTIONARY \
  -33692668  // 0xFDFDE404

bool wuffs_zlib__status__is_error(wuffs_zlib__status s);

const char* wuffs_zlib__status__string(wuffs_zlib__status s);

// ---------------- Public Consts

// ---------------- Structs

typedef struct {
  // Do not access the private_impl's fields directly. There is no API/ABI
  // compatibility or safety guarantee if you do so. Instead, use the
  // wuffs_zlib__adler32__etc functions.
  //
  // In C++, these fields would be "private", but C does not support that.
  //
  // It is a struct, not a struct*, so that it can be stack allocated.
  struct {
    wuffs_zlib__status status;
    uint32_t magic;

    uint32_t f_state;

  } private_impl;
} wuffs_zlib__adler32;

typedef struct {
  // Do not access the private_impl's fields directly. There is no API/ABI
  // compatibility or safety guarantee if you do so. Instead, use the
  // wuffs_zlib__decoder__etc functions.
  //
  // In C++, these fields would be "private", but C does not support that.
  //
  // It is a struct, not a struct*, so that it can be stack allocated.
  struct {
    wuffs_zlib__status status;
    uint32_t magic;

    wuffs_deflate__decoder f_flate;
    wuffs_zlib__adler32 f_adler;

    struct {
      uint32_t coro_susp_point;
      uint16_t v_x;
      uint32_t v_checksum;
      wuffs_zlib__status v_z;
      uint64_t scratch;
    } c_decode[1];
  } private_impl;
} wuffs_zlib__decoder;

// ---------------- Public Initializer Prototypes

// wuffs_zlib__decoder__initialize is an initializer function.
//
// It should be called before any other wuffs_zlib__decoder__* function.
//
// Pass WUFFS_VERSION and 0 for wuffs_version and for_internal_use_only.
void wuffs_zlib__decoder__initialize(wuffs_zlib__decoder* self,
                                     uint32_t wuffs_version,
                                     uint32_t for_internal_use_only);

// ---------------- Public Function Prototypes

wuffs_zlib__status wuffs_zlib__decoder__decode(wuffs_zlib__decoder* self,
                                               wuffs_base__writer1 a_dst,
                                               wuffs_base__reader1 a_src);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // WUFFS_ZLIB_H
