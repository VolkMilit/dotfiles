#autoload -Uz promptinit
autoload -U colors && colors
#promptinit
PS1=" [%~] >>> %{$reset_color%}%"
#if [ "$TERM" = "LXTerminal" ]; then
#	cat .aa
#fi
#PS1="\
# (%~)																			\
#	   %{$fg[cyan]%}% .·´¯\`·.´¯\`·.¸¸.·´¯\`·.¸><(((º> %{$reset_color%}%"
#prompt /home/volk/.config/zsh/themes/fishy.zsh-theme
