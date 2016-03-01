#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> /*定义了 uint64_t等*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>  
#include <netdb.h>  
#include <fcntl.h> 
#include <errno.h>

#include "../debug/debug.h"
#include "event.h"

#define MAXEVENTS 64  
#define DEFAULT_EVENT_POOL_SIZE            50000
#define STARTING_EVENT_THREADS                 4
//多少个打印一次
#define INTERVAL_NUM 1000

//这里只是演示 如何在epoll中放私有数据，fd和inx其实在两个handler函数中都有
struct private_data{
    int fd;
    int idx;
};  //不要忘记加分号


struct event_pool *pool = NULL;

  
//函数:  
//功能:创建和绑定一个TCP socket  
//参数:端口  
//返回值:创建的socket  
static int  
create_and_bind (char *port)  
{  
  struct addrinfo hints;  
  struct addrinfo *result, *rp;  
  int s, sfd;  
  
  memset (&hints, 0, sizeof (struct addrinfo));  
  hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */  
  hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */  
  hints.ai_flags = AI_PASSIVE;     /* All interfaces */  
  
  s = getaddrinfo (NULL, port, &hints, &result);  
  if (s != 0)  
    {  
      fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));  
      return -1;  
    }  
  
  for (rp = result; rp != NULL; rp = rp->ai_next)  
    {  
      sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);  
      if (sfd == -1)  
        continue;  
  
      s = bind (sfd, rp->ai_addr, rp->ai_addrlen);  
      if (s == 0)  
        {  
          /* We managed to bind successfully! */  
          break;  
        }  
  
      close (sfd);  
    }  
  
  if (rp == NULL)  
    {  
      fprintf (stderr, "Could not bind\n");  
      return -1;  
    }  
  
  freeaddrinfo (result);  
  
  return sfd;  
}  
  
  
//函数  
//功能:设置socket为非阻塞的  
static int  
make_socket_non_blocking (int sfd)  
{  
  int flags, s;  
  
  //得到文件状态标志  
  flags = fcntl (sfd, F_GETFL, 0);  
  if (flags == -1)  
    {  
      perror ("fcntl");  
      return -1;  
    }  
  
  //设置文件状态标志  
  flags |= O_NONBLOCK;  
  s = fcntl (sfd, F_SETFL, flags);  
  if (s == -1)  
    {  
      perror ("fcntl");  
      return -1;  
    }  
  
  return 0;  
}  
static int
socket_event_handler (int fd, int idx, void *data,
                      int poll_in, int poll_out, int poll_err)
{
    struct private_data *server_data;
    server_data = (struct private_data *)data;
    int done = 0;
    int ret = 0;
    if (poll_in == 0)
        return 0;
    while (1)  
                {  
                  ssize_t count;  
                  char buf[1024*128];  
                  
                  	/*struct iovec iov[2];
                    char	buf1[512] = {0};
                    char	buf2[512] = {0};
                    ssize_t size;
                    iov[0].iov_base=buf1;
                    iov[0].iov_len=10;
                    iov[1].iov_base=buf2;
                    iov[1].iov_len=10;
                  count = readv (server_data->fd, iov, 2);*/ 
                  count = read (server_data->fd, buf, sizeof(buf));  
                  if (count == -1)  
                    {  
                      /* If errno == EAGAIN, that means we have read all 
                         data. So go back to the main loop. 
                         非阻塞io返回EAGAIN表明数据读完了*/  
                      if (errno != EAGAIN)  
                        {  
                          perror ("read");  
                          done = 1;  
                        }  
                      break;  
                    }  
                  else if (count == 0)  
                    {  
                      /* End of file. The remote has closed the 
                         connection. */  
                      done = 1;  
                      break;  
                    }  
  
                  /* Write the buffer to standard output */ 
                  //printf("read fd=%d  size=%zu\n", server_data->fd, count);
                  //printf("read iov1  size=%zu\n", iov[0].iov_len);
                  //printf("read iov2  size=%zu\n", iov[1].iov_len);
                  //break;
                  //ret = write (1, buf, count);iov[0].iov_len  
                  //ret = write (1, buf1, iov[0].iov_len);
                  //printf("\n");
                  //ret = write (1, buf2, iov[1].iov_len);
                  if (ret == -1)  
                    {  
                      perror ("write");  
                      abort ();  
                    }  
         }  
  
              if (done)  
                {  
                  if (server_data->fd % INTERVAL_NUM == 0)
                        printf ("Closed connection on descriptor %d\n",  
                          server_data->fd);  
  
                  /* Closing the descriptor will make epoll remove it 
                     from the set of descriptors which are monitored. */  
                  //close (server_data->fd);
                  event_unregister(pool, fd , idx);
                  close (fd);
                }  
         return ret;
}  

