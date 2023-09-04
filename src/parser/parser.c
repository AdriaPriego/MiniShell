/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:38:29 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/04 23:18:17 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	> out							"Redirects {empty} to a file called out"
	< out							"It redirects standard input to a file called 'out' if it exists"
	ls |							"Opens std input" // (((("Syntax error"))))
	cat | cat						"Standard input open to write something"
	ls -la <						"Syntax error"
	|								"Syntax error"
	ls | sleep 3 | < dssd			"Executes 3 pipes and throws error for last process {file doesn't exist}"
	ls | sleep 3 | << eof			"Calls here doc and doesn't execute any process until here doc is finished"
	cat << eof < infile				"Open here_doc but uses infile as input for cat"
	< no_file wc -c < out | ls		"First command not executed because no_file doesn't exist, 'ls' executed"

	When it comes to redirections the last parameter is used, the rest of files will be created independently"
*/

int	count_arguments(t_lex *lexer)
{
	int	i;

	i = 0;
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == NONE)
		{
			if (!lexer->prev)
				i++;
			else if (lexer->prev->token == NONE || lexer->prev->token == PIPE)
				i++;
		}
		lexer = lexer->next;
	}
	return (i);
}

int	add_redirection(t_io **redirect, t_lex **head)
{
	t_lex	*temp;
	t_io	*new;

	temp = *head;
	new = redirect_lstnew();
	if (!new)
		return (1);
	redirect_lstadd_back(redirect, new);
	if (temp->token == LESS)
		new->type = IN;
	else if (temp->token == LESS_LESS)
		new->type = HERE_DOC;
	else if (temp->token == GREAT)
		new->type = OUT_TRUNC;
	else if (temp->token == GREAT_GREAT)
		new->type = OUT_APPEND;
	new->file = ft_strdup(temp->next->word);
	if (!new->file)
		return (1);
	*head = (*head)->next;
	return (0);
}

int	create_simple_command(t_lex **head, t_cmd *cmd)
{
	int		i;
	int		n_args;
	t_io	*redirect;

	redirect = NULL;
	n_args = count_arguments(*head);
	cmd->args = malloc(sizeof(char *) * (n_args + 1));
	if (!cmd->args)
		return (1);
	cmd->args[n_args] = NULL;
	i = 0;
	while (*head && (*head)->token != PIPE)
	{
		if ((*head)->token != NONE)
		{
			if (add_redirection(&redirect, head) == 1)
				return (1);
		}
		else
		{
			cmd->args[i] = ft_strdup((*head)->word);
			if (!cmd->args[i])
			{
				cmd->args = ft_free_matrix((char const **)cmd->args, i);
				return (1);
			}
			i++;
		}
		*head = (*head)->next;
	}
	cmd->redirect = redirect;
	if (*head && (*head)->token == PIPE)
		*head = (*head)->next;
	return (0);
}

void	print_commands(t_cmd *commands)
{
	int	i;
	printf("\n\n\n");
	while (commands)
	{
		printf("Args[][]: ");
		i = 0;
		while (commands->args[i])
		{
			printf("\"%s\",", commands->args[i]);
			i++;
		}
		if (commands->args[i] == NULL)
			printf("NULL");
		printf("\n");
		printf("Redirections: ");
		while (commands->redirect)
		{
			if (commands->redirect->type == IN)
				printf("(IN)");
			else if (commands->redirect->type == OUT_TRUNC)
				printf("(OUT_TRUNC)");
			else if (commands->redirect->type == OUT_APPEND)
				printf("(OUT_APPEND)");
			else if (commands->redirect->type == HERE_DOC)
				printf("(HERE_DOC)");
			printf("->%s, ", commands->redirect->file);
			commands->redirect = commands->redirect->next;
		}
		if (commands->redirect == NULL)
			printf("NULL");
		printf("\n");
		printf("		|\n");
		printf("		|\n");
		printf("		V\n");
		commands = commands->next;
	}
	if (commands == NULL)
			printf("NULL");
	printf("\n");
}

int	parser(t_cmd **commands, t_lex **lexer)
{
	t_cmd	*new;
	t_lex	*head;

	if (!lexer)
		return (0);
	if (check_syntax_error(*lexer) == 1)
		return (lexer_lstclear(lexer), 1);
	head = *lexer;
	while (head)
	{
		new = parser_lstnew();
		if (!new)
			return (lexer_lstclear(lexer), 1);
		parser_lstadd_back(commands, new);
		create_simple_command(&head, new);
		/* create_redirection_structure(&redirect);
				--fill *redirect
				--delete redirect nodes from lexer
		new = create_simple_command();
		if (!new)
			return (1);
		parser_lstadd_back(commands, new);
		while (head->token != ) */
		//head = head->next;
	}
	return (0);
}

		/* if (head->token == GREAT || head->token == GREAT_GREAT
			|| head->token == LESS || head->token == LESS_LESS)
		{

		}
		if (head->token == PIPE)
		{

		} */