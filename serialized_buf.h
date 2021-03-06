#ifndef __SERIALIZED_BUFF__
#define __SERIALIZED_BUFF__

typedef unsigned int uint32;

typedef struct ser_buf_ {
  
  #define SERIALIZE_BUFFER_DEFAULT_SIZE 512
  
  char *b;
  uint32 sz;
  uint32 pos;
  uint32 checkpoint;
} ser_buf_t;

void
init_serialized_buf(ser_buf_t** buf);

void
init_serialized_buffer_of_defined_size(ser_buf_t** b, uint32 size);

void
serialize_data(ser_buf_t* buf, char *data, uint32 nbytes);

void
deserialize_data(char *dest, ser_buf_t* buf, uint32 sz);

uint32
is_buf_empty(ser_buf_t* b);

void
cpy_to_buf_by_offset(ser_buf_t* b, uint32 size, char *value, uint32 offset);

void
mark_checkpoint_ser_buf(ser_buf_t* b);

uint32
get_ser_buf_checkpoint_by_offset(ser_buf_t* b);

/*
 could be either positive or negative number:
   +skip_sz means skip forward
   -skip_sz means skip backward
*/
void
ser_buf_skip(ser_buf_t* b, int skip_sz);

void
free_ser_buf(ser_buf_t* b);

#endif
