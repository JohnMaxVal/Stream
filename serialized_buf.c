#include "serialized_buf.h"
#include <stdlib.h>
#include <memory.h>

/* static uint32 */
/* get_ser_buf_available_space(ser_buf_t* b) { */
/*   return b->sz - b->pos; */
/* } */

static int
is_enough_space(ser_buf_t* b, int size) {
  int sign = size >= 0 ? 1 : -1;
  return (b->sz - b->pos) > (sign * size);
}

void
init_serialized_buf(ser_buf_t** buf) {
  *buf = (ser_buf_t *)malloc(sizeof(ser_buf_t));
  (*buf)->b = (char *)malloc(SERIALIZE_BUFFER_DEFAULT_SIZE * sizeof(char));
  (*buf)->sz = SERIALIZE_BUFFER_DEFAULT_SIZE;
  (*buf)->pos = 0;
  (*buf)->checkpoint = 0;
}

void
init_serialized_buffer_of_defined_size(ser_buf_t** buf, uint32 size) {
  *buf = (ser_buf_t *)malloc(sizeof(ser_buf_t));
  (*buf)->b = (char *)malloc(size * sizeof(char));
  (*buf)->sz = size;
  (*buf)->pos = 0;
  (*buf)->checkpoint = 0;  
}

void
serialize_data(ser_buf_t* buf, char *data, uint32 size) {
  if(!data || !size) return;

  if(is_enough_space(buf, size)) {
    memcpy((char*)buf->b + buf->pos, data, size);
    buf->pos += size;
    return;
  }

  while(!is_enough_space(buf, size)) // if not enough memory then double space
    buf->sz = buf->sz * 2;

  buf->b = (char*)realloc(buf->b, buf->sz);
  memcpy((char*)buf->b + buf->pos, data, size);
  buf->pos += size;
}

void
deserialize_data(char *dest, ser_buf_t* buf, uint32 sz) {
  if(buf == NULL)
    return;
  else if(dest == NULL)
    return;
  else if(sz == 0 || (buf->sz - buf->pos) < sz)
    return;
  memcpy(dest, (char *)buf->b + buf->pos, sz);
  buf->pos += sz;
}

uint32
is_buf_empty(ser_buf_t* b) {
  return b->sz == 0 ? 1 : 0;
}

/*
  For example, the below call must copy the string "csepracticals.com" in a serialize buffer at byte location 32th from the beginning of serialize buffer. The the API is not supposed to update b->next or b->size variables of the serialize buffer.

  copy_in_serialized_buffer_by_offset(ser_bff, 64, "csepracticals.com", 32);
 */

void
cpy_to_buf_by_offset(ser_buf_t* b,
		     uint32 size,
		     char *value,
		     uint32 offset) {
  if(b->sz < offset || !is_enough_space(b, size))
    return;

  memcpy(b->b + offset, value, size);
}

void
mark_checkpoint_ser_buf(ser_buf_t* b) {
  if(b == NULL) return;
  b->checkpoint = b->pos;
}

uint32
get_ser_buf_checkpoint_by_offset(ser_buf_t* b) {
  return b->checkpoint;
}

void
ser_buf_skip(ser_buf_t* b, int skip_sz) {
  if(b == NULL) return;
  
  if(is_enough_space(b, skip_sz)) {
    b->pos += skip_sz;
    return;
  }

  while(!is_enough_space(b, skip_sz)) {
    b->sz = b->sz * 2;
  }

  b->b = (char*)realloc(b->b, b->sz);
  b->pos += skip_sz;
}

void
free_ser_buf(ser_buf_t* b) {
  if(b == NULL)
    return;

  if(b->b != NULL)
    free(b->b);
  b->sz = 0;
  b->pos = 0;
  b->checkpoint = 0;
  free(b);
}
