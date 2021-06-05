#include "serialized_buf.h"
#include <stdlib.h>
#include <memory.h>

void
init_serialized_buf(ser_buf_t** buf) {
  *buf = (ser_buf_t *)malloc(sizeof(ser_buf_t));
  (*buf)->b = (char *)calloc(SERIALIZE_BUFFER_DEFAULT_SIZE, sizeof(char));
  (*buf)->sz = 0;
  (*buf)->pos = 0;
  (*buf)->checkpoint = 0;
}

void
init_serialized_buffer_of_defined_size(ser_buf_t** buf, uint32 size) {
  *buf = (ser_buf_t *)malloc(sizeof(ser_buf_t));
  (*buf)->b = (char *)calloc(size, sizeof(char));
  (*buf)->sz = 0;
  (*buf)->pos = 0;
  (*buf)->checkpoint = 0;  
}

void
serialize_data(ser_buf_t* buf, char *data, uint32 size) {
  if(!data || !size) return;

  uint32 free_space = buf->sz - buf->pos;
  char isResize = 0;

  while(free_space < size) { // if not enough memory then double space
    buf->sz = buf->sz * 2;
    free_space = buf->sz - buf->pos;
    isResize = 0;
  }

  if(!isResize) {
    memcpy((char*)buf->b + buf->pos, data, size);
    buf->pos += size;
    return;
  }

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
is_buf_empty(ser_buff_t* b) {
  return b->sz == 0 ?  : 0;
}
