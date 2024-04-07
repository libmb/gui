/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:23:22 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2024/04/08 00:13:40 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "mb_gui_fps.h"

#include "main.h"

static void	framebuffer_size_cb(GLFWwindow *window, int width, int height);
static void	process_input(GLFWwindow *window);

static void	*init(void)
{
	GLFWwindow	*window;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
			"Mandelbrot Set Viewer", NULL, NULL);
	if (window == NULL)
	{
		puts("Failed to create GLFW window");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress))
	{
		puts("Failed to initialize GLAD");
		exit(EXIT_FAILURE);
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_cb);
	return (window);
}

int	main(void)
{
	GLFWwindow *const	window = init();
	t_main_context		context;
	t_mb_gui_fps		fps;

	if (mb_gui_fps_init(&fps, 16667)
		|| init_context(&context))
		exit(EXIT_FAILURE);
	glfwSetWindowUserPointer(window, &context);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		if (mb_gui_fps_block(&fps)
			|| render(&context)
			|| mb_gui_fps_mark_as_rendered(&fps))
			break ;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	deinit_context(context);
	mb_gui_fps_finalize(fps);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

static void	framebuffer_size_cb(GLFWwindow *window, int width, int height)
{
	t_main_context *const	context = glfwGetWindowUserPointer(window);

	context->width = width;
	context->height = height;
	glViewport(0, 0, width, height);
}

static void	process_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
