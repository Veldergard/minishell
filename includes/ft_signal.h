/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:52:22 by itressa           #+#    #+#             */
/*   Updated: 2021/01/02 20:17:17 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

#define FT_SIG_DFL         (void (*)(int))0

#include <signal.h>

void	apply_signals_common(void);
void	apply_signals_parent(void);
void	remove_signals_parent(void);

#endif
