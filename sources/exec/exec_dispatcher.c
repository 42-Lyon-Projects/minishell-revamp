/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:38:24 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/08 09:48:25 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/ft_printf.h"

#include <stdlib.h>

void	ft_dispatch_commands(t_minishell *shell)
{
	char	*command;

	ft_concat_tokens(shell, _false);
	while (shell->commands.latest_command != NULL)
	{
		if (!ft_quote_is_closed(shell->commands.latest_command))
			ft_concat_quoted_pipes(shell, 0);
		ft_post_command(shell);
		command = ft_strtrim(shell->commands.latest_command, " ");
		ft_printf("COMMAND: |%s|\n", command);

		//TODO: Les doubles chevrons dans les String.						// CA A L'AIR D'ETRE BON
		//TODO: LES ESPACE APRES LES PIPE									// CA A L'AIR D'ETRE BON
		//TODO: LES PIPES SI ELLE EST EN DEBUT OU FIN DE STRING				// CA A L'AIR D'ETRE BON
		//TODO: ENVOYER UNE ERREUR EN CAS DE PIPE COLLES.					// CA A L'AIR D'ETRE BON
		//TODO: GERER LES | |												// CA A L'AIR D'ETRE BON
		//TODO: VIRER LE BUG DES PIPES EN FIN DE COMMANDE				// CA A L'AIR D'ETRE BON

		//TODO: CHERCHER SI Y'A DES VARIABLES D'ENV DANS LA STRING
		//TODO: LES REPLACE SI Y'EN A DES TROUVEES
		//TODO: Dispatch Envoyer Builtin dans Buildin et Autre dans Autre.

		if (ft_str_equals(command, "exit"))
		{
			free(command);
			shell->is_running = _false;
			return;
		}

		free(command);
		shell->commands.latest_command = NULL;
		ft_concat_tokens(shell, _false);
	}
}