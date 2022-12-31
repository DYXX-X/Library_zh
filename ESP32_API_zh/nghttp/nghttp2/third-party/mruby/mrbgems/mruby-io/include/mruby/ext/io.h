/*
** io。h-IO类
*/

#ifndef MRUBY_IO_H
#define MRUBY_IO_H

#if defined(__cplusplus)
extern "C" {
#endif

struct mrb_io {
  int fd;   /* 文件描述符，或-1*/
  int fd2;  /* 如果与fd或-1不同，则要写入的文件描述符*/
  int pid;  /* 儿童pid（用于管道）*/
  unsigned int readable:1,
               writable:1,
               sync:1,
               is_socket:1;
};

#define FMODE_READABLE             0x00000001
#define FMODE_WRITABLE             0x00000002
#define FMODE_READWRITE            (FMODE_READABLE|FMODE_WRITABLE)
#define FMODE_BINMODE              0x00000004
#define FMODE_APPEND               0x00000040
#define FMODE_CREATE               0x00000080
#define FMODE_TRUNC                0x00000800

#define E_IO_ERROR                 (mrb_class_get(mrb, "IOError"))
#define E_EOF_ERROR                (mrb_class_get(mrb, "EOFError"))

mrb_value mrb_io_fileno(mrb_state *mrb, mrb_value io);

#if defined(__cplusplus)
} /* 外部“C”{*/
#endif
#endif /* MRUBY_IO_H */

