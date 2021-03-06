#include "serialized_buf.h"
#include <stdlib.h>

int main(int argc, char **argv) {
  ser_buf_t *ser_buff = NULL;
  init_serialized_buf(&ser_buff);
  ser_buff = NULL;
  init_serialized_buffer_of_defined_size(&ser_buff, 1024);

  //cpy_to_buf_by_offset(ser_buff, 64, "csepracticals.com", 32);

  serialize_data(ser_buff, "Eugene", 7);
  ser_buf_skip(ser_buff, -5);
  ser_buf_skip(ser_buff, 10);

  free_ser_buf(ser_buff);
  
  return 0;
}
