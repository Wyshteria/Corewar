/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 23:56:03 by toliver           #+#    #+#             */
/*   Updated: 2019/12/19 03:41:32 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

#define BRIGHT	0x8
#define SMALL_SCREEN "screen is too small"

enum			e_color_type
{
	PLAYER1 = 1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	STANDARD_COLOR = 10,
};

enum			e_mode
{
	ENDED,
	RUNNING,
	TOO_SMALL,
};

#endif
