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
init_serialized_buffer_of_defined_size(ser_buff_t** b, int size);

void
serialize_data(ser_buf_t* buf, char *data, uint32 nbytes);

void
deserialize_data(char *dest, ser_buf_t* buf, uint32 sz);

#endif
