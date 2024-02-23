/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <acan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:47:35 by acan              #+#    #+#             */
/*   Updated: 2024/01/31 14:40:39 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "libft/libft.h"
# include "metachars.h"
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <termios.h>
# include "readline/readline.h"
# include "readline/history.h"

// STRUCTS
typedef struct s_env
{
	char				*name;
	char				*var;
	struct s_env		*next;
}						t_env;

typedef struct s_export
{
	char				*content;
	struct s_export		*next;
}						t_export;

typedef struct s_lexer
{
	char				*command;
	int					type;
	struct s_lexer		*next;
}						t_lexer;

typedef struct s_expander
{
	char				*command;
	int					type;
	int					is_first;
	char				*prev_cmd;
	struct s_expander	*next;
}						t_expander;

typedef struct s_files
{
	char				*filename;
	int					re_type;
	int					fd;
	struct s_files		*next;
}						t_files;

typedef struct s_parser
{
	char				**command;
	char				*heredoc;
	int					infile;
	int					outfile;
	pid_t				pid;
	t_files				*file;
	struct s_parser		*next;
}						t_parser;

typedef struct s_minishell
{
	t_env				*m_env;
	t_lexer				*m_lexer;
	t_expander			*m_expander;
	t_parser			*m_parser;
	t_export			*m_export;
	int					errorcode;
	int					cmd_count;
	int					**fd;
	char				**path;
	char				*line;
}						t_minishell;

int		g_signal;

// SIGNAL_FUNC

void					signal_init(void);
void					interrupt_here_document(int signal);

// UTILITY_FUNCS
void					free_double(char **str);
char					*gnl(int fd);
int						ft_strcmp(char *s1, char *s2);
char					**malloc_double(char **params, char *command);
char					*my_strjoin2(char *s1, char *s2);
void					echo_cmd(t_minishell *data, t_parser *prs);
char					*char_to_str(char *s, char c);
char					*my_strjoin(char *s1, char *s2);
int						isdir(const char *filename);
size_t					last_slash(char *filename);

// ENV_FUNCTIONS
void					env_delone(t_env *env, void (*del)(void *));
size_t					env_equals(char *env_node);
void					env_clear(t_env **env, void (*del)(void *));
void					env_addback(t_env **env, t_env *new);
t_env					*env_new(char *name, char *var);
t_env					*env_get(char **env, t_minishell *data);
void					path_get(t_env *m_env, t_minishell *data);

// EXPORT_FUNCTIONS
void					sort_export(t_export *ex);
void					combine_with_quotes(char *cmd, t_minishell *data);
void					export_set(char *env_node, t_minishell *data);
void					export_delone(t_export *export, void (*del)(void *));
void					export_clear(t_export **export, void (*del)(void *));
void					export_addback(t_export **export, t_export *new);
t_export				*export_new(char *content);

// LEXER_FUNCS
void					lexer_delone(t_lexer *lexer, void (*del)(void *));
void					lexer_clear(t_lexer **lexer, void (*del)(void *));
void					lexer_addback(t_lexer **lexer, t_lexer *new);
t_lexer					*lexer_new(char *command, int type);
void					lexer(t_minishell *data);
int						metachar_check(char c);
int						metastr_check(char *str);
t_list					*meta_seperate(t_list *lst);
void					add_lexer(t_list *list, t_minishell *data);
int						quote_check(char *str);
int						syntax_check(t_minishell *data);

// EXPANDER FUNCS

void					expander_delone(t_expander *expander,
							void (*del)(void *));
void					expander_clear(t_expander **expander,
							void (*del)(void *));
t_expander				*expander_new(t_lexer *lexer, char *command, int env);
void					expander_addback(t_expander **expander,
							t_expander *new);
void					expander(t_minishell *data);
int						should_be_done_but_null(char c);
int						printable_special_character(char c);
int						should_be_done_but_error(char c);
int						special_chars(char c);
int						all_after_dollar(char c);
void					remove_quotes(t_minishell *data, char quote);

// PARSER FUNCS
void					files_clear(t_files **files, void (*del)(void *));
void					parser_delone(t_parser *parser, void (*del)(void *));
void					parser_clear(t_parser **parser, void (*del)(void *));
void					parser_addback(t_parser **parser, t_parser *new);
t_files					*files_new(char *filename, int re_type, int fd);
void					files_addback(t_files **files, t_files *new);
t_parser				*parser_new(void);
void					heredoc_handle(t_minishell *data);
void					parser(t_minishell *data);
int						outfile_fd(t_expander *ex, t_parser *prs,
							t_minishell *data);
int						file_controls(t_expander **ex, t_parser *prs,
							t_minishell *data, int *fd);

// EXECUTER_FUNCS
int						is_builtin(char **command);
void					builtin_funcs(char **command, t_minishell *data,
							t_parser *prs, int builtincode);
void					executer(t_minishell *data, int loop);
void					open_pipes(t_minishell *data);
void					dup_stdio(t_minishell *data, t_parser *parser, int i);
void					wait_all(t_minishell *data, int builtin);
void					fd_closer(t_minishell *data);
void					free_double_int(int **fd);

// EXPORT_FUNCS
void					add_env_export(char *cmd, t_minishell *data);
void					del_same_node_exp(char *cmd, t_export **exp);
void					del_same_node_env(char *cmd, t_env *env);
void					env_print(t_minishell *data, t_parser *prs);
void					export_env(t_minishell *data, t_parser *prs);
void					unset_env_export(char **cmd, t_minishell *data,
							t_export *exp, t_env *env);

// CD_FUNCS

void					cd_cmd(t_minishell *data, t_parser *prs, char **cmd);
void					pwd_cmd(t_minishell *data, t_parser *prs);
void					oldpwd_set(t_minishell *data);
void					go_oldpwd(t_minishell *data);

// ERR_FUNC

void					executer_error(char *cmd, char *msg);
void					file_errors(char *prev_cmd, char *error, int *fd,
							t_minishell *data);
void					expander_errors(char *error);
void					cd_errors(t_minishell *data, int errorcode, char *file);

#endif