static int
socket_server_event_handler (int fd, int idx, void *data,
                             int poll_in, int poll_out, int poll_err)
{
     struct sockaddr in_addr;
     struct private_data *server_data;
     struct private_data *new_data;
     socklen_t in_len;  
     int new_sock; 
     int ret;
     char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];  
     server_data = (struct private_data *)data;

     
     if (poll_in) {
         while (1)  
         {
            
         new_sock = accept (server_data->fd, &in_addr, &in_len);
         if (new_sock == -1)  
                {  
                  if ((errno == EAGAIN) ||  
                      (errno == EWOULDBLOCK))  
                    {  
                      /* We have processed all incoming 
                         connections. */  
                      break;  
                    }  
                  else  
                    {  
                      perror ("accept");  
                      break;  
                    }  
                }  

                              //将地址转化为主机名或者服务名  
              ret = getnameinfo (&in_addr, in_len,  
                               hbuf, sizeof hbuf,  
                               sbuf, sizeof sbuf,  
                               NI_NUMERICHOST | NI_NUMERICSERV);//flag参数:以数字名返回  
                              //主机地址和服务地址  

            if (ret == 0)  
            {  
              if (new_sock % INTERVAL_NUM == 0)
                   printf("Accepted connection on descriptor %d "  
                     "(host=%s, port=%s)\n", new_sock, hbuf, sbuf);  
            }  

            /* Make the incoming socket non-blocking and add it to the 
             list of fds to monitor. */  
            ret = make_socket_non_blocking (new_sock);  
            if (ret == -1)  
                abort ();
            new_data = (struct private_data *)calloc(1, sizeof(struct private_data));
            new_data->fd = new_sock;
            new_data->idx =
            		event_register (pool,
            				new_sock,
            				socket_event_handler,
            				new_data,
            				1, 0);
            	if (new_data->idx == -1)
            		ret = -1;
                if (ret == -1) 
                    {
                       LOG_PRINT(D_LOG_ERR,
                           "failed to register the socket with event");
                            free(data);
                            close (new_sock);

                    }
         }
     }
    return ret;
}
int32_t main(int32_t argc, char **argv)
{
  int sfd;  
  int ret;
    
  struct private_data *data;
  
  if (argc != 2)  
    {  
      fprintf (stderr, "Usage: %s [port]\n", argv[0]);  
      exit (EXIT_FAILURE);  
    }  
  
  sfd = create_and_bind (argv[1]);  
  if (sfd == -1)  
    abort ();  
  
  ret = make_socket_non_blocking (sfd);  
  if (ret == -1)  
    abort ();  

  // listen之后客户端就可以连接和发送数据了，即使服务器还没有accept,内核已经收到数据，
  // 客户端可以一直发送数据直到服务器的接收缓存和客户端的发送缓存满了，write就会阻塞
  ret = listen (sfd, SOMAXCONN);  
  if (ret == -1)  
    {  
      perror ("listen");  
      abort ();  
    }  

  pool = event_pool_new (DEFAULT_EVENT_POOL_SIZE);
  data = (struct private_data *)calloc(1, sizeof(struct private_data));
  data->fd = sfd;
  data->idx = event_register (pool, sfd, socket_server_event_handler,
                                            data, 1, 0);
  if (data->idx == -1)
     ret = -1;
  if (ret == -1) 
    {
       LOG_PRINT(D_LOG_ERR,
           "failed to register the socket with event");
            free(data);
            close (sfd);
            exit(-1);
    }
  ret = event_dispatch (pool);

  return ret;  

}

#ifdef __cplusplus
}
#endif