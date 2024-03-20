/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:23:22 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2024/03/21 01:39:33 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "mb_core.h"
#include "mb_real_float.h"

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
	window = glfwCreateWindow(800, 600, "Mandelbrot Set Viewer", NULL, NULL);
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

	if (init_context(&context))
		exit(EXIT_FAILURE);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	deinit_context(context);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

static void	framebuffer_size_cb(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

static void	process_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
