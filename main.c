#include "serialized_buf.h"
#include <stdlib.h>

int main(int argc, char **argv) {
  ser_buf_t *ser_buff = NULL;
  init_serialized_buf(&ser_buff);
  ser_buff = NULL;
  init_serialized_buffer_of_defined_size(&ser_buff, 1024);

  cpy_to_buf_by_offset(ser_buff, 64, "csepracticals.com", 32);

  return 0;
}
