/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:38:29 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/07 11:47:32 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	fill_command(t_lex **head, t_io **redirect, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (*head && (*head)->token != PIPE)
	{
		if ((*head)->token != NONE)
		{
			if (add_redirection(redirect, head) == 1)
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
	cmd->redirect = *redirect;
	return (0);
}

int	create_simple_command(t_lex **head, t_cmd *cmd)
{
	int		n_args;
	t_io	*redirect;

	redirect = NULL;
	n_args = count_arguments(*head);
	cmd->args = malloc(sizeof(char *) * (n_args + 1));
	if (!cmd->args)
		return (1);
	cmd->args[n_args] = NULL;
	if (fill_command(head, &redirect, cmd) == 1)
		return (1);
	if (*head && (*head)->token == PIPE)
		*head = (*head)->next;
	return (0);
}

int	parser(t_cmd **commands, t_lex **lexer)
{
	t_cmd	*new;
	t_lex	*head;

	if (!lexer)
		return (0);
	if (check_syntax_error(*lexer) == SYNTAX_ERR)
		return (lexer_lstclear(lexer), SYNTAX_ERR);
	head = *lexer;
	while (head)
	{
		new = parser_lstnew();
		if (!new)
			return (1);
		parser_lstadd_back(commands, new);
		if (create_simple_command(&head, new) == 1)
			return (1);
	}
	return (0);
}

void	print_commands(t_cmd *commands)
{
	int		i;
	t_io	*temp;

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
		temp = commands->redirect;
		while (temp)
		{
			if (temp->type == IN)
				printf("(IN)");
			else if (temp->type == OUT_TRUNC)
				printf("(OUT_TRUNC)");
			else if (temp->type == OUT_APPEND)
				printf("(OUT_APPEND)");
			else if (temp->type == HERE_DOC)
				printf("(HERE_DOC)");
			printf("->%s, ", temp->file);
			temp = temp->next;
		}
		if (temp == NULL)
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
