#ifndef UTILS_H
#define UTILS_H

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int ft_isprint(int c);

char    *ft_strdup(const char *s1);

char    *ft_strjoin(char *stash, char *buf);

char    **ft_split(const char *s, char c);

size_t  ft_strlen(const char *str);

void	*ft_calloc(size_t count, size_t size);

void	*ft_memmove(void *dst, const void *src, size_t len);

void	*ft_memset(void *b, int c, size_t len);

void	ft_bzero(void *s, size_t n);

void	*ft_memcpy(void *dst, const void *src, size_t n);

int	ft_iswp(int c);

int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
