/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_apply_decisions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 00:57:15 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exp_apply_decision(t_pars *pars)
{
	t_exp_read_modes	arg1;
	t_char_types		arg2;

	pars->prev_exp_decision = pars->new_exp_decision;
	arg1 = pars->prev_exp_decision.exp_read_mode;
	arg2 = ft_char_type(pars->parser_text[0]);
	//printf("arg1 : %s\n", ft_getlabel_exp_read_modes(arg1));
	//printf("arg2 : %s\n", ft_getlabel_char_types(arg2));
	//printf("  arg2 = %c\n", pars->parser_text[0]);
	if (pars->initial_mode)
		ft_initial_mode_1(pars, &arg2);
	pars->new_exp_decision = pars->exp_decision[arg1][arg2];
	if (pars->initial_mode)
		ft_initial_mode_2(pars, &arg2);
	//printf("  arg2 = %c\n", pars->parser_text[0]);
	//printf("action : %s\n", ft_getlabel_exp_actions(pars->new_exp_decision.char_action));
	ft_debug_exp(pars);
	pars->ft_exp[pars->new_exp_decision.buffer_action](pars);
	return (pars->ft_exp[pars->new_exp_decision.char_action](pars));
}

int	ft_initial_mode_1(t_pars *pars, t_char_types *arg2)
{
	(void)pars;
	if (*arg2 != SPL_CHAR && *arg2 != DBL_CHAR && *arg2 != SEP_CHAR && *arg2 != DOL_CHAR)
		*arg2 = STD_CHAR;
	return (0);
}

int	ft_initial_mode_2(t_pars *pars, t_char_types *arg2)
{
	if (*arg2 == SPL_CHAR || *arg2 == DBL_CHAR || *arg2 == SEP_CHAR)
		pars->new_exp_decision.char_action = EXP_TAKE;
	return (0);
}

/*int	ft_exp_apply_decision(t_pars *pars)
{
	t_exp_read_modes	arg1;
	t_char_types		arg2;

	arg1 = pars->prev_exp_decision.exp_read_mode;
	arg2 = ft_char_type(pars->parser_text[0]);
	pars->prev_exp_decision = pars->new_exp_decision;
	//SUPPR
	pars->exp_mode = 0;
	if (pars->exp_mode)
		ft_initial_mode(&arg1, &arg2);
	pars->new_exp_decision = pars->exp_decision[arg1][arg2];
	//pars->new_exp_decision = pars->exp_decision[pars
	//	->prev_exp_decision.exp_read_mode]
	//[ft_char_type(pars->parser_text[0])];
	ft_debug_exp(pars);
	pars->ft_exp[pars->new_exp_decision.buffer_action](pars);
	return (pars->ft_exp[pars->new_exp_decision.char_action](pars));
}

int	ft_initial_mode(t_exp_read_modes *arg1, t_char_types *arg2)
{
	if (*arg2 == DBL_CHAR)
		*arg2 = STD_CHAR;
	(void)arg1;
	(void)arg2;
	return (0);
}*/

/*int	ft_exp_apply_decision(t_pars *pars)
{
	pars->prev_exp_decision = pars->new_exp_decision;
	pars->new_exp_decision = pars->exp_decision[pars
		->prev_exp_decision.exp_read_mode]
	[ft_char_type(pars->parser_text[0])];
	ft_debug_exp(pars);
	pars->ft_exp[pars->new_exp_decision.buffer_action](pars);
	return (pars->ft_exp[pars->new_exp_decision.char_action](pars));
}*/
