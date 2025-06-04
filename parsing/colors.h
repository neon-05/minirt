/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:41:26 by malapoug          #+#    #+#             */
/*   Updated: 2025/01/06 17:54:07 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

//====================(COLORS)==============================//

// Réinitialisation
# define RESET       "\033[0m"

// Couleurs de texte
# define BLACK       "\033[30m"
# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

// Couleurs de fond
# define BG_BLACK    "\033[40m"
# define BG_RED      "\033[41m"
# define BG_GREEN    "\033[42m"
# define BG_YELLOW   "\033[43m"
# define BG_BLUE     "\033[44m"
# define BG_MAGENTA  "\033[45m"
# define BG_CYAN     "\033[46m"
# define BG_WHITE    "\033[47m"

// Styles
# define BOLD        "\033[1m"
# define UNDERLINE   "\033[4m"
# define BLINK       "\033[5m"

#endif
