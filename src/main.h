/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:39:30 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2024/03/22 01:27:32 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>

# include "glad/gl.h"

# include "mb_core_type.h"
# include "mb_colorizer_basic_types.h"

# define DEFAULT_WINDOW_WIDTH 800
# define DEFAULT_WINDOW_HEIGHT 600

typedef struct s_main_context
{
	int						width;
	int						height;
	t_mb					*mb;
	t_mb_colorizer_basic	colorizer;
	GLuint					program;
	GLuint					vao;
	GLuint					vbo;
}	t_main_context;

t_err	init_context(t_main_context *out);
void	deinit_context(t_main_context context);

t_err	render(t_main_context *context);

#endif
