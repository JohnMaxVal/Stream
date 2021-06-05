#include "serialized_buf.h"
#include <stdlib.h>

int main(int argc, char **argv) {
  ser_buf_t *ser_buff = NULL;
  init_serialized_buf(&ser_buff);
  ser_buff = NULL;
  init_serialized_buffer_of_defined_size(&ser_buff, 1024);

  return 0;
}
