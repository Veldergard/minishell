/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itressa <itressa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:52:22 by itressa           #+#    #+#             */
/*   Updated: 2021/01/09 13:37:37 by itressa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# define FT_SIG_DFL         (void (*)(int))0

# include <signal.h>

void	do_common_signals(int num);
void	do_parent_signals(int num);
void	apply_signals_common(void);
void	apply_signals_parent(void);
void	remove_signals_parent(void);

#endif
