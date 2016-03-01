#ifdef __cplusplus
extern "C"{
#endif

#ifndef __ERROR_H__
#define __ERROR_H__

void	 err_dump(const char *, ...);
void	 err_msg(const char *, ...);
void	 err_quit(const char *, ...);
void	 err_ret(const char *, ...);
void	 err_sys(const char *, ...);

#endif

#ifdef __cplusplus
}
#endif

