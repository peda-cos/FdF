/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_fmt
{
	char	spec;
	int		width;
	int		prec;
	int		flag_minus;
	int		flag_zero;
	int		flag_hash;
	int		flag_plus;
	int		flag_space;
}				t_fmt;

/* Entry */
int			ft_printf(const char *fmt_str, ...);

/* Parser */
void		init_fmt(t_fmt *fmt);
const char	*parse_format(t_fmt *fmt, const char *ptr);

/* Dispatcher */
int			dispatch(t_fmt *fmt, va_list *ap);

/* Converters */
int			convert_char(t_fmt *fmt, va_list *ap);
int			convert_str(t_fmt *fmt, va_list *ap);
int			convert_ptr(t_fmt *fmt, va_list *ap);
int			convert_int(t_fmt *fmt, va_list *ap);
int			convert_uint(t_fmt *fmt, va_list *ap);
int			convert_hex(t_fmt *fmt, va_list *ap);
int			convert_percent(t_fmt *fmt);

/* Output helpers */
int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(const char *s, int fd);
int			ft_strlen(const char *s);

/* Number helpers */
int			ft_putnbr_base(unsigned long n, char *base, int blen);
int			ft_nbrlen_base(unsigned long n, int blen);

#endif
