#pragma once

#ifndef __KEY_H__
#define __KEY_H__

//Windows Defines
#ifdef WIN32
#ifdef _MSC_VER //less warnings from microsoft
#define stricmp _stricmp
#endif //_MSC_VER
#else //WIN32
#define stricmp	strcasecmp
#endif //WIN32

#define KEY_NONE 0
#ifdef WIN32
#define KEY_LBUTTON VK_LBUTTON
#define KEY_RBUTTON VK_RBUTTON
#define KEY_CANCEL VK_CANCEL
#define KEY_MBUTTON VK_MBUTTON
#if (_WIN32_WINNT >= 0x0500)
#define KEY_XBUTTON1 VK_XBUTTON1
#define KEY_XBUTTON2 VK_XBUTTON2
#else
#define KEY_XBUTTON1 KEY_NONE
#define KEY_XBUTTON2 KEY_NONE
#endif
#define KEY_BACK VK_BACK
#define KEY_TAB VK_TAB
#define KEY_CLEAR VK_CLEAR
#define KEY_RETURN VK_RETURN
#define KEY_SHIFT VK_SHIFT
#define KEY_CONTROL VK_CONTROL
#define KEY_MENU VK_MENU
#define KEY_PAUSE VK_PAUSE
#define KEY_CAPITAL VK_CAPITAL
#define KEY_KANA VK_KANA
#define KEY_HANGEUL VK_HANGEUL
#define KEY_HANGUL VK_HANGUL
#define KEY_JUNJA VK_JUNJA
#define KEY_FINAL VK_FINAL
#define KEY_HANJA VK_HANJA
#define KEY_KANJI VK_KANJI
#define KEY_ESCAPE VK_ESCAPE
#define KEY_CONVERT VK_CONVERT
#define KEY_NONCONVERT VK_NONCONVERT
#define KEY_ACCEPT VK_ACCEPT
#define KEY_MODECHANGE VK_MODECHANGE
#define KEY_SPACE VK_SPACE
#define KEY_PRIOR VK_PRIOR
#define KEY_NEXT VK_NEXT
#define KEY_END VK_END
#define KEY_HOME VK_HOME
#define KEY_LEFT VK_LEFT
#define KEY_UP VK_UP
#define KEY_RIGHT VK_RIGHT
#define KEY_DOWN VK_DOWN
#define KEY_SELECT VK_SELECT
#define KEY_PRINT VK_PRINT
#define KEY_EXEC VK_EXECUTE //KEY_EXECUTE is already defined in windows
#define KEY_SNAPSHOT VK_SNAPSHOT
#define KEY_INSERT VK_INSERT
#define KEY_DELETE VK_DELETE
#define KEY_HELP VK_HELP
#define KEY_0 '0'
#define KEY_1 '1'
#define KEY_2 '2'
#define KEY_3 '3'
#define KEY_4 '4'
#define KEY_5 '5'
#define KEY_6 '6'
#define KEY_7 '7'
#define KEY_8 '8'
#define KEY_9 '9'
#define KEY_A 'A'
#define KEY_B 'B'
#define KEY_C 'C'
#define KEY_D 'D'
#define KEY_E 'E'
#define KEY_F 'F'
#define KEY_G 'G'
#define KEY_H 'H'
#define KEY_I 'I'
#define KEY_J 'J'
#define KEY_K 'K'
#define KEY_L 'L'
#define KEY_M 'M'
#define KEY_N 'N'
#define KEY_O 'O'
#define KEY_P 'P'
#define KEY_Q 'Q'
#define KEY_R 'R'
#define KEY_S 'S'
#define KEY_T 'T'
#define KEY_U 'U'
#define KEY_V 'V'
#define KEY_W 'W'
#define KEY_X 'X'
#define KEY_Y 'Y'
#define KEY_Z 'Z'
#define KEY_LWIN VK_LWIN
#define KEY_RWIN VK_RWIN
#define KEY_APPS VK_APPS
#define KEY_SLEEP VK_SLEEP
#define KEY_NUMPAD0 VK_NUMPAD0
#define KEY_NUMPAD1 VK_NUMPAD1
#define KEY_NUMPAD2 VK_NUMPAD2
#define KEY_NUMPAD3 VK_NUMPAD3
#define KEY_NUMPAD4 VK_NUMPAD4
#define KEY_NUMPAD5 VK_NUMPAD5
#define KEY_NUMPAD6 VK_NUMPAD6
#define KEY_NUMPAD7 VK_NUMPAD7
#define KEY_NUMPAD8 VK_NUMPAD8
#define KEY_NUMPAD9 VK_NUMPAD9
#define KEY_MULTIPLY VK_MULTIPLY
#define KEY_ADD VK_ADD
#define KEY_SEPARATOR VK_SEPARATOR
#define KEY_SUBTRACT VK_SUBTRACT
#define KEY_DECIMAL VK_DECIMAL
#define KEY_DIVIDE VK_DIVIDE
#define KEY_F1 VK_F1
#define KEY_F2 VK_F2
#define KEY_F3 VK_F3
#define KEY_F4 VK_F4
#define KEY_F5 VK_F5
#define KEY_F6 VK_F6
#define KEY_F7 VK_F7
#define KEY_F8 VK_F8
#define KEY_F9 VK_F9
#define KEY_F10 VK_F10
#define KEY_F11 VK_F11
#define KEY_F12 VK_F12
#define KEY_F13 VK_F13
#define KEY_F14 VK_F14
#define KEY_F15 VK_F15
#define KEY_F16 VK_F16
#define KEY_F17 VK_F17
#define KEY_F18 VK_F18
#define KEY_F19 VK_F19
#define KEY_F20 VK_F20
#define KEY_F21 VK_F21
#define KEY_F22 VK_F22
#define KEY_F23 VK_F23
#define KEY_F24 VK_F24
#define KEY_NUMLOCK VK_NUMLOCK
#define KEY_SCROLL VK_SCROLL
#define KEY_LSHIFT VK_LSHIFT
#define KEY_RSHIFT VK_RSHIFT
#define KEY_LCONTROL VK_LCONTROL
#define KEY_RCONTROL VK_RCONTROL
#define KEY_LMENU VK_LMENU
#define KEY_RMENU VK_RMENU
#if (_WIN32_WINNT >= 0x0500)
#define KEY_BROWSER_BACK VK_BROWSER_BACK
#define KEY_BROWSER_FORWARD VK_BROWSER_FORWARD
#define KEY_BROWSER_REFRESH VK_BROWSER_REFRESH
#define KEY_BROWSER_STOP VK_BROWSER_STOP
#define KEY_BROWSER_SEARCH VK_BROWSER_SEARCH
#define KEY_BROWSER_FAVORITES VK_BROWSER_FAVORITES
#define KEY_BROWSER_HOME VK_BROWSER_HOME
#define KEY_VOLUME_MUTE VK_VOLUME_MUTE
#define KEY_VOLUME_DOWN VK_VOLUME_DOWN
#define KEY_VOLUME_UP VK_VOLUME_UP
#define KEY_MEDIA_NEXT_TRACK VK_MEDIA_NEXT_TRACK
#define KEY_MEDIA_PREV_TRACK VK_MEDIA_PREV_TRACK
#define KEY_MEDIA_STOP VK_MEDIA_STOP
#define KEY_MEDIA_PLAY_PAUSE VK_MEDIA_PLAY_PAUSE
#define KEY_LAUNCH_MAIL VK_LAUNCH_MAIL
#define KEY_LAUNCH_MEDIA_SELECT VK_LAUNCH_MEDIA_SELECT
#define KEY_LAUNCH_APP1 VK_LAUNCH_APP1
#define KEY_LAUNCH_APP2 VK_LAUNCH_APP2
#else
#define KEY_BROWSER_BACK KEY_NONE
#define KEY_BROWSER_FORWARD KEY_NONE
#define KEY_BROWSER_REFRESH KEY_NONE
#define KEY_BROWSER_STOP KEY_NONE
#define KEY_BROWSER_SEARCH KEY_NONE
#define KEY_BROWSER_FAVORITES KEY_NONE
#define KEY_BROWSER_HOME KEY_NONE
#define KEY_VOLUME_MUTE KEY_NONE
#define KEY_VOLUME_DOWN KEY_NONE
#define KEY_VOLUME_UP KEY_NONE
#define KEY_MEDIA_NEXT_TRACK KEY_NONE
#define KEY_MEDIA_PREV_TRACK KEY_NONE
#define KEY_MEDIA_STOP KEY_NONE
#define KEY_MEDIA_PLAY_PAUSE KEY_NONE
#define KEY_LAUNCH_MAIL KEY_NONE
#define KEY_LAUNCH_MEDIA_SELECT KEY_NONE
#define KEY_LAUNCH_APP1 KEY_NONE
#define KEY_LAUNCH_APP2 KEY_NONE
#endif
#define KEY_OEM_1 VK_OEM_1
#if (_WIN32_WINNT >= 0x0500)
#define KEY_OEM_PLUS VK_OEM_PLUS
#define KEY_OEM_COMMA VK_OEM_COMMA
#define KEY_OEM_MINUS VK_OEM_MINUS
#define KEY_OEM_PERIOD VK_OEM_PERIOD
#else
#define KEY_OEM_PLUS KEY_NONE
#define KEY_OEM_COMMA KEY_NONE
#define KEY_OEM_MINUS KEY_NONE
#define KEY_OEM_PERIOD KEY_NONE
#endif
#define KEY_OEM_2 VK_OEM_2
#define KEY_OEM_3 VK_OEM_3
#define KEY_OEM_4 VK_OEM_4
#define KEY_OEM_5 VK_OEM_5
#define KEY_OEM_6 VK_OEM_6
#define KEY_OEM_7 VK_OEM_7
#define KEY_OEM_8 VK_OEM_8
#if (_WIN32_WINNT >= 0x0500)
#define KEY_OEM_102 VK_OEM_102
#else
#define KEY_OEM_102 KEY_NONE
#endif
#define KEY_PROCESSKEY VK_PROCESSKEY
#if (_WIN32_WINNT >= 0x0500)
#define KEY_PACKET VK_PACKET
#else
#define KEY_PACKET KEY_NONE
#endif
#define KEY_ATTN VK_ATTN
#define KEY_CRSEL VK_CRSEL
#define KEY_EXSEL VK_EXSEL
#define KEY_EREOF VK_EREOF
#define KEY_PLAY VK_PLAY
#define KEY_ZOOM VK_ZOOM
#define KEY_NONAME VK_NONAME
#define KEY_PA1 VK_PA1
#define KEY_OEM_CLEAR VK_OEM_CLEAR
#else //WIN32
#define KEY_LBUTTON 0x8000 //LBUTTON
#define KEY_RBUTTON 0x8002 //RBUTTON
#define KEY_CANCEL KEY_NONE //CANCEL
#define KEY_MBUTTON 0x8001 //MBUTTON
#define KEY_XBUTTON1 KEY_NONE //XBUTTON1
#define KEY_XBUTTON2 KEY_NONE //XBUTTON2
#define KEY_BACK XK_BackSpace
#define KEY_TAB XK_Tab
#define KEY_CLEAR XK_Clear
#define KEY_RETURN XK_Return
#define KEY_SHIFT XK_Shift_L
#define KEY_CONTROL XK_Control_L
#define KEY_MENU KEY_NONE //MENU
#define KEY_PAUSE XK_Pause
#define KEY_CAPITAL XK_Caps_Lock
#define KEY_KANA KEY_NONE //KANA
#define KEY_HANGEUL KEY_NONE //HANGEUL
#define KEY_HANGUL KEY_NONE //HANGUL
#define KEY_JUNJA KEY_NONE //JUNJA
#define KEY_FINAL KEY_NONE //FINAL
#define KEY_HANJA KEY_NONE //HANJA
#define KEY_KANJI KEY_NONE //KANJI
#define KEY_ESCAPE KEY_NONE //ESCAPE
#define KEY_CONVERT KEY_NONE //CONVERT
#define KEY_NONCONVERT KEY_NONE //NONCONVERT
#define KEY_ACCEPT KEY_NONE //ACCEPT
#define KEY_MODECHANGE KEY_NONE //MODECHANGE
#define KEY_SPACE XK_space
#define KEY_PRIOR XK_Prior
#define KEY_NEXT XK_Next
#define KEY_END XK_End
#define KEY_HOME XK_Home
#define KEY_LEFT XK_Left
#define KEY_UP XK_Up
#define KEY_RIGHT XK_Right
#define KEY_DOWN XK_Down
#define KEY_SELECT KEY_NONE //SELECT
#define KEY_PRINT XK_Print
#define KEY_EXEC XK_Execute //KEY_EXECUTE is already defined in windows
#define KEY_SNAPSHOT KEY_NONE //SNAPSHOT
#define KEY_INSERT XK_Insert
#define KEY_DELETE XK_Delete
#define KEY_HELP XK_Help
#define KEY_0 '0'
#define KEY_1 '1'
#define KEY_2 '2'
#define KEY_3 '3'
#define KEY_4 '4'
#define KEY_5 '5'
#define KEY_6 '6'
#define KEY_7 '7'
#define KEY_8 '8'
#define KEY_9 '9'
#define KEY_A 'A'
#define KEY_B 'B'
#define KEY_C 'C'
#define KEY_D 'D'
#define KEY_E 'E'
#define KEY_F 'F'
#define KEY_G 'G'
#define KEY_H 'H'
#define KEY_I 'I'
#define KEY_J 'J'
#define KEY_K 'K'
#define KEY_L 'L'
#define KEY_M 'M'
#define KEY_N 'N'
#define KEY_O 'O'
#define KEY_P 'P'
#define KEY_Q 'Q'
#define KEY_R 'R'
#define KEY_S 'S'
#define KEY_T 'T'
#define KEY_U 'U'
#define KEY_V 'V'
#define KEY_W 'W'
#define KEY_X 'X'
#define KEY_Y 'Y'
#define KEY_Z 'Z'
#define KEY_LWIN KEY_NONE //LWIN
#define KEY_RWIN KEY_NONE //RWIN
#define KEY_APPS KEY_NONE //APPS
#define KEY_SLEEP KEY_NONE //SLEEP
#define KEY_NUMPAD0 XK_KP_0
#define KEY_NUMPAD1 XK_KP_1
#define KEY_NUMPAD2 XK_KP_2
#define KEY_NUMPAD3 XK_KP_3
#define KEY_NUMPAD4 XK_KP_4
#define KEY_NUMPAD5 XK_KP_5
#define KEY_NUMPAD6 XK_KP_6
#define KEY_NUMPAD7 XK_KP_7
#define KEY_NUMPAD8 XK_KP_8
#define KEY_NUMPAD9 XK_KP_9
#define KEY_MULTIPLY XK_KP_Multiply
#define KEY_ADD XK_KP_Add
#define KEY_SEPARATOR XK_KP_Separator
#define KEY_SUBTRACT XK_KP_Subtract
#define KEY_DECIMAL XK_KP_Decimal
#define KEY_DIVIDE XK_KP_Divide
#define KEY_F1 XK_F1
#define KEY_F2 XK_F2
#define KEY_F3 XK_F3
#define KEY_F4 XK_F4
#define KEY_F5 XK_F5
#define KEY_F6 XK_F6
#define KEY_F7 XK_F7
#define KEY_F8 XK_F8
#define KEY_F9 XK_F9
#define KEY_F10 XK_F10
#define KEY_F11 XK_F11
#define KEY_F12 XK_F12
#define KEY_F13 XK_F13
#define KEY_F14 XK_F14
#define KEY_F15 XK_F15
#define KEY_F16 XK_F16
#define KEY_F17 XK_F17
#define KEY_F18 XK_F18
#define KEY_F19 XK_F19
#define KEY_F20 XK_F20
#define KEY_F21 XK_F21
#define KEY_F22 XK_F22
#define KEY_F23 XK_F23
#define KEY_F24 XK_F24
#define KEY_NUMLOCK XK_Num_Lock
#define KEY_SCROLL XK_Scroll_Lock
#define KEY_LSHIFT XK_Shift_L
#define KEY_RSHIFT XK_Shift_R
#define KEY_LCONTROL XK_Control_L
#define KEY_RCONTROL XK_Control_R
#define KEY_LMENU KEY_NONE //LMENU
#define KEY_RMENU KEY_NONE //RMENU
#define KEY_BROWSER_BACK KEY_NONE //BROWSER_BACK
#define KEY_BROWSER_FORWARD KEY_NONE //BROWSER_FORWARD
#define KEY_BROWSER_REFRESH KEY_NONE //BROWSER_REFRESH
#define KEY_BROWSER_STOP KEY_NONE //BROWSER_STOP
#define KEY_BROWSER_SEARCH KEY_NONE //BROWSER_SEARCH
#define KEY_BROWSER_FAVORITES KEY_NONE //BROWSER_FAVORITES
#define KEY_BROWSER_HOME KEY_NONE //BROWSER_HOME
#define KEY_VOLUME_MUTE KEY_NONE //VOLUME_MUTE
#define KEY_VOLUME_DOWN KEY_NONE //VOLUME_DOWN
#define KEY_VOLUME_UP KEY_NONE //VOLUME_UP
#define KEY_MEDIA_NEXT_TRACK KEY_NONE //MEDIA_NEXT_TRACK
#define KEY_MEDIA_PREV_TRACK KEY_NONE //MEDIA_PREV_TRACK
#define KEY_MEDIA_STOP KEY_NONE //MEDIA_STOP
#define KEY_MEDIA_PLAY_PAUSE KEY_NONE //MEDIA_PLAY_PAUSE
#define KEY_LAUNCH_MAIL KEY_NONE //LAUNCH_MAIL
#define KEY_LAUNCH_MEDIA_SELECT KEY_NONE //LAUNCH_MEDIA_SELECT
#define KEY_LAUNCH_APP1 KEY_NONE //LAUNCH_APP1
#define KEY_LAUNCH_APP2 KEY_NONE //LAUNCH_APP2
#define KEY_OEM_1 KEY_NONE //OEM_1
#define KEY_OEM_PLUS KEY_NONE //OEM_PLUS
#define KEY_OEM_COMMA KEY_NONE //OEM_COMMA
#define KEY_OEM_MINUS KEY_NONE //OEM_MINUS
#define KEY_OEM_PERIOD KEY_NONE //OEM_PERIOD
#define KEY_OEM_2 KEY_NONE //OEM_2
#define KEY_OEM_3 KEY_NONE //OEM_3
#define KEY_OEM_4 KEY_NONE //OEM_4
#define KEY_OEM_5 KEY_NONE //OEM_5
#define KEY_OEM_6 KEY_NONE //OEM_6
#define KEY_OEM_7 KEY_NONE //OEM_7
#define KEY_OEM_8 KEY_NONE //OEM_8
#define KEY_OEM_102 KEY_NONE //OEM_102
#define KEY_PROCESSKEY KEY_NONE //PROCESSKEY
#define KEY_PACKET KEY_NONE //PACKET
#define KEY_ATTN KEY_NONE //ATTN
#define KEY_CRSEL KEY_NONE //CRSEL
#define KEY_EXSEL KEY_NONE //EXSEL
#define KEY_EREOF KEY_NONE //EREOF
#define KEY_PLAY KEY_NONE //PLAY
#define KEY_ZOOM KEY_NONE //ZOOM
#define KEY_NONAME KEY_NONE //NONAME
#define KEY_PA1 KEY_NONE //PA1
#define KEY_OEM_CLEAR KEY_NONE //OEM_CLEAR
#endif

//Functions
unsigned int getKeyNumber(char *key);
const TCHAR *getKeyString(unsigned int key);

#endif //__KEY_H__
