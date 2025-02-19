#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
# define MAX_S_BUFFER 200012
# define MAX_R_BUFFER 200013
# define MAX_CLIENTS 2048

char s_buffer[MAX_S_BUFFER], r_buffer[MAX_R_BUFFER];
fd_set r_set, w_set, c_set;
int max_fd = 0, gid = 0;

typedef struct s_client{
    int id;
    char msg[200000];
} t_client;

t_client clients[MAX_CLIENTS];

typedef struct s_server{
    struct sockaddr_in addr;
    socklen_t len;
    int sock;
    void (*init)(struct s_server *this, int port);
    void (*bind)(struct s_server *this);
    void (*listen)(struct s_server *this);
    int (*accept)(struct s_server *this);
    void (*broadcast)(int excluded_fd);
    void (*run)(struct s_server *this);
    void (*logger)(short type, int id, char *msg);
    void (*process_message)(struct s_server *this, int fd, int msg_len);
} t_server;

void    error(char *msg)
{
    if (msg)
        write(2, msg, strlen(msg));
    else
        write(2, "Fatal Error\n", 12);
    exit(1);
}

void    server_init(t_server *this, int port)
{
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sock == -1)
        error(NULL);
    this->len = sizeof(struct sockaddr_in);
    bzero(&clients, sizeof(clients));
    bzero(&this->addr, sizeof(this->addr));
    FD_ZERO(&c_set);
    FD_SET(this->sock, &c_set);
    max_fd = this->sock;
    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = htonl(2130706433);
    this->addr.sin_port = htons(port);
}

void    server_bind(t_server *this)
{
    if ((bind(this->sock, (const struct sockaddr *)&this->addr, sizeof(this->addr))) == -1)
        error(NULL);
}

void    server_listen(t_server *this)
{
    if (listen(this->sock, 100) == -1)
        error(NULL);
}

int     server_accept(t_server *this)
{
    return (accept(this->sock, (struct sockaddr *)&this->addr, &this->len));
}

void    broadcast_msg(int excluded_fd)
{

    for (int fd = 0; fd <= max_fd; fd++)
    {
        if (FD_ISSET(fd, &w_set) && fd != excluded_fd)
            if (send(fd, s_buffer, strlen(s_buffer), 0) == -1)
                error(NULL);
    }
}

void    load_log(short type, int id, char *msg)
{
    if (type == 0)
    {
        sprintf(s_buffer, "server: client %d has arrived\n", id);
        printf("[INFO] client with id: %d has been connected\n", id);
    }
    else if (type == 1)
    {
        sprintf(s_buffer, "server: client %d has left\n", id);
        printf("[INFO] client with id: %d has been disconnected\n", id);
        bzero(msg, strlen(msg));
    }
    else
    {
        sprintf(s_buffer, "client %d: %s\n", id, msg);
        printf("[INFO] message: %s sent by client woth id: %d\n", msg, id);
        bzero(msg, strlen(msg));

    }
}

void process_message(t_server *this, int fd, int msg_len) {
    for (int i = 0, j = strlen(clients[fd].msg); i < msg_len; i++, j++) {
        clients[fd].msg[j] = r_buffer[i];
        if (clients[fd].msg[j] == '\n') {
            clients[fd].msg[j] = 0;
            this->logger(2, clients[fd].id, clients[fd].msg);
            this->broadcast(fd);
            j = -1;
        }
    }
}

void    server_run(t_server *this)
{
    while (1337)
    {
        r_set = w_set = c_set;

        if (select(max_fd + 1, &r_set, &w_set, 0, 0) == -1) continue ;

        for (int fd = 0; fd <= max_fd; fd++)
        {
            if (FD_ISSET(fd, &r_set))
            {
                if (fd == this->sock)
                {
                    int c_sock = this->accept(this);
                    if (c_sock == -1) continue;
                    if (c_sock > max_fd) max_fd = c_sock;
                    FD_SET(c_sock, &c_set);
                    clients[c_sock].id = gid++;
                    this->logger(0, clients[c_sock].id, NULL);
                    this->broadcast(c_sock);
                }
                else
                {
                    int msg_len = recv(fd, r_buffer, sizeof(r_buffer), 0);
                    if (msg_len <= 0)
                    {
                        this->logger(1, clients[fd].id, clients[fd].msg);
                        this->broadcast(fd);
                        FD_CLR(fd, &c_set);
                        close(fd);
                    }
                    else
                        this->process_message(this, fd, msg_len);
                    
                }
            }
        }
    }
}


t_server server = {
    .init = server_init,
    .bind = server_bind,
    .listen = server_listen,
    .accept = server_accept,
    .broadcast = broadcast_msg,
    .run = server_run,
    .logger = load_log,
    .process_message = process_message
};



int main(int ac, char **av)
{
    if (ac != 2)
        error("Wrong number of arguments\n");

    server.init(&server, atoi(av[1]));
    server.bind(&server);
    server.listen(&server);
    server.run(&server);
    return (0);
}