/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:10:15 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/04 18:35:43 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// MIRAR QUE SE LE PASSA CON SEGURIDAD

#include <minishell.h>

char	*obtain_var(char *str)
{
	char	*val;
	int		i;

	i = 0;
	str++;
	val = malloc(ft_strlen_chr(str, '$') + 1);
	if (!val)
		return (NULL);
	while (ft_isdigit(str[i]) == 1 || ft_isalpha(str[i]) == 1)
	{
		val[i] = str[i];
		i++;
	}
	val[i] = '\0';
	return (val);
}
// CON ESTO VAR LO TENGO PERFECTO SI USO EL STRNCMP JUNTO AL STRLEN_CHR LO TENGO TODO EN TEORIA FUNCIONANDO
char	*expand(char *str, char **envp)
{
	int	i;
	char	*var;

	i = 0;
	(void)envp;
	var = obtain_var(str);
	ft_printf("%s\n", var);
	return (NULL);
}

void	expansor(t_lex **def, char **envp)
{
	t_lex	*lexer;
	char	str[200] = "";
	int		i;
	int		j;
	int		quote;

	j = 0;
	lexer = *def;
	quote = 0;
	while (lexer)
	{
		i = 0;
		while (lexer->token == NONE && lexer->word[i] != '\0')
		{
			if (lexer->word[i] == C_ONE_QUOTE)
				quote = 1;
			else if (lexer->word[i] == C_ONE_QUOTE && quote == 1)
				quote = 0;
			if (lexer->word[i] == '$' && quote == 0)
			{
				expand(&lexer->word[i], envp);
				j = ft_strlen(str);
			}
			else
				str[j++] = lexer->word[i];
			i++;
		}
		lexer = lexer->next;
	}
}

