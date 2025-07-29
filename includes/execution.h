/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:13:46 by jweber            #+#    #+#             */
/*   Updated: 2025/07/21 15:10:09 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ast.h"
# include "minishell.h"

enum	e_previous
{
	PREV_NONE,
	PREV_RIGHT,
	PREV_LEFT,
};

int		restore_fds(t_minishell *p_mini);
int		parent_execution(t_vector dir_args, t_minishell *p_mini, int pid);
int		case_forking(t_ast *ast, t_minishell *p_mini, int cmd_type);
int		case_no_forking(t_ast *ast, t_minishell *p_mini);
int		exec_func(t_ast *ast, t_minishell *p_mini);
int		exec_and(t_ast *ast, t_minishell *p_mini);
int		exec_or(t_ast *ast, t_minishell *p_mini);
int		exec_sequence(t_ast *ast, t_minishell *p_mini);
int		exec_pipe(t_ast *ast, t_minishell *p_mini);
int		exec_command(t_ast *ast, t_minishell *p_mini);
int		exec_subshell(t_ast *ast, t_minishell *p_mini);
int		exit_child(t_minishell *p_mini, int ret);
int		swap_fds(t_minishell *p_mini);
int		child_execution(t_ast *ast, t_minishell *p_mini, int cmd_type);
int		wait_children(t_minishell *p_mini);
int		call_builtins(t_minishell *p_mini, t_vector cmd_args);
void	close_on_error(t_minishell *p_mini);
int		close_case_no_pipe(t_minishell *p_mini);
int		close_fd1(t_minishell *p_mini);
int		redir_here_doc(t_minishell *p_mini, t_dirargs redir);
int		redir_append(char *filename);
int		redir_in(char *filename);
int		redir_out(char *filename);
int		get_path(t_minishell *p_mini, t_vector *p_path);
int		get_env_from_list(t_vector *p_new_env, t_list *env);
int		change_fd_redir(t_minishell *p_mini, t_vector redir);
int		change_fd_pipe(t_minishell *p_mini);
int		close_here_doc_fds(t_minishell *p_mini);
int		close_case_prev_left(t_minishell *p_mini, int final_ret);
int		close_case_prev_right(t_minishell *p_mini, int final_ret);
int		make_redirections(t_vector redir, t_minishell *p_mini);
int		init_minishell(t_minishell *p_mini, char **env);
void	init_builtins(t_minishell *p_mini);
int		init_env(t_minishell *p_mini, char **env);
int		init_path(t_minishell *p_mini);
int		find_command(char **p_cmd, t_vector path);
void	free_minishell(t_minishell *p_mini);

#endif
