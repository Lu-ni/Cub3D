/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lucas.nicollier@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:12:07 by lnicolli          #+#    #+#             */
/*   Updated: 2024/07/22 22:12:09 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __APPLE__
#  define KEY_ESC 53
#  define MOUSE_WHEEL_UP 4
#  define MOUSE_WHEEL_DOWN 5
#  define MOUSE_WHEEL_BTN 3
#  define MOUSE_BTN 1
#  define MOUSE_BTN_2 3

#  define UP 126
#  define DOWN 125
#  define LEFT 123
#  define RIGHT 124

#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_F 3
#  define KEY_H 4
#  define KEY_G 5
#  define KEY_Z 6
#  define KEY_X 7
#  define KEY_C 8
#  define KEY_V 9
#  define KEY_B 11
#  define KEY_Q 12
#  define KEY_W 13
#  define KEY_E 14
#  define KEY_R 15
#  define KEY_Y 16
#  define KEY_T 17
#  define KEY_1 18
#  define KEY_2 19
#  define KEY_3 20
#  define KEY_4 21
#  define KEY_6 22
#  define KEY_5 23
#  define KEY_EQUAL 24
#  define KEY_9 25
#  define KEY_7 26
#  define KEY_MINUS 27
#  define KEY_8 28
#  define KEY_0 29
#  define KEY_RIGHT_BRACKET 30
#  define KEY_O 31
#  define KEY_U 32
#  define KEY_LEFT_BRACKET 33
#  define KEY_I 34
#  define KEY_P 35
#  define KEY_RETURN 36
#  define KEY_L 37
#  define KEY_J 38
#  define KEY_QUOTE 39
#  define KEY_K 40
#  define KEY_SEMICOLON 41
#  define KEY_BACKSLASH 42
#  define KEY_COMMA 43
#  define KEY_SLASH 44
#  define KEY_N 45
#  define KEY_M 46
#  define KEY_PERIOD 47
#  define KEY_TAB 48
#  define KEY_SPACE 49
#  define KEY_GRAVE 50
#  define KEY_DELETE 51
#  define KEY_ENTER 52
#  define KEY_COMMAND 55
#  define KEY_SHIFT 56
#  define KEY_CAPSLOCK 57
#  define KEY_OPTION 58
#  define KEY_CONTROL 59
#  define KEY_RIGHT_SHIFT 60
#  define KEY_RIGHT_OPTION 61
#  define KEY_RIGHT_CONTROL 62
#  define KEY_FUNCTION 63
#  define KEY_F17 64
#  define KEY_VOLUME_UP 72
#  define KEY_VOLUME_DOWN 73
#  define KEY_MUTE 74
#  define KEY_F18 79
#  define KEY_F19 80
#  define KEY_F20 90
#  define KEY_F5 96
#  define KEY_F6 97
#  define KEY_F7 98
#  define KEY_F3 99
#  define KEY_F8 100
#  define KEY_F9 101
#  define KEY_F11 103
#  define KEY_F13 105
#  define KEY_F16 106
#  define KEY_F14 107
#  define KEY_F10 109
#  define KEY_F12 111
#  define KEY_F15 113
#  define KEY_HELP 114
#  define KEY_HOME 115
#  define KEY_PAGE_UP 116
#  define KEY_FORWARD_DELETE 117
#  define KEY_F4 118
#  define KEY_END 119
#  define KEY_F2 120
#  define KEY_PAGE_DOWN 121
#  define KEY_F1 122
#  define KEY_LEFT_ARROW 123
#  define KEY_RIGHT_ARROW 124
#  define KEY_DOWN_ARROW 125
#  define KEY_UP_ARROW 126
# endif

# ifdef __linux__
#  define KEY_ESC 65307
#  define MOUSE_WHEEL_UP 4
#  define MOUSE_WHEEL_DOWN 5
#  define MOUSE_WHEEL_BTN 2
#  define MOUSE_BTN 1
#  define MOUSE_BTN_2 3

#  define UP 65362
#  define DOWN 65364
#  define LEFT 65361
#  define RIGHT 65363

#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_F 102
#  define KEY_H 43
#  define KEY_G 42
#  define KEY_Z 122
#  define KEY_X 53
#  define KEY_C 54
#  define KEY_V 55
#  define KEY_B 56
#  define KEY_Q 113
#  define KEY_W 119
#  define KEY_E 101
#  define KEY_R 114
#  define KEY_Y 29
#  define KEY_T 28
#  define KEY_1 49
#  define KEY_2 50
#  define KEY_3 12
#  define KEY_4 13
#  define KEY_6 15
#  define KEY_5 14
#  define KEY_EQUAL 21
#  define KEY_9 18
#  define KEY_7 16
#  define KEY_MINUS 20
#  define KEY_8 17
#  define KEY_0 19
#  define KEY_RIGHT_BRACKET 35
#  define KEY_O 32
#  define KEY_U 30
#  define KEY_LEFT_BRACKET 34
#  define KEY_I 31
#  define KEY_P 33
#  define KEY_RETURN 36
#  define KEY_L 46
#  define KEY_J 44
#  define KEY_QUOTE 48
#  define KEY_K 45
#  define KEY_SEMICOLON 47
#  define KEY_BACKSLASH 51
#  define KEY_COMMA 59
#  define KEY_SLASH 61
#  define KEY_N 57
#  define KEY_M 58
#  define KEY_PERIOD 60
#  define KEY_TAB 23
#  define KEY_SPACE 32
#  define KEY_GRAVE 49
#  define KEY_DELETE 22
#  define KEY_ENTER 36
#  define KEY_COMMAND 133
#  define KEY_SHIFT 50
#  define KEY_CAPSLOCK 66
#  define KEY_OPTION 64
#  define KEY_CONTROL 37
#  define KEY_RIGHT_SHIFT 62
#  define KEY_RIGHT_OPTION 108
#  define KEY_RIGHT_CONTROL 105
#  define KEY_FUNCTION 63
#  define KEY_F17 95
#  define KEY_VOLUME_UP 123
#  define KEY_VOLUME_DOWN 122
#  define KEY_MUTE 121
#  define KEY_F18 96
#  define KEY_F19 97
#  define KEY_F20 98
#  define KEY_F5 71
#  define KEY_F6 72
#  define KEY_F7 73
#  define KEY_F3 69
#  define KEY_F8 74
#  define KEY_F9 75
#  define KEY_F11 95
#  define KEY_F13 96
#  define KEY_F16 97
#  define KEY_F14 98
#  define KEY_F10 76
#  define KEY_F12 96
#  define KEY_F15 97
#  define KEY_HELP 127
#  define KEY_HOME 110
#  define KEY_PAGE_UP 112
#  define KEY_FORWARD_DELETE 119
#  define KEY_F4 70
#  define KEY_END 115
#  define KEY_F2 68
#  define KEY_PAGE_DOWN 117
#  define KEY_F1 67
#  define KEY_LEFT_ARROW 113
#  define KEY_RIGHT_ARROW 114
#  define KEY_DOWN_ARROW 116
#  define KEY_UP_ARROW 111

# endif
#endif
